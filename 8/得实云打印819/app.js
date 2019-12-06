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
  },
  //anmite动画
   
    //渐入，渐出实现 
    show: function(that, param, opacity){
    var animation = wx.createAnimation({
      //持续时间800ms
      duration: 800,
      timingFunction: 'ease',
    });
    //var animation = this.animation
    animation.opacity(opacity).step()
    //将param转换为key
    var json = '{"' + param + '":""}'
    json = JSON.parse(json);
    json[param] = animation.export()
    //设置动画
    that.setData(json)
  },

  //滑动渐入渐出
  slideupshow: function (that, param, px, opacity) {
    var animation = wx.createAnimation({
      duration: 800,
      timingFunction: 'ease',
    });
    animation.translateY(px).opacity(opacity).step()
    //将param转换为key
    var json = '{"' + param + '":""}'
    json = JSON.parse(json);
    json[param] = animation.export()
    //设置动画
    that.setData(json)
  },

  //向右滑动渐入渐出
  sliderightshow: function (that, param, px, opacity) {
    var animation = wx.createAnimation({
      duration: 800,
      timingFunction: 'ease',
    });
    animation.translateX(px).opacity(opacity).step()
    //将param转换为key
    var json = '{"' + param + '":""}'
    json = JSON.parse(json);
    json[param] = animation.export()
    //设置动画
    that.setData(json)
  }


})