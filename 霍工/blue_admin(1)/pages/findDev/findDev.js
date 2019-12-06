var app = getApp();
Page({
	data: {
		btDevices: [],
    config: true,
    timeId:"",
    btopened:false,
	},
	onLoad: function () {
		var that = this
    that.setData({
      btDevices: [],
      timeId: setTimeout(function () {
        console.log("执行定时器")
        if (that.data.btDevices.length==1){
          wx.hideLoading();
          wx.navigateTo({
            url: '/pages/cardBag/cardBag?devId=' + that.data.btDevices[0].devId + '&devName=' + encodeURIComponent(that.data.btDevices[0].name) + "&devNum=" + that.data.btDevices[0].snNumber,
          })
        } else if (that.data.btDevices.length == 0){//1秒还没有搜到1个
          setTimeout(function () {//延长2秒搜索时长
            if (that.data.btDevices.length == 0 && that.data.btopened) {
              wx.hideLoading();
              wx.stopBluetoothDevicesDiscovery({
                success: function (res) {
                  console.log(res)
                }
              })
              wx.showModal({
                title: '提示',
                content: '请确认周围云盒处于正常供电状态，并下拉刷新设备列表。',
                showCancel:false,
              })
            }
          },2000)
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
        that.setData({
          btopened:true,
        })
        wx.startBluetoothDevicesDiscovery({
          services:["000000FF-0000-1000-8000-00805F9B34FB"],
          success: function (res) {//开始搜索成功
            console.log("###startBluetoothDevicesDiscovery###")
            console.log(res)
          },
          fail: function (res) {
            wx.showModal({
              showCancel: false,
              title: '提示',
              content: res.errMsg,
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
        wx.hideLoading();
        that.setData({
          btopened: false,
        })
        wx.showModal({
          showCancel: false,
          title: '提示',
          content: res.errCode==10001?"请先打开蓝牙开关，然后下拉刷新设备列表":res.errMsg,
        });
        console.log(res);
      }
    })
    
		wx.onBluetoothDeviceFound(function(devices) {
      console.log(devices)
      var devArray = devices.devices;
      for (var i = 0; i < devArray.length;i++){
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
        let snnumber = Array.prototype.slice.call(new Uint8Array(devArray[i].advertisData));
        let tempSn = "";
        for (let k = 0; k < 8 && snnumber.length > 8; k++) {
          tempSn += (snnumber[k] > 15 ? snnumber[k].toString(16) : ("0" + snnumber[k].toString(16)))
        }
        var newBtDevice = [{
          rssi: devArray[i].RSSI,
          name: devArray[i].name,
          devId: devArray[i].deviceId,
          img: rssi_level_img,
          snNumber: tempSn.toUpperCase(),
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

	onPullDownRefresh: function() {
		// 下拉清空记录，并重新搜索
		console.log('onPullDownRefresh')
		var that = this
		wx.stopPullDownRefresh()
    wx.showLoading({
      title: '正在刷新列表',
      mask:true,
    })
		wx.stopBluetoothDevicesDiscovery({
		  success: function (res) {
			  console.log(res)
			  wx.closeBluetoothAdapter({
			    success: function (res) {
				    console.log(res)
				    var num = that.data.btDevices.length
				    that.data.btDevices.splice(0,num)
				    that.setData({
					    btDevices : that.data.btDevices
				    });			
				    wx.openBluetoothAdapter({
				      success: function (res) {
                that.setData({
                  btopened: true,
                })
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
		  },
      fail(res) {
        wx.hideLoading();
        console.log(res)
        that.setData({
          btopened: false,
        })
        wx.showModal({
          showCancel: false,
          title: '提示',
          content: res.errCode == 10001 ? "请先打开蓝牙开关，然后重试。" : res.errMsg,
        });
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
  clickDetail:function(option){
    console.log(option.currentTarget.dataset)
    wx.navigateTo({
      url: '/pages/cardBag/cardBag?devId=' + option.currentTarget.dataset.deviceId + '&devName=' + encodeURIComponent(option.currentTarget.dataset.name) + "&devNum=" + option.currentTarget.dataset.number,
    })
  }
});

