// pages/sailbill/sailbill.js
var app = getApp();
var gbk = require('../../gbk.js');
var util = require('../../utils/util.js');
Page({

  /**
   * 页面的初始数据
   */
  data: {
    norbangding:false,
    hadPrint:"DP-230L-B197",
    isPrinter: false,
    devId: "",
    serviceUuid: "49535343-FE7D-4AE5-8FA9-9FAFD205E455",
    notifyUuid: "49535343-1E4D-4BD9-BA61-23C647249616",
    writeUuid: "49535343-8841-43F4-A8D4-ECBE34729BB3",

    strnum: "0034BE735002FF00",
    connectState:false,

    showModalStatus: false,//显示遮罩
    isHidden: 0,
    animationData: {},//选择动画
    modelimage:"../../imgs/model/chukudan.png",
    printNum:0,

  },
  //绑定打印机/连接打印机/重连打印机
  bangding:function(){
    app.globalData.needconnect=false;

    wx.navigateTo({
      url: '/pages/blesearch/blesearch'
    })
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var that=this;
    // this.setData({
    //   strnum: options.deviceNum,
    // })
    app.globalData.bindedName = "";
    app.globalData.bindedMac = "";
    app.globalData.connectState = that.data.connectState;
  wx.showLoading({
    title: '加载中...',
    mask:true,
  })
    wx.getStorage({
      key: 'bleName',
      success(res) {//去连接
        var indexpos=res.data.indexOf("$$$")
        var shoundShow= res.data.slice(0, indexpos);
        var shoundMac = res.data.slice(indexpos+3);
        that.setData({
          norbangding: false,
          hadPrint: "已绑定：" + shoundShow,
          devId: shoundMac,
        })
        app.globalData.bindedName = shoundShow;
        app.globalData.bindedMac = shoundMac;
        //////////////////蓝牙操作部分////////////////////
        wx.onBLEConnectionStateChange(function (res) {//监听连接状态变化，主要是由连接到断开的状态
          console.log(`device ${res.deviceId} state has changed,now connected state is: ${res.connected}`)
          that.setData({
            connectState: res.connected
          })
          app.globalData.connectState = that.data.connectState;
          if (!res.connected) {
            that.setData({
              norbangding: false,
              hadPrint: "连接已断开，点击重连"
            })
          }
        })
        wx.onBluetoothAdapterStateChange(function (res) {
          console.log(`adapterState changed, now is`, res)
        })
        wx.onBLECharacteristicValueChange(function (res) {
          console.log("###onBLECharacteristicValueChange###", "ble返回" + res.value.byteLength + "个byte数据")
        })
        wx.openBluetoothAdapter({//初始化蓝牙
          success: function (ressuccess) {
            wx.createBLEConnection({//创建连接
              deviceId: that.data.devId,
              success: function (res) {
                wx.getBLEDeviceServices({
                  deviceId: that.data.devId,
                  success: function (res) {
                    console.log('device services:', res.services)
                    // 保存已连接设备的服务
                    for (var j = 0; j < res.services.length; ++j) {
                      if (res.services[j].uuid == that.data.serviceUuid) {
                        that.data.isPrinter = true;
                        break;
                      }
                    }

                    //$$$$$$$$$$$$$$$$$$获取特征值$$$$$$$$$$$$$$$$$$$$//
                    if (that.data.isPrinter) {
                      wx.getBLEDeviceCharacteristics({
                        deviceId: that.data.devId,
                        serviceId: that.data.serviceUuid,
                        success: function (res) {
                          console.log('device getBLEDeviceCharacteristics success:', res.characteristics)
                          for (var n = 0; n < res.characteristics.length; ++n) {
                            if (res.characteristics[n].properties.notify == true) {
                              console.log('start notify')
                              var nUUID = res.characteristics[n].uuid;
                              wx.notifyBLECharacteristicValueChange({
                                state: true, // 启用 notify 功能
                                deviceId: that.data.devId,
                                serviceId: that.data.serviceUuid,
                                characteristicId: nUUID,
                                success: function (res2) {
                                  console.log('notifyBLECharacteristicValueChange success', res2.errMsg)
                                  //已连接成功
                                  that.setData({
                                    connectState: true,
                                    hadPrint: "已连接：" + shoundShow+",点击更换",
                                    notifyUuid: nUUID
                                  })
                                  app.globalData.devId = that.data.devId;
                                  app.globalData.connectState = true;
                                  wx.setStorage({
                                    key: "bleName",
                                    data: shoundShow + "$$$" + shoundMac,
                                    success(res) {
                                      console.log("success", res)
                                    },
                                    fail(res) {
                                      console.log("fail", res)
                                    }
                                  })
                                  wx.hideLoading()
                                },
                                fail: function (res) {
                                  that.setData({
                                    hadPrint: "已绑定：" + shoundShow + ",点击连接",
                                  })
                                  wx.hideLoading()
                                  wx.showModal({
                                    title: '提示',
                                    content: '自动连接失败，请手动重连。',
                                    showCancel: false,
                                  })
                                }
                              })
                            } else if (res.characteristics[n].properties.write == true) {
                              console.log('device write Characteristics found', n)
                              console.log('write characteristic:', res.characteristics[n].uuid)
                              that.setData({
                                writeUuid: res.characteristics[n].uuid
                              })
                            }
                          }
                        },
                        fail: function (res) {
                          console.log('device getBLEDeviceCharacteristics fail', res)
                          that.setData({
                            hadPrint: "已绑定：" + shoundShow + ",点击连接",
                          })
                          wx.hideLoading()
                          wx.showModal({
                            title: '提示',
                            content: '自动连接失败，请手动重连。',
                            showCancel: false,
                          })
                        }
                      })
                    } else {
                      that.setData({
                        hadPrint: "已绑定：" + shoundShow + ",点击连接",
                      })
                      wx.hideLoading()
                      wx.showModal({
                        title: '提示',
                        content: '非法设备，请手动重连。',
                        showCancel: false,
                      })
                    }
                    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//

                  },
                  fail: function (res) {
                    that.setData({
                      hadPrint: "已绑定：" + shoundShow + ",点击连接",
                    })
                    wx.hideLoading({});
                    wx.showModal({
                      title: '提示',
                      content: "连接失败，请手动连接打印机",
                      showCancel: false,
                    })
                  }
                })
              },
              fail: function (res) {
                that.setData({
                  hadPrint: "已绑定：" + shoundShow + ",点击连接",
                })
                wx.hideLoading({});
                wx.showModal({
                  title: '提示',
                  content: res.errCode == 10001 ? "请先打开蓝牙开关" : "连接失败，请手动连接打印机",
                  showCancel: false,
                })
                console.log("creatConnection failed", res)
              }
            })
          },
          fail:function(resfail){//初始化蓝牙失败
            that.setData({
              hadPrint: "已绑定：" + shoundShow + ",点击连接",
            })
            wx.hideLoading({});
            wx.showModal({
              title: '提示',
              content: resfail.errCode == 10001 ? "请先打开蓝牙开关" : "初始化蓝牙失败",
              showCancel: false,
            })
            console.log("openBluetoothAdapter failed", resfail)
          }
        })
        /////////////////////////////////////////////
      },
      fail(res){//说明未绑定打印机
        wx.hideLoading();
        that.setData({
          norbangding: true,
          hadPrint: "暂未绑定打印机，点击添加"
        })
        app.globalData.bindedName = "";
        app.globalData.bindedMac = "";
      }
    })
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {
    console.log("onReady")
  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {
    var that=this;
    console.log("onShow")
    ////////////////用户点击了打印列表里面的某一个///////////
    if (app.globalData.needconnect){
      wx.showLoading({
        title: '连接中...',
        mask:true,
      })
      wx.getConnectedBluetoothDevices({
        services: ["49535343-FE7D-4AE5-8FA9-9FAFD205E455",],
        success(res) {
          var connectedDev = res.devices;
          console.log(connectedDev)
          if (connectedDev.length == 1 && connectedDev[0].name == app.globalData.bindedName){//当前已连接，无需再操作
            wx.hideLoading();
            ///////////////////做蓝牙连接操作/////////////////////////////////
          }else{
            var shoundShow = app.globalData.bindedName;
            var shoundMac = app.globalData.bindedMac;
            that.setData({
              hadPrint: "正在连接" + shoundShow,
              devId: shoundMac,
            })
            wx.onBLEConnectionStateChange(function (res) {//监听连接状态变化，主要是由连接到断开的状态
              console.log("onshow",`device ${res.deviceId} state has changed,now connected state is: ${res.connected}`)
              that.setData({
                connectState: res.connected
              })
              app.globalData.connectState = that.data.connectState;
              if (!res.connected) {
                that.setData({
                  norbangding: false,
                  hadPrint: "连接已断开，点击重连"
                })
              }
            })
            wx.onBluetoothAdapterStateChange(function (res) {
              console.log("onshow",`adapterState changed, now is`, res)
            })
            wx.onBLECharacteristicValueChange(function (res) {
              console.log("onshow","###onBLECharacteristicValueChange###", "ble返回" + res.value.byteLength + "个byte数据")
            })
            wx.openBluetoothAdapter({//初始化蓝牙
              success: function (ressuccess) {
                wx.createBLEConnection({//创建连接
                  deviceId: that.data.devId,
                  success: function (res) {
                    wx.getBLEDeviceServices({
                      deviceId: that.data.devId,
                      success: function (res) {
                        console.log("onshow",'device services:', res.services)
                        // 保存已连接设备的服务
                        for (var j = 0; j < res.services.length; ++j) {
                          if (res.services[j].uuid == that.data.serviceUuid) {
                            that.data.isPrinter = true;
                            break;
                          }
                        }

                        //$$$$$$$$$$$$$$$$$$获取特征值$$$$$$$$$$$$$$$$$$$$//
                        if (that.data.isPrinter) {
                          wx.getBLEDeviceCharacteristics({
                            deviceId: that.data.devId,
                            serviceId: that.data.serviceUuid,
                            success: function (res) {
                              console.log("onshow",'device getBLEDeviceCharacteristics success:', res.characteristics)
                              for (var n = 0; n < res.characteristics.length; ++n) {
                                if (res.characteristics[n].properties.notify == true) {
                                  console.log("onshow",'start notify')
                                  var nUUID = res.characteristics[n].uuid;
                                  wx.notifyBLECharacteristicValueChange({
                                    state: true, // 启用 notify 功能
                                    deviceId: that.data.devId,
                                    serviceId: that.data.serviceUuid,
                                    characteristicId: nUUID,
                                    success: function (res2) {
                                      console.log("onshow",'notifyBLECharacteristicValueChange success', res2.errMsg)
                                      //已连接成功
                                      that.setData({
                                        connectState: true, 
                                        hadPrint: "已连接：" + shoundShow + ",点击更换",
                                        notifyUuid: nUUID
                                      })
                                      app.globalData.devId = that.data.devId;
                                      app.globalData.connectState=true;
                                      wx.setStorage({
                                        key: "bleName",
                                        data: shoundShow + "$$$" + shoundMac,
                                        success(res) {
                                          console.log("success", res)
                                        },
                                        fail(res) {
                                          console.log("fail", res)
                                        }
                                      })
                                      wx.hideLoading()
                                    },
                                    fail: function (res) {
                                      that.setData({
                                        hadPrint: "已绑定：" + shoundShow + ",点击连接",
                                      })
                                      wx.hideLoading()
                                      wx.showModal({
                                        title: '提示',
                                        content: '自动连接失败，请手动重连。',
                                        showCancel: false,
                                      })
                                    }
                                  })
                                } else if (res.characteristics[n].properties.write == true) {
                                  console.log("onshow",'device write Characteristics found', n)
                                  console.log("onshow",'write characteristic:', res.characteristics[n].uuid)
                                  that.setData({
                                    writeUuid: res.characteristics[n].uuid
                                  })
                                }
                              }
                            },
                            fail: function (res) {
                              console.log("onshow",'device getBLEDeviceCharacteristics fail', res)
                              that.setData({
                                hadPrint: "已绑定：" + shoundShow + ",点击连接",
                              })
                              wx.hideLoading()
                              wx.showModal({
                                title: '提示',
                                content: '自动连接失败，请手动重连。',
                                showCancel: false,
                              })
                            }
                          })
                        } else {
                          that.setData({
                            hadPrint: "已绑定：" + shoundShow + ",点击连接",
                          })
                          wx.hideLoading()
                          wx.showModal({
                            title: '提示',
                            content: '非法设备，请手动重连。',
                            showCancel: false,
                          })
                        }
                        //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//

                      },
                      fail: function (res) {
                        that.setData({
                          hadPrint: "已绑定：" + shoundShow + ",点击连接",
                        })
                        wx.hideLoading({});
                        wx.showModal({
                          title: '提示',
                          content: "连接失败，请手动连接打印机",
                          showCancel: false,
                        })
                      }
                    })
                  },
                  fail: function (res) {
                    that.setData({
                      hadPrint: "已绑定：" + shoundShow + ",点击连接",
                    })
                    wx.hideLoading({});
                    wx.showModal({
                      title: '提示',
                      content: res.errCode == 10001 ? "请先打开蓝牙开关" : "连接失败，请手动连接打印机",
                      showCancel: false,
                    })
                    console.log("onshow","creatConnection failed", res)
                  }
                })
              },
              fail: function (resfail) {//初始化蓝牙失败
                that.setData({
                  hadPrint: "已绑定：" + shoundShow + ",点击连接",
                })
                wx.hideLoading({});
                wx.showModal({
                  title: '提示',
                  content: resfail.errCode == 10001 ? "请先打开蓝牙开关" : "初始化蓝牙失败",
                  showCancel: false,
                })
                console.log("onshow","openBluetoothAdapter failed", resfail)
              }
            })
          }
        },
        fail:function(res){
          console.log(res)
          wx.hideLoading();
          wx.showModal({
            title: '提示',
            content: '连接失败，请重试。',
            showCancel:false,
          })
        }
      })
    }
   

    // if(app.globalData.bindedName==""){
    //   console.log("don't need connect")
    // }else{
    //   console.log("need connect")
    // }
    //////////////////////////////////////////////////////
  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {
    console.log("onHide")
  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {
    var that=this;
    console.log("main page onUnload")
    wx.closeBLEConnection({
      deviceId: that.data.devId,
      success: function (res) {
        console.log(res)
      },
      complete:function(res){
        wx.closeBluetoothAdapter({
         success: function (res) {
           console.log(res)
         }
        })
      }
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
  onShareAppMessage: function (res) {
   
  },
  
  //开单
  kaidan: function () {
    app.globalData.needconnect = false;
    wx.navigateTo({
      url: '/pages/kaidan/kaidan'
    })
  },
  //查看
  lookdingdan: function () {
    app.globalData.needconnect = false;
    var that = this;
    wx.navigateTo({
      url: '/pages/billlist/billlist?pageback=1&list=' + JSON.stringify(app.globalData.totalGoodsList),
    })
  },
  //打印
  printdingdan:function() {
    var that=this;
    var timenow=util.formatTime2(new Date());

    if (!that.data.connectState){
      wx.showModal({
        title: '提示',
        content: '请先连接打印机...',
        showCancel: false,
      })
      return;
    }

    if (app.globalData.totalGoodsList.length == 0) {
      wx.showModal({
        title: '提示',
        content: '当前无订单',
        showCancel: false,
      })
      return;
    }
    wx.showLoading({
      title: '云端处理中',
      mask: true,
    })
    var billnumShow = "0000" + app.globalData.billNymber;
    app.globalData.billNymber+=1;
    billnumShow = billnumShow.substr(billnumShow.length-5,5)
    var strSend = "^PW600^FWN^LH0,0^MMT^A0N,30,100,E:SIMSUN.FNT^CWL,E:SIMSUN.FNT^SEE:GB18030.DAT^CI26" +
      "^FO190,50^A0,36,36^FDX X X X专卖店^FS" +
      "^FO200,100^A0,24,24^FD" + timenow + "^FS" +
      "^FO20,140^A0,30,30^FD收银员：刘丽芳^FS" +
      "^FO20,190^A0,30,30^FD单号:1111-" + billnumShow + "^FS" +
      "^FO100,240^A0,30,30^FD商品             数量     单价    金额^FS" +
      "^FO10,280^A0,12,12^FD=====================================================^FS";
     
    var dataitem = "";
    var yPos = 320;
    var price=0
    var gList = app.globalData.totalGoodsList
    for (var i = 0; i < app.globalData.totalGoodsList.length ; i++) {
      dataitem += ("^FO20," + yPos + "^A0,30,30^FD" + gList[i].str1 + "^FS" +
        "^FO300," + (yPos+50) + "^AL,30,30^FD" + gList[i].str2 + "^FS" +
        "^FO400," + (yPos+50) + "^AL,30,30^FD" + gList[i].str3 + "^FS" +
        "^FO500," + (yPos+50) + "^AL,30,30^FD" + gList[i].str4 + "^FS"
      );
      yPos += 120;
      price += gList[i].str4;
    }

    strSend += dataitem;
    dataitem = "^FO10," +( yPos-20 )+"^A0,12,12^FD=====================================================^FS";
    yPos+=20;
    strSend += dataitem;

    dataitem = "^FO20," + yPos + "^A0,30,30^FD应收总额:^FS";
    dataitem += "^FO495," + yPos + "^A0,32,32^FD" + price + "^FS";
    yPos += 60;
    strSend += dataitem;

    dataitem = "^FO20," + yPos + "^A0,30,30^FD现金：0      微信支付:" + price + "     支付宝：0^FS";
    yPos += 60;
    strSend += dataitem;

    dataitem = "^FO20," + yPos + "^A0,30,30^FD电话:0577-12345678^FS";
    yPos += 60;
    strSend += dataitem;

    dataitem = "^FO20," + yPos + "^A0,30,30^FD地址:广州市南云三路46号^FS";
    yPos += 60;
    strSend += dataitem;

    dataitem = "^FO210," + yPos + "^A0,20,20^FD****谢谢光临****^FS";
    yPos += 40;
    strSend += dataitem;

    dataitem = "^FO140," + yPos + "^A0,20,20^FD注：特价商品不退不换，谢谢合作^FS";
    yPos += 80;
    strSend += dataitem;
    // strSend += (
    //   "^FO10,10^GB860,0,1^FS" +
    //   "^FO10," +(yPos-10)+"^GB860,0,1^FS" +
    //   "^FO10,10^GB0," + (yPos - 20)+",1^FS" +
    //   "^FO870,10^GB0," + (yPos - 20) +",1^FS"
    // )
    
    strSend = "^XA^LL" + yPos + strSend+"^XZ";

///////////////////////////
//    strSend = "^XA^PW400^LL300^MMT^A@,30,50,E:SIMSUN.FNT^CWL,E:SIMSUN.FNT^SEE:GB2312.DAT^CI26^AL,48,48^FO10,64^FD测试12345678ABC^FS^XZ"
///////////////////////////

    console.log(strSend)
    /////////////////蓝牙打印//////////////////////
    setTimeout(function () {
      wx.hideLoading();
      wx.showLoading({
        title: '数据发送中',
        mask:true,
      })
      that.getBinaryArrayData(strSend, function (res) {
        that.ContinueSend('指令发送失败', res)
      })
    }, 3000);
    

    //调用接口云端打印
    // that.getBinaryArrayData(strSend, function (res) {

    //   const arrayBuffer = new Uint8Array(res)
    //   const base64 = wx.arrayBufferToBase64(arrayBuffer)
    //   //////////////发送打印///////////////////////////
    //   wx.request({
    //     url: 'https://yun.dascomyun.cn/15_printapi/v2.0/cloud_print',
    //     header: {
    //       'content-type': 'application/json' // 默认值
    //     },
    //     method: "POST",
    //     data: {
    //       "number": that.data.strnum,
    //       "data": base64
    //     },
    //     success(res) {
    //       console.log(res.data)
    //       wx.hideLoading();
    //       if (res.data.code == 0){
    //         wx.showModal({
    //           title: '提示',
    //           content: '数据发送成功',
    //           showCancel: false
    //         })
    //         app.globalData.totalGoodsList = [];
    //       }  
    //       else {
    //         wx.showModal({
    //           title: '提示',
    //           content: '数据发送失败：' + res.data.data,
    //           showCancel: false
    //         })
    //       }
    //     },
    //     fail(res) {
    //       console.log(res)
    //       wx.hideLoading();
    //       wx.showModal({
    //         title: '提示',
    //         content: '网络请求失败',
    //         showCancel: false
    //       })
    //     }
    //   })
    //   ////////////////////////////////////////////////
    // });

  },
  ContinueSend: function (strShow, remainData) {
    var that = this
    if (remainData.length > 20) {
      var buffer = new ArrayBuffer(20);
      var dataView = new Uint8Array(buffer);
      for (var i = 0; i < 20; i++) {
        dataView[i] = remainData[i];
      }
      var a = remainData.slice(20);
      console.log("###buffer###", dataView);
      wx.writeBLECharacteristicValue({
        deviceId: that.data.devId,
        serviceId: that.data.serviceUuid,
        characteristicId: that.data.writeUuid,
        value: buffer,
        success: function (res) {
          console.log('发送成功，继续发送')
          that.ContinueSend(strShow, a);
        },
        fail: function (res) {
          // fail
          console.log('发送失败', res)
          wx.hideLoading({
          });

          wx.showModal({
            showCancel: false,
            title: '提示',
            content: strShow,
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
        characteristicId: that.data.writeUuid,
        value: buffer,
        success: function (res) {
          console.log('打印成功')
          wx.hideLoading({
          });
          app.globalData.totalGoodsList = [];
          wx.showModal({
            showCancel: false,
            title: '提示',
            content: "打印成功",
          });
        },
        fail: function (res) {
          // fail
          console.log('发送失败' + res)
          wx.hideLoading({
          });

          wx.showModal({
            showCancel: false,
            title: '提示',
            content: strShow,
          });
        }
      })
    }
  },
  sizeOfGbk: function (str) {
    var total = 0,
      charCode,
      i,
      len;
    for (i = 0, len = str.length; i < len; i++) {
      charCode = str.charCodeAt(i);
      if (charCode <= 0xff) {
        total += 1;
      } else {
        total += 2;
      }
    }
    return total;
  },

  getCodeStr: function () {
    return gbk.codestr;
  },

  utf2gbOne: function (utfCode) {
    var codeStr = this.getCodeStr();
    var gbkCode;
    var utfStart;
    var gbkStart = 0;

    utfStart = new Number(codeStr.indexOf(utfCode.toLowerCase()));
    if (utfStart != -1) {
      gbkStart = utfStart - 5;
      gbkCode = codeStr.substring(gbkStart, gbkStart + 4);
    } else {
      gbkCode = "a1a1";
    }

    return gbkCode;
  },

  getBinaryArrayData: function (text, resultCallBack) {

    var buffer = new Array(this.sizeOfGbk(text));
    var indexDV = 0;
    for (var i = 0; i < text.length; ++i) {
      if (text.charCodeAt(i) > 0xff) {
        var utfStr = text.charCodeAt(i).toString(16);
        var gbkStr = this.utf2gbOne(utfStr);

        var highByte = parseInt(gbkStr.substring(0, 2), 16);
        var lowByte = parseInt(gbkStr.substring(2, 4), 16);
        buffer[indexDV++] = highByte;
        buffer[indexDV++] = lowByte;

      } else {
        buffer[indexDV++] = text.charCodeAt(i);
      }
    }
    resultCallBack(buffer);
  },
  showbill1:function(){
    var that=this;
    var animation = wx.createAnimation({//动画
      duration: 500,//动画持续时间
      timingFunction: 'linear',//动画的效果 动画从头到尾的速度是相同的
    })
    animation.translateY(0).step()//在Y轴偏移tx，单位px

    this.animation = animation
    that.setData({
      showModalStatus: true,//显示遮罩       
      animationData: animation.export(),
      modelimage: "../../imgs/model/chukudan.png",
      printNum:1,
    })
    that.setData({//把选中值，放入判断值中
      isHidden: 1,
    })
  },
  showbill2: function () {
    var that = this;
    var animation = wx.createAnimation({//动画
      duration: 500,//动画持续时间
      timingFunction: 'linear',//动画的效果 动画从头到尾的速度是相同的
    })
    animation.translateY(0).step()//在Y轴偏移tx，单位px

    this.animation = animation
    that.setData({
      showModalStatus: true,//显示遮罩       
      animationData: animation.export(),
      modelimage: "../../imgs/model/tuoyundan2.png",
      printNum:2,
    })
    that.setData({//把选中值，放入判断值中
      isHidden: 1,
    })
  },
  showbill3: function () {
    var that = this;
    var animation = wx.createAnimation({//动画
      duration: 500,//动画持续时间
      timingFunction: 'linear',//动画的效果 动画从头到尾的速度是相同的
    })
    animation.translateY(0).step()//在Y轴偏移tx，单位px

    this.animation = animation
    that.setData({
      showModalStatus: true,//显示遮罩       
      animationData: animation.export(),
      modelimage: "../../imgs/model/biaoqian.png",
      printNum: 3,
    })
    that.setData({//把选中值，放入判断值中
      isHidden: 1,
    })
  },
  showbill4: function () {
    var that = this;
    var animation = wx.createAnimation({//动画
      duration: 500,//动画持续时间
      timingFunction: 'linear',//动画的效果 动画从头到尾的速度是相同的
    })
    animation.translateY(0).step()//在Y轴偏移tx，单位px

    this.animation = animation
    that.setData({
      showModalStatus: true,//显示遮罩       
      animationData: animation.export(),
      modelimage: "../../imgs/model/shouju.png",
      printNum: 4,
    })
    that.setData({//把选中值，放入判断值中
      isHidden: 1,
    })
  },
  /**隐藏弹出显示 */
  hideModal: function (data) {
    var that = this;
    that.setData({//把选中值，放入判断值中
      showModalStatus: false,//显示遮罩       
      isHidden: 0,
    })
  },
  printmodel:function(){
    var that=this;
    var sendData="";
 
    if (!that.data.connectState) {
      wx.showModal({
        title: '提示',
        content: '请先连接打印机...',
        showCancel: false,
      })
      return;
    }
    wx.showLoading({
      title: "云端处理中",
    })
    if(that.data.printNum==1){
      var strSend = "^XA^LL1200^FWR" +
        "^FO110,80^GB320,0,1^FS" +
        "^FO110,280^GB320,0,1^FS" +
        "^FO110,480^GB320,0,1^FS" +
        "^FO110,680^GB320,0,1^FS" +
        "^FO110,880^GB320,0,1^FS" +
        "^FO110,1080^GB320,0,1^FS" +

        "^FO110,80^GB0,1000,1^FS" +
        "^FO150,80^GB0,1000,1^FS" +
        "^FO190,80^GB0,1000,1^FS" +
        "^FO230,80^GB0,1000,1^FS" +
        "^FO270,80^GB0,1000,1^FS" +
        "^FO310,80^GB0,1000,1^FS" +
        "^FO350,80^GB0,1000,1^FS" +
        "^FO390,80^GB0,1000,1^FS" +
        "^FO430,80^GB0,1000,1^FS" +

        "^FO50,120^A0,20,20^FD提货人：张三^FS" +
        "^FO50,420^A0,20,20^FD库管员：李四^FS" +
        "^FO500,500^A0,40,40^FD产品出库单^FS" +
        "^FO450,90^A0,24,24^FD编号:6578456345^FS" +
        "^FO450,850^A0,20,20^FD2019年07月20日^FS" +
        "^FO10,70^A0,20,20^FD注：本单一式两联，第一联仓库存根，第二联交营业部。^FS" +

        "^FO395,140^A0,24,24^FD型号^FS" +
        "^FO395,340^A0,24,24^FD品名^FS" +
        "^FO395,540^A0,24,24^FD数量^FS" +
        "^FO395,740^A0,24,24^FD包装^FS" +
        "^FO395,940^A0,24,24^FD备注^FS"
        ;
        var tempList=[]
      tempList.push({ str1: "WTNV0083", str2: "女士外套", str3: "200", str4: "件"})
      tempList.push({ str1: "LNSPORT058", str2: "男士运动鞋", str3: "300", str4: "双" })
      tempList.push({ str1: "KSDM133", str2: "宽松大码T恤", str3: "100", str4: "件" })
      tempList.push({ str1: "JSDYD892", str2: "男士腰带", str3: "240", str4: "条" })
      tempList.push({ str1: "JK08NS", str2: "男士夹克", str3: "150", str4: "件" })
      tempList.push({ str1: "YRFCK890", str2: "羽绒服", str3: "400", str4: "件" })
      tempList.push({ str1: "QBLYQ845", str2: "连衣裙", str3: "200", str4: "件" })
      var dataitem = "";
      var hPos = 355;
      for (var i = 0; i < tempList.length; i++) {
        dataitem += ("^FO" + hPos + ",90^A0,22,22^FD" + tempList[i].str1 + "^FS" +
          "^FO" + hPos + ",290^A0,22,22^FD" + tempList[i].str2 + "^FS" +
          "^FO" + hPos + ",490^A0,22,22^FD" + tempList[i].str3 + "^FS" +
          "^FO" + hPos + ",690^A0,22,22^FD" + tempList[i].str4 + "^FS"
        );
        hPos -= 40;
      }
      strSend += (dataitem + "^XZ");
      
      setTimeout(function () {
        wx.hideLoading();
        wx.showLoading({
          title: '数据发送中',
          mask: true,
        })
        that.getBinaryArrayData(strSend, function (res) {
          that.ContinueSend('数据发送失败', res)
        })
      }, 3000);
      
    } else if (that.data.printNum == 2) {
      strSend = "^XA^LL430^PW560^FWN" +
        "^FO10,30^GB540,0,1^FS" +
        "^FO10,105^GB540,0,1^FS" +
        "^FO10,145^GB540,0,1^FS" +
        "^FO10,185^GB540,0,1^FS" +
        "^FO10,400^GB540,0,1^FS" +

        "^FO10,30^GB0,370,1^FS" +
        "^FO120,30^GB0,370,1^FS" +
        "^FO550,30^GB0,370,1^FS" +
        "^FO290,30^GB0,70,1^FS" +
        "^FO15,55^A0,24,24^FD北京^FS" +
        "^FO150,55^A0,24,24^FD上海^FS" +
        "^FO302,35^BCN,45,Y,N,N^FD9800065^FS" +

        "^FO15,115^A0,24,24^FD收货方      刘丽13588889999^FS" +
        "^FO15,155^A0,24,24^FD发货方      王芳18166668888^FS" +

        "^FO25,250^A0,24,24^FD货物^FS" +
        "^FO25,280^A0,24,24^FD信息^FS" +
        "^FO125,195^A0,24,24^FD货物名称：服装、女鞋^FS" +
        "^FO125,235^A0,24,24^FD件数：100箱^FS" +
        "^FO125,275^A0,24,24^FD重量：大^FS" +
        "^FO125,315^A0,24,24^FD代收货款：8879.0元^FS" +
        "^FO125,355^A0,24,24^FD运费：到付380.0元^FS" +
        "^FO415,355^A0,20,20^FD制单人：张楠^FS" +
        "^XZ";
      setTimeout(function () {
        wx.hideLoading();
        wx.showLoading({
          title: '数据发送中',
          mask: true,
        })
        that.getBinaryArrayData(strSend, function (res) {
          that.ContinueSend('数据发送失败', res)
        })
      }, 2000);
    } else if (that.data.printNum == 3) {
      strSend = "^XA^LL430^PW400^FWN" +
        "^FO10,50^A0,24,24^FD品名：蛇纹侧拉链女士短靴^FS" +
        "^FO10,100^A0,24,24^FD货号：GMG8281^FS" +
        "^FO10,150^A0,24,24^FD颜色：黑色^FS" +
        "^FO10,200^A0,24,24^FD尺码：37^FS" +
        "^FO10,250^A0,24,24^FD执行标准：QB1002-2005质量标准^FS"+
        "^FO40,300^BCN,80,Y,N,N^FDGMG8281220C01^FS^XZ";

      setTimeout(function () {
        wx.hideLoading();
        wx.showLoading({
          title: '数据发送中',
          mask: true,
        })
        that.getBinaryArrayData(strSend, function (res) {
          that.ContinueSend('数据发送失败', res)
        })
      }, 1500);
      
    } else if (that.data.printNum == 4) {
      var strSend = "^XA^LL1200^FWR" +
        "^FO10,100^GB520,0,1^FS" +
        "^FO10,1100^GB520,0,1^FS" +
        "^FO10,100^GB0,1000,1^FS" +
        "^FO530,100^GB0,1000,1^FS" +

        "^FO430,750^GB0,70,1^FS" +
        "^FO430,860^GB0,70,1^FS" +
        "^FO430,970^GB0,70,1^FS" +

        "^FO370,360^GB0,720,1^FS" +
        "^FO310,360^GB0,720,1^FS" +
        "^FO250,360^GB0,720,1^FS" +
        "^FO190,880^GB0,180,1^FS" +

        "^FO130,450^GB0,140,1^FS" +
        "^FO130,680^GB0,140,1^FS" +
        "^FO130,910^GB0,140,1^FS" +

        "^FO470,540^A0,36,36^FD收    据^FS" +
        "^FO435,760^A0,24,24^FD2019  年    07     月     20    日^FS" +
        "^FO375,280^A0,24,24^FD今收到      XX信息股份有限公司^FS" +
        "^FO315,280^A0,24,24^FD交  来     200台DL-635 云打印机现金^FS" +
        "^FO255,280^A0,24,24^FD人民币（大写）^FS" +
        "^FO255,450^A0,36,36^FD壹佰万元整^FS" +
        "^FO195,890^A0,36,36^FD1,000,000元^FS" +

        "^FO135,280^A0,24,24^FD收据单位（章）                    收款人                     交款人^FS" +
        "^FO65,280^A0,24,24^FD电话：020-89856434             网址：www.dascomyun.com^FS" +
        "^FO280,160^BQ,2,4^FDhttp://weixin.qq.com/r/6Cj27mfEeToGrSON9336^FS"+
        "^FO240,165^A0,20,20^FD关注公众号^FS^FO210,170^A0,20,20^FD了解更多^FS" +
        "^FO400,120^A0,20,20^FD本^FS^FO375,120^A0,20,20^FD收^FS^FO350,120^A0,20,20^FD据^FS"+
        "^FO325,120^A0,20,20^FD未^FS^FO300,120^A0,20,20^FD加^FS^FO275,120^A0,20,20^FD盖^FS" +
        "^FO250,120^A0,20,20^FD公^FS^FO225,120^A0,20,20^FD司^FS^FO200,120^A0,20,20^FD财^FS" +
        "^FO175,120^A0,20,20^FD务^FS^FO150,120^A0,20,20^FD章^FS^FO125,120^A0,20,20^FD无^FS" +
        "^FO100,120^A0,20,20^FD效^FS" +
        "^XZ";
        //"^FPV,5^FO50,120^A0,24,24^FD本收据未加盖公司财务章无效^FS"+

      strSend ="^XA^LL600^FO190,80^BQ,2,6^FDhttps://yun.dascomyun.cn/dsyun/html/index.html#0004C27350027B00^FS^XZ"
      strSend += strSend;
        setTimeout(function () {
          wx.hideLoading();
          wx.showLoading({
            title: '数据发送中',
            mask: true,
          })
          that.getBinaryArrayData(strSend, function (res) {
            that.ContinueSend('数据发送失败', res)
          })
        }, 3000);
    }
  }
})