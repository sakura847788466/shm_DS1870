// pages/detail_carbag/detail_carbag.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    srctu:true,
    imgSrc:"",
    number:"",
    array:["1","2","3","4","5"],
    show: false, //控制下拉列表的显示隐藏，false隐藏、true显示
    selectData: ["1", "2", "3", "4", "5"], //下拉列表的数据
    index: 0, //选择的下拉列 表下标,
    link:'',
    index_new:''//当前选择浓度
  },
  selectTap() {
    this.setData({
      show: !this.data.show,
    });
  },
  // 点击下拉列表
  optionTap(e) {
    let that = this;
    let Index = e.currentTarget.dataset.index; //获取点击的下拉列表的下标
    that.setData({
      index: Index,
      show: !that.data.show
    });
    console.log(that.data.selectData[that.data.index])
    that.setData({
      index_new: that.data.selectData[that.data.index]
    })
    const biaoZhu = that.data.selectData[that.data.index]
    // https://yun.dascomyun.cn/15_printapi/v2.0/preview/0004C27350027B00
    if(biaoZhu == 1){
      wx.request({
        url: 'https://yun.dascomyun.cn/15_printapi/v2.0/preview/0004C27350027B00', //仅为示例，并非真实的接口地址
        data: {
          url: that.data.link,
          threshold: 98,
          isAdBlock: false,
          concentration: biaoZhu
        },
        method: "POST",
        header: {
          'content-type': 'application/x-www-form-urlencoded',// 默认值
          'File-Type': "url_pdf"
        },
        success(res) {
          console.log(res.data)
          that.setData({
            imgSrc: res.data.data,
          })
          console.log(that.data.imgSrc)
        },
        fail(res) {
          console.log(res.data)
          wx.showModal({
            title: '提示',
            content: '清除失败',
          })
        }
      })
    }else if(biaoZhu == 2){
      wx.request({
        url: 'https://yun.dascomyun.cn/15_printapi/v2.0/preview/0004C27350027B00', //仅为示例，并非真实的接口地址
        data: {
          url: that.data.link,
          threshold: 125,
          isAdBlock: false,
          concentration: biaoZhu
        },
        method: "POST",
        header: {
          'content-type': 'application/x-www-form-urlencoded',// 默认值
          'File-Type': "url_pdf"
        },
        success(res) {
          console.log(res.data)
          that.setData({
            imgSrc: res.data.data,
          })
          console.log(that.data.imgSrc)
        },
        fail(res) {
          console.log(res.data)
          wx.showModal({
            title: '提示',
            content: '清除失败',
          })
        }
      })
    }else if(biaoZhu == 3){
      wx.request({
        url: 'https://yun.dascomyun.cn/15_printapi/v2.0/preview/0004C27350027B00', //仅为示例，并非真实的接口地址
        data: {
          url: that.data.link,
          threshold: 178,
          isAdBlock: false,
          concentration: biaoZhu
        },
        method: "POST",
        header: {
          'content-type': 'application/x-www-form-urlencoded',// 默认值
          'File-Type': "url_pdf"
        },
        success(res) {
          console.log(res.data)
          that.setData({
            imgSrc: res.data.data,
          })
          console.log(that.data.imgSrc)
        },
        fail(res) {
          console.log(res.data)
          wx.showModal({
            title: '提示',
            content: '清除失败',
          })
        }
      })
    }else if(biaoZhu == 4){
      wx.request({
        url: 'https://yun.dascomyun.cn/15_printapi/v2.0/preview/0004C27350027B00', //仅为示例，并非真实的接口地址
        data: {
          url: that.data.link,
          threshold: 203,
          isAdBlock: false,
          concentration: biaoZhu
        },
        method: "POST",
        header: {
          'content-type': 'application/x-www-form-urlencoded',// 默认值
          'File-Type': "url_pdf"
        },
        success(res) {
          console.log(res.data)
          that.setData({
            imgSrc: res.data.data,
          })
          console.log(that.data.imgSrc)
        },
        fail(res) {
          console.log(res.data)
          wx.showModal({
            title: '提示',
            content: '清除失败',
          })
        }
      })
    }else if(biaoZhu == 5){
      wx.request({
        url: 'https://yun.dascomyun.cn/15_printapi/v2.0/preview/0004C27350027B00', //仅为示例，并非真实的接口地址
        data: {
          url: that.data.link,
          threshold: 228,
          isAdBlock: false,
          concentration: biaoZhu
        },
        method: "POST",
        header: {
          'content-type': 'application/x-www-form-urlencoded',// 默认值
          'File-Type': "url_pdf"
        },
        success(res) {
          console.log(res.data)
          that.setData({
            imgSrc: res.data.data,
          })
          console.log(that.data.imgSrc)
        },
        fail(res) {
          console.log(res.data)
          wx.showModal({
            title: '提示',
            content: '清除失败',
          })
        }
      })
    }else{
      return false;
    }
  },


  click:function(){
    console.log(999)
    let that=this;
    wx.showLoading({
      title: '处理中',
    })
    if(that.data.srctu == true){
      //  清除广告
      wx.request({
        url: 'https://yun.dascomyun.cn/15_printapi/v2.0/preview/' + that.data.number, //仅为示例，并非真实的接口地址
        data: {
          url: that.data.link,
          isAdBlock:true
        },
        method: "POST",
        header: {
          'content-type': 'application/x-www-form-urlencoded',// 默认值
          'File-Type': "url_pdf"
        },
        success(res) {
          console.log(res.data)
          wx.hideLoading();
          wx.showModal({
            title: '提示',
            content: '清除广告成功',
          })
          that.setData({
            imgSrc: res.data.data,
            srctu: (!that.data.srctu)
          })
          console.log(that.data.srctu)
        },
        fail(res) {
          console.log(res.data)
          wx.showModal({
            title: '提示',
            content: '清除失败',
          })
        }
      })

    }else{
      this.setData({
        srctu: (!that.data.srctu)
      })
      wx.hideLoading();
      wx.showModal({
        title: '提示',
        content: '关闭成功',
      })
    }
    
    console.log(that.data.srctu)
   
    
  },
  save:function(e){
    let that = this;
    console.log(that.data.index_new)
    wx.setStorageSync('nongdu', that.data.index_new)
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
      imgSrc:options.imgSrc,
      link:options.Link,
      
    })
    console.log(that.data.link)
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