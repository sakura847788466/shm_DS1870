//logs.js
const util = require('../../utils/util.js')

Page({
  /**
   * 页面的初始数据
   */
  data: {
    list: [
      { id: 1, name: '数据一' },
      { id: 2, name: '数据二' },
      { id: 3, name: '数据三' }
    ]
  },
  //删除
  del: function (e) {
    var current = e.currentTarget.dataset.index;
    console.log(current);
    var list = this.data.list;
    list.splice(current, 1)
    this.setData({
      list: list
    })
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {

  },
})
