<template>
  <el-button type="primary"
             class="btn">打印测试<i class="el-icon-upload el-icon--right"></i></el-button>
</template>

<script>
export default {
  name: "help",
  mounted () {

    var ua = window.navigator.userAgent.toLowerCase();
    console.log(window.location)
    //微信环境
    console.log(wx)
    wx.miniProgram.getEnv(function (res) {
      console.log(res)
      const t = sessionStorage.getItem('num')
      console.log(t)
      if (res.miniprogram) {
        // 小程序环境下逻辑
        //向小程序发送信息```
        var info = {
          title: '11', //参数一
          value: '22', //参数二
        };

      }

    })


    function getParamer () {

      var url = window.location.href.split("?")[1]; /*获取url里"?"后面的值*/
      if (url) { /*判断是否是一个参数还是多个参数*/
        url = url.split("=")
        return url[1]; /*返回想要的参数值*/
        console.log(url[1])
      } else {
        return '';
      }
    }

  },
  data () {
    return {
      isShowUpdatServer: false,
      active: '',
      number: ''//设备编号
    }
  },
  methods: {
    created () {
      console.log(window.location.search.substr(1))

    },

    getQueryString: function (name) {
      var reg = new RegExp("(^|&)" + name + "=([^&]*)(&|$)", "i");
      var r = window.location.search.substr(1).match(reg);
      if (r != null) {
        return decodeURIComponent(r[2]);
      }
      return null;
    }


  },
}
</script>

<style scoped>
.btn {
  position: fixed;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
}
</style>
