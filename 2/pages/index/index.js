//index.js
//获取应用实例
const app = getApp()

Page({
  data: {
   
  },
  //事件处理函数
  goToPrint: function () {
    var that = this;
    // 只允许从相机扫码
    wx.scanCode({
      onlyFromCamera: true,
      success(res) {

        var num = res.result.indexOf("#")
        if (num < 0) {
          wx.showModal({
            title: '提示',
            content: '二维码格式错误',
            showCancel: false,
          })
        } else {
          var strnum = res.result.substr(num + 1)//序列号
          if (strnum.length != 16) {
            wx.showModal({
              title: '提示',
              content: '二维码格式错误',
              showCancel: false,
            })
            return;
          }
          var reg = /^[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F]/;
          if (!reg.test(strnum)) {
            wx.showModal({
              title: '提示',
              content: '二维码格式错误',
              showCancel: false,
            })
            return;
          } else {
            wx.navigateTo({
              url: '/pages/print/print?devtype=1&deviceNum=' + strnum
            })
          }

        }
      },
      fail(res) {
        wx.showModal({
          title: '提示',
          content: '扫码失败，请重试。',
          showCancel: false,
        })
      }
    })
  },
  onLoad: function () {
    
  },
  //条码机打印销售小票
  ToPrintSail: function () {
    var that = this;
    // 只允许从相机扫码
    wx.scanCode({
      onlyFromCamera: true,
      success(res) {

        var num = res.result.indexOf("#")
        if (num < 0) {
          wx.showModal({
            title: '提示',
            content: '二维码格式错误',
            showCancel: false,
          })
        } else {
          var strnum = res.result.substr(num + 1)//序列号
          if (strnum.length != 16) {
            wx.showModal({
              title: '提示',
              content: '二维码格式错误',
              showCancel: false,
            })
            return;
          }
          var reg = /^[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F]/;
          if (!reg.test(strnum)) {
            wx.showModal({
              title: '提示',
              content: '二维码格式错误',
              showCancel: false,
            })
            return;
          } else {
            wx.navigateTo({
              url: '/pages/sailbill/sailbill?deviceNum=' + strnum
            })
          }

        }
      },
      fail(res) {
        wx.showModal({
          title: '提示',
          content: '扫码失败，请重试。',
          showCancel: false,
        })
      }
    })
  },

  BLEPrint:function(){
    wx.navigateTo({
      url: '/pages/blesearch/blesearch',
    })
  },
  
})
