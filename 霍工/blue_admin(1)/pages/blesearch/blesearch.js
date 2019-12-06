var app = getApp();
Page({
  data: {
    btDevices: [
      {
        id: 1,
        rssi: -40,
        name: 'BT626',
        devId: '0',
        img: '/imgs/scan/2.png',
      }
    ],
  },
  onLoad: function (options) {
    var that = this
    for (var i = 0; i < that.data.btDevices.length; ++i) {
      that.data.btDevices.pop()
    }
    that.setData({
      btDevices: that.data.btDevices,
    });

    wx.onBluetoothDeviceFound(function (devices) {
      console.log("ble found", devices)
      wx.getBluetoothDevices({
        success: function (res) {

          var ln = 0;
          console.log(res, that.data.btDevices.length)
          if (that.data.btDevices.length != null)
            ln = that.data.btDevices.length
          for (var i = ln; i < res.devices.length; ++i) {
            //console.log(ln,that.data.btDevices.length,res.devices.length)
            var rssi_level_img;
            if (res.devices[i].RSSI > 0 || res.devices[i].name == '未知设备' || res.devices[i].name.indexOf("DP-") < 0) {
              continue;
            }
            if (res.devices[i].RSSI > -40) {
              rssi_level_img = '/imgs/scan/5.png'
            }
            else if (res.devices[i].RSSI > -50) {
              rssi_level_img = '/imgs/scan/4.png'
            }
            else if (res.devices[i].RSSI > -60) {
              rssi_level_img = '/imgs/scan/3.png'
            }
            else if (res.devices[i].RSSI > -70) {
              rssi_level_img = '/imgs/scan/2.png'
            }
            else {
              rssi_level_img = '/imgs/scan/1.png'
            }
            var newBtDevice = [{
              rssi: res.devices[i].RSSI,
              name: res.devices[i].name,
              devId: res.devices[i].deviceId,
              img: rssi_level_img,
            }];

            // dump redundant device
            for (var k = 0; k < that.data.btDevices.length; ++k) {
              //console.log('new ',res.devices[i].deviceId,'old',that.data.btDevices[k].devId)
              if (res.devices[i].deviceId == that.data.btDevices[k].devId) {
                //console.log('dump',k,that.data.btDevices[k].devId)
                that.data.btDevices.splice(k, 1);
                break;
              }
            }
            that.data.btDevices = that.data.btDevices.concat(newBtDevice)
          }
          that.setData({
            btDevices: that.data.btDevices
          });
        }
      })

    })

  },
  /**
     * 生命周期函数--监听页面卸载
     */
  onUnload: function () {
    console.log("page search onUnload")
    wx.stopBluetoothDevicesDiscovery({
    })
  },
  onHide: function () {
    var that = this
    wx.stopBluetoothDevicesDiscovery({
      success: function (res) {
        console.log(res)
      }
    })
  },

  onShow: function () {
    var that=this;
    wx.openBluetoothAdapter({
      success: function (res) {
        console.log(res)
        wx.startBluetoothDevicesDiscovery({
          //         services:["00FF"],
          success: function (res) {//开始搜索成功
            console.log("###startBluetoothDevicesDiscovery###")
            console.log(res)
          },
          fail: function (res) {
            wx.showModal({
              showCancel: false,
              title: '提示',
              content: "搜索蓝牙失败" + res.errMsg,
            });
            console.log(res);
            wx.stopBluetoothDevicesDiscovery({
              complete(res) {
                console.log(res)
              }
            })
          }
        })
      },
      fail: function (res) {
        wx.showModal({
          showCancel: false,
          title: '提示',
          content: res.errCode == 10001 ? "请先打开蓝牙开关" : res.errMsg,
        });
        console.log(res);
      }
    })
  },

  onPullDownRefresh: function () {
    // 下拉清空记录，并重新搜索
    console.log('onPullDownRefresh')
    var that = this
    wx.stopPullDownRefresh()
    wx.stopBluetoothDevicesDiscovery({
      success: function (res) {
        console.log(res)
       wx.closeBluetoothAdapter({
         success: function (res) {
           console.log(res)
            var num = that.data.btDevices.length
            that.data.btDevices.splice(0, num)
            that.setData({
              btDevices: that.data.btDevices
            });
            wx.openBluetoothAdapter({
              success: function (res) {
                console.log(res)
                wx.startBluetoothDevicesDiscovery({
                  //services: ['00FF'],
                  success: function (res) {
                    console.log(res)
                  },
                  fail: function (res) {
                    console.log(res);
                  }
                })
              },
              fail:function(openadapterRes){
                console.log(openadapterRes);
              }
            })
         }
      })
      },
      fail:function(res){
          console.log(res);
        wx.showModal({
          showCancel: false,
          title: '提示',
          content: res.errCode == 10001 ? "请先打开蓝牙开关" : res.errMsg,
        });
      }
    })
  },
  chooseBle:function(res){
    console.log(res.currentTarget.dataset.name)
    console.log(res.currentTarget.dataset.id)
    app.globalData.bindedName = res.currentTarget.dataset.name;
    app.globalData.bindedMac = res.currentTarget.dataset.id;
    app.globalData.needconnect = true;
   
    wx.navigateBack({
      delta: 1
    })
  }

});
