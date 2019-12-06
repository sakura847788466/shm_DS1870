$(function() {
    var feedback = "";
    var DS_1870 = document.getElementById('DS_1870');

    //初始化页数
    tabPage({
            infoList_c: '.infoList_c',
            pageNav: '#pageNav',
            pagePrev: '.prev',
            pageNext: '.next',
            curNum: 5 /*每页显示的条数*/ ,
            activeClass: 'active' /*高亮显示的class*/ ,
            ini: 0 /*初始化显示的页面*/
        })
        //loading 渲染
    $('.el-button--small').on('click', function() {

            var ipVal = $('.el-input__inner').val()
            if (ipVal == '') {
                alert("请先设置ip地址")
            } else {
                $('.el-message-box').css('display', 'none')
                $('.maskT').css('opacity', '0')
                $('.maskT').css('z-index', '-1000')
                load()

                function load() {
                    //先获取本地时间 模拟时间数据
                    function Appendzero(obj) {
                        if (obj < 10) return "0" + "" + obj;
                        else return obj;
                    }


                    var bgnDate = new Date()
                    var time = bgnDate.getFullYear() + "" + Appendzero(bgnDate.getMonth() + 1) + "" + Appendzero(bgnDate.getDate()) + "" + Appendzero(bgnDate.getHours()) + "" + Appendzero(bgnDate.getMinutes()) + "" + Appendzero(bgnDate.getSeconds()) + "" + bgnDate.getMilliseconds()
                    console.log(time)
                    var endTime = bgnDate.getFullYear() + "" + (bgnDate.getMonth() + 1) + "" + (bgnDate.getDate() + 7) + "" + bgnDate.getHours() + "" + bgnDate.getMinutes() + "" + bgnDate.getSeconds() + "" + bgnDate.getMilliseconds()
                    console.log(endTime)





                    var data = JSON.stringify({ //请求参数一
                        busBgnDate: '20191115000000001',
                        busEndDate: '20191115235900001',
                        busType: "02",
                        cardType: "3101",
                        cardNo: "0123456789", //需要传入ocx扫描返回的参数
                        pageNo: "1",
                        pageSize: "10"
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
                            console.log(res)
                            var resData = Base64.decode(res.data)
                            var resDataP = JSON.parse(resData)
                            var ticketList = Base64.decode(resDataP.message)
                            var tickList_end = JSON.parse(ticketList)
                            var loadList = tickList_end.billList;
                            for (var i = 0; i < loadList.length; i++) {
                                var str = "<div class='item'>" +
                                    "<div>" + loadList[i].billNo + "</div>" +
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
                                        console.log(res)
                                        var result = Base64.decode(res.data)
                                        var resultStr = JSON.parse(result)
                                        var resultT = Base64.decode(resultStr.message)
                                        var resulT_parse = JSON.parse(resultT)
                                            //获取placeCode 开票点
                                        console.log(resulT_parse.placeCode)
                                            /*--------------扫描获取有效纸质票据代码------------------------*/
                                        var saoM = DS_1870.TurnOnScanner(); //返回纸质票据代码
                                        // if (saoM == '' || saoM == null) {
                                        if (false) {

                                            alert("未获取到纸质票据代码");
                                        } else {
                                            /*--------------------获取可用的纸质票据号---------------------分隔----------------------扫描之后得到的纸质票据代码直接传入---------------------------------*/
                                            // 1. 先获取可用的纸质票据号码
                                            var request_number = JSON.stringify({
                                                // "placeCode": resulT_parse.placeCode,
                                                "placeCode": '003',
                                                "pBillBatchCode": '06020201' // 纸质票据代码  上一个接口可获得 06020201=>'无可用票据'

                                            })
                                            var request_numberBase64 = Base64.encode(request_number)

                                            var request_numberSign = "appid=ZLHIS6087743&data=" + request_numberBase64 + "&noise=ibuaiVcKdpRxkhJAXXXXX" + "&key=cda20555bfd3c0ee656f80d0cb&version=1.0";
                                            var signEnd = hex_md5(request_numberSign).toUpperCase()

                                            var request_end = { // 请求的最终数据
                                                "appid": "ZLHIS6087743",
                                                "data": request_numberBase64,
                                                "noise": "ibuaiVcKdpRxkhJAXXXXX",
                                                "version": "1.0",
                                                "sign": signEnd
                                            }

                                            $.ajax({
                                                url: ipVal + '/medical-web/api/medical/getPaperBillNo?random= ' + Math.random(), //获取可用的票据号
                                                method: 'POST',
                                                data: request_end,
                                                contentType: 'application/json',
                                                cache: false,
                                                success: (function(res) {
                                                    console.log(res)
                                                    var result = Base64.decode(res.data)
                                                    var resultStr = JSON.parse(result)
                                                    if (resultStr.result !== 'S0000') {
                                                        var resultT = Base64.decode(resultStr.message)
                                                            // alert(resultT) //返回的票据号
                                                        alert(resultT)
                                                    } else {
                                                        //转换换开的纸质票据
                                                        var resultT = Base64.decode(resultStr.message)
                                                        var resultT_parse = JSON.parse(resultT)
                                                        var pBillBatchCode = resultT_parse.pBillBatchCode //纸质票据代码
                                                        var pBillNo = resultT_parse.pBillNo //纸质票据号码
                                                            // console.log(pBillNo)
                                                            // console.log(pBillBatchCode)

                                                        /*--------------------转换为换开纸质票据---------------------分隔-------------------------------------------------------*/
                                                        var request_number = JSON.stringify({
                                                                "billBatchCode": loadList[index].billBatchCode, //电子发票票据代码
                                                                "billNo": loadList[index].billNo, //电子发票票号
                                                                "pBillBatchCode": pBillBatchCode, //纸质票据代码
                                                                "pBillNo": pBillNo, //纸质票据号码
                                                                // "placeCode": resulT_parse.placeCode,
                                                                "placeCode": '003',
                                                                "busDateTime": resulT_parse.busDateTime,
                                                                "operator": resulT_parse.payer
                                                            })
                                                            // console.log(request_number)
                                                        var request_numberBase64 = Base64.encode(request_number)

                                                        var request_numberSign = "appid=ZLHIS6087743&data=" + request_numberBase64 + "&noise=ibuaiVcKdpRxkhJAXXXXX" + "&key=cda20555bfd3c0ee656f80d0cb&version=1.0";
                                                        var signEnd = hex_md5(request_numberSign).toUpperCase()

                                                        var request_end = { // 请求的最终数据
                                                            "appid": "ZLHIS6087743",
                                                            "data": request_numberBase64,
                                                            "noise": "ibuaiVcKdpRxkhJAXXXXX",
                                                            "version": "1.0",
                                                            "sign": signEnd
                                                        }
                                                        $.ajax({
                                                            url: ipVal + '/medical-web/api/medical/turnPaper?random= ' + Math.random(),
                                                            method: 'POST',
                                                            data: request_end,
                                                            contentType: 'application/json',
                                                            cache: false,
                                                            success: (function(res) {
                                                                console.log(res)
                                                                var result = Base64.decode(res.data)
                                                                var resultStr = JSON.parse(result)
                                                                if (resultStr.result !== 'S0000') {
                                                                    var resultStrT = Base64.decode(resultStr.message)
                                                                    alert(resultStrT) //错误提示
                                                                } else {
                                                                    var resultStrT = Base64.decode(resultStr.message)
                                                                    // alert("换开成功" + resultStrT) //换开成功=>操作成功 =>打印

                                                                    /*-------------------- 打印纸质票据---------------------分隔-------------------------------------------------------*/
                                                                    var testData = resulT_parse; //票据详情下的信息

                                                                    console.log(testData.cardNo + testData.payer)

                                                                    var str1 = "                                      四川省财政电子票据\n"
                                                                    var str2 = "                                   CHINA WELFARE LOTTERY\n\n"
                                                                    var str3 = "票据名称："+loadList[index].billName+"                电子票据代码:" + loadList[index].billBatchCode + "           电子票据号码：002045876\n" +
                                                                        "收款单位：" + testData.payee + "                                    电子票据检验码：" + testData.placeCode +
                                                                        "               电子票据开票日期：" + testData.busDateTime + "\n"

                                                                    var str4 =
                                                                        "费别                                金额                              项目                            单位                       单价                      数量\n" +
                                                                        "" + testData.chargeDetail[0].chargeName + "      " + testData.chargeDetail[0].amt +
                                                                        "" + testData.chargeDetail[0].chargeName + "       " + testData.chargeDetail[0].amt + "      " + testData
                                                                        .chargeDetail[0].chargeName + "    " + testData.chargeDetail[0].unit +
                                                                        "             160           6             960\n" +
                                                                        "合计:      " + testData.ownPay + "";
                                                                    var byteArray = new Array();
                                                                    getBinaryArrayData(str1, function(res1) {
                                                                        console.log(res1.length)
                                                                        byteArray[0] = 0xD;
                                                                        byteArray[1] = 0x1B;
                                                                        byteArray[2] = 0x40;

                                                                        byteArray[3] = 27; //居中
                                                                        byteArray[4] = 97;
                                                                        byteArray[5] = 1;

                                                                        byteArray[6] = 27; //字体样式
                                                                        byteArray[7] = 33;
                                                                        byteArray[8] = 0x38;
                                                                        byteArray[index++] = 27;
                                                                        byteArray[index++] = 33;
                                                                        byteArray[index++] = 8;
                                                                        var index = 9;
                                                                        byteArray[index++] = 27; //行距
                                                                        byteArray[index++] = 51;
                                                                        byteArray[index++] = 70;
                                                                        for (let i = 0; i < res1.length; i++) {
                                                                            byteArray[index++] = res1[i];
                                                                        }
                                                                        getBinaryArrayData(str2, function(res2) {
                                                                          byteArray[index++] = 27; //居中
                                                                          byteArray[index++] = 97;
                                                                          byteArray[index++] = 1;

                                                                            byteArray[index++] = 27;
                                                                            byteArray[index++] = 33;
                                                                            byteArray[index++] = 8;
                                                                            for (let j = 0; j < res2.length; j++) {
                                                                                byteArray[index++] = res2[j];
                                                                            }

                                                                            getBinaryArrayData(str3, function(res3) {
                                                                                // console.log(res3.length)
                                                                                byteArray[index++] = 27;
                                                                                byteArray[index++] = 33;
                                                                                byteArray[index++] = 0;
                                                                                byteArray[index++] = 27;
                                                                                byteArray[index++] = 97;
                                                                                byteArray[index++] = 0;
                                                                                for (let k = 0; k < res3.length; k++) {
                                                                                    byteArray[index++] = res3[k];
                                                                                }
                                                                                getBinaryArrayData(str4, function(res4) {
                                                                                    //  console.log(res4.length)
                                                                                    byteArray[index++] = 27;
                                                                                    byteArray[index++] = 33;
                                                                                    byteArray[index++] = 8;
                                                                                    for (let m = 0; m < res4.length; m++) {
                                                                                        byteArray[index++] = res4[m];
                                                                                    }
                                                                                    byteArray[index++] = 29;
                                                                                    byteArray[index++] = 86;
                                                                                    byteArray[index++] = 0;
                                                                                    const arrayBuffer = new Uint8Array(byteArray)
                                                                                    console.log(arrayBuffer)
                                                                                    const base64 = btoa(String.fromCharCode.apply(null, arrayBuffer));
                                                                                    console.log(base64)
                                                                                    jQuery.support.cors = true;
                                                                                    $.ajax({
                                                                                        url: 'https://yun.dascomyun.cn/15_printapi/v2.0/cloud_print',
                                                                                        contentType: 'application/json', // 默认值,
                                                                                        type: "POST",
                                                                                        data: JSON.stringify({
                                                                                            "number": '000BBF7350021C00',
                                                                                            "data": base64
                                                                                        }),
                                                                                        success: function(res) {
                                                                                            console.log(res.data)
                                                                                            alert(res.data)
                                                                                        },
                                                                                        fail: function(res) {
                                                                                            console.log(res.data)
                                                                                        }
                                                                                    })
                                                                                });
                                                                            });
                                                                        });
                                                                    });
                                                                    /*打印操作*/
                                                                }
                                                            }),
                                                            fail: (function(err) {
                                                                alert("请求出错" + err)
                                                            })
                                                        })
                                                    }
                                                }),
                                                fail: function(err) {
                                                    alert("请求出错" + err)
                                                }
                                            })

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
            }

        })
        /* */
    function getBinaryArrayData(text, resultCallBack) {

        var buffer = new Array(sizeOfGbk(text));
        // console.log(buffer)
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
    //分页

    function tabPage(tabPage) {
        var pageMain = $(tabPage.infoList_c)
            /*获取内容列表*/
        var pageNav = $(tabPage.pageNav)
            /*获取分页*/
        var pagePrev = $(tabPage.pagePrev)
            /*上一页*/
        var pageNext = $(tabPage.pageNext)
            /*下一页*/

        var curNum = tabPage.curNum
            /*每页显示数*/
        var len = Math.ceil(pageMain.find('.item').length / curNum)
        var itemNum = pageMain.find('.item').length //6
        console.log(itemNum)


        /*计算总页数*/
        console.log(len)
        var pageList = ''
            /*生成页码*/
        var iNum = 0
            /*当前的索引值*/
        for (var i = 0; i < len; i++) {
            pageList += '<a href="javascript:;">' + (i + 1) + '</a>'
        }
        pageNav.append(pageList)
            //首页高亮显示
        pageNav.find('a:first').addClass(tabPage.activeClass)

        /*******标签页的点击事件*******/
        pageNav.find('a').each(function() {
            $(this).click(function() {
                pageNav.find('a').removeClass(tabPage.activeClass)
                $(this).addClass(tabPage.activeClass)
                iNum = $(this).index()
                $(pageMain).find('.item').hide()
                for (var i = ($(this).html() - 1) * curNum; i < $(this).html() * curNum; i++) {
                    $(pageMain).find('.item').eq(i).show()
                }

            })
        })

        $(pageMain).find('li').hide()

        /************首页的显示*********/
        for (var i = 0; i < curNum; i++) {
            $(pageMain).find('.item').eq(i).show()
        }

        /*下一页*/
        pageNext.click(function() {
            console.log('点击下一页')
            $(pageMain)
                .find('.item')
                .hide()
            if (iNum == len - 1) {
                alert('已经是最后一页')
                for (var i = (len - 1) * curNum; i < len * curNum; i++) {
                    $(pageMain)
                        .find('li')
                        .eq(i)
                        .show()
                }
                return false
            } else {
                pageNav.find('a').removeClass(tabPage.activeClass)
                iNum++
                pageNav
                    .find('a')
                    .eq(iNum)
                    .addClass(tabPage.activeClass)
            }
            for (var i = iNum * curNum; i < (iNum + 1) * curNum; i++) {
                $(pageMain)
                    .find('.item')
                    .eq(i)
                    .show()
            }
        })

        /*上一页*/
        pagePrev.click(function() {
            console.log('上一页')
            $(pageMain)
                .find('.item')
                .hide()
            if (iNum == 0) {
                alert('当前是第一页')
                for (var i = 0; i < curNum; i++) {
                    $(pageMain)
                        .find('.item')
                        .eq(i)
                        .show()
                }
                return false
            } else {
                pageNav.find('a').removeClass(tabPage.activeClass)
                iNum--
                pageNav
                    .find('a')
                    .eq(iNum)
                    .addClass(tabPage.activeClass)
            }
            for (var i = iNum * curNum; i < (iNum + 1) * curNum; i++) {
                $(pageMain)
                    .find('.item')
                    .eq(i)
                    .show()
            }
        })
    }



    // 点击查询 ， 时间查询
    $('.caXun').on('click', function() {

        var time = $('.data').val()
        console.log(time)
            // $.ajax({
            //   url: ipVal + '/medical-web/api/medical/getEBillUnPrintList',
            //   type: 'POST',
            //   data: {
            //     times: times
            //   },
            //   contentType: 'application/json',
            //   dataType: 'json',
            //   success: (function (res) {
            //     console.log(res)
            //   }),
            //   fail: (function (err) {
            //     alert(err)
            //   })
            // })
    })

    $('.con_cc').on('click', function() {
        $('.maskInfo').show()
        $('.maskInfo').animate({
            height: '700px',
            width: '900px'
        })
    })

    $('.isTrue').click(function() {
            //调用接口，判断是否ocx能和网页进行连接
            WEB_OcxTest()

        })
        //ocx测试控件连接
    function WEB_OcxTest() {
        feedback = DS_1870.OcxTest();
        if (feedback) {
            $('.loadEffect').show()
            setTimeout(function() {
                $('.loadEffect').hide()
                $('.maskInfo').hide()
                $('.user').show()

                WEB_EnterCard();

            }, 1000)
        } else {
            alert("ocx链接失败")
        }
    }
    //允许进卡
    function WEB_EnterCard() {
        feedback = DS_1870.EnterCard();
        console.log("进卡" + feedback)
        if (feedback) {
            alert("进卡成功");
            $('.loadEffect').show()
            setTimeout(function() {
                $('.loadEffect').hide()
                $('.maskInfo').hide()
                $('.user').show()
            }, 1000)
            WEB_ReadMagcard(); //获取磁卡信息
        } else {
            alert("进卡超时");
            WEB_MoveCard(); //退卡
        }
    }

    function WEB_MoveCard() //退卡
    {
        feedback = DS_1870.MoveCard();
        console.log("退卡" + feedback)
        if (feedback) {
            alert("退卡成功");
        } else {
            alert("退卡失败")
        }
    }

    function WEB_ReadMagcard() //读磁条卡
    {
        feedback = DS_1870.ReadMagcard();
        console.log("读磁卡" + feedback)

        if ("" != feedback) {
            alert(feedback)
        } else {
            alert("无磁卡信息")
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

    $('.userIstrue').click(function() {
        //执行loading
        // load()
        $('.loadEffect').css('z-index', '2000')
        $('.loadEffect').show()
        setTimeout(function() {
            $('.loadEffect').hide()
            $('.user').hide()
            $('.infoListW').show()
        }, 1000)
    })

    $('.print').click(function() {
        $('.loadEffect').show()
        setTimeout(function() {
            $('.loadEffect').hide()
            if ($('.loadEffect').css('display') == 'none') {
                alert('打印成功')
            } else {
                alert('打印失败')
            }
        }, 2000)
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