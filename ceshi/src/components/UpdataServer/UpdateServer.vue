<template>
  <el-dialog title="请求服务设置" :close-on-click-modal="false" :close-on-press-escape="false"
             :visible.sync="dialogFormVisible" :show-close="false" width="500px" @keyup.enter.native="inputValidator(active)">
    <el-tabs v-model="type" type="card" >
      <el-tab-pane label="IP设置" name="ip">
        <div class="ip-alert">
          <span class="ip-alert-tip">IP:</span>
          <el-input v-model="initIp"/>
        </div>
        <div class="ip-alert">
          <span class="ip-alert-tip">端口:</span>
          <el-input v-model="port"/>
        </div>
      </el-tab-pane>
      <el-tab-pane label="域名设置" name="url">
        <div class="ip-alert">
          <span class="ip-alert-tip">网址:</span>
          <el-input v-model="url"/>
        </div>
      </el-tab-pane>

    </el-tabs>
    <div>
      <h2 class="p1">示例提示和服务说明</h2>
      <h3 class="p1">示例：</h3>
      <p>假如服务部署在203.195.138.133 服务端口号为 30003
        域名为 http://opentest.cn
        如选择ip设置则可选上面的服务ip和端口号,若选域名则可对于的域名即可。</p>
      <h3 class="p1">说明：</h3>
      <p>1.IP不用加http://，该IP不是当前的电脑的ip地址而是服务部署的地址</p>
      <p>IP：203.195.138.133 端口号：40003</p>
      <p>2.域名：</p>
      <p>http://www.baidu.com</p>
      <p>https://www.baidu.com</p>
    </div>
    <div slot="footer" class="dialog-footer" >
      <el-button  v-show="isShowClose" @click="close">取 消</el-button>
      <el-button type="primary"  @click="inputValidator(active)">确 定</el-button>
    </div>
  </el-dialog>
</template>

<script>
  import myLocalStorage from '../../util/localStorage'
  import {verificationIp, verificationPort, verificationUrl} from '../../util/tool'
  export default {
    name: "UpdateServer",
    mounted(){
      let server = myLocalStorage.get('server')
      if(server){
        server = JSON.parse(server)
        this.isShowClose = true
        if(server.type=='ip'){
          let s = server.http.split(':')
          this.initIp = s[0]
          this.port = s[1]
        }else{
          this.url = server.http
        }
      }

    },
    data() {
      return {
        dialogFormVisible: true,
        initIp: '',
        port: '',
        url: '',
        isShowClose:false,
        type:'ip'
      }
    },
    methods: {
      inputValidator(activeName) {
        const server = {}
        if (this.type == 'ip') {
          let {initIp, port} = this
          initIp = initIp.trim()
          port = port.trim()
          server.type = 'ip'
          const msgIP = verificationIp(initIp)
          const msgPort = verificationPort(port)
          if (!msgIP) {
          } else {
            this.$message({
              type:'error',
              message:msgIP,
              duration:3000,
              showClose:true
            })
            return
          }
          if (!msgPort) {
            server.http = initIp + ':' + port
          } else {
            this.$message({
              type:'error',
              message:msgPort,
              duration:3000,
              showClose:true
            })
            return
          }
          myLocalStorage.set('server', JSON.stringify(server))
          myLocalStorage.set("isShowUpdateServer", Date.now());
          this.dialogFormVisible = false
          window.location.reload()
        } else if (this.type == 'url') {
          server.type = 'url'
          let url = this.url
          url = url.trim()
          const msgUrl = verificationUrl(url)
          if (!msgUrl) {
            server.http = url
          } else {
            this.$message({
              type:'error',
              message:msgUrl,
              duration:3000,
              showClose:true
            })
            return
          }
          myLocalStorage.set('server', JSON.stringify(server))
          myLocalStorage.set("isShowUpdateServer", Date.now());
          this.dialogFormVisible = false
          window.location.reload()
        }

      },
    },
    props:{
      active:String,
      close:Function
    }
  }
</script>

<style scoped>
  .ip-alert {
    display: flex;
    flex-direction: row;
    margin-bottom: 18px;
  }

  .ip-alert-tip {
    display: inline-block;
    width: 60px;
    margin-right: 18px;
    line-height: 40px;
    text-align: right;
  }
  .p1{
    margin-top: 5px;
  }
  p{
    margin: 10px 0;
    padding-left: 18px;
    line-height: 18px;
  }
</style>
