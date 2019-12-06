$(function() {
  var feedback = "";
  var DS_1870 = document.getElementById('DS_1870');
  var UserData = {
      userData: null,
      name: location.hostname,
  }
  var pageNo = 1;
  $('.el-button--small').on('click', function() {

      var ipVal = $('.el-input__inner').val()
      if (ipVal == '') {
          $.messager.alert('提示', '请先设置ip')
      } else {
          
          $('.el-message-box').css('display', 'none')
          $('.maskT').css('opacity', '0')
          $('.maskT').css('z-index', '-1000')
          $('.con_cc').on('click', function() {
              //点击进入之后直接执行进卡   点击进卡
              $('.maskInfo').show()
              $('.maskInfo').animate({
                  height: '700px',
                  width: '900px'
              })
              yh() //执行计时
              $('.con_tL').css('display', 'none')
              setTimeout(function() {
                  WEB_OcxTest(ipVal, pageNo); //链接ocx 延时两秒执行
              }, 2000)

          })
      }

  })

  //退卡
  $('.outCard').on('click', function(res) {
      WEB_MoveCard()
  })

  $('.data').click(function() {
      $('#cc').show()
  })

  // 日历事件
  $('#cc').calendar({
      current: new Date(),
      months: ['一月', '二月', '三月', '四月', '五月', '六月', '七月', '八月', '九月', '十月', '十一月', '十二月'],
      weeks: ['星期天', '星期一', '星期二', '星期三', '星期四', '星期五', '星期六']
  })


  $('#cc').calendar({
      onSelect: function(date) {
          var bgnDate = new Date()
          var time = bgnDate.getFullYear() + "" + (bgnDate.getMonth() + 1) + "" + "0" + "" + bgnDate.getDate() + "" + bgnDate.getHours() + "" + bgnDate.getMinutes() + "" + bgnDate.getSeconds() + "" + bgnDate.getMilliseconds()
          $('.data').val(time)
          $('#cc').hide()
      }
  })
})

/*------------------------------------------------------------------------------------------------相关函数------------------------------------------------------------ */
function load(feedback, ipVal, pageNo, pageSize) {

  var data = JSON.stringify({ //请求参数一
      busBgnDate: '20191115000000001',
      busEndDate: '20191115235900001',
      busType: "02",
      cardType: "3101",
      cardNo: feedback, //需要传入ocx扫描返回的参数 feedback
      pageNo: pageNo,
      pageSize: pageSize
  })
  var baseData = Base64.encode(data) //data转化base64编码

  //noise获取
  var noise = Math.uuid(32) //32位uuid标识符
  console.log(noise)

  //sign设置
  var sign = "appid=ZLHIS6087743&data=" + baseData + "&noise=" + noise;
  var stringSign = sign + "&key=cda20555bfd3c0ee656f80d0cb&version=1.0";
  var signEnd = hex_md5(stringSign).toUpperCase()
  console.log(signEnd)
      //最终请求参数
  var requestData = {
          "appid": "ZLHIS6087743",
          "data": baseData, //base64编码
          "noise": noise, //随机数 
          "version": "1.0", //固定版本号
          "sign": signEnd
      }
      // 发起请求
  jQuery.support.cors = true;
  $.ajax({
      url: ipVal + '/medical-web/api/medical/getEBillUnPrintList', //http://[ip]:[port]/[service]/api/medical/ [接口服务标识]
      type: 'POST',
      data: requestData,
      contentType: 'application/json',
      dataType: 'json',
      cache: false, //不从浏览器缓存中加载请求信息
      success: (function(res) {
          // console.log(res)
          // var resData = Base64.decode(res.data)
          // var resDataP = JSON.parse(resData)
          // var ticketList = Base64.decode(resDataP.message)
          // var tickList_end = JSON.parse(ticketList)
          // var loadList = tickList_end.billList;
          var testData_load = {
              "total": 2,
              "billList": [{
                  "idCardNo": "",
                  "ivcDateTime": "20191115152632492",
                  "billBatchCode": "06010119",
                  "busDate": "20191115085500010",
                  "sex": "男",
                  "billName": "医疗门诊收费票据（电子）",
                  "remark": "备注",
                  "payer": "测试01",
                  "billNo": "0000014012",
                  "random": "afe91d",
                  "totalAmt": 1800,
                  "busNo": "20191115000021"
              }, {
                  "idCardNo": "",
                  "ivcDateTime": "20191115152636748",
                  "billBatchCode": "06010119",
                  "busDate": "20191115085500010",
                  "sex": "男",
                  "billName": "医疗门诊收费票据（电子）",
                  "remark": "备注",
                  "payer": "测试01",
                  "billNo": "0000014013",
                  "random": "40cee9",
                  "totalAmt": 1800,
                  "busNo": "20191115000022"
              }, {
                  "idCardNo": "",
                  "ivcDateTime": "20191115152632492",
                  "billBatchCode": "06010119",
                  "busDate": "20191115085500010",
                  "sex": "男",
                  "billName": "医疗门诊收费票据（电子）",
                  "remark": "备注",
                  "payer": "测试01",
                  "billNo": "0000014012",
                  "random": "afe91d",
                  "totalAmt": 1800,
                  "busNo": "20191115000021"
              }, {
                  "idCardNo": "",
                  "ivcDateTime": "20191115152632492",
                  "billBatchCode": "06010119",
                  "busDate": "20191115085500010",
                  "sex": "男",
                  "billName": "医疗门诊收费票据（电子）",
                  "remark": "备注",
                  "payer": "测试01",
                  "billNo": "0000014012",
                  "random": "afe91d",
                  "totalAmt": 1800,
                  "busNo": "20191115000021"
              }, {
                  "idCardNo": "",
                  "ivcDateTime": "20191115152632492",
                  "billBatchCode": "06010119",
                  "busDate": "20191115085500010",
                  "sex": "男",
                  "billName": "医疗门诊收费票据（电子）",
                  "remark": "备注",
                  "payer": "测试01",
                  "billNo": "0000014012",
                  "random": "afe91d",
                  "totalAmt": 1800,
                  "busNo": "20191115000021"
              }, {
                  "idCardNo": "",
                  "ivcDateTime": "20191115152632492",
                  "billBatchCode": "06010119",
                  "busDate": "20191115085500010",
                  "sex": "男",
                  "billName": "医疗门诊收费票据（电子）",
                  "remark": "备注",
                  "payer": "测试01",
                  "billNo": "0000014012",
                  "random": "afe91d",
                  "totalAmt": 1800,
                  "busNo": "20191115000021"
              }, {
                  "idCardNo": "",
                  "ivcDateTime": "20191115152632492",
                  "billBatchCode": "06010119",
                  "busDate": "20191115085500010",
                  "sex": "男",
                  "billName": "医疗门诊收费票据（电子）",
                  "remark": "备注",
                  "payer": "测试01",
                  "billNo": "0000014012",
                  "random": "afe91d",
                  "totalAmt": 1800,
                  "busNo": "20191115000021"
              }, {
                  "idCardNo": "",
                  "ivcDateTime": "20191115152632492",
                  "billBatchCode": "06010119",
                  "busDate": "20191115085500010",
                  "sex": "男",
                  "billName": "医疗门诊收费票据（电子）",
                  "remark": "备注",
                  "payer": "测试01",
                  "billNo": "0000014012",
                  "random": "afe91d",
                  "totalAmt": 1800,
                  "busNo": "20191115000021"
              }, {
                  "idCardNo": "",
                  "ivcDateTime": "20191115152632492",
                  "billBatchCode": "06010119",
                  "busDate": "20191115085500010",
                  "sex": "男",
                  "billName": "医疗门诊收费票据（电子）",
                  "remark": "备注",
                  "payer": "测试01",
                  "billNo": "0000014012",
                  "random": "afe91d",
                  "totalAmt": 1800,
                  "busNo": "20191115000021"
              }],
              "pageNo": 1
          }
          var loadList = testData_load.billList;
          for (var i = 0; i < loadList.length; i++) {
              var str = "<div class='item'>" +
                  "<div><input type='checkbox' class='inp' value='' autocomplete='off'/></div>"+
                  "<div>" + loadList[i].busNo + "</div>" +
                  "<div>" + loadList[i].ivcDateTime + "</div>" + 
                  "<div>" + loadList[i].billBatchCode + "</div>" +
                  "<div>$" + loadList[i].totalAmt + "</div>" +
                  "<div>" + loadList[i].billName + "</div>" +
                  "<div>" +
                  "<div class='print' data-index=" + i + "  >打印票据</div>" +
                  "</div>" +
                  "</div>"

              $('.infoList_c').append(str)
          }
          /*分页 */
          $every_page = 6;

          $items = $(".infoList_c  .item");
          $total_all = $items.length; //总条数
          console.log($total_all)
          $page_num = Math.round($total_all / $every_page) //向上取整（2.5 ==> 3）

          $("#total_page").text($page_num);
          //初始化页面，只显示前5条。
          $(".infoList_c  .item:gt(" + ($every_page - 1) + ")").each(function() {
                  $(this).hide();
              })
              //点击下一条按钮函数。
          $("#next_page").click(function() {
              $current_page = ($("#current_page").text()); //获取当前页码
              console.log($current_page)
              if ($current_page < $page_num) {
                  $("#current_page").text(++$current_page);
                  $.each($(".infoList_c  .item"), function(index, item) {
                      //获取下一页显示的开始索引。
                      var start = ($("#current_page").text() - 1) * $every_page;
                      if (index >= start && index < start + $every_page) {
                          $(this).show();
                      } else {
                          $(this).hide();
                      }
                  })
              } else {
                  return false;
              }
          })
          $("#pre_page").click(function() { //上一页
              $current_page = ($("#current_page").text());
              if ($current_page > 1) {
                  $("#current_page").text(--$current_page);
                  $.each($(".infoList_c  .item"), function(index, item) {
                      var start = ($("#current_page").text() - 1) * $every_page;
                      if (index >= start && index < start + $every_page) {
                          $(this).show();
                      } else {
                          $(this).hide();
                      }
                  })
              } else {
                  return false;
              }
          })

          /*分页 */
          $('.print').on('click', function() {
              var index = $(this).attr("data-index")
                  //1.获取电子票据明细接口拿到placeCode参数
                  //2.获取扫描参数 
              var request_number1 = JSON.stringify({
                  billNo: loadList[index].billNo, //电子发票号码
                  billBatchCode: loadList[index].billBatchCode, //电子票据编码
                  random: loadList[index].random //电子校验码
              })
              var request_codeBase64 = Base64.encode(request_number1)

              var request_numberSign = "appid=ZLHIS6087743&data=" + request_codeBase64 + "&noise=ibuaiVcKdpRxkhJAXXXXX" + "&key=cda20555bfd3c0ee656f80d0cb&version=1.0";
              var signEnd = hex_md5(request_numberSign).toUpperCase()

              var request_end = { // 请求的最终数据
                  "appid": "ZLHIS6087743",
                  "data": request_codeBase64,
                  "noise": "ibuaiVcKdpRxkhJAXXXXX",
                  "version": "1.0",
                  "sign": signEnd
              }

              $.ajax({
                  url: ipVal + '/medical-web/api/medical/getBillDetail?random= ' + Math.random(),
                  method: 'POST',
                  data: request_end,
                  contentType: 'application/json',
                  cache: false,
                  success: (function(res) {
                      // console.log(res)
                      // var result = Base64.decode(res.data)
                      // var resultStr = JSON.parse(result)
                      // var resultT = Base64.decode(resultStr.message)
                      /*--------------扫描获取有效纸质票据代码------------------------*/
                      var saoM = DS_1870.AutoTurnOnScanner(); //返回纸质票据代码
                      // alert(saoM)
                      if (saoM == '' || saoM == null) {
                          $.messager.alert('提示', '未获得纸质票据代码')
                      } else {

                          var testData = {
                              "ownPay": 3330,
                              "otherfundPay": 2220,
                              "sex": "男",
                              "accountPay": 1000,
                              "chargeDetail": [{
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "CT费",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "CT费",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }],
                              "remark": "备注",
                              "busType": "02",
                              "selfCashPay": 400,
                              "medicalCareType": "城镇居民基本医疗保险",
                              "totalAmt": 1800,
                              "cardNo": "0123456789",
                              "author": "票据编制人",
                              "patientId": "10000",
                              "age": "33",
                              "selfPayAmt": 3000,
                              "fundPay": 1110,
                              "payChannelDetail": [{
                                  "payChannelCode": "02",
                                  "payChannelValue": 1800
                              }],
                              "listDetail": [{
                                  "amt": 100,
                                  "unit": "计量单位 ",
                                  "remark": "备注",
                                  "chrgtype": "费用类型1", //费用类型1
                                  "std": 50,
                                  "name": "药品名称/剂型",
                                  "number": 2,
                                  "code": "编码2"
                              }, {
                                  "amt": 12,
                                  "unit": "元 ",
                                  "remark": "早餐",
                                  "chrgtype": "CT费",
                                  "std": 50,
                                  "name": "药品名称/剂型",
                                  "number": 2,
                                  "code": "编码2"
                              }, {
                                  "amt": 12,
                                  "unit": "元 ",
                                  "remark": "早餐",
                                  "chrgtype": "CT费",
                                  "std": 50,
                                  "name": "药品名称/剂型",
                                  "number": 2,
                                  "code": "编码2"
                              }],
                              "medicalInstitution": "综合医院",
                              "busDateTime": "20191115085500010",
                              "cashPay": 0,
                              "payee": "收费员",
                              "cardType": "3101",
                              "otherParameter": [{
                                  "infoName": "卡类型",
                                  "infoValue": "3101"
                              }, {
                                  "infoName": "卡号",
                                  "infoValue": "0123456789"
                              }, {
                                  "infoName": "医保类型",
                                  "infoValue": "城镇居民基本医疗保险"
                              }, {
                                  "infoName": "性别",
                                  "infoValue": "男"
                              }, {
                                  "infoName": "科室",
                                  "infoValue": "科室"
                              }, {
                                  "infoName": "患者门诊号",
                                  "infoValue": "10001"
                              }, {
                                  "infoName": "个人账户支付",
                                  "infoValue": "1000"
                              }, {
                                  "infoName": "个人账户余额",
                                  "infoValue": "0"
                              }, {
                                  "infoName": "医保统筹基金支付",
                                  "infoValue": "1110"
                              }, {
                                  "infoName": "其它医保支付",
                                  "infoValue": "2220"
                              }, {
                                  "infoName": "自费金额",
                                  "infoValue": "3330"
                              }, {
                                  "infoName": "现金预交款金额",
                                  "infoValue": "0"
                              }, {
                                  "infoName": "转账预交款金额",
                                  "infoValue": "0"
                              }, {
                                  "infoName": "支票预交款金额",
                                  "infoValue": "0"
                              }, {
                                  "infoName": "补交金额(转账)",
                                  "infoValue": "0"
                              }, {
                                  "infoName": "退还金额(转账)",
                                  "infoValue": "0"
                              }, {
                                  "infoName": "医疗机构类型",
                                  "infoValue": "综合医院"
                              }, {
                                  "infoName": "年龄",
                                  "infoValue": "33"
                              }, {
                                  "infoName": "患者唯一ID",
                                  "infoValue": "10000"
                              }, {
                                  "infoName": "医保机构编码",
                                  "infoValue": "0090"
                              }, {
                                  "infoName": "个人自付",
                                  "infoValue": "3000"
                              }, {
                                  "infoName": "个人现金支付",
                                  "infoValue": "400"
                              }, {
                                  "infoName": "交款人支付宝账户",
                                  "infoValue": "患者支付宝账户"
                              }, {
                                  "infoName": "微信支付订单号",
                                  "infoValue": "微信支付订单号"
                              }, {
                                  "infoName": "02",
                                  "infoValue": "100"
                              }, {
                                  "infoName": "02",
                                  "infoValue": "100"
                              }],
                              "category": "科室",
                              "payer": "测试01",
                              "placeCode": "003",
                              "otherSpecialParameter": [],
                              "patientNo": "10001",
                              "busNo": "20191115000016"
                          }; //票据详情下的信息
                          var str0 = "";
                          var str1 = "四川省医疗单位门诊结算票据";
                          var str2 = loadList[index].billBatchCode;
                          var str3 = loadList[index].billNo;
                          var str4 = testData.payee;
                          var str5 = loadList[index].random;
                          var str6 = "" + timeStr(testData.busDateTime) + "\r\n";
                          var str7 = "收费时间：" + timeStr(testData.busDateTime) + "\r\n"; //收费时间
                          var str8 = "项目名称";
                          var str9 = "数量/单位";
                          var str10 = "金额(元)";
                          var str11 = "备注";
                          var str12 = "项目名称";
                          var str13 = "数量/单位";
                          var str14 = "金额(元)";
                          var str15 = "备注";
                          var str16 = "金额";
                          var str17 = "合计(大写):   " + Arabia_to_Chinese(testData.ownPay) + "";
                          var str18 = "合计:   " + testData.ownPay + "";
                          var str19 = "业务流水号:" + testData.busNo + "";
                          var str20 = "门诊号:挂号 ";
                          var str21 = "就诊时间:" + timeStr(testData.busDateTime) + "\r\n";
                          var str22 = "医疗机构类型:" + testData.medicalInstitution + "";
                          var str23 = "医保类型:" + testData.otherParameter[2].infoValue + "";
                          var str24 = "医保编码:" + testData.otherParameter[19].infoValue + "";
                          var str25 = "性别:" + testData.sex + "\r\n";
                          var str26 = "医疗统筹基金支付:" + testData.otherParameter[8].infoValue + "";
                          var str27 = "其他支付:" + testData.otherParameter[9].infoValue + "";
                          var str28 = "个人账户支付:" + testData.otherParameter[6].infoValue + "";
                          var str29 = "个人现金支付:" + testData.otherParameter[9].infoValue + "\r\n";
                          var str30 = "个人支付:" + testData.otherParameter[19].infoValue + "";
                          var str31 = "个人自费:" + testData.otherParameter[19].infoValue + "";
                          var str32 = '四川省人民医院';
                          var str33 = 'YYL099'
                          var byteArray = new Array();

                          var position = {
                              n1: 60, //x =>实际测横向1英尺 = 60;
                              n2: 145 //y =>1英寸  实际测纵向 = 145
                          }

                          //打印数据转换
                          getBinaryArrayData(str0, function(res0) { //先跳行到起始点
                              byteArray[0] = 0xD;
                              byteArray[1] = 0x1B;
                              byteArray[2] = 0x40;

                              byteArray[4] = 27;
                              byteArray[5] = 74;
                              byteArray[6] = position.n2; // 跳行到起始点 155

                              byteArray[7] = 27; //绝对定位
                              byteArray[8] = 36;
                              byteArray[9] = position.n1; //60
                              byteArray[10] = 0;

                              byteArray[11] = 28; //字号
                              byteArray[12] = 101;
                              byteArray[13] = 20;
                              byteArray[14] = 20;

                              var index = 15;



                              for (var m = 0; m < res0.length; m++) {
                                  byteArray[index++] = res0[m];
                              }
                          getBinaryArrayData(str1, function(res1) { //票据名称

                              byteArray[index++] = 27; //绝对定位
                              byteArray[index++] = 36;
                              byteArray[index++] = position.n1 + 50; //110    
                              byteArray[index++] = 0;

                              for (var m = 0; m < res1.length; m++) {
                                  byteArray[index++] = res1[m];
                              }
                          getBinaryArrayData(str2, function(res2) { //电子票据代码

                              byteArray[index++] = 27; //绝对定位
                              byteArray[index++] = 36;
                              byteArray[index++] = position.n1 - 32;
                              byteArray[index++] = 1;

                              for (var m = 0; m < res2.length; m++) {
                                  byteArray[index++] = res2[m];
                              }
                          getBinaryArrayData(str3, function(res3) { //电子票据号码

                              byteArray[index++] = 27; //绝对定位
                              byteArray[index++] = 36;
                              byteArray[index++] = position.n1 + 70;
                              byteArray[index++] = 1;

                              for (var m = 0; m < res3.length; m++) {
                                  byteArray[index++] = res3[m];
                              }
                          getBinaryArrayData(str4, function(res4) { //收款人


                              byteArray[index++] = 27; //绝对定位
                              byteArray[index++] = 36;
                              byteArray[index++] = position.n1 + 57;
                              byteArray[index++] = 0;

                              byteArray[index++] = 27; //跳行间距
                              byteArray[index++] = 74;
                              byteArray[index++] = 38;



                              for (var m = 0; m < res4.length; m++) {
                                  byteArray[index++] = res4[m];
                              }
                          getBinaryArrayData(str5, function(res5) { //电子票据检验码

                              byteArray[index++] = 27; //绝对定位
                              byteArray[index++] = 36;
                              byteArray[index++] = position.n1 - 26;
                              byteArray[index++] = 1;

                              for (var m = 0; m < res5.length; m++) {
                                  byteArray[index++] = res5[m];
                              }
                          getBinaryArrayData(str6, function(res6) { //开票日期


                              byteArray[index++] = 27; //绝对定位
                               byteArray[index++] = 36;
                              byteArray[index++] = position.n1 + 76;
                              byteArray[index++] = 1;

                              for (var m = 0; m < res6.length; m++) {
                                  byteArray[index++] = res6[m];
                              }
                          getBinaryArrayData(str7, function(res7) { //收费时间

                              byteArray[index++] = 27; //跳行
                              byteArray[index++] = 74;
                              byteArray[index++] = 19;

                              byteArray[index++] = 27; //绝对定位
                              byteArray[index++] = 36;
                              byteArray[index++] = position.n1;
                              byteArray[index++] = 0;

                              for (var m = 0; m < res7.length; m++) {
                                  byteArray[index++] = res7[m];
                              }
                          getBinaryArrayData(str8, function(res8) { //项目名称


                              byteArray[index++] = 27;
                              byteArray[index++] = 74;
                              byteArray[index++] = 27;

                              byteArray[index++] = 27; //绝对定位
                              byteArray[index++] = 36;
                              byteArray[index++] = position.n1;
                              byteArray[index++] = 0;

                              for (var m = 0; m < res8.length; m++) {
                                  byteArray[index++] = res8[m];
                              }
                          getBinaryArrayData(str9, function(res9) { //数量/单位

                              byteArray[index++] = 27; //绝对定位
                              byteArray[index++] = 36;
                              byteArray[index++] = position.n1 + 56;
                              byteArray[index++] = 0;

                              for (var m = 0; m < res9.length; m++) {
                                  byteArray[index++] = res9[m];
                              }
                          getBinaryArrayData(str10, function(res10) { //金额


                              byteArray[index++] = 27; //绝对定位
                              byteArray[index++] = 36;
                              byteArray[index++] = position.n1 + 112;
                              byteArray[index++] = 0;

                              for (var m = 0; m < res10.length; m++) {
                                  byteArray[index++] = res10[m];
                              }
                          getBinaryArrayData(str11, function(res11) { //备注


                              byteArray[index++] = 27; //绝对定位
                              byteArray[index++] = 36;
                              byteArray[index++] = position.n1 + 168;
                              byteArray[index++] = 0;

                              for (var m = 0; m < res11.length; m++) {
                                  byteArray[index++] = res11[m];
                              }
                          getBinaryArrayData(str12, function(res12) { //项目名称


                              byteArray[index++] = 27; //绝对定位
                              byteArray[index++] = 36;
                              byteArray[index++] = position.n1 - 48;
                              byteArray[index++] = 1;



                              for (var m = 0; m < res12.length; m++) {
                                   byteArray[index++] = res12[m];
                              }
                          getBinaryArrayData(str13, function(res13) { //数量单位


                              byteArray[index++] = 27; //绝对定位
                              byteArray[index++] = 36;
                              byteArray[index++] = position.n1 + 8;
                              byteArray[index++] = 1;

                              for (var m = 0; m < res13.length; m++) {
                                  byteArray[index++] = res13[m];
                              }
                          getBinaryArrayData(str14,function(res14) { //金额

                              byteArray[index++] =27; //绝对定位
                              byteArray[index++] = 36;
                              byteArray[index++] = position.n1 + 64;
                              byteArray[index++] = 1;



                             for (var m = 0; m < res14.length; m++) {
                               byteArray[index++] =res14[m];
                             }
                          getBinaryArrayData(str15,function(res15) { //备注

                               byteArray[index++] = 27; //绝对定位
                               byteArray[index++] = 36;
                               byteArray[index++] = position.n1 + 120;
                               byteArray[index++] = 1;

                              for (var m = 0; m < res15.length; m++) {
                                  byteArray[index++] = res15[m];
                              }
                          /*循环的内容*/

                          for (var i = 0; i < (testData.listDetail.length - 1); i++) {
                               var str_num = testData.listDetail[i].amt.toString();
                               var number = testData.listDetail[i].number.toString();

                               console.log(str_num)
                               console.log(testData.listDetail.length)
                          getBinaryArrayData(testData.listDetail[i].chrgtype, function(res24) { //费用类型

                               console.log(res24)
                               byteArray[index++] = 27; //绝对定位
                               byteArray[index++] = 36;
                               byteArray[index++] = position.n1;
                               byteArray[index++] = 0;

                               byteArray[index++] = 27;
                               byteArray[index++] = 74;
                                byteArray[index++] = 38;

                                for (var m = 0; m < res24.length; m++) {
                                    byteArray[index++] = res24[m];
                                }
                          getBinaryArrayData(number, function(res25) {
                                console.log("数量" + res25)
                                byteArray[index++] = 27; //绝对定位
                                byteArray[index++] = 36;
                                byteArray[index++] = position.n1 + 56;
                                byteArray[index++] = 0;


                                for (var m = 0; m < res25.length; m++) {
                                    byteArray[index++] = res25[m];
                                }
                          getBinaryArrayData(str_num, function(res26) {
                                console.log("金额" + res26)
                                byteArray[index++] = 27; //绝对定位
                                byteArray[index++] = 36;
                                byteArray[index++] = position.n1 + 92;
                                byteArray[index++] = 0;



                                for (var m = 0; m < res26.length; m++) {
                                    byteArray[index++] = res26[m];
                                }
                          getBinaryArrayData(testData.listDetail[i].remark, function(res27) {
                                console.log("备注" + res27)
                                byteArray[index++] = 27; //绝对定位
                                byteArray[index++] = 36;
                                byteArray[index++] = position.n1 + 168;
                                byteArray[index++] = 0;


                                for (var m = 0; m < res27.length; m++) {
                                    byteArray[index++] = res27[m];
                                }

                           getBinaryArrayData(testData.listDetail[1].chrgtype, function(res28) {
                                console.log("项目名称" + res28)
                                byteArray[index++] = 27; //绝对定位
                                byteArray[index++] = 36;
                                byteArray[index++] = position.n1 - 48;
                                byteArray[index++] = 1;


                                for (var m = 0; m < res28.length; m++) {
                                    byteArray[index++] = res28[m];
                                }
                           getBinaryArrayData(number, function(res29) {
                                console.log("数量/名称" + res29)
                                byteArray[index++] = 27; //绝对定位
                                byteArray[index++] = 36;
                                byteArray[index++] = position.n1 + 8;
                                byteArray[index++] = 1;


                                for (var m = 0; m < res29.length; m++) {
                                    byteArray[index++] = res29[m];
                                }
                          getBinaryArrayData(str_num, function(res30) {
                                console.log("金额" + res30)
                                byteArray[index++] = 27; //绝对定位
                                byteArray[index++] = 36;
                                byteArray[index++] = position.n1 + 64;
                                byteArray[index++] = 1;


                                for (var m = 0; m < res30.length; m++) {
                                    byteArray[index++] = res30[m];
                                }
                          getBinaryArrayData(testData.listDetail[1].remark, function(res30) {
                                console.log("备注" + res30)
                                byteArray[index++] = 27; //绝对定位
                                byteArray[index++] = 36;
                                byteArray[index++] = position.n1 + 120;
                                byteArray[index++] = 1;


                                for (var m = 0; m < res30.length; m++) {
                                    byteArray[index++] = res30[m];
                                 }
                                });
                               });
                             });
                            });
                          });
                        });
                      });
                    });
                  }
                  /*--------------循环内容----------------------*/

                        getBinaryArrayData(str17, function(res17) { //合计(大写)


                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1;
                            byteArray[index++] = 0;


                            byteArray[index++] = 27;
                            byteArray[index++] = 74;
                            byteArray[index++] = 180;

                            byteArray[index++] = 27;
                            byteArray[index++] = 74;
                            byteArray[index++] = 40;

                            for (var m = 0; m < res17.length; m++) {
                                byteArray[index++] = res17[m];
                            }

                        getBinaryArrayData(str18, function(res18) { //合计()

                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1 + 168;
                            byteArray[index++] = 0;
                            for (var m = 0; m < res18.length; m++) {
                                byteArray[index++] = res18[m];
                            }
                        getBinaryArrayData(str19, function(res19) { //业务流水
                            byteArray[index++] = 27; //跳行间距
                            byteArray[index++] = 74;
                            byteArray[index++] = 76;


                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1;
                            byteArray[index++] = 0;
                            for (var m = 0; m < res19.length; m++) {
                                byteArray[index++] = res19[m];
                            }
                        getBinaryArrayData(str20, function(res20) { //业务标识
                                                                                                                                                                         byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1 + 100; //172
                            byteArray[index++] = 0;
                            for (var m = 0; m < res20.length; m++) {
                                byteArray[index++] = res20[m];
                            }
                        getBinaryArrayData(str21, function(res21) { //就诊时间
                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1 + 64;
                            byteArray[index++] = 1;



                            for (var m = 0; m < res21.length; m++) {
                                byteArray[index++] = res21[m];
                            }
                        getBinaryArrayData(str22, function(res22) { //医疗机构类型
                                                                                                                          

                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1;
                            byteArray[index++] = 0;



                            for (var m = 0; m < res22.length; m++) {
                                byteArray[index++] = res22[m];
                            }
                        getBinaryArrayData(str23, function(res23) { //医保类型
                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1 + 102;
                            byteArray[index++] = 0;



                            for (var m = 0; m < res23.length; m++) {
                                byteArray[index++] = res23[m];
                            }
                        getBinaryArrayData(str24, function(res24) { //医保编码
                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1 - 28;
                            byteArray[index++] = 1;



                            for (var m = 0; m < res24.length; m++) {
                                byteArray[index++] = res24[m];
                            }
                        getBinaryArrayData(str25, function(res25) { //性别
                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1 + 64;
                            byteArray[index++] = 1;



                            for (var m = 0; m < res25.length; m++) {
                                byteArray[index++] = res25[m];
                            }
                        getBinaryArrayData(str26, function(res26) { //医疗统筹基金支付
                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1;
                            byteArray[index++] = 0;



                            for (var m = 0; m < res26.length; m++) {
                                byteArray[index++] = res26[m];
                            }
                        getBinaryArrayData(str27, function(res27) { //其他支付
                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1 + 102;
                            byteArray[index++] = 0;



                            for (var m = 0; m < res27.length; m++) {
                                byteArray[index++] = res27[m];
                            }
                        getBinaryArrayData(str28, function(res28) { //个人账户支付
                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1 - 28;
                            byteArray[index++] = 1;

                            for (var m = 0; m < res28.length; m++) {
                                byteArray[index++] = res28[m];
                            }
                        getBinaryArrayData(str29, function(res29) { //个人现金支付
                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1 + 64;
                            byteArray[index++] = 1;
                            for (var m = 0; m < res29.length; m++) {
                                byteArray[index++] = res29[m];
                            }
                        getBinaryArrayData(str30, function(res30) { //个人支付
                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1;
                            byteArray[index++] = 0;

                            for (var m = 0; m < res30.length; m++) {
                                byteArray[index++] = res30[m];
                            }
                        getBinaryArrayData(str31, function(res31) { //个人自费
                             byteArray[index++] = 27; //绝对定位
                             byteArray[index++] = 36;
                             byteArray[index++] = position.n1 + 102;
                             byteArray[index++] = 0;
                             for (var m = 0; m < res31.length; m++) {
                                  byteArray[index++] = res31[m];
                             }
                        getBinaryArrayData(str32, function(res32) {
                             byteArray[index++] = 27; //绝对定位
                             byteArray[index++] = 36;
                             byteArray[index++] = position.n1 + 59;
                             byteArray[index++] = 0;

                             byteArray[index++] = 27; //跳行间距
                             byteArray[index++] = 74;
                             byteArray[index++] = 27;



                            for (var m = 0; m < res32.length; m++) {
                                byteArray[index++] = res32[m];
                            }
                        getBinaryArrayData(str33, function(res33) {
                            byteArray[index++] = 27; //绝对定位
                            byteArray[index++] = 36;
                            byteArray[index++] = position.n1 + 87;
                            byteArray[index++] = 1;

                            for (var m = 0; m < res33.length; m++) {
                                byteArray[index++] = res33[m];
                            }
                            byteArray[index++] = 0x0C;

                            var arrayBuffer = new Uint8Array(byteArray)
                            console.log(arrayBuffer)

                            Bytes2HexString(arrayBuffer);
                            //ocx打印
                            });
                           });
                          });
                         });
                         });
                        });
                       });
                      });
                     });
                    });
                   });
                  });
                 });
                });
               });
              });
             });
            });
           });
          });
         });
        });
       });
      });
     });
    });
   });
  });
 });
});
});
});
});


}
}),
fail: (function(err) {
                alert("请求出错" + err)
                  })
              })
          })
      }),
      fail: (function(err) {
          alert("无效的ip" + err)
      })
  })
}
//先获取本地时间 模拟时间数据
function Appendzero(obj) {
  if (obj < 10) return "0" + "" + obj;
  else return obj;
}

function getBinaryArrayData(text, resultCallBack) {

  var buffer = new Array(sizeOfGbk(text));
  var indexDV = 0;
  for (var i = 0; i < text.length; ++i) {
      if (text.charCodeAt(i) > 0xff) {
          var utfStr = text.charCodeAt(i).toString(16);
          var gbkStr = utf2gbOne(utfStr);

          var highByte = parseInt(gbkStr.substring(0, 2), 16);
          var lowByte = parseInt(gbkStr.substring(2, 4), 16);
          buffer[indexDV++] = highByte;
          buffer[indexDV++] = lowByte;

      } else {
          buffer[indexDV++] = text.charCodeAt(i);
      }
  }
  resultCallBack(buffer);
}
/* */
function sizeOfGbk(str) {
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
}
/* */
function getCodeStr() {
  return codeStr
}
/*   */
function utf2gbOne(utfCode) {
  var codeStr = getCodeStr();
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
}

/* ------------------------打印相关------------------------------------*/
function Bytes2HexString(arrBytes) {
  var str = "";
  for (var i = 0; i < arrBytes.length; i++) {
      var tmp;
      var num = arrBytes[i];
      if (num < 0) {
          //此处填坑，当byte因为符合位导致数值为负时候，需要对数据进行处理
          tmp = (255 + num + 1).toString(16);
      } else {
          tmp = num.toString(16);
      }
      if (tmp.length == 1) {
          tmp = "0" + tmp;
      }
      str += tmp;
  }
  console.log("转换的" + str)
  WEB_print(str) //打印

}

function WEB_print(data) {
  feedback = DS_1870.PrintData(data);
  console.log(feedback) //打印状态
}
//ocx测试控件连接
function WEB_OcxTest(ipVal, pageNo) {
  feedback = DS_1870.OcxTest();
  console.log(feedback) //判断ocx的链接状态
  if (feedback) {

      WEB_EnterCard(ipVal, pageNo)

  } else {
      $.messager.alert('提示', 'ocx版本不匹配,请安装最新的版本');

  }
}
//进卡
function WEB_EnterCard(ipVal, pageNo) {
  feedback = DS_1870.EnterCard('COM1');
  var status = Sixteen_ten(feedback, true)
  // var status = ''

  console.log("进卡" + status) //读卡器状态 0x33
  if (status == '0x33') { //成功0x30
      clearTimeout(t);
      $('.loadEffect').show()
      setTimeout(function() {
          $('.loadEffect').hide()
          $('.maskInfo').hide()
          $('.user').show()
      }, 1000)
      setTimeout(function() {
          WEB_ReadMagCard(ipVal, pageNo); //获取磁卡信息

      }, 3000)
  } else if (status == '0x31') {
        clearTimeout(t);
      $.messager.confirm('提示', '读卡器串口打开失败', function(res) {
          if (res) {
              WEB_MoveCard();
          }
      });
  } else if (status == '0x32') {
    clearTimeout(t);
      $.messager.alert('提示', '卡片不在前端位置')
      WEB_MoveCard(); //退卡
  } else if (status == '0x33') {
        clearTimeout(t);
        $.messager.confirm('提示', '读卡机内有卡', function(res) {
          if (res) {
              WEB_MoveCard();
          }
      });

  } else if (status == '0x34') {
    clearTimeout(t);
      $.messager.alert('提示', '读卡机内无卡，请插入卡片!');

  } else if (status == '0x35') {
     clearTimeout(t);
      $.messager.confirm('提示', '读卡器超时!', function(res) {
          if (res) {
              location.reload()
          }
      });
     
  } else {
     return false;

  }
}

//倒计时
function yh() {
t = setTimeout(yh, 1000);
var i = $('.a').html();
i -= 1; //i每次减一
$('.a').html(i)
if (i <= 0) {
    clearTimeout(t)
    $('.a').css('display', 'none')
    $.messager.confirm('提示','进卡超时',function(res){
      if(res){
        location.reload()
      }
    })
    
}; //i=0时结束
};

function WEB_MoveCard() //退卡
{
  feedback = DS_1870.MoveCard('COM1');
  console.log(feedback) //146
  var status = Sixteen_ten(feedback, true)
  console.log("退卡" + status) //读卡器状态 0x92
  if (status === '0x30') {
      location.reload() //刷新页面
  } else {
      $.messager.alert('提示', '退卡失败!');


  }
}

function WEB_ReadMagCard(ipVal, pageNo) //读磁条卡
{
  feedback = DS_1870.ReadMagCard('COM1');
  console.log("读磁卡" + feedback)

  if (feedback == '') {

      //访问后台拿用户数据数据
      var data = JSON.stringify({ //请求参数一
          busBgnDate: '20191115000000001',
          busEndDate: '20191115235900001',
          busType: "02",
          cardType: "3101",
          cardNo: feedback, //需要传入ocx扫描返回的参数 feedback
          pageNo: pageNo,
          pageSize: "9"
      })
      var baseData = Base64.encode(data) //data转化base64编码

      //noise获取
      var noise = Math.uuid(32) //32位uuid标识符
      console.log(noise)

      //sign设置
      var sign = "appid=ZLHIS6087743&data=" + baseData + "&noise=" + noise;
      var stringSign = sign + "&key=cda20555bfd3c0ee656f80d0cb&version=1.0";
      var signEnd = hex_md5(stringSign).toUpperCase()
      console.log(signEnd)
          //最终请求参数
      var requestData = {
              "appid": "ZLHIS6087743",
              "data": baseData, //base64编码
              "noise": noise, //随机数 
              "version": "1.0", //固定版本号
              "sign": signEnd
          }
          // 发起请求
      jQuery.support.cors = true;
      $.ajax({
              url: ipVal + '/medical-web/api/medical/getEBillUnPrintList', //http://[ip]:[port]/[service]/api/medical/ [接口服务标识]
              type: 'POST',
              data: requestData,
              contentType: 'application/json',
              dataType: 'json',
              cache: false, //不从浏览器缓存中加载请求信息
              success: (function(res) {
                  // console.log(res)
                  // var resData = Base64.decode(res.data)
                  // var resDataP = JSON.parse(resData)
                  // var ticketList = Base64.decode(resDataP.message)
                  // var tickList_end = JSON.parse(ticketList)
                  var testData_load = { //死数据测试
                      "total": 2,
                      "billList": [{
                          "idCardNo": "",
                          "ivcDateTime": "20191115152632492",
                          "billBatchCode": "06010119",
                          "busDate": "20191115085500010",
                          "sex": "男",
                          "billName": "医疗门诊收费票据（电子）",
                          "remark": "备注",
                          "payer": "测试01",
                          "billNo": "0000014012",
                          "random": "afe91d",
                          "totalAmt": 1800,
                          "busNo": "20191115000021"
                      }],
                      "pageNo": 1
                  }
                  var loadList = testData_load.billList;

                  /*获取详情 */
                  var request_number1 = JSON.stringify({
                      billNo: loadList[0].billNo, //电子发票号码
                      billBatchCode: loadList[0].billBatchCode, //电子票据编码
                      random: loadList[0].random //电子校验码
                  })
                  var request_codeBase64 = Base64.encode(request_number1)

                  var request_numberSign = "appid=ZLHIS6087743&data=" + request_codeBase64 + "&noise=ibuaiVcKdpRxkhJAXXXXX" + "&key=cda20555bfd3c0ee656f80d0cb&version=1.0";
                  var signEnd = hex_md5(request_numberSign).toUpperCase()

                  var request_end = { // 请求的最终数据
                      "appid": "ZLHIS6087743",
                      "data": request_codeBase64,
                      "noise": "ibuaiVcKdpRxkhJAXXXXX",
                      "version": "1.0",
                      "sign": signEnd
                  }

                  $.ajax({
                      url: ipVal + '/medical-web/api/medical/getBillDetail?random= ' + Math.random(),
                      method: 'POST',
                      data: request_end,
                      contentType: 'application/json',
                      cache: false,
                      success: (function(res) {
                          // console.log(res)
                          // var result = Base64.decode(res.data)
                          // var resultStr = JSON.parse(result)
                          // var resultT = Base64.decode(resultStr.message)
                          // var resulT_arr = JSON.parse(resultT)
                          var resulT_arr = {
                              "ownPay": 3330,
                              "otherfundPay": 2220,
                              "sex": "男",
                              "accountPay": 1000,
                              "chargeDetail": [{
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "CT费",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "CT费",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }, {
                                  "amt": 100,
                                  "unit": "元",
                                  "remark": "备注",
                                  "selfAmt": 0,
                                  "std": 100,
                                  "chargeName": "ICU材料",
                                  "number": 1,
                                  "chargeCode": "0801"
                              }],
                              "remark": "备注",
                              "busType": "02",
                              "selfCashPay": 400,
                              "medicalCareType": "城镇居民基本医疗保险",
                              "totalAmt": 1800,
                              "cardNo": "0123456789",
                              "author": "票据编制人",
                              "patientId": "10000",
                              "age": "33",
                              "idCardNo": "452701199612161111",
                              "selfPayAmt": 3000,
                              "fundPay": 1110,
                              "payChannelDetail": [{
                                  "payChannelCode": "02",
                                  "payChannelValue": 1800
                              }],
                              "listDetail": [{
                                  "amt": 100,
                                  "unit": "计量单位 ",
                                  "remark": "备注",
                                  "chrgtype": "费用类型1", //费用类型1
                                  "std": 50,
                                  "name": "药品名称/剂型",
                                  "number": 2,
                                  "code": "编码2"
                              }, {
                                  "amt": 100,
                                  "unit": "计量单位 ",
                                  "remark": "备注",
                                  "chrgtype": "挂号费",
                                  "std": 50,
                                  "name": "药品名称/剂型",
                                  "number": 2,
                                  "code": "编码2"
                              }],
                              "medicalInstitution": "综合医院",
                              "busDateTime": "20191115085500010",
                              "cashPay": 0,
                              "payee": "收费员",
                              "cardType": "3101",
                              "otherParameter": [{
                                  "infoName": "卡类型",
                                  "infoValue": "3101"
                              }, {
                                  "infoName": "卡号",
                                  "infoValue": "0123456789"
                              }, {
                                  "infoName": "医保类型",
                                  "infoValue": "城镇居民基本医疗保险"
                              }, {
                                  "infoName": "性别",
                                  "infoValue": "男"
                              }, {
                                  "infoName": "科室",
                                  "infoValue": "科室"
                              }, {
                                  "infoName": "患者门诊号",
                                  "infoValue": "10001"
                              }, {
                                  "infoName": "个人账户支付",
                                  "infoValue": "1000"
                              }, {
                                  "infoName": "个人账户余额",
                                  "infoValue": "0"
                              }, {
                                  "infoName": "医保统筹基金支付",
                                  "infoValue": "1110"
                              }, {
                                  "infoName": "其它医保支付",
                                  "infoValue": "2220"
                              }, {
                                  "infoName": "自费金额",
                                  "infoValue": "3330"
                              }, {
                                  "infoName": "现金预交款金额",
                                  "infoValue": "0"
                              }, {
                                  "infoName": "转账预交款金额",
                                  "infoValue": "0"
                              }, {
                                  "infoName": "支票预交款金额",
                                  "infoValue": "0"
                              }, {
                                  "infoName": "补交金额(转账)",
                                  "infoValue": "0"
                              }, {
                                  "infoName": "退还金额(转账)",
                                  "infoValue": "0"
                              }, {
                                  "infoName": "医疗机构类型",
                                  "infoValue": "综合医院"
                              }, {
                                  "infoName": "年龄",
                                  "infoValue": "33"
                              }, {
                                  "infoName": "患者唯一ID",
                                  "infoValue": "10000"
                              }, {
                                  "infoName": "医保机构编码",
                                  "infoValue": "0090"
                              }, {
                                  "infoName": "个人自付",
                                  "infoValue": "3000"
                              }, {
                                  "infoName": "个人现金支付",
                                  "infoValue": "400"
                              }, {
                                  "infoName": "交款人支付宝账户",
                                  "infoValue": "患者支付宝账户"
                              }, {
                                  "infoName": "微信支付订单号",
                                  "infoValue": "微信支付订单号"
                              }, {
                                  "infoName": "02",
                                  "infoValue": "100"
                              }, {
                                  "infoName": "02",
                                  "infoValue": "100"
                              }],
                              "category": "科室",
                              "payer": "测试01",
                              "placeCode": "003",
                              "otherSpecialParameter": [],
                              "patientNo": "10001",
                              "busNo": "20191115000016"
                          }
                          $('.name').val(resulT_arr.payer)
                          $('.sex').val(resulT_arr.sex)
                          $('.kaHao').val(feedback)
                          $('.age').val(resulT_arr.age)
                          $('.idCard').val(resulT_arr.idCardNo)
                      }),
                      fail: function(err) {
                          console.log(err)
                      }
                  })
              }),
              fail: (function(err) {
                  console.log(err)
              })
          })
          /*------------------------------------------后台用户信息----------------  */
      $('.userIstrue').click(ipVal, function() {

          $('.loadEffect').css('z-index', '2000')
          $('.loadEffect').show()

          setTimeout(function() {
              $('.loadEffect').hide()
              $('.user').hide()
              $('.infoListW').show()
          }, 1000)
          load(feedback, ipVal, pageNo) //执行load()渲染

      })
  } else {
      $.messager.alert('提示', '无磁卡信息')
          //无此卡信息
  }
}



function WEB_TurnOnScanner() // 打开扫描头 扫描
{
  feedback = DS_1870.TurnOnScanner();
  if ("" == feedback) { //返回纸质票据编码和票据号
      alert("无条码信息");
      return feedback
  } else {
      //执行
  }

}

function AutoTurnOnScanner() { //自动扫描

  feedback = DS_1870.AutoTurnOnScanner();
  if ("" != feedback) {
      console.log(feedback)
  } else {
      console.log("自动扫描失败")
  }

}
/*-------------------------------- */
//10进制转换16进制

function Sixteen_ten(str, status) { //print true 10->16    false 16->10
  str = Number(str);

  if (status) {
      return '0x' + str.toString(16)
  } else {
      return parseInt(str, 16)
  }
}
//数字转换大写金额
function Arabia_to_Chinese(Num) {
  // debugger;
  for (i = Num.length - 1; i >= 0; i--) {
      Num = Num.replace(",", "")
      Num = Num.replace(" ", "")
      Num = Num.replace("￥", "")
  }
  if (isNaN(Num)) { //验证输入的字符是否为数字
      alert("请检查小写金额是否正确");
      return;
  }
  //---字符处理完毕，开始转换，转换采用前后两部分分别转换---//
  part = String(Num).split(".");
  newchar = "";
  //小数点前进行转化
  for (i = part[0].length - 1; i >= 0; i--) {
      if (part[0].length > 10) { alert("位数过大，无法计算"); return ""; } //若数量超过拾亿单位，提示
      tmpnewchar = ""
      perchar = part[0].charAt(i);
      switch (perchar) {
          case "0":
              tmpnewchar = "零" + tmpnewchar;
              break;
          case "1":
              tmpnewchar = "壹" + tmpnewchar;
              break;
          case "2":
              tmpnewchar = "贰" + tmpnewchar;
              break;
          case "3":
              tmpnewchar = "叁" + tmpnewchar;
              break;
          case "4":
              tmpnewchar = "肆" + tmpnewchar;
              break;
          case "5":
              tmpnewchar = "伍" + tmpnewchar;
              break;
          case "6":
              tmpnewchar = "陆" + tmpnewchar;
              break;
          case "7":
              tmpnewchar = "柒" + tmpnewchar;
              break;
          case "8":
              tmpnewchar = "捌" + tmpnewchar;
              break;
          case "9":
              tmpnewchar = "玖" + tmpnewchar;
              break;
      }
      switch (part[0].length - i - 1) {
          case 0:
              tmpnewchar = tmpnewchar + "元";
              break;
          case 1:
              if (perchar != 0) tmpnewchar = tmpnewchar + "拾";
              break;
          case 2:
              if (perchar != 0) tmpnewchar = tmpnewchar + "佰";
              break;
          case 3:
              if (perchar != 0) tmpnewchar = tmpnewchar + "仟";
              break;
          case 4:
              tmpnewchar = tmpnewchar + "万";
              break;
          case 5:
              if (perchar != 0) tmpnewchar = tmpnewchar + "拾";
              break;
          case 6:
              if (perchar != 0) tmpnewchar = tmpnewchar + "佰";
              break;
          case 7:
              if (perchar != 0) tmpnewchar = tmpnewchar + "仟";
              break;
          case 8:
              tmpnewchar = tmpnewchar + "亿";
              break;
          case 9:
              tmpnewchar = tmpnewchar + "拾";
              break;
      }
      newchar = tmpnewchar + newchar;
  }
  //小数点之后进行转化
  if (String(Num).indexOf(".") != -1) {
      if (part[1].length > 2) {
          alert("小数点之后只能保留两位,系统将自动截段");
          part[1] = part[1].substr(0, 2)
      }
      for (i = 0; i < part[1].length; i++) {
          tmpnewchar = ""
          perchar = part[1].charAt(i)
          switch (perchar) {
              case "0":
                  tmpnewchar = "零" + tmpnewchar;
                  break;
              case "1":
                  tmpnewchar = "壹" + tmpnewchar;
                  break;
              case "2":
                  tmpnewchar = "贰" + tmpnewchar;
                  break;
              case "3":
                  tmpnewchar = "叁" + tmpnewchar;
                  break;
              case "4":
                  tmpnewchar = "肆" + tmpnewchar;
                  break;
              case "5":
                  tmpnewchar = "伍" + tmpnewchar;
                  break;
              case "6":
                  tmpnewchar = "陆" + tmpnewchar;
                  break;
              case "7":
                  tmpnewchar = "柒" + tmpnewchar;
                  break;
              case "8":
                  tmpnewchar = "捌" + tmpnewchar;
                  break;
              case "9":
                  tmpnewchar = "玖" + tmpnewchar;
                  break;
          }
          if (i == 0) tmpnewchar = tmpnewchar + "角";
          if (i == 1) tmpnewchar = tmpnewchar + "分";
          newchar = newchar + tmpnewchar;
      }
  }
  //替换所有无用汉字
  while (newchar.search("零零") != -1)
      newchar = newchar.replace("零零", "零");
  newchar = newchar.replace("零亿", "亿");
  newchar = newchar.replace("亿万", "亿");
  newchar = newchar.replace("零万", "万");
  newchar = newchar.replace("零元", "元");
  newchar = newchar.replace("零角", "");
  newchar = newchar.replace("零分", "");


  if (newchar.charAt(newchar.length - 1) == "元" || newchar.charAt(newchar.length - 1) == "角")
      newchar = newchar + "整"
      //  document.write(newchar);
  return newchar;

}

//时间搓截取
function timeStr(timeStr) {
  var time = timeStr.slice(0, 8);
  return time;
}
//获取起始时间时间搓
function getTime() {
  var bgnDate = new Date()
  var startTime = bgnDate.getFullYear() + "" + Appendzero(bgnDate.getMonth() + 1) + "" + Appendzero(bgnDate.getDate()) + "" + Appendzero(bgnDate.getHours()) + "" + Appendzero(bgnDate.getMinutes()) + "" + Appendzero(bgnDate.getSeconds()) + "" + bgnDate.getMilliseconds()


  return startTime;
}
//结束时间
function getEndTime() {
  var bgnDate = new Date();
  var endTime = bgnDate.getFullYear() + "" + Appendzero(bgnDate.getMonth() + 1) + "" + Appendzero(bgnDate.getDate()) + "" + Appendzero(bgnDate.getHours()) + "" + Appendzero(bgnDate.getMinutes()) + "" + Appendzero(bgnDate.getSeconds()) + "" + bgnDate.getMilliseconds()
  return endTime;
}

//查询
function find() {

}


//userData本地存储

function init() {
  if (!UserData.userData) {
      UserData.userData = document.createElement('INPUT');
      UserData.userData.type = "hidden";
      UserData.userData.style.display = "none";
      UserData.userData.addBehavior("#default#userData");
      document.body.appendChild(UserData.userData);
      var expires = new Date();
      expires.setDate(expires.getDate() + 365);
      UserData.userData.expires = expires.toUTCString();
  } else {
      return false;
  }
}

function setItem(key, value) {

  if (UserData.init()) {
      UserData.userData.load(UserData.name);
      UserData.userData.setAttribute(key, value);
      UserData.userData.save(UserData.name);
  }
}

function getItem(key) {
  if (UserData.init()) {
      UserData.userData.load(UserData.name);
      return UserData.userData.getAttribute(key)
  }
}

function remove(key) {
  if (UserData.init()) {
      UserData.userData.load(UserData.name);
      UserData.userData.removeAttribute(key);
      UserData.userData.save(UserData.name);
  }

}

//全选
$(function () {
$(".checkAll").on('click',function () {
  var thisStatus = $(".checkAll").prop("checked");
  $(".inp").prop("checked", thisStatus);
})
})

// 子选矿控制全选框
$(function () {
$(".inp").on('click',function () {
  //子选择框选中的个数
  console.log(999)
  var num = $('.inp:checked').length;
  console.log(num);
  //子选择框总共的个数
  var numAll = $(".inp").length;
  console.log(numAll);
  if (num == numAll) {
    $(".checkAll").prop("checked", true)
  } else {
    $(".checkAll").prop("checked", false)
  }
})
})