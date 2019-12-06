<template>
  <div class="right">
    <div class="box">
      <div class="title">
        <div class="title_nav">
          热部署
        </div>
      </div>

      <div class="body">
        <div style="height: 290px;border-bottom: 1px solid #e7e7e7">
          <div style="display: flex;align-items: center;margin-bottom:18px">
            <p style="margin-right: 24px">当前版本号：<span style="color: #666;font-size: 14px">{{version||'...'}}</span></p>
            <el-button type="primary" size="mini" @click.prevent="getMyVersion()" :loading="loading">刷新版本</el-button>
          </div>
          <div style="display: flex;justify-content: space-between;align-items: center">
            <p style="font-size: 18px;">请选择导入文件：<span style="color: red;font-size: 14px">{{hotDeployName}}</span>
            </p>
            <input id="hotDeployData" type="file" style="display: none;" @change="request($event)" accept=".jar"/>
            <label for="hotDeployData" class="btn" title="请导入.zip文件">
              文件导入
            </label>
          </div>
        </div>
        <div style="display: flex;justify-content: flex-end;margin-top: 20px">
          <el-button type="primary" @click.prevent="mySubmit()">立即部署</el-button>
        </div>
      </div>

    </div>
  </div>
</template>

<script>
  import {deploy, getVersion} from '../../api'

  export default {
    name: "HotDeploy",
    mounted() {
      getVersion()
        .then(res => {
          this.version = res.data
        })
        .catch(res => {
          console.log(res);
        })
    },
    data() {
      return {
        hotDeployName: '',//导入文件名
        version: '',//版本名称
        loading: false,//点击刷新版本按钮的
      }
    },
    methods: {

      getMyVersion() {
        this.loading = true
        const date = Date.now() + 3000
        getVersion()
          .then(res => {
            if (!(Date.now() > date)) {
              setTimeout(() => {
                this.loading = false
                this.version = res.data
                this.$message({
                  type: 'success',
                  message: '获取版本号成功',
                  duration: 3000,
                  showClose: true
                })
              }, 1500)
            } else {
              this.loading = false
              this.version = res.data
              this.$message({
                type: 'success',
                message: '获取版本号成功',
                duration: 3000,
                showClose: true
              })
            }

          })
          .catch(res => {
            this.loading = false
            this.$message({
              type: 'error',
              message: '获取版本号失败',
              duration: 3000,
              showClose: true
            })
          })
      },

      //数据导入
      request(e) {
        let files = e.target.files[0];
        const reg = /\.jar$/
        if (!reg.test(files.name)) {
          this.$message({
            type: 'error',
            message: '文件类型有误',
            duration: 3000,
            showClose: true
          })
          return
        }
        this.hotDeployName = files.name
      },

      mySubmit() {

        if (this.hotDeployName == '') {
          this.$message({
            type: 'error',
            message: '请上传导入文件',
            duration: 3000,
            showClose: true
          })
          return
        }

        const formData = new FormData()
        const file = document.getElementById('hotDeployData').files[0]
        formData.append('file', file)

        this.$confirm('此操作将执行热部署, 是否继续?', '提示', {
          confirmButtonText: '确定',
          cancelButtonText: '取消',
          type: 'warning'
        })
          .then(() => {
            const loading = this.$loading({
              lock: true,
              text: '正在部署中...',
              spinner: 'el-icon-loading',
              background: 'rgba(0, 0, 0, 0.7)'
            });
            deploy(formData)
              .then(res => {
                setTimeout(() => {
                  this.myGetVersion(loading)
                }, 3000)

              })
              .catch(res => {
                loading.close();
                this.$message({
                  type: 'error',
                  message: res.data,
                  duration: 3000,
                  showClose: true
                })
              })
          })

      },

      myGetVersion(loading) {
        getVersion()
          .then(res => {
            loading.close();
            this.version = res.data
            this.$message({
              type: 'success',
              message: '部署成功',
              duration: 3000,
              showClose: true
            })
          })
          .catch(res => {
            this.myGetVersion(loading)
          })
      }

    },
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
    width: 1000px;
    height: 750px;
  }

  .title {
    box-sizing: border-box;
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding-bottom: 20px;
    width: 100%;
    font-size: 24px;
    border-bottom: 1px solid #ddd;
  }

  .btn {
    display: inline-block;
    margin: 0;
    width:98px;
    height:40px;
    line-height: 40px;
    white-space: nowrap;
    -webkit-appearance: none;
    text-align: center;
    -webkit-box-sizing: border-box;
    box-sizing: border-box;
    outline: 0;
    -webkit-transition: .1s;
    transition: .1s;
    font-weight: 400;
    -moz-user-select: none;
    color: #FFF;
    background-color: #F56C6C;
    border-color: #F56C6C;
    font-size: 14px;
    border-radius: 4px;
    cursor: pointer;
  }

  .body {
    margin-top: 18px;
    font-size: 18px;
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
