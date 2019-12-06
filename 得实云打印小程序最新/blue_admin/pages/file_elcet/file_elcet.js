// pages/file_elcet/file_elcet.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    webUrl: '',
    printfNumber:'0034BE735002FF00'
  },
  bindmessage:function(e){
    console.log(e.detail.data)
    console.log("接收页面数据")
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    let that = this;
    let printfNumber = that.data.printfNumber;
    let url = `http://localhost:3001?printfNumber=${printfNumber}`;

    that.setData({ webUrl: url })
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
    // var that = this;
    // // console.log(this.data.webUrl);
    // return {
    //   printfNumber:that.data.printfNumber,
    //   success(e) {
    //     wx.showShareMenu({
    //       // 要求小程序返回分享目标信息
    //       withShareTicket: true
    //     });
    //   },
    // }
  }
})