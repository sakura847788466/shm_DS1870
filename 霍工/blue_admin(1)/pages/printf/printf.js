
const app = getApp();

function inArray(arr, key, val) {
  for (let i = 0; i < arr.length; i++) {
    if (arr[i][key] === val) {
      return i;
    }
  }
  return -1;
}

// ArrayBuffer转16进度字符串示例
function ab2hex(buffer) {
  var hexArr = Array.prototype.map.call(
    new Uint8Array(buffer),
    function (bit) {
      return ('00' + bit.toString(16)).slice(-2)
    }
  )
  return hexArr.join('');
}

Page({

  /**
   * 页面的初始数据
   */
  data: {
      link:[],
      status:"",
      strnum:"0034BF7350020200",
      animation_abb:null,
      animation_add:null,
      jia:true,
      text: "请输入短信链接",
      color:'',
      showview: false,
      showStatus:true,
      linkList:[],
      textValue:'',
      animationList:[],//动画数组
      errStatus:false,//错误提示弹出框
      buffer: '', //发送的缓存数据
      printIndex: 1,
      chs: [],
      characteristicId: '',
      startT: '',//开始时间
      purl: '',

      deviceId:'',//设备id
      serviceId:'',//设备服务id
      characteristicId:''//设备特征值id



  },

//点击进入详情查看
detail:function(){
  let that = this;
  console.log(that.data.strnum)
  console.log(that.data.link)
  wx.getStorage({
    key: 'nongdu',
    success: function(res) {
      console.log(res.data)
      if (res.data == 1) {
        wx.request({
          url: 'https://yun.dascomyun.cn/15_printapi/v2.0/preview/'+that.data.strnum, //仅为示例，并非真实的接口地址
          data: {
            url: that.data.link,
            threshold: 98,
            isAdBlock: false,
            concentration: res.data
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
            // console.log(that.data.imgSrc)
            wx.navigateTo({
              url: '../detail_carbag/detail_carbag?imgSrc=' + that.data.imgSrc + '&Link=' + that.data.link,
            })
          },
          fail(res) {
            console.log(res.data)
          }
        })
      } else if (res.data == 2) {
        wx.request({
          url: 'https://yun.dascomyun.cn/15_printapi/v2.0/preview/0004C27350027B00', //仅为示例，并非真实的接口地址
          data: {
            url: that.data.link,
            threshold: 125,
            isAdBlock: false,
            concentration: res.data
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
            // console.log(that.data.imgSrc)
            wx.navigateTo({
              url: '../detail_carbag/detail_carbag?imgSrc=' + that.data.imgSrc + '&Link=' + that.data.link,
            })
          },
          fail(res) {
            console.log(res.data)
          }
        })
      } else if (res.data == 3) {
        wx.request({
          url: 'https://yun.dascomyun.cn/15_printapi/v2.0/preview/0004C27350027B00', //仅为示例，并非真实的接口地址
          data: {
            url: that.data.link,
            threshold: 178,
            isAdBlock: false,
            concentration: res.data
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
            // console.log(that.data.imgSrc)
            wx.navigateTo({
              url: '../detail_carbag/detail_carbag?imgSrc=' + that.data.imgSrc + '&Link=' + that.data.link,
            })
            wx.navigateTo({
              url: '../detail_carbag/detail_carbag?imgSrc=' + that.data.imgSrc + '&Link=' + that.data.link,
            })
          },
          fail(res) {
            console.log(res.data)
          }
        })
      } else if (res.data == 4) {
        wx.request({
          url: 'https://yun.dascomyun.cn/15_printapi/v2.0/preview/0004C27350027B00', //仅为示例，并非真实的接口地址
          data: {
            url: that.data.link,
            threshold: 203,
            isAdBlock: false,
            concentration: res.data
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
            // console.log(that.data.imgSrc)
            wx.navigateTo({
              url: '../detail_carbag/detail_carbag?imgSrc=' + that.data.imgSrc + '&Link=' + that.data.link,
            })
          },
          fail(res) {
            console.log(res.data)
          }
        })
      } else if (res.data == 5) {
        wx.request({
          url: 'https://yun.dascomyun.cn/15_printapi/v2.0/preview/0004C27350027B00', //仅为示例，并非真实的接口地址
          data: {
            url: that.data.link,
            threshold: 228,
            isAdBlock: false,
            concentration: res.data
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
            // console.log(that.data.imgSrc)
            wx.navigateTo({
              url: '../detail_carbag/detail_carbag?imgSrc=' + that.data.imgSrc + '&Link=' + that.data.link,
            })
          },
          fail(res) {
            console.log(res.data)
          }
        })
      } else {
        return false;
      }
    },
  })
},
  setValue: function (e) {
    let that = this;
    that.setData({
      textValue: e.detail.value
    })

  },
//获取短信信息
  getValue: function (e) {
    let that = this;
    var websiteName = that.data.textValue;
    console.log(websiteName)

    let reg = /^([hH][tT]{2}[pP]:\/\/|[hH][tT]{2}[pP][sS]:\/\/)(([A-Za-z0-9-~]+)\.)+([A-Za-z0-9-~\/])+$/;

    //路径限制
    if (websiteName == "") {
      that.setData({
        color: "red"
      })
      return false;
    }
    else if (!reg.test(websiteName)) {
      that.setData({
        text: "输入的链接格式不对",
        color: "red"
      })
      return false;
    }
    else {
      that.setData({
        text: "短信链接可用",
        color: "green"
      })
      app.globalData.linkList.push(websiteName)
      console.log(app.globalData.linkList)//将需要的链接组成一个数组
      wx.showLoading({
        title: 'loading......',
      })
      wx.request({
        url: 'https://yun.dascomyun.cn/15_printapi/v2.0/judge',
        data:
          { url: websiteName },
        method: "POST",
        header: {
          'content-type': 'application/json' // 默认值
        },
        success: function (res) {
          wx.hideLoading();
          that.setData({
            showview: false,
            linkList:app.globalData.linkList
          })
        },
        fail: function (err) {
          console.log(err)
        }
      })
    }

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
    let that = this;
    that.setData({
      showview: (!that.data.showview),
      // text: "请输入短信链接",
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
////////////////////////蓝牙打印//////////////////////////////////
printfByBle:function(){
  console.log(999)
  let that = this;
  for (var i = 0; i < that.data.linkList.length; i++) {
    console.log(that.data.linkList[i])
    wx.request({
      url: 'https://yun.dascomyun.cn/15_printapi/v2.0/extract',//拿到当前短信链接的PDF链接
      data: {
        url: that.data.linkList[i]
      },
      method: 'POST',
      header: {
        'content-type': 'application/json'
      },
      success(res) {
        console.log(res.data)
        if (res.data.code == 0) {//已获得PDF链接  
          console.log(res.data.data[1])//将PDF链接进行打印
          wx.request({
            url: 'https://test.dascomyun.cn/203_30011/small/simulation',
            data:{
              'url':res.data.data[1],
              'simulationType':'ZPL',
              'threshold': 178,
              'dpi':203,
              'concentration':16,
              'paperWidth':4.2
            },
            method: 'POST',
            header: {
              'content-type': 'application/json'
            },
            success(res){
              console.log(res)
              const base64 = res.data.data;
                  console.log(base64)
                  const arrayBuffer = wx.base64ToArrayBuffer(base64)
                  console.log(arrayBuffer)
                  var arrayBufferT = new Uint8Array(arrayBuffer);
                  console.log(arrayBufferT)
                  // that.setData({
                  //   buffer: arrayBufferT
                  // })
                  /*向蓝牙发送数据*/
                  that.print(arrayBufferT) 
            },
            fail(err){
              console.log(err)
            }
          })
        }else{
          wx.showModal({
            title: '提示',
            content: '获取短信的PDF链接失败',
          })
        }
      },
      fail(err){
        console.log(err)
        wx.showModal({
          title: '提示',
          content: '获取短信链接pdf失败',
        })
      }
    })
  }
},
  //获取蓝牙服务

  getBLEDeviceServices(deviceId) {
    var that = this;
    console.log('获取蓝牙服务')
    wx.getBLEDeviceServices({
      deviceId,
      success: (res) => {
        console.log(res)
        for (let i = 0; i < res.services.length; i++) {
          that.getBLEDeviceCharacteristics(deviceId, res.services[i].uuid)
        }
      }
    })
  },
  //服务特征值
  getBLEDeviceCharacteristics(deviceId, serviceId) {
    let that = this;
    wx.getBLEDeviceCharacteristics({
      deviceId,
      serviceId,
      success: (res) => {
        console.log('getBLEDeviceCharacteristics success', res.characteristics)
        for (let i = 0; i < res.characteristics.length; i++) {
          let item = res.characteristics[i]
          if (item.properties.read) {
            wx.readBLECharacteristicValue({
              deviceId,
              serviceId,
              characteristicId: item.uuid,
            })
          }
          if (item.properties.write && (item.uuid == "49535343-8841-43F4-A8D4-ECBE34729BB3" ||
            item.uuid == "00008201-0000-1000-8000-00805F9B34FB")) {
            that.setData({
              canWrite: true
            })
            that._deviceId = deviceId
            that._serviceId = serviceId
            that._characteristicId = item.uuid
            //this.writeBLECharacteristicValue()
            // console.log(that._characteristicId)
            // console.log(that._deviceId)
            // console.log(that._serviceId)
          }
          if (item.properties.notify || item.properties.indicate) {
            wx.notifyBLECharacteristicValueChange({
              deviceId,
              serviceId,
              characteristicId: item.uuid,
              state: true,
              success(res) {
                console.log(item)
                console.log("success", res)
              },
              fail(res) {
                console.log(item)
                console.log("fail", res)
              }
            })
          }
        }
      },
      fail(res) {
        console.error('getBLEDeviceCharacteristics', res)
      }
    })
    // 操作之前先监听，保证第一时间获取数据
    wx.onBLECharacteristicValueChange((characteristic) => {
      const idx = inArray(this.data.chs, 'uuid', characteristic.characteristicId)
      const data = {}
      if (idx === -1) {
        data[`chs[${this.data.chs.length}]`] = {
          uuid: characteristic.characteristicId,
          value: ab2hex(characteristic.value)
        }
      } else {
        data[`chs[${idx}]`] = {
          uuid: characteristic.characteristicId,
          value: ab2hex(characteristic.value)
        }
      }
      // data[`chs[${this.data.chs.length}]`] = {
      //   uuid: characteristic.characteristicId,
      //   value: ab2hex(characteristic.value)
      // }
      this.setData(data)
    })
  },
  writeBLECharacteristicValue() {
    let buffer = new ArrayBuffer(1)
    let dataView = new DataView(buffer)
    dataView.setUint8(0, 0xE)
    wx.writeBLECharacteristicValue({
      deviceId: that.data.deviceId,
      serviceId: that.data.serviceId,
      characteristicId: that.data.characteristicId,
      value: buffer,
    })
  },
  //发送数据 先使能
  print(userData) {
    var curtime = new Date();
    var starttime = curtime.getHours() + ":" + curtime.getMinutes() + ":" + curtime.getSeconds();
    this.setData({
      startT: starttime,
    })

    console.log(starttime)
    wx.showLoading({
      title: '发送中',
      mask: false,
    })


    console.log(userData)

    let sendData = [];
    var indexTemp = 0;
    for (let i = 0; i < this.data.printIndex; i++) {
      for (let j = 0; j < userData.length; j++) {
        sendData[indexTemp++] = userData[j];
      }
    }

    let head = [0x14, 0x0, 0x5, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0]
    head[3] = (indexTemp & 0xff);
    head[4] = ((indexTemp >> 8) & 0xff);
    head[5] = ((indexTemp >> 16) & 0xff);

    var sum = 0;
    for (let i = 0; i < indexTemp; i++) {
      sum += sendData[i];
    }
    head[6] = (sum & 0xff);
    head[7] = ((sum >> 8) & 0xff);
    head[8] = ((sum >> 16) & 0xff);
    head[9] = ((sum >> 24) & 0xff);

    var buffer = new ArrayBuffer(10);
    var dataView = new Uint8Array(buffer);
    for (var i = 0; i < 10; i++) {
      dataView[i] = head[i];
    }
    console.log(buffer)
    var that = this;
    //看是否有此设备id和设备名称ada
    console.log(that._deviceId)
    console.log(that._serviceId)
    
    wx.writeBLECharacteristicValue({
      deviceId: that._deviceId,
      serviceId: that._serviceId, //'000082FF-0000-1000-8000-00805F9B34FB'
      characteristicId: that._characteristicId,//'00008201-0000-1000-8000-00805F9B34FB',
      value: buffer,
      success: function (res) {
        console.log('使能成功，发打印数据')
        console.log(sendData)
        that.ConfigSend(sendData);
      },
      fail: function (res) {
        // fail
        console.log('使能失败', res)
        wx.hideLoading({
        });

        wx.showModal({
          showCancel: false,
          title: '提示',
          content: "使能失败",
          success: function (res) {

          }
        });
      }
    })

  },
  //发送数据
  ConfigSend: function (remainData) {
    var that = this
    if (remainData.length > 20) {
      var buffer = new ArrayBuffer(20);
      var dataView = new Uint8Array(buffer);
      for (var i = 0; i < 20; i++) {
        dataView[i] = remainData[i];
      }
      var a = remainData.slice(20);

      wx.writeBLECharacteristicValue({
        deviceId: this._deviceId,
        serviceId: this._serviceId,
        characteristicId: this._characteristicId == "00008201-0000-1000-8000-00805F9B34FB" ? "00008202-0000-1000-8000-00805F9B34FB" : this._characteristicId,
        value: buffer,
        success: function (res) {
          console.log('发送成功，继续发送')
          that.ConfigSend(a);
        },
        fail: function (res) {
          // fail
          console.log('发送失败', res)
          wx.hideLoading({
          });

          wx.showModal({
            showCancel: false,
            title: '提示',
            content: "发送失败，请重试...",
            success: function (res) {

            }
          });
        }
      })
    } else {
      var buffer = new ArrayBuffer(remainData.length);
      var dataView = new Uint8Array(buffer);
      for (var i = 0; i < remainData.length; i++) {
        dataView[i] = remainData[i];
      }
      console.log("###buffer余数###", dataView);
      wx.writeBLECharacteristicValue({
        deviceId: this._deviceId,
        serviceId: this._serviceId,
        characteristicId: this._characteristicId == "00008201-0000-1000-8000-00805F9B34FB" ? "00008202-0000-1000-8000-00805F9B34FB" : this._characteristicId,
        value: buffer,
        success: function (res) {
          console.log('发送成功');
          wx.hideLoading({
          });
          let curtime = new Date();
          var endtime = curtime.getHours() + ":" + curtime.getMinutes() + ":" + curtime.getSeconds();
          console.log(endtime)
          wx.showModal({
            title: '提示',
            content: '开始发送:' + that.data.startT + "\n发送完成:" + endtime,
            showCancel: false,
            success: function (res) {

            }
          })
        },
        fail: function (res) {
          // fail
          console.log('发送失败', res)
          wx.hideLoading({
          });

          wx.showModal({
            showCancel: false,
            title: '提示',
            content: "发送失败，请重试...",
          });
        }
      })
    }
  },
///////////////////////蓝牙打印/////////////////////////////

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
  
    
    let that = this;
    that.setData({
      deviceId: options.deviceId,
      serviceId: options.serviceId,
      characteristicId: that.characteristicId,
    })

    let btDevId = options.deviceId
    that.getBLEDeviceServices(btDevId)//获取该设备的蓝牙服务

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
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {
      // 创建动画实例
    let that = this;
    that.animation = wx.createAnimation()
  },
  translate: function (e) {
    let that = this;
    var index = e.currentTarget.dataset.index;
    
    that.animation.translate(-375).rotate(0).step();
    app.globalData.linkList.splice(index, 1)//删除对应下标的数据
    console.log(app.globalData.linkList)
    that.setData({ 
      animation_abb: that.animation.export(),
      // linkList:app.globalData.linkList
      })
    
  },
  // 旋转
  translateRote:function(){
      let that = this;
      if(that.data.showStatus == true){
        if(that.data.linkList.length >= 5){
            that.setData({
              errStatus:(!that.data.errStatus)
            })
        }else{
          that.animation.translate(0).rotate(90).step();
          that.setData({
            showStatus: (!that.data.showStatus),
            jia: (!that.data.jia)
          })
        }
      }
      else{
        that.animation.translate(0).rotate(-90).step();
        that.setData({
          showStatus: (!that.data.showStatus),
          jia: (!that.data.jia)

        })
      }
    that.setData({
      animation_add:that.animation.export()
    })
  },
  istrue:function(){
    let that = this;
    that.setData({
      errStatus:(!that.data.errStatus)
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