// pages/cardBag/cardBag.js
const app =getApp();

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
    bannerList:["../../imgs/banner/lunbo1@2x.png","../../imgs/banner/lunbo2@2x.png","../../imgs/banner/lunbo3@2x.png"],
    userifo:[],
    showview:false,
    textValue:[],
    color:"",
    text:"请输入短信链接",
    printfNum:"",//打印机编号
    status:"",//打印机状态
    accessToken:"",//用户token,
    devId:'',//蓝牙设备id
    deviceName:'',//蓝牙名称
    serviceUuid:'000082FF-0000-1000-8000-00805F9B34FB',//符合得实设备uuid
    configUuid: "00008204-0000-1000-8000-00805F9B34FB",//写入蓝牙所需要的参数，蓝牙特征值的uuid
    writeCharacteristicId:'',//符合写 读 notify的uuid
    notifyServicweId:'',
    writeServicweId:'',
    notify_id:'',
    read_id:'',
    write_id:'',
    base64Url:'',
    buffer:'', //发送的缓存数据
    printIndex: 1,
    chs:[],
    characteristicId:'',
    startT:'',//开始时间
    purl:'',
    linkList: ['http://u.baiwang.com/LqOukLCgF5c']//ceshi 假数据写死



  
  },
//弹出框设置
 change:function(){
   let that = this;
   that.setData({
     showview:(!that.data.showview)
   })
 },
  close: function (options) {
    console.log(options)
    let that = this;
    that.setData({
      showview: (!that.data.showview),
      text: "请输入短信链接",
      color: "",
    })
  },
  setValue: function (e) {
    let that = this;
    that.setData({
      textValue: e.detail.value
    })

  },
  //获取文本域内的值  打印路径
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
      wx.request({
        url: 'https://yun.dascomyun.cn/15_printapi/v2.0/judge',
        data:
          { url: that.data.textValue },
        method: "POST",
        header: {
          'content-type': 'application/json' // 默认值
        },
        success: function (res) {
          that.setData({
            showview: false
          })
          wx.navigateTo({
            url: '../printf/printf?lick=' + that.data.textValue,
          })
        },
        fail: function (err) {
          console.log(err)
        }
      })
    }

  },
  //点击卡包打印没有完成 access_token
  cardClick: function () {
    let that = this;
    let pages = getCurrentPages(); //获取加载的页面

    let currentPage = pages[pages.length - 1]; //获取当前页面的对象

    let url = currentPage.route;//当前页面url
    console.log(url, '当前页面路径')
    if (url) {
      that.setData({
        purl: url
      })
    }else{
      return;
    }
    console.log("点击事件")
    var printNum = wx.getStorage({
      key: 'printNumber',
      success: function (res) {
        console.log(res.data)
        //打印机编号
        wx.request({
          url: 'https://yun.dascomyun.cn/open/configSign',
          data:{
            url:that.data.purl,
            appid:'wx4943f6480a79a436'
          },
          method:'GET',
          header: {
                  'content-type': 'application/json',
          },
          success(res){
            console.log(res)
            wx.config({
              beta: true,
              debug: false, // 开启调试模式,调用的所有api的返回值会在客户端alert
              appId: res.data.appid, // 必填，公众号的唯一标识
              timestamp: res.data.timestamp, // 必填，生成签名的时间戳
              nonceStr: res.data.nonceStr, // 必填，生成签名的随机串
              signature: res.data.signature, // 必填，签名，见附录1
              jsApiList: ['chooseInvoice', 'scanQRCode'], // 必填，需要使用的JS接口列表，所有JS接口列表见附录2
            });
          },
          fail(err){
            console.log(err)
          }
              

        })
        // wx.chooseInvoice({
        //   success: function (res) {
        //     console.log(res.invoiceInfo)
        //     var arr = JSON.parse(res.invoiceInfo);
        //     console.log(arr[0].card_id)
        //     console.log(arr[0].encrypt_code)
        //     if (res.invoiceInfo == "") {
        //       console.log("没有选择任何发票")
        //     } else {
        //       wx.request({
        //         url: 'https://yun.dascomyun.cn/open/showAInfo ',
        //         header: {
        //           'content-type': 'application/json',
        //         },
        //         data:{
        //           appid:'wx4943f6480a79a436'
        //         },
        //         method: "GET",
        //         success(res) {
        //           console.log("success", res)//获取appid
        //         },
        //         fail(res) {
        //           console.log("failed", res)
        //         }
        //       });
        //       // wx.request({
        //       //   url: "https://yun.dascomyun.cn/cardInfo/appid",
        //       //   data: { 
        //       //     appid: 'wx4943f6480a79a436',
        //       //     ticketsList: [
        //       //       { 
        //       //         "card_id": arr[0].card_id,
        //       //         "encrypt_code": arr[0].encrypt_code 
        //       //          }]
        //       //       },
        //       //   method: 'POST',
        //       //   header: {
        //       //     'content-type': 'application/json' // 默认值
        //       //   },
        //       //   success(res) {
        //       //     console.log(res.data)
        //       //     if (res.data.errcode == 0) {
        //       //       ////////////////////////打印///////////////////////////
                   
        //       //       ///////////////////////////////////////////////////////
        //       //     } else {
        //       //       wx.showModal({
        //       //         title: 'ERROR',
        //       //         content: "发票URL：" + res.data.errmsg,
        //       //         showCancel: false,
        //       //       })
        //       //     }
        //       //   },
        //       //   fail(res) {
        //       //     console.log("fail", res.errMsg)
        //       //   }
        //       // })
        //     }
        //   },
        //   fail: function (err) {
        //     console.log(err)
        //   }
        // })
      },
    })
  },
  //选择本地图片进行打印
  // printimage: function () {
  //   var that = this;
  //   wx.chooseImage({
  //     success: res => {
  //       wx.getFileSystemManager().readFile({
  //         filePath: res.tempFilePaths[0], //选择图片返回的相对路径
  //         encoding: 'base64',
  //         success: res => { //成功的回调
  //           // console.log('data:image/png;base64,' + res.data)
  //           wx.showLoading({
  //             title: '处理中...',
  //             mask: true,
  //           })
  //           wx.request({
  //             url: 'https://yun.dascomyun.cn/15_printapi/v2.0/convertPrintData',
  //             header: {
  //               'content-type': 'application/json',
  //               'File-Type': 'photo',
  //             },
  //             data: {
  //               'conver':res.data,
  //               "type": 'photo',
  //               'printdata': 'FZ',
  //               'instruction':'ZPL',
  //               'threshold':'178',
  //               'paperWidth':10.5,
  //               'concentration':2,
  //               'dpi': 203
  //             },
  //             method: "POST",
  //             success(res) {
  //               wx.hideLoading();
  //               console.log("success", res)//返回后台打印的数据
  //               console.log(res.data.data)
               
  //               const base64 = JSON.stringify([res.data.data]);
  //               const arrayBuffer = wx.base64ToArrayBuffer(base64)
  //               console.log(arrayBuffer)
  //               var arrayBufferT = new Uint8Array(arrayBuffer);
  //               console.log(arrayBufferT)
  //               that.setData({
  //                 buffer:arrayBufferT
  //               })
  //               /*向蓝牙发送数据*/   
  //               that.print(arrayBufferT)            
  //               // that.print(that.data.characteristicId, that.data.buffer, that.data.serviceUuid)

  //             },
  //             fail(res) {
  //               console.log("failed", res)
  //               wx.hideLoading();
  //               wx.showModal({
  //                 title: '提示',
  //                 content: '打印失败',
  //                 showCancel: false,
  //               })
  //             }

  //           });
  //         },
  //         fail(res) {
  //           console.log(res)
  //         }
  //       })
  //     },
  //     fail(res) {
  //       console.log("choose image failed:", res)
  //     }
  //   })
  // },
  printfByBle: function () {
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
            wx.downloadFile({
              url: res.data.data[1],
              success(res) {
                console.log(res)
                wx.getFileSystemManager().readFile({
                  filePath: res.tempFilePath,
                  encoding: 'base64',
                  success(res) {
                    console.log("读取文件成功", res)
                    /*向蓝牙发送数据*/
                    wx.request({
                      url: 'https://yun.dascomyun.cn/15_printapi/v2.0/convertPrintData',
                      data: {
                        "conver": res.data,//打印数据的base
                        "type": "pdf",
                        'printdata': 'FZ',
                        'instruction': 'ZPL',
                        'threshold': '178',
                        'paperWidth': 4.2,
                        'concentration': 2,
                        'dpi': 203
                      },
                      method: 'POST',
                      header: {
                        'content-type': 'application/json'
                      },
                      success(res) {
                        console.log("获取仿真数据成功", res)
                        const base64 = JSON.stringify([res.data.data]);
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
                      fail(err) {
                        console.log(err)
                      }
                    })
                  },
                  fail(err) {
                    console.log(err)
                  }
                })


              },
              fail(err) {
                console.log(err)
              }
            })

          } else {
            wx.showModal({
              title: '提示',
              content: '获取短信的PDF链接失败',
            })
          }
        },
        fail(err) {
          console.log(err)
        }
      })
    }
  },
 //获取蓝牙服务
  getBLEDeviceServices(deviceId) {
    var that = this;
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
            console.log(that._characteristicId)
            console.log(that._deviceId)
            console.log(that._serviceId)
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
      deviceId: that._deviceId,
      serviceId: that._serviceId,
      characteristicId: that._characteristicId,
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
    // console.log(remainData)   发送的数据
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
        characteristicId: "00008202-0000-1000-8000-00805F9B34FB" ,
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
        characteristicId: "00008202-0000-1000-8000-00805F9B34FB" ,
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

  /* 生命周期函数--监听页面加载
   */
  
  onLoad: function (options) {
    let that = this;
    wx.showLoading({
      title: '蓝牙连接中...',
      mask: true,
    })
    var btDevId = options.devId;
    console.log(btDevId)//蓝牙id
    that.setData({
      deviceName: options.devName,
      devId:btDevId
    })
    /*创建蓝牙连接 */
    console.log("创建蓝牙连接")
    wx.createBLEConnection({
      deviceId: btDevId,
      timeout: 3000,
      success: function (res) {
        console.log("蓝牙连接成功")
        wx.showLoading({
          title: '蓝牙连接成功',
          mask:true,
        })
        that.getBLEDeviceServices(btDevId)
        setTimeout(function () {
          wx.hideLoading()
        }, 2000)
        wx.stopBluetoothDevicesDiscovery();//连接成功后停止搜索
      },
      fail: function (err) {
          console.log(err)
        wx.hideLoading({

        });
        wx.showModal({
          title: '提示',
          content: "连接失败，请近距离操作设备",
          showCancel: false,
          success: function (res) {
            if (res.confirm) {
              wx.navigateBack({
                delta: 1
              })
            }
          }
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

  }
   
})