// pages/detail_carbag/detail_carbag.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    srctu:true,
    imgSrc:"../../imgs/diancan/cai11.jpg",
    number:"",
    array:["1","2","3","4","5"],
    show: false, //控制下拉列表的显示隐藏，false隐藏、true显示
    selectData: ["1", "2", "3", "4", "5"], //下拉列表的数据
    index: 0, //选择的下拉列 表下标,
  },
  selectTap() {
    this.setData({
      show: !this.data.show,
    });
  },
  // 点击下拉列表
  optionTap(e) {
    let Index = e.currentTarget.dataset.index; //获取点击的下拉列表的下标
    this.setData({
      index: Index,
      show: !this.data.show
    });
  },


  click:function(){
    console.log(999)
    let that=this;
    this.setData({
      srctu: (!that.data.srctu)
    })
    console.log(that.data.srctu)
   
    
  },
  bindPickerChange: function (e) {
    let that = this;
    console.log('picker发送选择改变，携带值为', e.detail.value)
    console.log(e.detail)
    that.setData({
      index: e.detail.value
    })
    console.log(that.data.index)
    // wx.request({
    //   url: 'https://yun.dascomyun.cn/15_printapi/v2.0/preview/' + that.data.number, //仅为示例，并非真实的接口地址
    //   data: {
    //     url: that.data.link,
    //     concentration:that.data.index
    //   },
    //   method: "POST",
    //   header: {
    //     'content-type': 'application/x-www-form-urlencoded',// 默认值
    //     'File-Type': "url_pdf"
    //   },
    //   success(res) {
    //     console.log(res.data)
    //     that.setData({
    //       imgSrc: res.data.data
    //     })
       
    //   },
    //   fail(res) {
    //     console.log(res.data)
    //   }
    // })
  },

  save:function(){
      wx.navigateTo({
        url: '../printf/printf',
      })
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    let that = this;
    that.setData({
      imgSrc:options.imgSrc
    })
      wx.getStorage({
        key: 'printNumber',
        success: function(res) {
          that.setData({
            number:res.data
          })
          console.log("设备编号" + that.data.number)

        },
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

  }
})