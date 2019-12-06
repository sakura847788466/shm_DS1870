var all = []

$(function() {
  var status = true //开关状态
  var status_IP = true
  console.log(API) //apiConfig.js名单中的
  /*设置ip- 手动输入 */
  var ipBenDi = window.localStorage.getItem('IP')
  console.log(ipBenDi)
  if (ipBenDi !== null) {
    console.log('缓存存在')
    $('.el-message-box').css('display', 'none')
    $('.maskT').css('opacity', '0')
    $('.maskT').css('z-index', '-1000')
    load(ipBenDi)
    $('.add button').click(() => {
      $('.mask').css('opacity', '0.5')
      $('.mask').css('z-index', '1000')
      $('.pageTwo').css('display', 'block')
      $('.pageTwo').css('z-index', '9999')
    })
    $('.close').click(() => {
      $('.mask').css('opacity', '0')
      $('.mask').css('z-index', '-1000')
      $('.pageTwo').css('display', 'none')
    })
  } else if (ipBenDi == null || ipBenDi == ' ') {
    console.log('缓存不存在')

    $('.ipTrue').click(() => {
      let textValue = $('.el-input__inner').val()
      console.log(textValue)
      if (textValue == '') {
        alert('请输入ip地址')
      } else {
        /*渲染页面 */
        load(textValue)
        window.localStorage.setItem('IP', textValue) //缓存本地
        $('.el-message-box').css('display', 'none')
        $('.maskT').css('opacity', '0')
        $('.maskT').css('z-index', '-1000')

        $('.add button').click(() => {
          $('.mask').css('opacity', '0.5')
          $('.mask').css('z-index', '1000')
          $('.pageTwo').css('display', 'block')
          $('.pageTwo').css('z-index', '9999')
        })
        $('.close').click(() => {
          $('.mask').css('opacity', '0')
          $('.mask').css('z-index', '-1000')
          $('.pageTwo').css('display', 'none')
        })
      }
    })
  } else {
    return false
  }

  //页面开启和关闭负载
  if (status == true) {
    let API = window.localStorage.getItem('IP')
    console.log(API)
    $.ajax({
      url: API + '/nginx/restartNginx', //开启负载
      data: {},
      type: 'GET',
      contentType: 'application/json',
      success: function(res) {
        console.log(res)
      },
      fail: function(err) {
        console.log(err)
      }
    })
  } else {
    $.ajax({
      url: API + '/nginx/closeNginx', //关闭负载
      data: {},
      type: 'GET',
      contentType: 'application/json',
      success: function(res) {
        console.log(res)
      },
      fail: function(err) {
        console.log(err)
      }
    })
  }
  /*开关点击切换 */
  $('.switch').click(() => {
    let API = window.localStorage.getItem('IP')
    console.log(API)
    if (status == true) {
      console.log(99)
      $('.hide_img').css('display', 'block')
      $('.show_img').css('display', 'none')
      status = false
      console.log(status)
      $.ajax({
        url: API + '/nginx/closeNginx', //关闭负载
        data: {},
        type: 'GET',
        contentType: 'application/json',
        success: function(res) {
          console.log(res)
        },
        fail: function(err) {
          console.log(err)
        }
      })
    } else {
      status = true
      $.ajax({
        url: API + '/nginx/restartNginx', //开启负载
        data: {},
        type: 'GET',
        contentType: 'application/json',
        success: function(res) {
          console.log(res)
        },
        fail: function(err) {
          console.log(err)
        }
      })
      console.log(88)
      $('.hide_img').css('display', 'none')
      $('.show_img').css('display', 'block')
    }
  })
})

/*添加事件*/
function add() {
  var ip = $('.ipT').val()
  var Control_port = $('.Control_portT').val()
  var data_port = $('.data_portT').val()
  var request_port = $('.request_portT').val()
  console.log(ip + Control_port + data_port + request_port)
  var new_ip = 'http://' + ip + ':' + request_port + '/config/getVersion'
  console.log(new_ip)
  var str =
    `<div class="item-top item_nav" >
    <input type="text" name = 'ip' value='` +
    ip +
    `'  calss='ip'/>
    <input type="text" name = 'Control_port' value='` +
    Control_port +
    `' />
    <input type="text" name = 'data_port' value='` +
    data_port +
    `' />
    <input type="text" name = 'request_port' value='` +
    request_port +
    `' />
    <input type="text"  class='new_status'/>
  </div>`
  $.ajax({
    url: new_ip, //获取状态
    type: 'GET',
    contentType: 'application/json',
    success: function(res) {
      if (res.code == 0) {
        all.push(ip + ':' + request_port + '*' + Control_port + '&' + data_port)
        $('.first').append(str)
        $('.new_status')
          .val('正常')
          .css('color', '#409EFF')
      } else {
        $('.first').append(str)
        $('.new_status')
          .val('不正常')
          .css('color', 'red')
      }
    },
    fail: function(err) {
      console.log(err)
      alert('添加错误,状态值不正常')
    }
  })
  $('.ipT').val(' ')
  $('.Control_portT').val(' ')
  $('.data_portT').val(' ')
  $('.request_portT').val(' ')
  $('.mask').css('opacity', '0')
  $('.mask').css('z-index', '-1000')
  $('.pageTwo').css('display', 'none')
}

/*状态判断接口 */
function getStatus() {
  var ip = $('.ip').val()
  // console.log(ip)
  var request_port = $('.port').val()
  // console.log(request_port)
  var statusGet_ip = ip + ':' + request_port
  // console.log(statusGet_ip)
  var url = 'http://' + statusGet_ip + '/config/getVersion'
  console.log(url)
  $.ajax({
    url: url, //获取状态
    type: 'GET',
    contentType: 'application/json',
    success: function(res) {
      console.log(res)
      if (res.code == 0) {
        $('.status')
          .val('正常')
          .css('color', '#409EFF')
      } else {
        $('.status')
          .val('不正常')
          .css('color', 'red')
      }
    },
    fail: function(err) {
      console.log(err)
    }
  })
}

/*-----------提交------ */
function submitT() {
  var API = window.localStorage.getItem('IP')
  console.log(all)
  var ipAll = []
  var request_portAll = []
  var controll_portAll = []
  var data_portAll = []
  var serverData = []
  var controllData = []
  var dataData = []

  for (let i = 0; i < all.length; i++) {
    var ip = all[i].split(':')[0]
    ipAll.push(ip)
    var request_port = all[i].split(':')[1].split('*')[0]
    request_portAll.push(request_port)
    var controll_port = all[i]
      .split(':')[1]
      .split('*')[1]
      .split('&')[0]
    controll_portAll.push(controll_port)
    var data_port = all[i]
      .split(':')[1]
      .split('*')[1]
      .split('&')[1]
    data_portAll.push(data_port)

    var ipS = ipAll[i] + ':' + request_portAll[i]
    serverData.push(ipS)

    var ipC = ipAll[i] + ':' + controll_portAll[i]
    controllData.push(ipC)

    var ipD = ipAll[i] + ':' + data_portAll[i]
    dataData.push(ipD)
  }
  // console.log(ipAll)
  // console.log(request_portAll)
  // console.log(controll_portAll)
  // console.log(data_portAll)

  // console.log(serverData)
  // console.log(controllData)
  // console.log(dataData)

  var data = JSON.stringify({
    serverData: serverData,
    controllData: controllData,
    dataData: dataData
  })
  console.log(data)
  $.ajax({
    url: API + '/nginx/setNginxConfig', //提交
    data: data,
    type: 'POST',
    contentType: 'application/json',
    success: function(res) {
      console.log(res)
      if (res == 0) {
        alert('提交成功')
        $('.add button')
          .attr('disabled', true)
          .css('background', '#d1d6dc')
          .css('color', '#00000')
        $('.submit button')
          .attr('disabled', true)
          .css('background', '#d1d6dc')
          .css('color', '#00000')
      } else {
        alert('提交失败')
      }
    },
    fail: function(err) {
      console.log(err)
    }
  })
}

/*修改 */
function XiuGai() {
  $('.el-message-box').css('display', 'block')
  $('.maskT').css('opacity', '0.5')
  $('.maskT').css('z-index', '1000')

  $('.ipTrue').click(() => {
    let newIp = $('.el-input__inner').val()
    console.log(newIp)
    if (newIp == '') {
      alert('请输入ip地址')
      $('.isTrue').attr('disabled', true)
    } else {
      /*渲染页面 */
      load(newIp)
      console.log(all)
      window.location.reload() //刷新当前页面
      window.localStorage.setItem('IP', newIp) //缓存本地
      $('.el-message-box').css('display', 'none')
      $('.maskT').css('opacity', '0')
      $('.maskT').css('z-index', '-1000')
      $('.isTrue').attr('disabled', false)
    }
  })
}

/*数据渲染*/
function load(API) {
  var dongTaiIP = window.localStorage.getItem('IP')
  $('.top_content').html('当前连接IP:' + dongTaiIP)
  try {
    $.ajax({
      url: API + '/nginx/getUpdateHttp', //请求端口数据
      data: {},
      type: 'GET',
      contentType: 'application/json',
      success: function(res) {
        var arr = res.data
        // console.log(arr)
        $.ajax({
          url: API + '/nginx/getUpdateNetty', //控制端口数据
          data: {},
          type: 'GET',
          contentType: 'application/json',
          success: function(res) {
            // console.log(res.data)
            var a = res.data
            var a_port1 = a[0].split(':')[1]
            // var a_port2 = a[1].split(':')[1]
            var new_arr1 = arr[0] + '*' + a_port1
            // var new_arr2 = arr[1] + "*" + a_port2;

            // console.log(new_arr1)
            // console.log(new_arr2)
            $.ajax({
              url: API + '/nginx/getUpdateNettyData', //数据端口数据
              data: {},
              type: 'GET',
              contentType: 'application/json',
              success: function(res) {
                // console.log(res.data)
                var b = res.data
                var b_port1 = b[0].split(':')[1]
                // var b_port2 = b[1].split(':')[1]
                var news_arr1 = new_arr1 + '&' + b_port1
                // var news_arr2 = new_arr2 + "&" + b_port2

                // console.log(news_arr1)
                // console.log(news_arr2)

                all.push(news_arr1)
                // all.push(news_arr2)
                // console.log(all)
                for (var i = 0; i < all.length; i++) {
                  let ip = all[i].split(':')[0]
                  // console.log(ip)
                  let port = all[i]
                    .split(':')[1]
                    .split(':')[0]
                    .split('*')[0]
                  // console.log(port)
                  let Control_port = all[i]
                    .split(':')[1]
                    .split(':')[0]
                    .split('*')[1]
                    .split('&')[0]
                  // console.log(Control_port)
                  let data_port = all[i]
                    .split(':')[1]
                    .split(':')[0]
                    .split('*')[1]
                    .split('&')[1]
                  let ipNode =
                    `<div class="item-top item_nav">
                                    <input type="text" value='` +
                    ip +
                    `'  class="ip"/>
                                    <input type="text" value='` +
                    Control_port +
                    `' class='Control_port'/>
                                    <input type="text" value='` +
                    data_port +
                    `' class='data_port'/>
                                    <input type="text" value='` +
                    port +
                    `' class="port"/>
                                    <input type="text" value='' class='status'/>
                                  </div>`
                  $('.first').append(ipNode)
                }
                getStatus() //获取状态
              },
              fail: function(err) {
                console.log(err)
              }
            })
          },
          fail: function(err) {
            console.log(err)
          }
        })
      },
      fail: function(err) {
        console.log(err)
      }
    })
  } catch (e) {
    console.log(e)
  }
}

/*close */
function cancel() {
  $('.mask').css('opacity', '0')
  $('.mask').css('z-index', '-1000')
  $('.pageTwo').css('display', 'none')
}
