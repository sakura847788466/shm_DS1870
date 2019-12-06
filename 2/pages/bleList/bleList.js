var app = getApp();
Page({
  data: {
    btDevices: [],
    config: true,
    timeId: "",
  },
  onLoad: function () {
    var that = this
    that.setData({
      btDevices: [],
      timeId: setTimeout(function () {
        console.log("执行定时器")
        if (that.data.btDevices.length == 1) {
          wx.hideLoading();
          wx.navigateTo({
            url: '/pages/cardBag/cardBag?devId=' + that.data.btDevices[0].devId + '&devName=' + that.data.btDevices[0].name,
          })
        } else if (that.data.btDevices.length == 0) {//1秒还没有搜到1个
          setTimeout(function () {//延长2秒搜索时长
            if (that.data.btDevices.length == 0) {
              wx.hideLoading();
              wx.showModal({
                title: '提示',
                content: '请确认周围云盒处于正常供电状态，并近距离操作云盒。',
                showCancel: false,
              })
            }
          }, 2000)
        }
      }, 1000)
    })
    wx.showLoading({
      title: '正在搜索设备',
      mask: true,
    })
  },

  onHide: function () {
    var that = this
    console.log("on hide")
    clearTimeout(that.data.timeId);
    wx.stopBluetoothDevicesDiscovery({
      success: function (res) {
        console.log(res)
      }
    })
  },

  onShow: function () {
    var that = this

    wx.openBluetoothAdapter({
      success: function (res) {
        console.log(res)
        wx.startBluetoothDevicesDiscovery({
          services: ["000000FF-0000-1000-8000-00805F9B34FB"],//"000000FF-0000-1000-8000-00805F9B34FB"得实含义的
          success: function (res) {//开始搜索成功
            console.log("###startBluetoothDevicesDiscovery###")
            console.log(res)
          },
          fail: function (res) {
            wx.showToast({
              title: '请先开启蓝牙',
              icon: 'none',
              duration: 1000
            })
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
        wx.hideLoading();
        wx.showModal({
          showCancel: false,
          title: '提示',
          content: res.errCode == 10001 ? "请先打开蓝牙开关，然后下拉刷新设备列表" : res.errMsg,
        });
        console.log(res);
      }
    })

    wx.onBluetoothDeviceFound(function (devices) {
      console.log(devices)
      var devArray = devices.devices;
      for (var i = 0; i < devArray.length; i++) {
        var rssi_level_img;
        if (devArray[i].RSSI > -40) {
          rssi_level_img = '/imgs/scan/5.png'
        }
        else if (devArray[i].RSSI > -50) {
          rssi_level_img = '/imgs/scan/4.png'
        }
        else if (devArray[i].RSSI > -60) {
          rssi_level_img = '/imgs/scan/3.png'
        }
        else if (devArray[i].RSSI > -70) {
          rssi_level_img = '/imgs/scan/2.png'
        }
        else {
          rssi_level_img = '/imgs/scan/1.png'
        }
        var newBtDevice = [{
          rssi: devArray[i].RSSI,
          name: devArray[i].name,
          devId: devArray[i].deviceId,
          img: rssi_level_img,
        }];
        that.data.btDevices = that.data.btDevices.concat(newBtDevice)
      }
      that.setData({
        btDevices: that.data.btDevices
      });
      wx.hideLoading();
      app.globalData.btDevices = that.data.btDevices
    })

  },

  onPullDownRefresh: function () {
    // 下拉清空记录，并重新搜索
    console.log('onPullDownRefresh')
    var that = this
    wx.stopPullDownRefresh()
    wx.showLoading({
      title: '正在刷新列表',
      mask: true,
    })
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
                  services: ["000000FF-0000-1000-8000-00805F9B34FB"],
                  success: function (res) {
                    console.log(res)
                  }
                })
              }
            })
          }
        })
      }
    })
  },
  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {
    var that = this;
    clearTimeout(that.data.timeId);
    wx.stopBluetoothDevicesDiscovery({
      success: function (res) {
        wx.closeBluetoothAdapter({
          success: function (res) {
            console.log(res)
          }
        })
      }
    })

  },
  connectBLEDevice: function () {       //连接低功耗蓝牙设备
    var that = this;
    var deviceId = '84:0D:8E:39:9D:E6';
    my.connectBLEDevice({
      deviceId: "84:0D:8E:39:9D:E6",
      success: (res) => {
        console.log("蓝牙连接成功");
        wx.navigateTo({
          url: '/pages/cardBag/cardBag',
        })
        my.hideLoading();
      },
      fail: (res) => { 
        console.log(res)
      }
    });
  },

});

