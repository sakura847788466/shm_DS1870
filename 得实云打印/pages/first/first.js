var app = getApp();
// page/first/first.js
Page({

  /**
   * 页面的初始数据
   */
  data: {

  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {

    //获取扫到页面的参数
    if (options.q !== undefined) {
      var scan_url = decodeURIComponent(options.q);

      console.log(scan_url);
    } else {
      console.log(123);
    }
    // var launchToastDuration = 0;
    // if (app.globalData.platform === 'ios') {
    //   launchToastDuration = 1500
    // }
    // else {
    //   launchToastDuration = 2000
    // }
    // wx.showToast({
    //   title: '加载中',
    //   icon: 'loading',
    //   mask: true,
    //   duration: 5000
    // })
  },
  //调用小程序中的扫一扫功能
  scanCode() {
    let that = this;
    wx.scanCode({
      success(res) {
        console.log(res.result);
        wx.navigateTo({
          url: '../diancan/diancan?title=' + res.result

        })
      }
    })
  },
  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  },

  goToCfg: function () {
    wx.navigateTo({
      url: "/pages/sailbill/sailbill",
    })
  },


  goToYunPrint: function () {
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
})