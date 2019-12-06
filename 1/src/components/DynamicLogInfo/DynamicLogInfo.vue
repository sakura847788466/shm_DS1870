<template>
  <div class="box">
    <div class="title">
      <span>实时日志信息</span>
      <!--<el-button :type="type=='info.log'?'success':'primary'"-->
                 <!--size="small" style="margin-left: 18px"-->
                 <!--@click.prevent="onClickLogType('info.log')">info.log-->
      <!--</el-button>-->
      <!--<el-button :type="type=='warn.log'?'success':'primary'"-->
                 <!--size="small" @click.prevent="onClickLogType('warn.log')">warn.log-->
      <!--</el-button>-->
      <!--<el-button :type="type=='error.log'?'success':'primary'"-->
                 <!--size="small" @click.prevent="onClickLogType('error.log')">error.log-->
      <!--</el-button>-->


      <el-button type="danger" size="small" style="margin-left: auto" @click.prevent="back">返回</el-button>
    </div>
    <div class="log-view" v-html="info">
    </div>
  </div>
</template>

<script>
  import {conversionLog, getUrl} from "../../util/tool";

  export default {
    name: "DynamicLogInfo",
    mounted() {
      this.type = this.logType
      const URL = getUrl()
      const url = `ws://${URL}/websocket/${this.type}`
      // const url = `ws://${URL}/websocket/test/movie`
      this.websocket(url)
    },
    data() {
      return {
        info: '',
        type: '',
        ws:null
      }
    },
    methods: {
      back() {
        this.$alert('是否返回静态日志', '操作提示').then(res => {
          this.isShowLogView()
        })
      },

      onClickLogType(type) {
        if (type == this.type) {
          this.type = type
        } else {
          this.info = ''
          this.type = type
          const URL = getUrl()
          const url = `ws://${URL}/websocket/${type}`
          this.ws.close()
          this.websocket(url)
        }
      },

      websocket(url) {
        let that = this
        if ('WebSocket' in window) {
          this.ws = new WebSocket(url);
        }
        else {
          alert('Not support websocket')
        }

        this.ws.onerror = function () {
          setMessageInnerHTML("error");
        };


        this.ws.onopen = function (event) {
          setMessageInnerHTML("...");
        }

        this.ws.onmessage = function (event) {
          setMessageInnerHTML(event.data);
        }


        this.ws.onclose = function () {
          // setMessageInnerHTML("close");
        }

        window.onbeforeunload = function () {
          this.ws.close();
        }

        function setMessageInnerHTML(innerHTML) {
          that.info = that.info + conversionLog(innerHTML)
        }

        function closeWebSocket() {
          this.ws.close();
        }
      }
    },

    props: {
      isShowLogView: Function,
      logType: String
    }
  }
</script>

<style scoped>
  .box {
    box-sizing: content-box;
    margin: 0 auto;
    width: 1200px;
    height: 660px;
  }

  .title {
    display: flex;
    justify-content: space-between;
    padding-bottom: 10px;
    width: 100%;
    font-size: 24px;
    border-bottom: 1px solid #E7E7E7;
  }

  .log-view {
    overflow-y: scroll;
    overflow-x: hidden;
    margin-top: 30px;
    padding: 30px 0 0 30px;
    width: 100%;
    height: 600px;
    background-color: #333333;
    color: green;
    text-indent: 5px;
    word-wrap: break-word;
    line-height: 20px;
    font-size: 16px;
  }
</style>
