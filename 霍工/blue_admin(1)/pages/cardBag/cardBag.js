// pages/cardBag/cardBag.js
const app =getApp();


Page({

  /**
   * 页面的初始数据
   */
  data: {
    bannerList: ["../../imgs/banner/50_20190916001.png", "../../imgs/banner/50_20190916002.png","../../imgs/banner/50_20190916003.png"],
    icon: '',
    userifo:[],
    showview:false,
    textValue:[],
    color:"",
    text:"请输入短信链接",
    status:"",//打印机状态
    accessToken:"",//用户token,
    printIndex: 1,
    purl:'',
    strnum: "0034BE735002FF00",
    linkList:'',
    printfStatus:false,//设备状态
    errMesg:true,//错误提示

    startT: "",
    devId:"84:0D:8E:39:99:C2",
    serviceUuid: "000082FF-0000-1000-8000-00805F9B34FB",
    flagUuid:"00008201-0000-1000-8000-00805F9B34FB",
    printUuid: "00008202-0000-1000-8000-00805F9B34FB",
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
        text: "请输入短信链接",
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
        title: 'loading...',
      })
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
            showview: false,
          })
          wx.hideLoading();
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
  //点击卡包打印
  cardClick: function () {
    var that = this;
    if (!that.data.printfStatus){
      wx.showModal({
        title: '提示',
        content: '当前没有连接设备,请连接设备后重试。',
        showCancel: true,
        cancelText: "取消",
        confirmText: "立即连接",
        success: function (res) {
          if (res.confirm) {
            wx.createBLEConnection({//创建连接
              deviceId: that.data.devId,
              timeout: 5000,
              success: function (res) {

                wx.getBLEDeviceServices({
                  // 这里的 devId 需要在 getBluetoothDevices 或 onBluetoothDeviceFound 接口中获取
                  deviceId: that.data.devId,
                  success: function (res) {
                    let hasDasService = false;
                    console.log('device services:', res.services)
                    // 保存已连接设备的服务
                    for (var j = 0; j < res.services.length; ++j) {
                      if (res.services[j].uuid == that.data.serviceUuid) {
                        hasDasService = true;
                      }
                    }

                    ///////////////////////获取特征值//////////////////////////
                    if (hasDasService) {//含有得实定义的服务UUID
                      wx.getBLEDeviceCharacteristics({
                        deviceId: that.data.devId,
                        serviceId: that.data.serviceUuid,
                        success: function (res) {
                          console.log("连接成功")
                          that.setData({
                            printfStatus: true,
                          })
                        },
                        fail: function (res) {
                          console.log('device getBLEDeviceCharacteristics fail', res)
                        }
                      })
                    } else {
                      wx.showModal({
                        title: '提示',
                        content: '连接失败，请查验设备状态！',
                        showCancel: false,
                      })
                    }
                  }
                })
              },
              fail: function (res) {
                console.log(res);
                wx.hideLoading({

                });
                wx.showModal({
                  title: '提示',
                  content: "连接失败",
                  showCancel: false,
                })
              }
            })
          }
        }
      })
    }else
      wx.chooseInvoice({
        success: function (res) {
          console.log(res)
          console.log(JSON.parse(res.invoiceInfo))

          if (JSON.parse(res.invoiceInfo).length == 0) {
            console.log("没有选择任何发票")
            wx.showModal({
              title: '提示',
              content: '没有选择任何发票',
              showCancel:false,
            })
          } else {
            wx.showLoading({
              title: '处理中...',
              mask:true,
            })
            wx.request({
              url: 'https://test.dascomyun.cn/wx/small/getcardInfo',
              data: JSON.parse(res.invoiceInfo),
              method: "POST",
              success(res) {
                console.log(res)
                if (res.statusCode!=200){
                  wx.hideLoading();
                  wx.showModal({
                    title: '提示',
                    content: '提取发票信息失败,请重试',
                    showCancel:false,
                  })
                  return;
                }
                let pdfirl = JSON.parse(res.data[0]).user_info.pdf_url;
                console.log('success', pdfirl )
                //console.log(res)
                // wx.downloadFile({
                //   url: pdfirl,
                //   success(res) {
                 //   if (res.statusCode === 200) {
                 //     const FileSystemManager = wx.getFileSystemManager()
                      // FileSystemManager.readFile({ //读文件
                      //   filePath: res.tempFilePath,
                      //   encoding: 'base64',
                      //   success(res) {
                          // console.log(res.data)
                          wx.request({
                            url: 'https://test.dascomyun.cn/203_30011/small/simulation',
                            header: {
                              'content-type': 'application/json',
                            },
                            method: "POST",
                            data: {
                              "url": pdfirl,
                              "simulationType": "ZPL",
                              "threshold":178,
                              "dpi": 203, 
                              "concentration":16,
                              "paperWidth": 4.2,
                            },
                            
                            success(res) {
                              //console.log("success", res)
                              if (res.data.code == 0) {//获取到打印数据的base64
                                wx.hideLoading();
                                wx.showLoading({
                                  title: '正在传输数据',
                                  mask:false,
                                })
                                var curtime = new Date();
                                var starttime = curtime.getHours() + ":" + curtime.getMinutes() + ":" + curtime.getSeconds();
                                that.setData({
                                  startT: starttime,
                                })
                                const arrayBuffer = wx.base64ToArrayBuffer(res.data.data)
                                var sendData = Array.prototype.slice.call(new Uint8Array(arrayBuffer));
                                //console.log(sendData)
                                let indexTemp = sendData.length;
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
                              
                                wx.writeBLECharacteristicValue({
                                  deviceId: that.data.devId,
                                  serviceId: that.data.serviceUuid,
                                  characteristicId: that.data.flagUuid,
                                  value: buffer,
                                  success: function (res) {
                                    console.log('使能成功，发打印数据')
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
                                      content: "打印失败：传输数据失败",
                                      success: function (res) {

                                      }
                                    });
                                  }
                                })
                              } else {
                                wx.hideLoading({
                                });
                                wx.showModal({
                                  title: '提示',
                                  content: '打印失败：' + res.data.data,
                                  showCancel: false,
                                })
                              }

                            },
                            fail(res) {
                              console.log("failed", res)
                              wx.hideLoading({
                              });
                              wx.showModal({
                                title: '提示',
                                content: '打印失败：请求数据失败',
                                showCancel: false,
                              })
                            }

                          });
                        // },
                        // fail(res){
                        //   console.log(res)
                        //   wx.hideLoading();
                        //   wx.showModal({
                        //     title: '提示',
                        //     content: '获取数据失败,请重试3',
                        //     showCancel: false,
                        //   })
                        // }
                      // })
                      
                      
                    // }else{
                    //   console.log(res)
                    //   wx.hideLoading();
                    //   wx.showModal({
                    //     title: '提示',
                    //     content: '获取数据失败,请重试1',
                    //     showCancel: false,
                    //   })
                    // }
                  //},
                  // fail(res){
                  //   console.log(res)
                  //   wx.hideLoading();
                  //   wx.showModal({
                  //     title: '提示',
                  //     content: '获取数据失败:' + res.errMsg,
                  //     showCancel: false,
                  //   })
                  // }
                //})
              },
              fail(res) {
                console.log('fail', res)
                wx.hideLoading();
                wx.showModal({
                  title: '提示',
                  content: '获取数据失败,请重试',
                  showCancel: false,
                })
              }

            })
          }

        },
        fail: function (err) {
          console.log(err)
        }
      })
  },
  //选择本地图片进行打印
  printimage: function () {
    var that = this;
    // wx.openDocument({
    //   filePath: '',
    // })
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
 //web-view测试
  towabview:function(){
    wx.navigateTo({
      url: '../file_elcet/file_elcet',
    })
  },
 istrue:function(){
   let that = this;
   wx.request({
     url: 'https://yun.dascomyun.cn/15_printapi/v2.0/CheckPrinter/' + that.data.strnum,
     method: "GET",
     success(res) {
       if (res.data.data.main == "离线") {
         that.setData({
           errMesg: true  //false离线显示 ，true在线隐藏
         })
       } else if (res.data.data.main == "正常") {
         that.setData({
           errMesg: true
         })
       }
     },
     fail(res) {
       console.log(res)
     }
   })
   that.setData({
     errMesg:!that.data.errMesg
   })
 },
  
    
  onLoad:function(options){
    var that=this;
    var btDevId = options.devId;
    that.setData({
      devId: btDevId,
      //strnum: decodeURIComponent(options.devName),
      strnum:options.devNum,
    })
    wx.openBluetoothAdapter({
      success: function (res) {
        wx.createBLEConnection({//创建连接
          deviceId: that.data.devId,
          timeout: 3000,
          success: function (res) {
           
            wx.getBLEDeviceServices({
              // 这里的 devId 需要在 getBluetoothDevices 或 onBluetoothDeviceFound 接口中获取
              deviceId: that.data.devId,
              success: function (res) {
                let hasDasService = false;
                console.log('device services:', res.services)
                // 保存已连接设备的服务
                for (var j = 0; j < res.services.length; ++j) {
                  if (res.services[j].uuid == that.data.serviceUuid) {
                    hasDasService = true;
                  }
                }

                ///////////////////////获取特征值//////////////////////////
                if (hasDasService) {//含有得实定义的服务UUID
                  wx.getBLEDeviceCharacteristics({
                    deviceId: that.data.devId,
                    serviceId: that.data.serviceUuid,
                    success: function (res) {
                      console.log('getBLEDeviceCharacteristics success:', res.characteristics)
                      console.log("连接成功")
                      that.setData({
                        printfStatus:true,
                      })
                    },
                    fail: function (res) {
                      console.log('device getBLEDeviceCharacteristics fail', res)
                    }
                  })
                } else {
                  wx.showModal({
                    title: '提示',
                    content: '非法设备！',
                    showCancel: false,
                  })
                }
              }
            })
          },
          fail: function (res) {
            console.log(res);
            wx.hideLoading({

            });
            wx.showModal({
              title: '提示',
              content: "连接失败",
              showCancel: false,
            })
          }
        })
      },
      fail: function (res) {
        wx.showModal({
          showCancel: false,
          title: '提示',
          content: res.errCode == 10001 ? "请先打开蓝牙开关，然后下拉刷新设备列表" : res.errMsg,
        });
        console.log(res);
      }
    })
    wx.onBLEConnectionStateChange(function (res) {
      that.setData({
        printfStatus: res.connected,
      })
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
    // const t = setInterval(()=>{
    //   let that = this;
    //   wx.request({
    //     url: 'https://yun.dascomyun.cn/15_printapi/v2.0/CheckPrinter/' + that.data.strnum,
    //     method: "GET",
    //     success(res) {
    //       if (res.data.data.main == "离线") {
    //         that.setData({
    //           printfStatus: false
    //         })
    //       } else if (res.data.data.main == "正常") {
    //         that.setData({
    //           printfStatus: true`  
    //         })
    //         clearInterval(t)
    //       }
    //     },
    //     fail(res) {
    //       console.log(res)
    //     }
    //   })
    // },5000)
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
    var that=this;
    wx.closeBLEConnection({
      deviceId: that.data.devId,
      success: function (res) {
        console.log(res)
      }
    })
    that.setData({
      printfStatus:false,
    })
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
        deviceId: that.data.devId,
        serviceId: that.data.serviceUuid,
        characteristicId: that.data.printUuid,
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
            content: "发送打印数据失败，请重试...",
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
        deviceId: that.data.devId,
        serviceId: that.data.serviceUuid,
        characteristicId: that.data.printUuid,
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
            content: '发送完成，等待打印\n开始时间:' + that.data.startT + "\n结束时间:" + endtime,
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
   
})