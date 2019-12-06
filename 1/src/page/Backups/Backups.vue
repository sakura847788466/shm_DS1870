<template>

</template>

<script>
import {
  backup,
  delBackData,
  exportData,
  getFilelevel,
  importData,
  recovery
} from '../../api'
import Firmware from "../Firmware/Firmware";
import { getConfig, setConfig } from "../../api";

export default {
  name: "Backups",
  mounted () {
    this.getBackupsData()
    //导出数据的表名
    // getCollections()
    //   .then(res => {
    //     this.exportCollections = res.data
    //   })
    //   .catch(res => {
    //     console.log(res);
    //   })
    // getCollecjson()
    //   .then(res => {
    //     this.importCollections = res.data
    //   })
    //   .catch(res => {
    //     console.log(res);
    //   })
    this.getLogSetting()
  },
  data () {
    return {
      value: '',
      activeName: 'e',//默认显示数据导出
      activeDate: 'month',
      checkList: [],//导出多选框数组
      importList: [],//导入的数组
      firmwareName: '',//导入的文件名
      // exportCollections: [],//导出数据表目录c
      // importCollections: [],//导入数据表目录
      Data: [],//总打印记录
      backupsData: [],//分页展示数据
      currentPage: 1,
      pageNum: 10,
      loading: false,//是否显示按钮的加载
      timer: { month: '1', day: '1', twoDay: '1', text: '' },//数据定时备份时间
      configData: '',//配置的信息数据
      stepStatus: { active: 1, status: '', title: '步骤一', titler: '步骤二', titles: '步骤三' }

    }
  },
  methods: {
    //获取备份数据
    getBackupsData () {
      getFilelevel()
        .then(res => {
          this.Data = []
          this.backupsData = []
          for (let i = 0; i < res.data.length; i++) {
            this.Data.push({ id: i + 1, number: res.data[i] })
          }
          this.backupsData = this.Data.slice(0, this.pageNum)
        })
        .catch(res => {
          console.log(res);
        })
    },
    changeData (val) {
      if (val == 'day') {
        const time = this.configData.timingbackup.split(' ')  //设置日 0 0 0 1/3 * *    //设置月日 0 0 0 3 1/1 *
        //this.ci=onfigData又可能是设置日时间也有可能是设置日月时间
        console.log(time)
        if (time[4] == "*") { //设置日时间
          let day = time[3].split('/')
          this.timer.day = day[1]
          this.timer.twoDay = day[1]
          this.timer.text = `按日期，每隔${day[1]}日`

        } else {
          let day = time[3]
          this.timer.day = day
          this.timer.twoDay = day
          this.timer.text = `按日期,每隔${day}日`
        }

      } else if (val == "month") {
        const time = this.configData.timingbackup.split(" ")
        if (time[4] == "*") {
          let day = time[3].split('/')
          this.timer.day = day[1]
          this.timer.twoDay = day[1]
          let month = time[3].split('/')
          this.timer.month = month[0]
          this.timer.text = `按月份和日期，每隔${month[0]}个月的${day[1]}日`
        } else {
          let day = time[3]  //0 0 0 3 1/1 *
          console.log(day)
          this.timer.day = day
          this.timer.twoDay = day
          let month = time[4].split('/')
          console.log(month)
          this.timer.month = month[1]
          this.timer.text = `按月份和日期，每隔${month[1]}个月的${day}日`
        }
      }

    },
    //数据库还原
    handleFinder (index, row) {
      this.$confirm('此操作将还原当前数据, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning',
        closeOnClickModal: false
      }).then(() => {
        const recoveryname = this.backupsData[index].number
        const loading = this.$loading({
          lock: true,
          text: '数据还原中...',
          spinner: 'el-icon-loading',
          background: 'rgba(0, 0, 0, 0.7)'
        });
        recovery(recoveryname)
          .then(res => {
            loading.close()
            this.$message({
              type: 'success',
              message: '还原备份数据成功',
              duration: 3000,
              showClose: true,
            })
            setTimeout(() => {
              window.location.reload()
            }, 3000)
          })
          .catch(res => {
            setTimeout(() => {
              loading.close()
              this.$message({
                type: 'error',
                message: '还原备份数据失败',
                duration: 3000,
                showClose: true
              })
            }, 3000)

          })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消还原备份数据'
        });
      });

    },

    startBackups () {
      backup()
        .then(res => {
          this.$message({
            type: 'success',
            message: '备份数据成功',
            duration: 3000,
            showClose: true
          })
          this.currentPage = 1
          getFilelevel()
            .then(res => {
              this.Data = []
              this.backupsData = []
              for (let i = 0; i < res.data.length; i++) {
                this.Data.push({ id: i + 1, number: res.data[i] })
              }
              // console.log(this.Data.length / this.pageNum);
              this.backupsData = this.Data.slice(0, this.pageNum)
            })
        })
        .catch(res => {
          this.$message({
            type: 'error',
            message: '备份数据失败',
            duration: 3000,
            showClose: true
          })
        })
    },
    //分页
    handleChange (val) {
      this.backupsData = this.Data.slice(0, val)
    },
    handleCurrentChange (val) {
      let last = this.pageNum * val;
      let first = last - this.pageNum;
      this.backupsData = []
      this.backupsData = this.Data.slice(first, last)
    },

    //初始化数据定时备份
    getLogSetting () {
      getConfig()
        .then(res => {
          const time = res.data.timingbackup.split(' ')
          this.configData = res.data
          if (time[4] == '*') {//设置日期   设置天数的  time[4]才等于*
            this.activeDate = 'day'
            let twoDay = time[3].split('/')
            this.timer.twoDay = twoDay[1]
            this.timer.text = `按日期，每隔${twoDay[1]}日`
          } else {
            this.timer.day = time[3]
            let month = time[4].split('/')
            this.timer.month = month[1]
            this.timer.text = `按月份和日期，每隔${month[1]}个月的${time[3]}日`
          }
        })
        .catch(res => {

        })
    },

    //设置定时备份数据
    updateSetting () {
      let text = ''
      if (this.activeDate == 'month') {
        this.configData.timingbackup = `0 0 0 ${this.timer.day} 1/${this.timer.month} *`
        text = `是否设置每隔${this.timer.month}个月的${this.timer.day}号定时备份数据`
        //0 0 0 1 1/2 *
      } else {
        this.configData.timingbackup = `0 0 0 1/${this.timer.twoDay} * *`
        text = `是否设置每个月的${this.timer.twoDay}号定时备份数据`
        //0 0 0 1/5 * *
      }
      this.$confirm(text, '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning',
        closeOnClickModal: false
      }).then(() => {
        const loading = this.$loading({
          lock: true,
          text: 'Loading',
          spinner: 'el-icon-loading',
          background: 'rgba(0, 0, 0, 0.7)'
        });
        setConfig(this.configData).then(res => {
          this.$message({
            type: 'success',
            message: res.data,
            duration: 3000,
            showClose: true
          })
          loading.close()
          this.getLogSetting()
        }).catch(res => {
          this.$message({
            type: 'error',
            message: '修改失败',
            duration: 3000,
            showClose: true
          })
          loading.close()
        })
      })
    },

    //数据导出
    derive () {
      if (this.checkList.length > 0) {
        this.$prompt('请输入导出文件的保存名称', '提示', {
          confirmButtonText: '确定',
          cancelButtonText: '取消',
          closeOnClickModal: false
        })
          .then(({ value }) => {
            const collection = this.checkList.toString()
            const url = exportData({ collection, saveName: value })
            window.location.href = url
            this.stepStatus.active = 3
            this.stepStatus.status = 'success'
          })
      } else {
        this.$message({
          type: 'error',
          message: '请选择导出的文件',
          duration: 1500,
          showClose: true
        });
      }

    },


    //数据导入
    request (e) {
      let files = e.target.files[0];
      const reg = /\.zip/
      if (!reg.test(files.name)) {
        this.$message({
          type: 'error',
          message: '文件类型有误',
          duration: 3000,
          showClose: true
        })
        return
      }
      this.firmwareName = files.name
      this.stepStatus.active = 2
      this.stepStatus.status = 'success'
      this.stepStatus.title = '已完成'
      this.stepStatus.titler = '进行中'
    },

    mySubmit () {
      if (this.firmwareName == '') {
        this.$message({
          type: 'error',
          message: '请上传导入文件',
          duration: 3000,
          showClose: true,
        })
        return
      }
      if (this.importList < 1) {
        this.$message({
          type: 'error',
          message: '请选择导入文件选项',
          duration: 3000,
          showClose: true
        })
        return
      }
      const name = this.importList.toString()
      const formData = new FormData()
      const file = document.getElementById('firmwareName').files[0]
      formData.append('file', file)

      this.$confirm('此操作将覆盖旧数据, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning',
        closeOnClickModal: false

      }).then(() => {
        importData(name, formData)
          .then(res => {
            this.$message({
              type: 'success',
              message: res.data,
              duration: 3000,
              showClose: true
            })
          })
          .catch(res => {
            this.$message({
              type: 'error',
              message: res.data,
              duration: 3000,
              showClose: true
            })
          })
      })

    },
    //删除备份数据
    handleDel (row) {
      this.$confirm('此操作将删除当前数据, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        const deldataname = row.number
        const loading = this.$loading({
          lock: true,
          text: '数据删除中...',
          spinner: 'el-icon-loading',
          background: 'rgba(0, 0, 0, 0.7)'
        });
        delBackData(deldataname)
          .then(res => {
            loading.close()
            this.getBackupsData()
            this.$message({
              type: 'success',
              message: '删除备份数据成功',
              duration: 3000,
              showClose: true,
            })
          })
          .catch(res => {
            setTimeout(() => {
              loading.close()
              this.$message({
                type: 'error',
                message: '删除备份数据失败',
                duration: 3000,
                showClose: true
              })
            }, 3000)

          })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除备份数据'
        });
      });
    }
  },
  components: { Firmware }
}
</script>

<style scoped>
.right {
  display: flex;
  justify-content: center;
  justify-items: center;
  width: 100%;
  /*min-height: 800px;*/
}

.box {
  box-sizing: content-box;
  width: 1000px;
  height: 750px;
}

.title {
  padding-bottom: 20px;
  margin-bottom: 10px;
  font-size: 24px;
  border-bottom: 1px solid #e7e7e7;
}

.nav {
  display: flex;
  padding-bottom: 10px;
}

.body {
  height: 350px;
  border-top: 1px solid #e7e7e7;
}
/*Ada */
.body_ada {
  display: flex;
  flex-direction: column;
  justify-content: space-between;
  align-items: center;
  height: 350px;
}
.top_ada {
  width: 100%;
  flex: 1;
}
.bottom_ada {
  flex: 5;
  width: 100%;
  display: flex;
  justify-content: space-between;
  align-items: center;
}
.bottom_ada .left_ada {
  flex: 1;
  height: 272px;
}
.bottom_ada .left_ada .btnR_ada {
  position: absolute;
  top: 50%;
  left: 68%;
  transform: translate(-50%, -50%);
}
.bottom_ada .content_ada {
  flex: 2;
  height: 272px;
}
.bottom_ada .right_ada {
  flex: 1;
  height: 272px;
  position: relative;
}
.bottom_ada .right_ada .btnC_ada {
  position: absolute;
  top: 50%;
  left: 34%;
  transform: translate(-50%, -50%);
}
.content_ada {
  display: flex;
  align-items: center;
  flex-direction: column;
}
/* ada */
.footer {
  display: flex;
  justify-content: flex-end;
  padding-top: 20px;
  height: 60px;
  border-top: 1px solid #e7e7e7;
}

.btn {
  display: inline-block;
  margin: 0;
  padding: 12px 20px;
  width: 100px;
  line-height: 1;
  white-space: nowrap;
  -webkit-appearance: none;
  text-align: center;
  -webkit-box-sizing: border-box;
  box-sizing: border-box;
  outline: 0;
  -webkit-transition: 0.1s;
  transition: 0.1s;
  font-weight: 500;
  -moz-user-select: none;
  color: #fff;
  background-color: #f56c6c;
  border-color: #f56c6c;
  font-size: 14px;
  border-radius: 4px;
  cursor: pointer;
}

.my-dialog-body {
  width: 540px;
  height: 150px;
  color: #000;
  border: 1px solid rgba(220, 223, 230, 1);
  border-radius: 4px;
}

.my-dialog-body-title {
  margin: 0 15px;
  height: 45px;
  line-height: 45px;
  border-bottom: 1px solid #e4e7ed;
}

.my-dialog-body-content {
  display: flex;
  align-items: center;
  margin: 20px 15px;
}

.pagination {
  display: flex;
  justify-content: center;
  align-items: center;
  margin-top: 24px;
}

@media (max-width: 1200px) {
  .box {
    width: 90%;
  }
}
</style>
