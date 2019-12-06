<template>

</template>

<script>
import { getFirmwareNormalinfo, updateFirmware } from '../../api'
import MyPopover from '../../components/MyPopover/MyPopover'
import { transitionWifiFirmwareVersion } from "../../util/tool";

export default {
  name: "Firmware",
  mounted () {
    // const data = []
    // for (let i=0;i<11;i++){
    //   data.push({id:i,type:'force',time:'',wifiFirmwareVersion:'0.19.01.1',number:'000BBE735002700'+i,ipsString:'192.168.11.112',state:false})
    // }
    // this.firmwareInfoData = data
    // this.firmwareInfo = this.firmwareInfoData.slice(0, this.pageNum)
    getFirmwareNormalinfo()
      .then(res => {
        //给每一个number加上一个ID
        for (let i = 0; i < res.data.length; i++) {
          res.data[i].id = i + 1
          res.data[i].type = 'force'
          res.data[i].time = ''
          res.data[i].state = false
          res.data[i].wifiFirmwareVersion = transitionWifiFirmwareVersion(res.data[i].wifiFirmwareVersion)
        }
        this.firmwareInfoData = res.data
        this.firmwareInfo = this.firmwareInfoData.slice(0, this.pageNum)
      })
      .catch(res => {
        console.log(res);
      })
  },
  data () {
    return {
      search: '',//搜索
      firmwareData: '',//固件的base64数据
      firmwareInfo: [],//固件的信息
      //批量选择
      multipleSelection: [],//保存的批量数据
      isIndeterminate: false,
      checkAll: false,
      allType: 'force',//批量升级模式
      allTime: '',//批量定时升级时间
      lastTime1: 0,
      lastTime2: 0,
      /*分页数据*/
      pageNum: 10,
      currentPage: 1,
      firmwareInfoData: [],//分页总信息
      isCustom: false,//是否显示自定义列
      customList: [
        { name: '打印机编号', state: true, value: 'number' },
        { name: '版本号', state: true, value: 'wifiFirmwareVersion' },
        { name: 'IP', state: true, value: 'ip' },
        { name: '操作', state: true, value: 'handle' },
        { name: '升级模式', state: true, value: 'pattern' },
      ],
      custom: {
        number: true,
        ip: true,
        handle: true,
        pattern: true,
        wifiFirmwareVersion: true,
      }
    }
  },
  methods: {
    request (e, row, type) {
      const files = e.target.files[0];
      const reg = /(.ota|.bin)$/
      if (!reg.test(files.name)) {
        this.$message({
          type: 'error',
          message: '文件类型有误',
          duration: 3000,
          showClose: true
        })
        return
      }
      if (type != 'all') {
        this.firmwareInfo[row.id - 1].firmwareName = files.name
      }

      let reader = new FileReader()
      const that = this;
      reader.onload = function (e) {
        let result = e.target.result.split(',')
        if (type != 'all') {
          //单个升级
          that.handleFinder(row, result[1])
        } else {
          that.batchUpgradeFirmware(result[1])
        }
      }
      reader.readAsDataURL(files);
    },

    //单个升级
    handleFinder (row, result) {

      let data = {
        number: row.number,
        data: result,
        type: row.type
      }

      if (row.type === 'wecut') {
        data.timeStr = row.time
        updateFirmware(data)
          .then(res => {
            this.$message({
              type: 'success',
              message: '定时升级固件任务建立成功',
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
      } else {
        updateFirmware(data)
          .then(res => {
            this.$message({
              type: 'success',
              message: '固件正在升级',
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
      }

    },

    //获取多选的内容
    oneSelect (index, state) {
      if (state) {
        this.firmwareInfo[index].state = true
        this.multipleSelection.push(this.firmwareInfo[index])
        this.checkAll = this.multipleSelection.length === this.firmwareInfo.length;
        this.isIndeterminate = this.multipleSelection.length < this.firmwareInfo.length && this.multipleSelection.length != 0;
      } else {
        const number = this.firmwareInfo[index].number
        for (let i = 0; i < this.multipleSelection.length; i++) {
          if (number === this.multipleSelection[i].number) {
            this.multipleSelection.splice(i, 1)
          }
        }
        this.isIndeterminate = this.multipleSelection.length < this.firmwareInfo.length && this.multipleSelection.length != 0;
        this.checkAll = this.multipleSelection.length === 0;
      }
    },

    handleCheckAllChange (val) {
      if (val) {
        for (let i = 0; i < this.firmwareInfo.length; i++) {
          this.firmwareInfo[i].state = true
        }
        this.multipleSelection = []
        this.multipleSelection = [...this.firmwareInfo]
        this.isIndeterminate = false;
      } else {
        for (let i = 0; i < this.firmwareInfo.length; i++) {
          this.firmwareInfo[i].state = false
        }
        this.multipleSelection = []
        this.isIndeterminate = false;
      }

    },


    //批量升级
    batchUpgradeFirmware (result) {
      const firmwareList = this.multipleSelection
      if (firmwareList.length > 0) {
        if (this.allType === 'wecut') {//判断是不是定时模式
          for (let i = 0; i < firmwareList.length; i++) {
            let data = {
              number: firmwareList[i].number,
              data: result,
              type: this.allType,
              timeStr: this.allTime,//由于是定时模式就添加allTime字段
            }
            updateFirmware(data)//发送升级固件请求
              .then(res => {
                this.$message({
                  type: 'success',
                  message: '批量定时升级固件任务建立成功',
                  duration: 3000,
                  showClose: true
                })
              })
              .catch(res => {
                this.$message({
                  type: 'error',
                  message: data.number + res.data,
                  duration: 3000,
                  showClose: true
                })
              })
          }
        } else {
          for (let i = 0; i < firmwareList.length; i++) {
            let data = {//如果不是定时模式就不用增加timeStr自动
              number: firmwareList[i].number,
              data: result,
              type: this.allType,
            }
            updateFirmware(data)//发送升级固件请求
              .then(res => {
                this.$message({
                  type: 'success',
                  message: '批量升级开始',
                  duration: 3000,
                  showClose: true
                })
              })
              .catch(res => {
                this.$message({
                  type: 'error',
                  message: data.number + res.data,
                  duration: 3000,
                  showClose: true
                })
              })
          }
        }
      } else {
        this.$message({
          type: 'error',
          message: '请选择要升级的打印机',
          duration: 3000,
          showClose: true
        })
      }


    },

    setTime (index, row) {
      if (row.type !== 'wecut') {
        this.firmwareInfo[index].time = ''
      }

    },

    timeOut (lastTimeName) {
      const nowTime = Date.now()
      if (nowTime - this.lastTime1 < 2000) {
        console.log(1);
        this[lastTimeName] = nowTime
        return false
      } else {
        this[lastTimeName] = nowTime
        return true
      }
    },

    //分页
    handleChange (val) {
      this.firmwareInfo = this.firmwareInfoData.slice(0, val)
    },
    handleCurrentChange (val) {
      this.multipleSelection = []
      this.checkAll = false
      for (let i = 0; i < this.firmwareInfo.length; i++) {
        this.firmwareInfo[i].state = false
      }
      let last = this.pageNum * val;
      let first = last - this.pageNum;
      this.firmwareInfo = []
      this.firmwareInfo = this.firmwareInfoData.slice(first, last)
    },

    defaultFun (data) {
      this.custom = {}
      for (let item of data) {
        this.custom[item.value] = item.state
      }
    },
    confirmFun (data) {
      this.custom = {}
      for (let item of data) {
        this.custom[item.value] = item.state
      }
      this.customList = data
    }
  },

  components: { MyPopover }
}
</script>

<style scoped>
.right {
  display: flex;
  justify-content: center;
  justify-items: center;
  width: 100%;
}

.box {
  box-sizing: content-box;
  width: 1200px;
  height: 700px;
}

.title {
  box-sizing: content-box;
  display: flex;
  justify-content: space-between;
  padding-bottom: 10px;
  width: 100%;
  height: 40px;
  line-height: 40px;
  font-size: 24px;
  border-bottom: 1px solid rgba(231, 231, 231, 1);
}

.btn {
  display: block;
  margin: 0;
  height: 30px;
  line-height: 30px;
  background: rgba(64, 158, 255, 1);
  border-radius: 4px;
  white-space: nowrap;
  text-align: center;
  box-sizing: border-box;
  outline: 0;
  transition: 0.1s;
  font-weight: 500;
  -moz-user-select: none;
  color: #fff;
  border-color: #409eff;
  font-size: 14px;
  cursor: pointer;
}

.one-btn {
  width: 60px;
}

.all-btn {
  margin-left: 10px;
  margin-right: 22px;
  width: 80px;
}

.btn:hover {
  background: #66b1ff;
  border-color: #66b1ff;
  color: #fff;
}

.pagination {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-top: 10px;
}

.question {
  display: inline-block;
  margin-left: 10px;
  width: 12px;
  height: 12px;
  background: url("../../assets/问号1.png") no-repeat;
  background-size: 100% 100%;
}

.on-question {
  display: inline-block;
  margin-left: 10px;
  width: 12px;
  height: 12px;
  background: url("../../assets/问号2.png") no-repeat;
  background-size: 100% 100%;
}

@media (max-width: 1200px) {
  .box {
    width: 90%;
  }
}
</style>
