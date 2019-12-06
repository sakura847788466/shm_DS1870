// pages/diancan/diancan.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    selected: true,
    selected1: false,
    selected2: false,

    carArray: [],
    carMoney: 0,
    carlen: 0,
    currentNavbar: '0',
    typeID:0,

    cartArray: [],


    navbar: [{ typeId: 0, typeName: "热卖", typeStatus: 1, bId: 1, menuList: Array(0) },
      { typeId: 1, typeName: "优惠", typeStatus: 0, bId: 1, menuList: Array(0) },
      { typeId: 2, typeName: "新鲜上市", typeStatus: 0, bId: 1, menuList: Array(0) },
      { typeId: 3, typeName: "进店必点", typeStatus: 0, bId: 1, menuList: Array(0) },
      { typeId: 4, typeName: "超值套餐", typeStatus: 0, bId: 1, menuList: Array(0) },
      { typeId: 5, typeName: "新菜品", typeStatus: 0, bId: 1, menuList: Array(0) },
    ],
    carArray1: [{
      carNum: 0, carShow: true, carText: "简介", mId: 389, mImage: "../../imgs/diancan/cai1.jpg", mName:"青椒干煸五花肉",mPrice:39.99,mSpec:"辣度" },
      { carNum: 0, carShow: true, carText: "简介", mId: 390, mImage: "../../imgs/diancan/cai11.jpg", mName: "蜜汁名菜", mPrice: 18, mSpec: "名菜"},
      { carNum: 0, carShow: true, carText: "简介", mId: 391, mImage: "../../imgs/diancan/cai12.jpg", mName: "安猪烧肉", mPrice: 24, mSpec: "烧肉",},
      { carNum: 0, carShow: true, carText: "简介", mId: 392, mImage: "../../imgs/diancan/cai13.jpg", mName: "清蒸石斑鱼", mPrice: 39, mSpec: "辣度" },
      { carNum: 0, carShow: true, carText: "简介", mId: 393, mImage: "../../imgs/diancan/cai14.jpg", mName: "棒棒肉", mPrice: 20, mSpec: "辣度"}],


    carArray2: [{
      carNum: 0, carShow: true, carText: "简介", mId: 394, mImage: "../../imgs/diancan/jiaozi.jpg", mName: "凉拌豆角", mPrice: 9.9, mSpec: "凉拌"},
      { carNum: 0, carShow: true, carText: "简介", mId: 395, mImage: "../../imgs/diancan/cai21.jpg", mName: "红烧猪蹄", mPrice: 12, mSpec: "爽口" },
      { carNum: 0, carShow: true, carText: "简介", mId: 396, mImage: "../../imgs/diancan/cai22.jpg", mName: "红烧肉", mPrice: 9.9, mSpec: "美味" },
    ],

    carArray3: [{
      carNum: 0, carShow: true, carText: "简介", mId: 397, mImage: "../../imgs/diancan/doufu.jpg", mName: "排骨蒸豆腐", mPrice: 23, mSpec: "辣度" },
      { carNum: 0, carShow: true, carText: "简介", mId: 398, mImage: "../../imgs/diancan/cai31.jpg", mName: "梅菜扣肉", mPrice: 14, mSpec: "口感好"},
      { carNum: 0, carShow: true, carText: "简介", mId: 399, mImage: "../../imgs/diancan/cai32.jpg", mName: "爆炒腰花", mPrice: 13, mSpec: "辣度" },
    ],

    carArray4: [{
      carNum: 0, carShow: true, carText: "简介", mId: 400, mImage: "../../imgs/diancan/paigu.jpg", mName: "梅菜扣肉", mPrice: 39.9, mSpec: "香辣" },
      { carNum: 0, carShow: true, carText: "简介", mId: 401, mImage: "../../imgs/diancan/cai61.jpg", mName: "汤圆", mPrice: 40, mSpec: "口感好"},
      { carNum: 0, carShow: true, carText: "简介", mId: 402, mImage: "../../imgs/diancan/cai62.jpg", mName: "泉水鱼", mPrice: 30, mSpec: "清爽" },
      { carNum: 0, carShow: true, carText: "简介", mId: 403, mImage: "../../imgs/diancan/cai63.jpg", mName: "白切鸡", mPrice: 17, mSpec: "稚嫩，口感好"},
    ],

    carArray5: [{
      carNum: 0, carShow: true, carText: "简介", mId: 404, mImage: "../../imgs/diancan/niuliu.jpg", mName: "孜然葱香牛柳", mPrice: 39.99, mSpec: "辣度" },
      { carNum: 0, carShow: true, carText: "简介", mId: 405, mImage: "../../imgs/diancan/cai41.jpg", mName: "红烧鸡块", mPrice: 15, mSpec: "香脆"},
      { carNum: 0, carShow: true, carText: "简介", mId: 406, mImage: "../../imgs/diancan/cai42.jpg", mName: "酸甜猪脚", mPrice: 40, mSpec: "酸辣爽口" },
      { carNum: 0, carShow: true, carText: "简介", mId: 407, mImage: "../../imgs/diancan/cai43.jpg", mName: "烤肉", mPrice: 34, mSpec: "酥脆"},
      { carNum: 0, carShow: true, carText: "简介", mId: 408, mImage: "../../imgs/diancan/cai44.jpg", mName: "锅烧羊肉", mPrice: 39.99, mSpec: "香辣"}
    ],

    carArray6: [{
      carNum: 0, carShow: true, carText: "简介", mId: 397, mImage: "../../imgs/diancan/dougupaigu.jpg", mName: "豆豉剁椒蒸排骨", mPrice: 39.9, mSpec: "辣度,美味", },
      { carNum: 0, carShow: true, carText: "简介", mId: 398, mImage: "../../imgs/diancan/cai51.jpg", mName: "叫花鸡", mPrice: 60, mSpec: "民间小吃", },
      { carNum: 0, carShow: true, carText: "简介", mId: 399, mImage: "../../imgs/diancan/cai52.jpg", mName: "鱼香肉丝", mPrice: 12, mSpec: "辣度", },
    ],

  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var that=this;
    this.setData({
      selected1: false,
      selected2: false,
      selected: true,
      carArray: that.data.carArray1,
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
  selected: function (e) {
    var that = this
    this.setData({
      selected1: false,
      selected2: false,
      selected: true,
      carArray:that.data.carArray1,
    })
    if(that.data.typeID==0){
      that.setData({
        carArray: that.data.carArray1,
      })
    } else if (that.data.typeID == 1) {
      that.setData({
        carArray: that.data.carArray2,
      })
    } else if (that.data.typeID == 2) {
      that.setData({
        carArray: that.data.carArray3,
      })
    } else if (that.data.typeID == 3) {
      that.setData({
        carArray: that.data.carArray4,
      })
    } else if (that.data.typeID == 4) {
      that.setData({
        carArray: that.data.carArray5,
      })
    } else if (that.data.typeID == 5) {
      that.setData({
        carArray: that.data.carArray6,
      })
    }
  },

  //购物车
  selected1: function (e) {
    var that = this;
    //getcartlist(that)
    this.setData({
      selected1: true,
      selected2: false,
      selected: false,
    })

    that.setData({
      cartArray: that.data.cartArray
    })
  },

  selected2: function (e) {

    this.setData({
      selected: false,
      selected1: false,
      selected2: true,
    })
  },
  /**
   * 切换 navbar
   */
  swichNav(e) {
    var that = this;
    
    that.setData({
      currentNavbar: e.currentTarget.dataset.idx,
      typeID: e.currentTarget.dataset.idx
    })
    if (e.currentTarget.dataset.idx==0){
      that.setData({
        carArray:that.data.carArray1
      });
      console.log(that.data.carArray1)
    } else if (e.currentTarget.dataset.idx == 1) {
      that.setData({
        carArray: that.data.carArray2
      });
    } else if (e.currentTarget.dataset.idx == 2) {
      that.setData({
        carArray: that.data.carArray3
      });
    } else if (e.currentTarget.dataset.idx == 3) {
      that.setData({
        carArray: that.data.carArray4
      });
    } else if (e.currentTarget.dataset.idx == 4) {
      that.setData({
        carArray: that.data.carArray5
      });
    } else if (e.currentTarget.dataset.idx == 5) {
      that.setData({
        carArray: that.data.carArray6
      });
    }
  },
  //添加菜品
  carAdd: function (event) {
    var that = this;
    var index = event.target.dataset.alphaBeta;
 
    that.data.carArray[index].carNum = that.data.carArray[index].carNum + 1; //数量新增
    that.setData({
      carArray: that.data.carArray,
      carMoney: (parseFloat(that.data.carArray[index].mPrice) + parseFloat(that.data.carMoney)).toFixed(2),
      carlen: parseInt(that.data.carlen) + 1
    })

    var needPush = true;
    for (var i = 0; i < that.data.cartArray.length; i++) {
      if (that.data.cartArray[i].mId == that.data.carArray[index].mId) {
        needPush = false;
        that.data.cartArray[i].num ++;
      }
    }
    if (needPush)
      that.data.cartArray.push({
        typeID: that.data.typeID,
        mId: that.data.carArray[index].mId,
        mImage: that.data.carArray[index].mImage,
        mName: that.data.carArray[index].mName,
        carText: that.data.carArray[index].carText,
        mPrice: that.data.carArray[index].mPrice,
        num: that.data.carArray[index].carNum
      })
      // console.log(that.data.cartArray)
      console.log(that.data.cartArray[index])
      //打印出push进去的值
  },
  //数量减少
  carReduce: function (event) {
    var that = this;
    var index = event.target.dataset.alphaBeta;
    console.log(index);
    if (that.data.carArray[index].carNum == 0) {

    } else {
      that.data.carArray[index].carNum = that.data.carArray[index].carNum - 1; //数量减少
      that.setData({
        carArray: that.data.carArray,
        carMoney: (parseFloat(that.data.carMoney) - parseFloat(that.data.carArray[index].mPrice)).toFixed(2),
        carlen: parseInt(that.data.carlen) - 1
      })
      for (var i = 0; i < that.data.cartArray.length; i++) {
        if (that.data.cartArray[i].mId == that.data.carArray[index].mId) {
          that.data.cartArray[i].num--;
          if (that.data.cartArray[i].num==0){
            that.data.cartArray.splice(i, 1)
            this.setData({
              cartArray: that.data.cartArray
            })
          }
        }
      }
    }

  },
  //购物车添加菜品
  cartAdd: function (event) {
    var that = this;

    var i = event.target.dataset.alphaBeta;
    var index = event.target.dataset.id; //获取菜单id
    that.data.cartArray[i].num = parseFloat(that.data.cartArray[i].num) + 1;

    that.setData({
      carMoney: (parseFloat(that.data.cartArray[i].mPrice) + parseFloat(that.data.carMoney)).toFixed(2),
      carlen: parseInt(that.data.carlen) + 1,
      cartArray: that.data.cartArray
    })
    var tid = that.data.cartArray[i].typeID;
    var tempmid = that.data.cartArray[i].mId;
    if(tid==0){
      for (var m = 0; m < that.data.carArray1.length;m++){
        if (that.data.carArray1[m].mId == tempmid){
          that.data.carArray1[m].carNum++;
          break;
        }
      }
      that.setData({
        carArray1: that.data.carArray1
      })
    } else if (tid == 1) {
      for (var m = 0; m < that.data.carArray2.length; m++) {
        if (that.data.carArray2[m].mId == tempmid) {
          that.data.carArray2[m].carNum++;
          break;
        }
      }
      that.setData({
        carArray2: that.data.carArray2
      })
    } else if (tid == 2) {
      for (var m = 0; m < that.data.carArray3.length; m++) {
        if (that.data.carArray3[m].mId == tempmid) {
          that.data.carArray3[m].carNum++;
          break;
        }
      }
      that.setData({
        carArray3: that.data.carArray3
      })
    } else if (tid == 3) {
      for (var m = 0; m < that.data.carArray4.length; m++) {
        if (that.data.carArray4[m].mId == tempmid) {
          that.data.carArray4[m].carNum++;
          break;
        }
      }
      that.setData({
        carArray4: that.data.carArray4
      })
    } else if (tid == 4) {
      for (var m = 0; m < that.data.carArray5.length; m++) {
        if (that.data.carArray5[m].mId == tempmid) {
          that.data.carArray5[m].carNum++;
          break;
        }
      }
      that.setData({
        carArray5: that.data.carArray5
      })
    } else if (tid == 5) {
      for (var m = 0; m < that.data.carArray6.length; m++) {
        if (that.data.carArray6[m].mId == tempmid) {
          that.data.carArray6[m].carNum++;
          break;
        }
      }
      that.setData({
        carArray6: that.data.carArray6
      })
    }
    
  },
  cartReduce: function (event) {
    var that = this;
    var i = event.target.dataset.alphaBeta;
    var index = event.target.dataset.id; //获取菜单id
    
    var restMoney = (parseFloat(that.data.carMoney) - parseFloat(that.data.cartArray[i].mPrice)).toFixed(2);
    var tid = that.data.cartArray[i].typeID;
    var tempmid = that.data.cartArray[i].mId;

    if (that.data.cartArray[i].num == 1) { //如果数量为1则删除
      that.data.cartArray.splice(i, 1)
    } else { //否则减少数量
      that.data.cartArray[i].num = parseFloat(that.data.cartArray[i].num) - 1;

    }

    that.setData({
      carMoney: restMoney,
      carlen: parseInt(that.data.carlen) - 1,
      cartArray: that.data.cartArray
    })
 
    if (tid == 0) {
      for (var m = 0; m < that.data.carArray1.length; m++) {
        if (that.data.carArray1[m].mId == tempmid) {
          that.data.carArray1[m].carNum--;
          break;
        }
      }
      that.setData({
        carArray1: that.data.carArray1
      })
    } else if (tid == 1) {
      for (var m = 0; m < that.data.carArray2.length; m++) {
        if (that.data.carArray2[m].mId == tempmid) {
          that.data.carArray2[m].carNum--;
          break;
        }
      }
      that.setData({
        carArray2: that.data.carArray2
      })
    } else if (tid == 2) {
      for (var m = 0; m < that.data.carArray3.length; m++) {
        if (that.data.carArray3[m].mId == tempmid) {
          that.data.carArray3[m].carNum--;
          break;
        }
      }
      that.setData({
        carArray3: that.data.carArray3
      })
    } else if (tid == 3) {
      for (var m = 0; m < that.data.carArray4.length; m++) {
        if (that.data.carArray4[m].mId == tempmid) {
          that.data.carArray4[m].carNum--;
          break;
        }
      }
      that.setData({
        carArray4: that.data.carArray4
      })
    } else if (tid == 4) {
      for (var m = 0; m < that.data.carArray5.length; m++) {
        if (that.data.carArray5[m].mId == tempmid) {
          that.data.carArray5[m].carNum--;
          break;
        }
      }
      that.setData({
        carArray5: that.data.carArray5
      })
    } else if (tid == 5) {
      for (var m = 0; m < that.data.carArray6.length; m++) {
        if (that.data.carArray6[m].mId == tempmid) {
          that.data.carArray6[m].carNum--;
          break;
        }
      }
      that.setData({
        carArray6: that.data.carArray6
      })
    }
  },
//提交订单
  settlement: function () {
    var that = this;
    if (that.data.carMoney == 0) {
      wx.showModal({
        title: '提示',
        content: '您还没有点餐，请先点餐！',
        showCancel: false,
        confirmColor: '#007a7a',
        confirmText:"确  定"
      })
    } else {
      console.log(that.data.cartArray);
      for(var i = 0;i<that.data.cartArray.length;i++){
        console.log('typeID=' + that.data.cartArray[i].typeID + '& mId=' + that.data.cartArray[i].mId + '& mName=' + that.data.cartArray[i].mName + '&mPrice=' + that.data.cartArray[i].mPrice + '&num=' +that.data.cartArray[i].num + '&mImage=' +that.data.cartArray[i].mImage + '&carText=' + that.data.cartArray[i].carText)
        //输出参数
      }
     wx.showModal({
       title: '提示',
       content: '订单已提交，后厨正在备菜中，请稍等！',
       showCancel:false,
       confirmText: "确  定",
       confirmColor: '#333333',
       success(res) {
         if (res.confirm) {//清空购物车
          
             for (var m = 0; m < that.data.carArray1.length; m++) {  
              that.data.carArray1[m].carNum=0;
             }
          
             for (var m = 0; m < that.data.carArray2.length; m++) {
                that.data.carArray2[m].carNum=0;
             }
          
             for (var m = 0; m < that.data.carArray3.length; m++) {   
                 that.data.carArray3[m].carNum=0;
             }
             
             for (var m = 0; m < that.data.carArray4.length; m++) {
                 that.data.carArray4[m].carNum=0;           
             }
          
             for (var m = 0; m < that.data.carArray5.length; m++) {      
                 that.data.carArray5[m].carNum=0;           
             }
            
             for (var m = 0; m < that.data.carArray6.length; m++) {
                 that.data.carArray6[m].carNum=0;     
             }
             that.setData({
               carArray1: that.data.carArray1,
               carArray2: that.data.carArray2,
               carArray3: that.data.carArray3,
               carArray4: that.data.carArray4,
               carArray5: that.data.carArray5,
               carArray6: that.data.carArray6,
               cartArray:[],
               carMoney: 0,
               carlen: 0,
             })
           if(that.data.typeID==0){
             that.setData({
               carArray: that.data.carArray1,
             })
           } else if (that.data.typeID == 1) {
             that.setData({
               carArray: that.data.carArray2,
             })
           } else if (that.data.typeID == 2) {
             that.setData({
               carArray: that.data.carArray3,
             })
           } else if (that.data.typeID == 3) {
             that.setData({
               carArray: that.data.carArray4,
             })
           } else if (that.data.typeID == 4) {
             that.setData({
               carArray: that.data.carArray5,
             })
           } else if (that.data.typeID == 5) {
             that.setData({
               carArray: that.data.carArray6,
             })
           }  
         }
       }
     })
    }

  },
})