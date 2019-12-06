// pages/billlist/billlist.js
var util = require('../../utils/util.js');
var app = getApp();
var gbk = require('../../gbk.js');
Page({

  /**
   * 页面的初始数据
   */
  data: {
    billlist: [],
    needback:0,
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var that = this;
    that.setData({
      billlist: JSON.parse(options.list),
      needback: options.pageback,
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

  },
  removeItem: function (e) {
    var i = e.currentTarget.dataset.index;
    var list = this.data.billlist;
    var deletenum = list[i].str2
   
    list.splice(i, 1)
    this.setData({
      billlist: list
    })
    app.globalData.totalGoodsList = list;
    app.globalData.shoppingnum-=deletenum;
  },
  //打印
  printdingdan: function () {
    var that = this;
    var timenow = util.formatTime2(new Date());

    if (!app.globalData.connectState) {
      wx.showModal({
        title: '提示',
        content: '当前没有连接打印机，去连接',
        showCancel: false,
        success(res) {
          if (res.confirm) {
            wx.navigateBack({
              delta: that.data.needback
            })
          } else if (res.cancel) {
            console.log('用户点击取消')
          }
        }
        
      })
      return;
    }

    if (app.globalData.totalGoodsList.length == 0) {
      wx.showModal({
        title: '提示',
        content: '当前无可打印订单',
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

    billnumShow = billnumShow.substr(billnumShow.length - 5, 5)
    var strSend = "^PW600^FWN^LH0,0^MMT^A0N,30,100,E:SIMSUN.FNT^CWL,E:SIMSUN.FNT^SEE:GB18030.DAT^CI26" +
      "^FO190,50^A0,36,36^FDX X X X专卖店^FS" +
      "^FO200,100^A0,24,24^FD" + timenow + "^FS" +
      "^FO20,140^A0,30,30^FD收银员：刘丽芳^FS" +
      "^FO20,190^A0,30,30^FD单号:1111-" + billnumShow + "^FS" +
      "^FO100,240^A0,30,30^FD商品             数量     单价    金额^FS" +
      "^FO10,280^A0,12,12^FD=====================================================^FS";

    var dataitem = "";
    var yPos = 320;
    var price = 0
    var gList = app.globalData.totalGoodsList
    for (var i = 0; i < app.globalData.totalGoodsList.length; i++) {
      dataitem += ("^FO20," + yPos + "^A0,30,30^FD" + gList[i].str1 + "^FS" +
        "^FO300," + (yPos + 50) + "^AL,30,30^FD" + gList[i].str2 + "^FS" +
        "^FO400," + (yPos + 50) + "^AL,30,30^FD" + gList[i].str3 + "^FS" +
        "^FO500," + (yPos + 50) + "^AL,30,30^FD" + gList[i].str4 + "^FS"
      );
      yPos += 120;
      price += gList[i].str4;
    }

    strSend += dataitem;
    dataitem = "^FO10," + (yPos - 20) + "^A0,12,12^FD=====================================================^FS";
    yPos += 20;
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
    
    strSend = "^XA^LL" + yPos + strSend + "^XZ";

    console.log(strSend)
    /////////////////蓝牙打印//////////////////////
    setTimeout(function () {
      wx.hideLoading();
      wx.showLoading({
        title: '数据发送中',
        mask: true,
      })
      that.getBinaryArrayData(strSend, function (res) {
        that.ContinueSend('指令发送失败', res)
      })
    }, 3000);
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
        deviceId: app.globalData.devId,
        serviceId: app.globalData.serviceUuid,
        characteristicId: app.globalData.writeUuid,
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
        deviceId: app.globalData.devId,
        serviceId: app.globalData.serviceUuid,
        characteristicId: app.globalData.writeUuid,
        value: buffer,
        success: function (res) {
          console.log('打印成功')
          wx.hideLoading({
          });
          app.globalData.totalGoodsList = [];
          app.globalData.shoppingnum=0;
          that.setData({
            billlist: [],
          })

          wx.showModal({
            showCancel: false,
            title: '提示',
            content: "打印成功，继续开单",
            success(res) {
              if (res.confirm) {
                wx.navigateBack({
                  delta: 1
                })
              } else if (res.cancel) {
                console.log('用户点击取消')
              }
            }
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
})