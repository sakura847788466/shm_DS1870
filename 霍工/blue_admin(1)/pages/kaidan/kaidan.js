// pages/test/test.js
var app = getApp();
Page({
  data: {
    dataList: [],
    good_code:"",
    good_name: "",
    goodPrice: 99.99,//商品价格
    goodcolors: [
      { "color_name": "红色", "flower_id": "11d7" },
      { "color_name": "蓝色", "flower_id": "3994" },
      { "color_name": "米白色", "flower_id": "3ebc"},
      { "color_name": "黑色", "flower_id": "425c" },
      { "color_name": "金色", "flower_id": "4ea0" },
      { "color_name": "紫色", "flower_id": "5eda" },
    ],
    goodsizes: [
      { "size_name": "S", "size_id": "11d7" },
      { "size_name": "M", "size_id": "3994" },
      { "size_name": "L", "size_id": "3ebc" },
      { "size_name": "XL", "size_id": "425c" },
      { "size_name": "XXL", "size_id": "4ea0" },
      { "size_name": "XXXL", "size_id": "5eda" },
    ],
  
    showSelect:"",
    sizeSelected:"",
    sizeSelect:0,
    duration: 1000,
    flowerImgSelect: '../../imgs/goods/lianyiqun.png',//选中的花色图片
    colorNameSelect: "",//
    colorSelect: 0,//判断是否选中
    isHidden: 0,
    animationData: {},//选择动画
    showModalStatus: false,//显示遮罩
    goodNum: 1,//商品数量
    select: 0,//商品详情、参数切换
    goodsList: [],
    selectNum:0,//购物车里面数量
  },
  /**
 * 生命周期函数--监听页面加载
 */
  onLoad: function (options) {
  var that=this;
    
    wx.getStorage({
      key: 'goodData',
      success(res) {//已保存，直接显示
        that.setData({
          dataList: [
            {
              goods_id: "YD7M620",
              goods_title: '运动鞋款1',
              goods_img: "../../imgs/goods/xie1.png",
              goods_price: '80'
            }, {
              goods_id: "YD7M638",
              goods_title: '运动鞋款2',
              goods_img: "../../imgs/goods/xie2.png",
              goods_price: '70'
            }, {
              goods_id: "YD5BG40",
              goods_title: '凉鞋',
              goods_img: '../../imgs/goods/xie3.png',
              goods_price: '99'
            }, {
              goods_id: "YD9PR88",
              goods_title: '高跟鞋',
              goods_img: '../../imgs/goods/xie4.png',
              goods_price: '120'
            }, {
              goods_id: "LY0AV55",
              goods_title: '连衣裙',
              goods_img: '../../imgs/goods/lianyiqun.png',
              goods_price: '180'
            }, {
              goods_id: "SY8U311",
              goods_title: '上衣',
              goods_img: '../../imgs/goods/shangyi.png',
              goods_price: '95'
            }, {
              goods_id: "CK8QT96",
              goods_title: '长裤',
              goods_img: '../../imgs/goods/kuzi.png',
              goods_price: '90'
            }, {
              goods_id: "DK8QT98",
              goods_title: '短裤',
              goods_img: '../../imgs/goods/duanku.png',
              goods_price: '75'
            }
          ],
        })
        
      },
      fail(res){//加载，云端抓取
        wx.showLoading({
          title: '云端提取数据中',
          mask:true,
        })
        setTimeout(function () {
          wx.hideLoading();
          that.setData({
            dataList: [
              {
                goods_id: "YD7M620",
                goods_title: '运动鞋款1',
                goods_img: "../../imgs/goods/xie1.png",
                goods_price: '80'
              }, {
                goods_id: "YD7M638",
                goods_title: '运动鞋款2',
                goods_img: "../../imgs/goods/xie2.png",
                goods_price: '70'
              }, {
                goods_id: "YD5BG40",
                goods_title: '凉鞋',
                goods_img: '../../imgs/goods/xie3.png',
                goods_price: '99'
              }, {
                goods_id: "YD9PR88",
                goods_title: '高跟鞋',
                goods_img: '../../imgs/goods/xie4.png',
                goods_price: '120'
              }, {
                goods_id: "LY0AV55",
                goods_title: '连衣裙',
                goods_img: '../../imgs/goods/lianyiqun.png',
                goods_price: '180'
              }, {
                goods_id: "SY8U311",
                goods_title: '上衣',
                goods_img: '../../imgs/goods/shangyi.png',
                goods_price: '95'
              }, {
                goods_id: "CK8QT96",
                goods_title: '长裤',
                goods_img: '../../imgs/goods/kuzi.png',
                goods_price: '90'
              }, {
                goods_id: "DK8QT98",
                goods_title: '短裤',
                goods_img: '../../imgs/goods/duanku.png',
                goods_price: '75'
              }
            ],
          })
          wx.setStorage({
            key: "goodData",
            data: "8条数据",
            success(res) {
              console.log("success", res)
            },
            fail(res) {
              console.log("fail", res)
            }
          })
        }, 3000);
      }
    })

  },
  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {
    var that = this;
    that.setData({
      goodsList: app.globalData.totalGoodsList,
      selectNum: app.globalData.shoppingnum,
    })
  },
  /**选择颜色 */
  chooseFlower: function (data) {
    var that = this;
    var flower_id = data.currentTarget.dataset.select;
    var color_name = data.currentTarget.dataset.flowerName;
    var showinfo="";
    if (that.data.sizeSelected==""){
      showinfo = color_name
    }else{
      showinfo = color_name + "+"+ that.data.sizeSelected;
    }
    that.setData({//把选中值，放入判断值中
      colorNameSelect: color_name,
      colorSelect: flower_id,
      showSelect: showinfo
    })
    
  },
  /**选择尺码 */
  chooseSize: function (data) {
    var that = this;
    var s_id = data.currentTarget.dataset.select;
    var s_name = data.currentTarget.dataset.flowerName;
    var showinfo = "";
    if (that.data.colorNameSelect == "") {
      showinfo = s_name
    } else {
      showinfo = that.data.colorNameSelect +"+" + s_name;
    }
    that.setData({//把选中值，放入判断值中
      sizeSelected: s_name,
      sizeSelect: s_id,
      showSelect: showinfo
    })
    
  },
  /**点击对应商品、显示页面 */
  viewFlowerArea: function (data) {
    var that = this;
    var ipos=data.currentTarget.dataset.index
    var animation = wx.createAnimation({//动画
      duration: 500,//动画持续时间
      timingFunction: 'linear',//动画的效果 动画从头到尾的速度是相同的
    })
    animation.translateY(0).step()//在Y轴偏移tx，单位px

    this.animation = animation
    if(ipos>3){
      that.setData({
        goodsizes: [
          { "size_name": "S", "size_id": "11d7" },
          { "size_name": "M", "size_id": "3994" },
          { "size_name": "L", "size_id": "3ebc" },
          { "size_name": "XL", "size_id": "425c" },
          { "size_name": "XXL", "size_id": "4ea0" },
          { "size_name": "XXXL", "size_id": "5eda" },
        ],
      })   
    } else if (ipos > 1){
      that.setData({
        goodsizes: [
          { "size_name": "36", "size_id": "11d7" },
          { "size_name": "37", "size_id": "3994" },
          { "size_name": "38", "size_id": "3ebc" },
          { "size_name": "39", "size_id": "425c" },
          { "size_name": "40", "size_id": "4ea0" },
          { "size_name": "41", "size_id": "5eda" },
        ],
      })
    } else {
      that.setData({
        goodsizes: [
          { "size_name": "38", "size_id": "11d7" },
          { "size_name": "39", "size_id": "3994" },
          { "size_name": "40", "size_id": "3ebc" },
          { "size_name": "41", "size_id": "425c" },
          { "size_name": "42", "size_id": "4ea0" },
          { "size_name": "43", "size_id": "5eda" },
        ],
      })
    }
    that.setData({
      showModalStatus: true,//显示遮罩       
      animationData: animation.export(),
      flowerImgSelect: that.data.dataList[ipos].goods_img,
      goodPrice: that.data.dataList[ipos].goods_price,
      good_name: that.data.dataList[ipos].goods_title,
      good_code: that.data.dataList[ipos].goods_id,
      showSelect:"",
      colorNameSelect:"",
      colorSelect:0,
      sizeSelected:"",
      sizeSelect:0,
      goodNum:1,
    })
    that.setData({//把选中值，放入判断值中
      isHidden: 1,
    })
  },
  /**隐藏选择花色区块 */
  hideModal: function (data) {
    var that = this;
    that.setData({//把选中值，放入判断值中
      showModalStatus: false,//显示遮罩       
      isHidden: 0,
    })
  },
  goodAdd: function (data) {

    var that = this;
    var goodCount = that.data.goodNum + 1;
    that.setData({//商品数量+1
      goodNum: goodCount,
    })

  },
  goodReduce: function (data) {
    var that = this;
    var goodCount = that.data.goodNum - 1;
    that.setData({//商品数量-1
      goodNum: goodCount
    })
  },
  
  /**
 * 加入购物车
 */
  addCart: function (data) {
    var that = this;
    var thatData = that.data;
   
    var good_name = thatData.good_name;//good_name
    var gn = thatData.goodNum;//数量
    var good_price = thatData.goodPrice;//价格
    var strcode = thatData.good_code;

    if (that.data.colorNameSelect == "" || that.data.sizeSelected == ""){
      wx.showModal({
        title: '提示',
        content: '请选择颜色/尺码',
        showCancel:false,
      })
    }else{
      var strSelect = strcode + "|" + good_name + "|" + that.data.colorNameSelect + "|" + that.data.sizeSelected;
      var needPush=true;
      for (var i = 0; i < that.data.goodsList.length;i++){
        if (that.data.goodsList[i].str1 == strSelect){
          needPush=false;
          that.data.goodsList[i].str2 = that.data.goodsList[i].str2+gn;
          that.data.goodsList[i].str4 = that.data.goodsList[i].str4 + gn * good_price;
        }
      }
      if (needPush){
        that.data.goodsList.push({
          str1: strSelect,
          str2: gn,
          str3: good_price,
          str4: gn * good_price
        })
      }
      
      app.globalData.totalGoodsList = that.data.goodsList;
      console.log(app.globalData.totalGoodsList)
      wx.showToast({
        title: '添加成功！',
        duration: 2000,
      })
      that.setData({//把选中值，放入判断值中
        showModalStatus: false,//显示遮罩       
        isHidden: 0,
        selectNum: gn+that.data.selectNum,
      })
      app.globalData.shoppingnum = that.data.selectNum;
    }
  },
  lookAndPrint:function(){
    var that = this;
    wx.navigateTo({
      url: '/pages/billlist/billlist?pageback=2&list=' + JSON.stringify(app.globalData.totalGoodsList),
    })
  }
})