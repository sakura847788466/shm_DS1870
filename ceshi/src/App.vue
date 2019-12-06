<template>
  <div id="app">
    <div class="jindutiao" v-if="jindutiao"></div>
    <Header/>
    <router-view/>
    <UpdateServer v-if="isShowUpdatServer" :active="active"/>
  </div>
</template>

<script>
  import {mapActions} from "vuex";
  import ajax from "./api/ajax";
  import myLocalStorage from "./util/localStorage";
  import {verificationIp, verificationPort, verificationUrl} from "./util/tool";
  import Header from "./components/Header/Header";
  import UpdateServer from "./components/UpdataServer/UpdateServer";

  export default {
    name: "App",
    created() {
      this.localHttp();

      const type = this.validatorHttp();
      if (type) {
        this.getWhiteList()
          .then(() => {
            setTimeout(()=>{
              this.jindutiao = false
            },2000)
          })
          .catch(err => {
            this.jindutiao = false
            this.$notify.error({
              title: "错误",
              message: "请求服务设置，出错了",
              duration: 0
            });
          });
      } else {
        this.isShowUpdatServer = true;
      }

    },
    data() {
      return {
        isShowUpdatServer: false,
        active: "ip",
        jindutiao: true
      };
    },
    methods: {
      ...mapActions(["getWhiteList"]),
      validatorHttp() {
        let server = myLocalStorage.get("server");
        if (server) {
          server = JSON.parse(server);
          if (server.type == "ip") {
            let s = server.http.split(":");
            const msgIP = verificationIp(s[0]);
            const msgPort = verificationPort(s[1]);
            if (msgIP) {
              this.$message.error(msgIP);
              return;
            }
            if (msgPort) {
              this.$message.error(msgPort);
            }
          } else {
            let url = server.http;
            const msgUrl = verificationUrl(url);
            if (msgUrl) {
              this.$message.error(msgUrl);
            }
          }
          return true;
        } else {
          return false;
        }
      },

      localHttp() {
        const server = {};
        const http = location.protocol + '//' + location.hostname;
        // const http = "http://192.168.11.151";
        const port = ":30003";
        let getAll;
        //判断是ip还是网址
        if (location.port == "") {
          server.type = "url";
          getAll = () => ajax(http + "/whitelist/getAll");
        } else {
          server.type = "ip";
          getAll = () => ajax(http + port + "/whitelist/getAll");
        }
        const date = Date.now();
        const sevenNow = 1000 * 60 * 60 * 24 * 3;
        // console.log(http + port + "/whitelist/getAll");
        getAll()
          .then(res => {
            try {
              //判断如果三天时间过了，就从新弹出弹框
              const isShowServer = JSON.parse(myLocalStorage.get("isShowServer"));
              if (date > isShowServer + sevenNow) {
                myLocalStorage.set("isShowServer", Date.now());
                this.$confirm(
                  "检测到当前服务可以能正常访问, 是否使用当前服务?",
                  "提示",
                  {
                    confirmButtonText: "确定",
                    cancelButtonText: "取消",
                    type: "warning"
                  }
                )
                  .then(() => {
                    if (server.type == "ip") {
                      server.http = location.hostname + port;
                    } else {
                      server.http = http;
                    }
                    myLocalStorage.set("server", JSON.stringify(server));
                    window.location.reload()
                  })
                  .catch(() => {
                    this.isShowUpdatServer = true;
                  });
              }
            } catch (error) {
              console.log(147)
              myLocalStorage.set("isShowServer", Date.now());
              this.$confirm(
                "检测到当前服务可以能正常访问, 是否使用当前服务?",
                "提示",
                {
                  confirmButtonText: "确定",
                  cancelButtonText: "取消",
                  type: "warning"
                }
              )
                .then(() => {

                  if (server.type == "ip") {
                    server.http = location.hostname + port;
                  } else {
                    server.http = http;
                  }
                  myLocalStorage.set("server", JSON.stringify(server));
                  window.location.reload()
                })
                .catch(() => {
                  this.isShowUpdatServer = true;
                });
            }
          })
          .catch(res => {
            try {
              //判断如果三天时间过了，就从新弹出弹框
              const isShowUpdateServer = JSON.parse(
                myLocalStorage.get("isShowUpdateServer")
              );
              if (date > isShowUpdateServer + sevenNow) {
                myLocalStorage.set("isShowUpdateServer", Date.now());
                this.isShowUpdatServer = true;
              }
            } catch (error) {
              this.isShowUpdatServer = true;
            }
          });
      }
    },

    components: {UpdateServer, Header}
  };
</script>

<style>
  #app {
    width: 100%;
    /*overflow-x: hidden;*/
  }

  input::-webkit-outer-spin-button,
  input::-webkit-inner-spin-button {
    -webkit-appearance: none;
  }

  input[type="number"] {
    -moz-appearance: textfield;
  }

  .el-tooltip__popper[x-placement^=right] .popper__arrow {
    border-right-color: #5C5C5C;
  }

  .el-popper[x-placement^=right] .popper__arrow::after {
    border-right-color: #5C5C5C;

  }

  .el-table--enable-row-transition .el-table__body td {
    -webkit-transition: background-color .25s ease;
    transition: background-color .25s ease;
  }

  .el-table td.is-center, .el-table th.is-center {
    text-align: center;
  }

  .el-table--enable-row-transition .el-table__body td {
    -webkit-transition: background-color .25s ease;
    transition: background-color .25s ease;
  }

  .el-table td.is-center, .el-table th.is-center {
    text-align: center;
  }

  .el-table td, .el-table th.is-leaf {
    border-bottom: 1px solid #EBEEF5;
  }

  .el-table td {
    padding: 9px 0;
    min-width: 0;
    -webkit-box-sizing: border-box;
    box-sizing: border-box;
    text-overflow: ellipsis;
    vertical-align: middle;
    position: relative;
    text-align: left;
  }

  .popover {
    padding: 10px 15px;
    line-height: 18px;
    font-size: 12px;
    color: #fff;
    border-radius: 6px;
    background-color: #5C5C5C !important;
  }

  .popover > .popper__arrow:after {
    border-left-color: #5C5C5C !important;

  }

  .select-box .el-input__suffix {
    height: 33px;
  }

  .select-box .el-input {
    padding: 0;
    width: 100px;
  }

  .select-box .el-input__inner {
    height: 38px;
  }

  .jindutiao {
    position: absolute;
    width: 0;
    height: 3px;
    background-color: firebrick ;
    transition: .3s;
    animation: loading 3s infinite ease-in-out;
  }

  @keyframes loading {
    from {
      width: 0;
    }
    to {
      width: 100%;
    }
  }
</style>
