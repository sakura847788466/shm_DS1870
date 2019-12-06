var app = getApp();
var gbk = require('../../gbk.js');
var util = require('../../utils/util.js');
// page/print/print.js
Page({
  /**
   * 页面的初始数据
   */
  data: {
    devtext:"设备号：",
    strnum: "0034BE735002FF00",
    strdanhao: "123456789",
    tihuoname: "张三",
    kuguanyuan: "李四",
    xinghao: "DP-230L",
    goodName: "便携式打印机",
    amount: "21",
    baozhuang: "箱",
    itemList:[],
  //////////////////////////////////////////////
    printTypeNum:1,//2-BLE打印，1-云打印
    closed: false,
    isPrinter:false,
    devId: "",
    serviceUuid:"49535343-FE7D-4AE5-8FA9-9FAFD205E455",
    notifyUuid: "49535343-1E4D-4BD9-BA61-23C647249616",
    writeUuid:  "49535343-8841-43F4-A8D4-ECBE34729BB3",
  //////////////////////////////////////////////
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var that=this;
    var typenum = options.devtype;
    if (typenum==1){
      this.setData({
        printTypeNum:1,
        devtext: "设备号：",
        strnum: options.deviceNum,
      })
    }else{
      this.setData({
        printTypeNum:2,
        devtext:"设备名：",
        strnum: options.devName,
        devId: options.devId,
      })
      wx.showLoading({
        title: '连接中...',
        mask:true,
      })
      wx.onBLEConnectionStateChange(function (res) {
        console.log(`device ${res.deviceId} state has changed, connected: ${res.connected}`)
        if ((!res.connected) && (!that.data.closed)) {
          wx.showModal({
            title: '提示',
            content: '连接已断开',
            showCancel: false,
            success(res) {
              if (res.confirm) {
                wx.navigateBack({
                  delta: 1
                })
              }
            }
          })
        }
      })
      wx.onBluetoothAdapterStateChange(function (res) {
        console.log(`adapterState changed, now is`, res)
      })
      wx.onBLECharacteristicValueChange(function (res) {
        console.log("###onBLECharacteristicValueChange###", "ble返回" + res.value.byteLength + "个byte数据")
      })
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
                  that.data.isPrinter=true;
                  break;
                }
              }
              
              ///////////////////////获取特征值//////////////////////////
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
                              devtext:"已连接：",
                              notifyUuid: nUUID
                            })
                            wx.hideLoading()
                          },
                          fail: function (res) {
                            wx.showModal({
                              title: '提示',
                              content: '非法设备！',
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
                    wx.showModal({
                      title: '提示',
                      content: '非法设备！',
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
              } else {
                wx.showModal({
                  title: '提示',
                  content: '非法设备！',
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

              //////////////////////////////////////////////////////

            },
            fail:function(res){
              wx.hideLoading({

              });
              wx.showModal({
                title: '提示',
                content: res.errMsg,
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
        fail: function (res) {
          wx.hideLoading({

          });
          wx.showModal({
            title: '提示',
            content: res.errMsg,
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
    }
   
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
    var that=this;
    that.setData({
      itemList: app.globalData.totalList,
    })
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
    var that = this;
    if (that.data.printTypeNum==2){
      wx.closeBLEConnection({
        deviceId: that.data.devId,
        success: function (res) {
          console.log(res)
        }
      })
      that.data.closed = true;
    }
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

//编号
  mbianhao: function (e) {
    this.setData({
      strdanhao : e.detail.value
    })
  },
  //提货人
  mtihuo: function (e) {
    this.setData({
      tihuoname : e.detail.value
    })
  },
  //库管员
  mkuguan: function (e) {
    this.setData({
      kuguanyuan : e.detail.value
    })
  },
  //型号
  mxinghao: function (e) {
    this.setData({
      xinghao : e.detail.value
    })
  },
  //品名
  mgoodname: function (e) {
    this.setData({
      goodName : e.detail.value
    })
  },
  //数量
  mAmount: function (e) {
    this.setData({
      amount: e.detail.value
    })
  },
  //包装
  mbaozhuang: function (e) {
    this.setData({
      baozhuang : e.detail.value
    })
  },
 
  addItem: function (e) {
    var that=this;
    that.data.itemList.push({
      str1: that.data.xinghao, 
      str2: that.data.goodName, 
      str3: that.data.amount, 
      str4: that.data.baozhuang})
    app.globalData.totalList = that.data.itemList;
    wx.showModal({
      title: '提示',
      content: '成功添加一条数据',
      showCancel:false,
      success:function(res){
        console.log(res)
      },
      fail:function(res){
        console.log(res)
      }
    })
  },

  yulandata:function(e){
    var that = this;
    wx.navigateTo({
      url: '../itemlist/itemlist?list=' + JSON.stringify(app.globalData.totalList),
    })
  },

  printDemo:function(){
    var that=this;
    var timeArray = util.formatTime(new Date());
    var time = timeArray[0] + " 年 " + timeArray[1] + " 月 " + timeArray[2] + " 日"

    if(app.globalData.totalList.length==0){
      wx.showModal({
        title: '提示',
        content: '请添加出库产品',
        showCancel:false,
      })
      return;
    }
    wx.showLoading({
      title: '处理中...',
      mask: true,
    })
    var strSend ="^XA^LL1200^FWR"+
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

      "^FO50,120^A0,20,20^FD提货人：" + that.data.tihuoname+"^FS" +
      "^FO50,420^A0,20,20^FD库管员：" + that.data.kuguanyuan + "^FS" +
      "^FO500,500^A0,40,40^FD产品出库单^FS" +
      "^FO450,90^A0,24,24^FD编号:" + that.data.strdanhao + "^FS" +
      "^FO450,850^A0,20,20^FD" + time + "^FS"+
      "^FO10,70^A0,20,20^FD注：本单一式两联，第一联仓库存根，第二联交营业部。^FS" +

      "^FO395,140^A0,24,24^FD型号^FS" +
      "^FO395,340^A0,24,24^FD品名^FS" +
      "^FO395,540^A0,24,24^FD数量^FS" +
      "^FO395,740^A0,24,24^FD包装^FS" +
      "^FO395,940^A0,24,24^FD备注^FS" 
    ;
    var dataitem="";
    var hPos=355;
    for (var i = 0; i < app.globalData.totalList.length && i<7;i++){
      dataitem += ("^FO" + hPos + ",90^A0,22,22^FD" + that.data.itemList[i].str1+"^FS" +
        "^FO" + hPos + ",290^A0,22,22^FD" + that.data.itemList[i].str2 + "^FS" +
        "^FO" + hPos + ",490^A0,22,22^FD" + that.data.itemList[i].str3 + "^FS" +
        "^FO" + hPos + ",690^A0,22,22^FD" + that.data.itemList[i].str4 + "^FS"
        );
      hPos-=40;
    }
    strSend += (dataitem+"^XZ");
    strSend += strSend;
   // strSend = "^XA^PW800~SD30^LH0,0^FO200,100,0^BQN,2,5,L^FH\\^FDMA,http://yun.dascomyun.cn/dsyun/html/index.html#000BBF7350021C00^FS^XZ";
    if(that.data.printTypeNum==1){
      that.getBinaryArrayData(strSend, function (res) {
            
        const arrayBuffer = new Uint8Array(res)
        const base64 = wx.arrayBufferToBase64(arrayBuffer)
        //////////////发送打印///////////////////////////
        wx.request({
          url: 'https://yun.dascomyun.cn/15_printapi/v2.0/cloud_print',
          header: {
            'content-type': 'application/json' // 默认值
          },
          method:"POST",
          data:{
            "number": that.data.strnum,
            "data": base64
          },
          success(res) {
            console.log(res.data)
            wx.hideLoading();
            if (res.data.code == 0)
              wx.showModal({
                title: '提示',
                content: '数据发送成功',
                showCancel: false
              })
            else {
              wx.showModal({
                title: '提示',
                content: '数据发送失败：' + res.data.data,
                showCancel: false
              })
            }
          },
          fail(res){
            console.log(res)
            wx.hideLoading();
            wx.showModal({
              title: '提示',
              content: '网络请求失败',
              showCancel: false
            })
          }
        })
        ////////////////////////////////////////////////
      });
    }else{
      that.getBinaryArrayData(strSend, function (res) {
        that.ContinueSend('指令发送失败', res)
      })
    }
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
          console.log('发送成功')
          wx.hideLoading({
          });

          wx.showModal({
            showCancel: false,
            title: '提示',
            content: "发送成功",
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
  DS1100print:function(){
    var that = this;
    var timeArray = util.formatTime(new Date());
    var time = timeArray[0] + " 年 " + timeArray[1] + " 月 " + timeArray[2] + " 日";
    if (app.globalData.totalList.length == 0) {
      wx.showModal({
        title: '提示',
        content: '请添加出库产品',
        showCancel: false,
        success:function(res){
          console.log(res)
        },
        fail:function(res){
          console.log(res)
        }
      })
      return;
    }
    wx.showLoading({
      title: '处理中...',
      mask: true,
    })
    //2,10,
    var strSend = "                                        产品出库单\n"+
      "编号：" + that.data.strdanhao + "                                                             " + time+"\n"+
      "┌─────────┬─────────┬─────────┬─────────┬─────────┐\n"+
      "│       型号       │       品名       │       数量       │       包装       │       备注       │\n";

      var temp="";
      var needspace=0;
      for (var i = 0; i < app.globalData.totalList.length && i < 7; i++) {

        strSend +="├─────────┼─────────┼─────────┼─────────┼─────────┤\n"

        needspace=18-that.sizeOfGbk(that.data.itemList[i].str1)
        temp = that.data.itemList[i].str1;
        for (var j = 0; j < needspace;j++){
          temp+=" ";
        }
        strSend +=("│"+temp);
        
        needspace = 18 - that.sizeOfGbk(that.data.itemList[i].str2)
        temp = that.data.itemList[i].str2;
        for (var j = 0; j < needspace; j++) {
          temp += " ";
        }
        strSend += ("│" + temp);

        needspace = 18 - that.sizeOfGbk(that.data.itemList[i].str3)
        temp = that.data.itemList[i].str3;
        for (var j = 0; j < needspace; j++) {
          temp += " ";
        }
        strSend += ("│" + temp);
   
        needspace = 18 - that.sizeOfGbk(that.data.itemList[i].str4)
        temp = that.data.itemList[i].str4;
        for (var j = 0; j < needspace; j++) {
          temp += " ";
        }
        strSend += ("│" + temp +"│                  │\n");
    };

    strSend += "└─────────┴─────────┴─────────┴─────────┴─────────┘\n"+
      "  提货人：" + that.data.tihuoname + "                库管员：" + that.data.kuguanyuan+"\n"+
      "注：本单一式两联，第一联仓库存储，第二联交营业部。\n"


    that.getBinaryArrayData(strSend, function (res) {
      console.log(res)

      res=res.concat([0xD,0xA,0xC])

      const arrayBuffer = new Uint8Array(res)
      const base64 = wx.arrayBufferToBase64(arrayBuffer)
      //////////////发送打印///////////////////////////
      wx.request({
        url: 'https://yun.dascomyun.cn/15_printapi/v2.0/cloud_print', 
        header: {
          'content-type': 'application/json' // 默认值
        },
        method: "POST",
        data: {
          "number": that.data.strnum,
          "data": base64
        },
        success(res) {
          console.log(res.data)
          wx.hideLoading();
          if (res.data.code == 0)
            wx.showModal({
              title: '提示',
              content: '数据发送成功',
              showCancel: false
            })
          else {
            wx.showModal({
              title: '提示',
              content: '数据发送失败：' + res.data.data,
              showCancel: false
            })
          }
        },
        fail(res) {
          console.log(res)
          wx.hideLoading();
          wx.showModal({
            title: '提示',
            content: '网络请求失败',
            showCancel: false
          })
        }
      })
      ////////////////////////////////////////////////
    });
  }
})