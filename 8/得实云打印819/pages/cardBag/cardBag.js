// pages/cardBag/cardBag.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    bannerList:["../../imgs/banner/lunbo1@2x.png","../../imgs/banner/lunbo2@2x.png","../../imgs/banner/lunbo3@2x.png"],
    userifo:[],
    showview:false,
    textValue:[],
    color:"",
    text:"请输入短信链接",
    printfNum:"",//打印机编号
    status:"",//打印机状态
    accessToken:""//用户token
  },
//短信打印
sms:function(){


},
//弹出框设置
 change:function(){
   let that = this;
   that.setData({
     showview:(!that.data.showview)
   })
 },

 close:function(options){
   console.log(options)
     let that = this;
     that.setData({
       showview:(!that.data.showview),
       text:"请输入短信链接",
       color: "",
     })
 },
 setValue:function(e){
   let that = this;
   that.setData({
     textValue:e.detail.value
   })
 },
 //获取文本域内的值  打印路径
  getValue:function(e){
    let that = this;
    var websiteName = that.data.textValue;
       console.log(websiteName)
    let reg = /^([hH][tT]{2}[pP]:\/\/|[hH][tT]{2}[pP][sS]:\/\/)(([A-Za-z0-9-~]+)\.)+([A-Za-z0-9-~\/])+$/;

    //路径限制
      if (websiteName == "") {
        that.setData({
          color:"red"
        })
        return false;
      }
      else if (!reg.test(websiteName)) {
        that.setData({
          text:"输入的链接格式不对",
          color:"red"
        })
        return false;
      }
      else{
        that.setData({
          text:"短信链接可用",
          color:"green"
        })
        wx.request({
          url: 'https://yun.dascomyun.cn/15_printapi/v2.0/judge',
          data:
            { url: that.data.textValue},
          method:"POST",
          header: {
            'content-type': 'application/json' // 默认值
          },
          success:function(res){
            that.setData({
              showview: false
            })
            wx.navigateTo({
              url: '../printf/printf?lick=' +that.data.textValue,
            })
          },
          fail:function(err){
            console.log(err)
          }
        })
      }

  },
  //点击卡包打印没有完成 access_token
  cardClick: function() {
    let that = this;
    console.log("点击事件")
    var printNum = wx.getStorage({
      key: 'printNumber',
      success: function(res) {
        console.log(res.data)
        //打印机编号
        wx.chooseInvoice({
          success: function (res) {
            console.log(res.invoiceInfo)
            console.log(res.invoiceInfo.card_id)//undefined
            console.log(res.invoiceInfo.encrypt_code)//undefined  有错
            if (res.invoiceInfo == "") {
              console.log("没有选择任何发票")
            } else {
              wx.request({
                url: "https://api.weixin.qq.com/card/invoice/reimburse/getinvoiceinfo?access_token={" + that.data.accessToken + "}",
                data: {
                  card_id: res.invoiceInfo.card_id,
                  yencrypt_code: res.invoiceInfo.encrypt_code
                },
                method: 'POST',
                header: {
                  'content-type': 'application/json' // 默认值
                },
                success(res) {
                  console.log(res.data)
                  if (res.data.errcode == 0) {
                    //还不行  access_token无效  错误提示
                    // wx.showModal({
                    //   title: '提示',
                    //   content:"发票URL："+ res.data.user_info.pdf_url ,
                    //   showCancel:false,
                    // })

                    ////////////////////////打印///////////////////////////
                    wx.request({
                      url: 'https://yun.dascomyun.cn/15_printapi/v2.0/print/' + that.data.printfNum,
                      data: {
                        'url': res.data.user_info.pdf_url,
                      },
                      method: 'POST',
                      header: {
                        'content-type': 'application/x-www-form-urlencoded',
                        'File-Type': 'url_pdf',
                      },
                      success(res) {
                        console.log(res.data)
                      },
                      fail(res) {
                        console.log("请求打印失败：", res.data)
                      }
                    })

                    ///////////////////////////////////////////////////////
                  } else {
                    wx.showModal({
                      title: 'ERROR',
                      content: "发票URL：" + res.data.errmsg,
                      showCancel: false,
                    })
                  }
                },
                fail(res) {
                  console.log("fail", res.errMsg)
                }
              })
            }

          },
          fail: function (err) {
            console.log(err)
          }
        })
      },
    })
  },
  //选择本地图片进行打印
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
                'number': that.data.printfNum,
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
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    let that = this;
   //获取access_token
    wx.request({
      url: 'https://api.weixin.qq.com/cgi-bin/token',
      data: {
        grant_type: "client_credential",
        appid: "wx646bf0db0e0be0e4",
        secret: "072e6a62a8f43f19f9fa2d24a303a86b"
      },
      header: {
        'content-type': 'application/json' // 默认值
      },
      success(res) {
        if (res.data.access_token != undefined) {
          console.log("token", res.data.access_token)
          that.setData({
            accessToken: res.data.access_token,
          })
        } else {
          console.log("get token failed:", res.data.errmsg)
        }
      },
      fail(res) {
        console.log(res)
      }
    })
    //打印机编号本地
    wx.setStorageSync("printNumber","0030BE7350021A00")
    var parintfNum = wx.getStorage({
      key: 'printNumber',
      success: function(res) {
        that.setData({
          printfNum:res.data
        })
      },
      fail: function(res) {},
      complete: function(res) {
        //获取打印机状态
        wx.request({
          url: 'https://yun.dascomyun.cn/15_printapi/v2.0/CheckPrinter/0030BE7350021A00',
          data: {
            // number: "0030BE7350021A00",
          },
          method: "GET",
          success: function (res) {
            console.log("打印机状态"+res.data.data.main)
            wx.setStorageSync("status", res.data.data.main)
            that.setData({
              status:res.data.data.main
            })
          }
        })
      },
    })
    //查询用户是否授权
    wx.getSetting({
      success(res) {
        console.log(res)
        if (!res.authSetting['scope.invoice']) {
          wx.authorize({
            scope: 'scope.record',
            success() {
              // 用户已经同意小程序使用查看发票功能，后续调用对应接口不会弹窗询问
            }
          })
        }
      },
      fail(res) {
        console.log("fail", res)
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

  }
   
})