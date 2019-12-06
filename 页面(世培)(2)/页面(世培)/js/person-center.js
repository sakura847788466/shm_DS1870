$(function () {
  console.log(API)
  $('.el-button').click(() => {
    if ($('.el-input__inner').val() == '') {
      alert("请设置ip")
    } else {
      $('.el-message-box').css('display', 'none')
      $('.mask').css("opacity", '0')
      $('.mask').css('z-index', '-1000')

      var API = $('.el-input__inner').val();



    }
  })
  // $('.isTrue').attr("disable", true)
  $('.close').click(() => {
    $('.option').css("display", "none")
    $('.mask').css("opacity", '0')
    $('.mask').css('z-index', '-1000')
  })
})



/*设置 */
function setting() {
  var ip = $('.request_ip').val()
  var contRoll_port = $('.contRoll_port').val()
  var data_port = $('.data_port').val()
  var link_data_port = $('.link_data_port').val()
  var data = JSON.stringify({
    ip: ip,
    dataPort: data_port,
    controllerPort: contRoll_port,
    countUrl: link_data_port
  })
  console.log(data)
  $.ajax({
    url: API + '/TCP/socketConfig',
    data: data,
    type: 'POST',
    contentType: 'application/json',
    success: function (res) {
      console.log(res)
      $('.option').css("display", "block")
      $('.mask').css("opacity", '0.5')
      $('.mask').css('z-index', '1000')


      //禁止点击事件
      $('.sN').attr("disabled", true)
      $('.sL').attr("disabled", true)
      $('.uP').attr("disabled", true)

      $('.successNum').attr('disabled', true)
      $('.successLink').attr('disabled', true)
      $('.upDataOnline').attr('disabled', true)


    },
    fail: function (err) {
      console.log(err)
      alert("配置失败")
    }
  })
  $(".inputList-mask").css("opacity", "0.5")
  $(".inputList-mask").css("z-index", "1000")


}
/*修改 */
function upData() {
  $(".inputList-mask").css("opacity", "0")
  $(".inputList-mask").css("z-index", "-1000")
  if ($(".inputList-mask").css("opacity", '0')) {
    var ip = $('.request_ip').val()
    var contRoll_port = $('.contRoll_port').val()
    var data_port = $('.data_port').val()
    var link_data_port = $('.link_data_port').val()
    var data = JSON.stringify({
      ip: ip,
      dataPort: data_port,
      controllerPort: contRoll_port,
      countUrl: link_data_port
    })
    console.log(data)
    $.ajax({
      url: API + '/TCP/socketConfig', //关闭负载
      data: data,
      type: 'POST',
      contentType: 'application/json',
      success: function (res) {
        console.log(res)

      },
      fail: function (err) {
        console.log(err)
      }
    })
  } else {
    console.log("修改遮罩层未关闭就请求")
  }

}

/*获取打印成功数 */
function successNum() {
  $.ajax({
    url: API + '/TCP/getPrint',
    data: {},
    type: 'GET',
    contentType: 'application/json',
    success: function (res) {
      console.log(res)
      $('.successNum').val(res)
    },
    fail: function (err) {
      console.log(err)
    }
  })
}

/*连接成功数 */
function successLink() {
  $.ajax({
    url: API + '/TCP/getCount',
    data: {},
    type: 'GET',
    contentType: 'application/json',
    success: function (res) {
      console.log(res)
      $('.successLink').val(res)
    },
    fail: function (err) {
      console.log(err)
    }
  })
}

/*主动上传数 */
function successUpData() {
  $.ajax({
    url: API + '/TCP/reportMsg',
    data: {},
    type: 'GET',
    contentType: 'application/json',
    success: function (res) {
      console.log(res)
      $('.upDataOnline').val(res)
    },
    fail: function (err) {
      console.log(err)
    }
  })
}
/*开始 */
function start() {
  console.log("点击我")
  var times = $('.times').val()
  console.log(times)
  $.ajax({
    url: API + '/TCP/yanshisocketStart',
    data: {
      times: times
    },
    type: 'POST',
    contentType: 'application/x-www-form-urlencoded',
    success: function (res) {
      console.log(res)
      $('.upDataOnline').val(' ')
      $('.successLink').val(' ')
      $('.successNum').val(' ')




      $('.sN').css('background-color', '#109c55')
      $('.sL').css('background-color', '#109c55')
      $('.uP').css('background-color', '#109c55')

      //开启button点击
      $('.sN').attr("disabled", false)
      $('.sL').attr("disabled", false)
      $('.uP').attr("disabled", false)

      $('.successNum').attr('disabled', false)
      $('.successLink').attr('disabled', false)
      $('.upDataOnline').attr('disabled', false)

    },
    fail: function (err) {
      console.log(err)
    }
  })

}

/*结束 */
function end() {
  $.ajax({
    url: API + '/TCP/closeSocket',
    data: {},
    type: 'GET',
    contentType: 'application/x-www-form-urlencoded',
    success: function (res) {
      console.log(res)
      $('.sN').attr("disabled", true).css("background-color", "#bfc3c1")
      $('.sL').attr("disabled", true).css("background-color", "#bfc3c1")
      $('.uP').attr("disabled", true).css("background-color", "#bfc3c1")

      $('.successNum').attr('disabled', true)
      $('.successLink').attr('disabled', true)
      $('.upDataOnline').attr('disabled', true)

    },
    fail: function (err) {
      console.log(err)
    }
  })
}