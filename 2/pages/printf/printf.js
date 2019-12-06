// pages/printf/printf.js

const app = getApp();

Page({

  /**
   * 页面的初始数据
   */
  data: {
      link:[],
      status:"",
      strnum:"0030BE7350021A00",
      animation_abb:null,
      animation_add:null,
      jia:true,
      text: "请输入短信链接",
      color:'',
      showview: false,
      showStatus:true,
      linkList:[]


  },

//点击进入详情查看
detail:function(){
  let that = this;
  console.log(that.data.strnum)
  console.log(that.data.link)
    wx.request({
      url: 'https://yun.dascomyun.cn/15_printapi/v2.0/preview/'+that.data.strnum, //仅为示例，并非真实的接口地址
      data: {
        url: that.data.link,
      },
      method:"POST",
      header: {
        'content-type': 'application/x-www-form-urlencoded' ,// 默认值
        'File-Type':"url_pdf"
      },
      success(res) {
        console.log(res.data)
        that.setData({
          imgSrc:res.data.data
        })
         wx.navigateTo({
           url: '../detail_carbag/detail_carbag?imgSrc='+that.data.imgSrc,
            })
      },
      fail(res){
        console.log(res.data)
      }
    })

},

// 加号
add:function(){
  let that = this;
  that.setData({
  })
},
//短信弹出框
  change: function () {
    let that = this;
    that.setData({
      showview: (!that.data.showview),
      jia:(!that.data.jia)
    })
  },
  close: function (options) {
    // console.log(options)
    let that = this;
    that.setData({
      showview: (!that.data.showview),
      text: "请输入短信链接",
      color: "",
    })
  },
//本地文件打印
  printimage: function () {
    var that = this;
    wx.chooseImage({
      success: res => {
        wx.getFileSystemManager().readFile({
          filePath: res.tempFilePaths[0], //选择图片返回的相对路径
          encoding: 'base64',
          success: res => { //成功的回调
            console.log('data:image/png;base64,' + res.data)
            wx.showLoading({
              title: '处理中...',
              mask: true,
            })
            wx.request({
              url: 'https://yun.dascomyun.cn/15_printapi/v2.0/printPreview',
              header: {
                'content-type': 'application/json',
                'File-Type': 'photo',
              },
              data: {
                'number': that.data.strnum,
                "receive": res.data,
                'isPrint': true,
              },
              method: "POST",
              success(res) {
                console.log("success", res)
                wx.hideLoading();
                if (res.data.code == 0) {
                  wx.showModal({
                    title: '提示',
                    content: '打印成功',
                    showCancel: false,
                  })
                } else {
                  wx.showModal({
                    title: '提示',
                    content: '打印失败' + res.data.data,
                    showCancel: false,
                  })
                }

              },
              fail(res) {
                console.log("failed", res)
                wx.hideLoading();
                wx.showModal({
                  title: '提示',
                  content: '打印失败',
                  showCancel: false,
                })
              }

            });
          },
          fail(res) {
            console.log(res)
          }
        })
      },
      fail(res) {
        console.log("choose image failed:", res)
      }
    })
  },
//打印
printf:function(){
  let that = this;

  wx.request({
    url: 'https://yun.dascomyun.cn/15_printapi/v2.0/extract',//拿到当前短信链接的PDF链接
      data:{
        url:that.data.link
      },
    method: 'POST',
    header: {
      'content-type': 'application/json'
    },
    success(res) {
      console.log(res.data)
      if (res.data.code == 0) {//已获得PDF链接  
        console.log(res.data.data[1])//将PDF链接发送给后台拿仿真数据
        wx.request({
          url: 'https://yun.dascomyun.cn/v2.0/convertPrintData',
          data: {
            'conver': res.data.data[1],
            "type": 'url_photo',
            'printdata': 'FZ',
            'instruction': 'ZPL',
            'threshold': '178',
            'paperWidth': 10.5,
            'concentration': 2,
            'dpi': 203
          },
          method: 'POST',
          header: {
            'content-type': 'application/x-www-form-urlencoded',
          },
          success(res) {
            console.log(res)
            if (res.data.code == 0) {
              wx.showModal({
                title: '提示',
                content: '获取buffer成功',
                showCancel: false,
              })
              // wx.navigateTo({
              //   url: '../cardBag/cardBag',
              // })
            } else {
              wx.showModal({
                title: '提示',
                content: '获取buffer失败' + res,
                showCancel: false,
              })
            }

          },
          fail(res) {
            console.log("请求打印失败：", res.data)
            wx.hideLoading();
            wx.showModal({
              title: '提示',
              content: '请求打印失败',
              showCancel: false,
            })
          }
        })
      } else {
        console.log("请求打印失败")
        wx.hideLoading();
        wx.showModal({
          title: '提示',
          content: '提取发票失败' + res.data.data,
          showCancel: false,
        })
      }
    },
    fail(res) {
      console.log("请求打印失败：", res.data)
      wx.hideLoading();
      wx.showModal({
        title: '提示',
        content: '网络请求失败',
        showCancel: false,
      })
    }
  })

},
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
  
    console.log(options)
    let that = this;
    wx.getStorage({
      key: 'status',
      success: function(res) {
        console.log(res)
        that.setData({
          status:res.data
        })
      },
    })
    that.setData({
      link:that.options.lick,
      linkList: app.globalData.linkList
    })
    console.log(that.data.link)
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {
      // 创建动画实例
    let that = this;
    that.animation = wx.createAnimation()
  },
  translate: function () {
    let that = this;
    that.animation.translate(-375).rotate(0).step();
    that.setData({ 
      animation_abb: that.animation.export() 
      })
  },
  // 旋转
  translateRote:function(){
      let that = this;
      if(that.data.showStatus == true){
        that.animation.translate(0).rotate(90).step();
        that.setData({
          showStatus:false,
          jia: (!that.data.jia)

        })
      }
      else{
        that.animation.translate(0).rotate(-90).step();
        that.setData({
          showStatus:true,
          jia: (!that.data.jia)

        })
      }
    that.setData({
      animation_add:that.animation.export()
    })
  },

  translatey: function () {
    let that = this;
    that.animation.translate(0, 150).step();

    that.setData({
      animation_y: that.animation.export()
    })
  },
  setValue: function (e) {
    let that = this;
    that.setData({
      textValue: e.detail.value
    })
  },
  // getValue: function (e) {
  //   let that = this;
  //   var websiteName = that.data.textValue;
  //   console.log(websiteName)
  //   let reg = /^([hH][tT]{2}[pP]:\/\/|[hH][tT]{2}[pP][sS]:\/\/)(([A-Za-z0-9-~]+)\.)+([A-Za-z0-9-~\/])+$/;

  //   //路径限制
  //   if (websiteName == "") {
  //     that.setData({
  //       color: "red"
  //     })
  //     return false;
  //   }
  //   else if (!reg.test(websiteName)) {
  //     that.setData({
  //       text: "输入的链接格式不对",
  //       color: "red"
  //     })
  //     return false;
  //   }
  //   else {
  //     that.setData({
  //       text: "短信链接可用",
  //       color: "green"
  //     })
  //     app.globalData.linkList.push(websiteName)
  //     console.log(app.globalData.linkList)
  //     that.setData({
  //       linkList:app.globalData.linkList
  //     })
  //     wx.request({
  //       url: 'https://yun.dascomyun.cn/15_printapi/v2.0/judge', //判断是否可以打印的状态
  //       data:
  //         { url: that.data.textValue },
  //       method: "POST",
  //       header: {
  //         'content-type': 'application/json' // 默认值
  //       },
  //       success: function (res) {
  //         that.setData({
  //           showview: false
  //         })
  //         console.log("地二张打印成功")
  //       },
  //       fail: function (err) {
  //         console.log(err)
  //       }
  //     })
  //   }

  // },
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