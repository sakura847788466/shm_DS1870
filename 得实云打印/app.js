//app.js
App({
  onLaunch: function () {
    var self = this
    wx.getSystemInfo({
      success: function (res) {
        console.log(res.model)
        console.log(res.pixelRatio)
        console.log(res.windowWidth)
        console.log(res.windowHeight)
        console.log(res.language)
        console.log(res.version)
        console.log(res.platform)
        self.globalData.platform = res.platform;
      }
    })

    console.log('App Launch')
  },
  globalData: {
    userInfo: null,
    platform: 'ios',
    totalList: [],
    totalGoodsList:[],
    bindedName:"",
    bindedMac:"",
    needconnect:false,
    shoppingnum:0,

    connectState: false,
    billNymber: 1,
    devId: "",
    serviceUuid: "49535343-FE7D-4AE5-8FA9-9FAFD205E455",
    notifyUuid: "49535343-1E4D-4BD9-BA61-23C647249616",
    writeUuid: "49535343-8841-43F4-A8D4-ECBE34729BB3",
  }
})