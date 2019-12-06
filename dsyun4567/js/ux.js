define(function(require, exports, module) {
	var $ = require('zepto') //他其实和jquery是一样的
		,
		Swiper = require('swiper') //轮播插件
		,
		ua = navigator.userAgent.toLowerCase() //ua
		,
		isWeixin = ua.indexOf('micromessenger') != -1 //如果是微信浏览器
		,
		hhref = location.href //整个href值
		,
		crr = hhref.split("#")[1] //打印机编号
		,
		wx = require('wx') //需求到微信sdk
		,
		constant = require("constant") //需求到接口文件
		,
		UrlJoint1 = constant.EInvoicePrint_PrintApi_15_1 //url拼
		,
		UrlJoint12 = constant.EInvoicePrint_PrintApi_15_2 //url拼
		,
		UrlJoint2 = constant.EInvoicePrint_WeiXin_12_1,
		UrlJoint5 = constant.EInvoicePrint_WeiXin_12_2,
		hash = window.location.hash //hash值
		,
		cubicBezier = "cubic-bezier(0,.09,0,1)" //贝塞尔动画曲线
		,
		cubicBezier2 = "cubic-bezier(0,1.37,.44,.95)",
		cubicBezier3 = "cubic-bezier(0,.65,.12,1.66)",
		sasb = [] //缓存用
		,
		Name //用于发票名字
		, SetSpace = sessionStorage.getItem('allSpace') //所有发票
		,
		lockersval //抽屉控件的变量
		, isURI = /(https?|ftp|file|http):\/\/[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]/,
		uas = navigator.userAgent //也是ua的意思
		,
		ipad = uas.match(/(iPad).*OS\s([\d_]+)/) //如果是ipad
		,
		isIphone = !ipad && uas.match(/(iPhone\sOS)\s([\d_]+)/) //如果是iphone
		,
		isAndroid = uas.match(/(Android)\s+([\d.]+)/) //如果是安卓
		,
		isMobile = isIphone || isAndroid //是否手机
		,
		off = false //开关
		,
		printNumber = sessionStorage.getItem("printNumber") //打印机编号
		,
		space_list = [] //发票列表
		,
		intervalLoading //loading的动画定时器
		, intervalLoading2, one = true,
		credentials = true,
		APPID = 'wx4943f6480a79a436'

	window.URL = window.URL || window.webkitURL;
	//所有的全局变量

	/*
	    快速定位搜索   双击 > 复制 > ctrl+f > 粘贴 > 搜索  || 定位完成
	    bug在这里（这是出现bug的mark）
	    url拼接
	    
	    轮询打印机

	    渲染模板  渲染模块
	    
	    上传限制
	    转2进制文件
	    缓存盒子
	    打印按钮
	    后端打印模块
	    抽屉弹窗控件
	    弹窗控件

	    微信发票
	    短信打印
	    本地上传事件

	    重新加载页面或者刷新时
	    各种页面弹出的方法
	    懒加载banner图片
	    loading动画
	    清除动画 loading动画
	    遮罩层控件

	    
	    邮箱打印事件
	    删除打印发票事件
	    按钮开关与事件

	    预览图片的大小
	    点击阈值调节事件
	    阈值界面设置
	*/

	function GetsThePrinterStatus() {
		var hash = window.location.hash;
		if(hash.length > 16) {
			indexalert()
		}
	}
	GetsThePrinterStatus()
	//url拼接

	var constants = {
		OpenId: function() {
			return UrlJoint2 + "/openid?code="
			//短信打印
		},
		urlstatus: function() {
			return UrlJoint1 + "/v2.0/judge"
			//短信打印
		},

		printAll: function() {
			return UrlJoint1 + '/v2.0/print/' //12.18
			//三种打印已经融合了
		},

		getcont: function() {
			return UrlJoint1 + '/v2.0/restrictPrint?number='
		},

		preview: function() {
			return UrlJoint1 + '/v2.0/preview/'
			//预览打印
		},
		previewqgg: function() {
			return UrlJoint12 + '/v2.0/preview/'
			//去广告预览打印
		},
		config: function() {
			return UrlJoint5 + '/configSign' //UrlJoint2+'/configSign'
			//获取 wx配置
		},
		ticketSign: function() {
			return UrlJoint5 + '/cardSign'
			//拉取发票签名
		},
		fetchTicket: function() {
			return UrlJoint5 + '/cardInfo/' + APPID
			//拉取
		},
		checkPrinter: function() {
			return UrlJoint1 + '/v2.0/CheckPrinter/'
			// [number] 验证设备号是否合法
		},
	}

	//alert(constants.UserOperationData()+"123")

	//根据路由跳转页面
	window.onhashchange = function() { //监听hash值变化，实现页面变换
		var hash = window.location.hash; //获取url#以后的内容（包括#）
		console.log(hash)
		changePage(hash); //监听hash值然后传进这个方法里面，他会根据hash值去弹出相对应的页面

	}

	function changePage(hash) {
		//alert(hash)
		$(".msm_print_box").animate({
			transform: "scale(0)"
		}, 200)
		$(".space_upload").css("display", "block")
		$(".lodin_box").css("transform", "rotate(0)")
		msmH()
		if(hash == '') {
			// alert('我是空'+hash)
			return false
		}
		if(hash.length > 16) {
			AllSpaceRem() //回到主页就要清空票夹
			$(".index").css({
				'z-index': '10',
			})
		}
		if(hash != "#index") {
			// alert(hash)
			//$(".return").animate({transform:"translateY(0rem)"},400)
			$(".index").css({
				'z-index': '10',
			})
			$(".index").animate({
				"opacity": "1",
				"transform": "scale(1)"
			}, 140, cubicBezier)
			$(".index_icon_in").css({
				"opacity": "0",
				"transform": "scale(1)"
			})
			$(".index_txt").css("color", "black")
			$(".title").html("主页")
		} else {
			// alert(hash)
			indexalert()
		}

		if(hash != "#print") {
			$(".print").css({
				"z-index": "1",
				"transform": " translateX(130%)"
			})
			$(".print").animate({
				"opacity": "0",
				"transform": "scale(0.9) translateX(130%)"
			}, 140, cubicBezier)
			$(".aj_input").animate({
				transform: " translateY(3.5rem)"
			}, 600)
			hidBtn()
			previewH()
			$(".aj_input").animate({
				transform: " translateY(3.5rem)"
			}, 140)
		} else {
			printalert()
		}
	}
	//清除动画 loading动画
	//使用他时，传个参数1进去的话，就会往#index哪里跳转，
	//hash是index的话自动登录不会生效，一般调用不传1
	function clearanimate(val) {
		var b = 1
		if(val == 1) {
			sessionStorage.setItem("b", b)
			// window.location.href = '#index';
			//alert("执行")
			// indexalert()
		}
	}
	//进入的时候如果有number号的话就存起来
	if(crr != undefined || crr != null) {
		if(crr.length > 9) { //#后面的长度大于9的时候
			sessionStorage.setItem("printNumber", crr);
		}
	}
	printPlliing();
	if(sessionStorage.getItem("b")) {
		clearanimate()
	} else {
		if(isWeixin) {
			getWxUserInfo()
		} else {
			var val = 1
			clearanimate(val)
		}
	}

	//重新加载页面或者刷新时，监听路由事件不好使了，得用这个判断
	if(hash == "#index") {
		indexalert()
	} else if(hash == "#print") {
		printalert()
	}

	//各种页面弹出的方法
	function indexalert() {
		entrance = ""
		AllSpaceRem() //回到主页就要清空票夹
		//$(".return").animate({transform:"translateY(-100%)"},400)
		clearanimate(1)
		//hashReturn($(".index"))

		$(".index").css("z-index", "10")
		$(".index").animate({
			"opacity": "1",
			"transform": "scale(1)"
		}, 600, cubicBezier)

		$(".index_txt").css("color", "#fb4e7a")
		$(".index_icon_in").css({
			"opacity": "1",
			"transform": "scale(1.3)"
		})

		$(".title").html("主页")
	}

	function printalert() {
		clearInterval(set1);
		template()
		$(".aj_input").animate({
			transform: " translateY(0rem)"
		}, 600, cubicBezier)
		//hashReturn($(".print"))

		$(".print").css({
			"z-index": "10",
			"transform": " translateX(130%)"
		})
		$(".print").animate({
			"opacity": "1",
			"transform": "scale(1) translateX(0%)"
		}, 600, cubicBezier)

		$(".title").html("打印发票")
	}

	//懒加载banner图片
	setTimeout(function() {
		var img_len = $(".swiper-slide").children("img").length
		for(var i = 0; i < img_len; i++) {
			var srcc = $(".swiper-slide").children("img").eq(i).attr("src-data")
			$(".swiper-slide").children("img").eq(i).attr("src", srcc)
			setTimeout(function() {
				$(".swiper-slide").children("img").css('opacity', '1')
			}, 5)
		}
	}, 10)

	//loading动画
//	function scale() {
//		$(".loading_img").animate({
//			transform: "scale(0.7)"
//		}, 500, cubicBezier, function() {
//			$(this).animate({
//				transform: "scale(1)"
//			}, 100, cubicBezier3, function() {
//				setTimeout(rotateY, 1500)
//			})
//
//		})
//	}

//	function rotateY() {
//		$(".loading_img").animate({
//			transform: "rotateY(180deg)"
//		}, 600, cubicBezier, function() {
//			$(this).css("transform", "rotateY(0deg)")
//			setTimeout(scale, 100)
//		})
//	}
//	rotateY()

	//遮罩层控件
	function maskS() {
		$(".maskLayer").animate({
			display: "block"
		}, 14, function() {
			$(this).animate({
				opacity: "1"
			}, 300)
		})
	}

	function maskH() {
		$(".maskLayer").animate({
			display: "none"
		}, 14, function() {
			$(this).animate({
				opacity: "0"
			}, 300)
		})
	}

	//抽屉弹窗控件
	//弹窗控件
	function lockers(lockersval) {

		var html = (`
				<section class="locker_warp">
				    <section class="locker">
				    	<section class="locker_ts">错误提示</section>
				    	<section class="locker_img"><img src="../img/public/cuowu@2x.gif"/></section>
					    <section class="locker_con"></section>
					    <section id="locker_btn" class="locker_btn">确定</section>
				    </section>
				    <section class="locker_blur"></section>
				</section>
			`)
		$("body").append(html)
		$(".locker").css("transform", "translateY(-150%)")
		$(".locker_con").html(lockersval)
		$(".locker").animate({
			transform: "translateY(0%)"
		}, 300, cubicBezier)
		var parents = $(".locker").length
		if(parents == 2) {
			$(".locker_warp").eq(0).remove()
		}
	}
	$("body").on('tap', '.locker_blur', function() {
		lockerh()
	})

	function lockerh() {
		$(".locker").eq(0).animate({
			transform: "translateY(-150%)"
		}, 30, cubicBezier, function() {
			$(".locker_warp").eq(0).remove()
		})
	}
	$("body").on("touchmove", '.locker', function() {
		lockerh()
	})
	$("body").on("tap", ".locker_btn", function() {
		lockerh()
	})

	//轮询打印机
	var resmain;
	var t = 200;
	var set1 = setInterval(printPlliing, t);

	function printPlliing(val) {

		var printNumber = sessionStorage.getItem("printNumber")
		if(!printNumber) {
			if(val == 1) {
				lockers("未获取到打印机编号")
			}
			$(".munber_status").html("编号为空").css("color", "red")
			$(".munber_img").attr("src", "../img/public/cuo@2x.png")
			return false;
		}
		$(".munber").html(printNumber)
		if(printNumber.length != 16) {
			$(".munber_status").html("打印机编号错误")
			$(".munber_img").attr("src", "../img/public/cuo@2x.png")
			printStateTxt()
			return false;
		}
		$.ajax({
			url: constants.checkPrinter() + printNumber,
			complete: function(xhr) {
				var res = JSON.parse(xhr.response),
					txtState

				if(res.code == 0) {
					if(res.data.main == "错误") {
						txtState = "离线"
					} else {
						txtState = res.data.main
					}
					//					txtState = res.data.main
					// GetsThePrinterStatus()
				} else {
					txtState = res.data
				}

				$(".munber_status").html(txtState)
				//.html(printStatus(res.code))
				printStateTxt()

				if(res.code != "0") {
					if(one == true) {
						lockers(txtState)
						one = false
					}
				}
				if(res.data.main == undefined) {
					console.log("打印机状态：" + res.data)
				} else {
					console.log("打印机状态：" + res.data.main)
				}
				clearInterval(set1);

				if(txtState == "正常") {
					//					lockerh()
					$(".munber_img").attr("src", "../img/public/dui@2x.png")
					clearInterval(set1);
					//					t = 20000;
					//					set1 = setInterval(printPlliing, t);
				} else {
					$(".munber_img").attr("src", "../img/public/cuo@2x.png")
					clearInterval(set1);
					t = 1000;
					set1 = setInterval(printPlliing, t);
				}
			}
		})

	}
	$()
	//$(function () {
	//printPlliing()
	//})

	//setInterval(printPlliing, 10000)
	setInterval(printStateTxt, 6000)

	function printStateTxt() {
		var statu = $(".munber_status").html()

		if(statu == "正常") {
			$(".munber_status").css("color", "black")
			$(".status_img").css("background-color", "rgb(51, 153, 204)")
			$(".ber_top_img").attr("src", "../img/public/printy.png")
		} else {
			$(".munber_status").css("color", "red")
			$(".ber_top_img").attr("src", "../img/public/printx.png")
			$(".status_img").css("background-color", "red")
		}

	}

	/**
	 *************************************************************
	 * 打印
	 *************************************************************
	 */

	//打印界面的小电池
	function battery() {
		var len = $(".print_space_list").children("li").length
		var battery = $(".print_len").children("i")
		if(len == 0) battery.attr("class", "level0")
		if(len == 1) battery.attr("class", "level1")
		if(len == 2) battery.attr("class", "level2")
		if(len == 3) battery.attr("class", "level3")
		if(len == 4) battery.attr("class", "level4")
		if(len == 5) battery.attr("class", "level5")
	}

	//上传限制
	function Suffix(fileType) {
		if(fileType == undefined) return false;
		var pdfType = fileType.name.split(".")
		var size = fileType.size
		var type = fileType.type
		//		if(pdfType[pdfType.length - 1] != "pdf") {
		//			lockers("只能上传pdf文件类型，您上传的文件类型为 [." + pdfType[pdfType.length - 1] + "]格式")
		//			
		//			return false;
		//		} else 
		if(size > 1048576 * 2) {
			lockers('请上传不超过2M的文件')

			return false;
		} else {
			return true;
		}
	}

	//转2进制文件
	function dataURItoBlob(base64Data) {
		var byteString;
		if(base64Data.split(',')[0].indexOf('base64') >= 0)
			byteString = atob(base64Data.split(',')[1]);
		else
			byteString = unescape(base64Data.split(',')[1]);
		var mimeString = base64Data.split(',')[0].split(':')[1].split(';')[0];
		var ia = new Uint8Array(byteString.length);
		for(var i = 0; i < byteString.length; i++) {
			ia[i] = byteString.charCodeAt(i);
		}
		return new Blob([ia], {
			type: mimeString
		});
	}
	//渲染模板  渲染模块
	//渲染模块，拿缓存里面的数据出来渲染，而不是直接渲染
	//当缓存更新的时候调用一次这个方法，就可以不刷新页面进行渲染
	function template() {
		var allSpace = sessionStorage.getItem('allSpace')

		//缓存存在的时候自做这些事
		if(allSpace) {
			sasb = JSON.parse(allSpace)
			var htmlPrint = "";
			for(var i = 0; i < sasb.length; i++) {

				//发票的uploadParameter值标示他是从哪里传进来的发票
				//分有wecat、 msm、 file、 ticket 四种，每种的渲染方式不同
				//console.log(sasb[i].url[0])
				if(sasb[i].uploadParameter == "file") {
					htmlPrint += (`
						<li class="print_space_list_loca"   data-type = "${sasb[i].uploadParameter}"  >
	            			<div class="print_space_name">${sasb[i].name}</div>
	            			<div class="">
	            				<span class="print_space_money">大小：${sasb[i].size}</span>
	            			</div>
	            			<div class="sta">状态：</div>
	            			<i class="print_space_delete"></i>
	            			<i class="print_space_preview"></i>
	            			<i class="printq_space_blur"></i>
	            		</li>	
					`)
					$(".print_space_list").html(htmlPrint)
				}

				//短信链接
				if(sasb[i].uploadParameter == "msm") {
					var urls
					if(sasb[i].url) {
						urls = sasb[i].url
					} else {
						urls = sasb[i].Url
					}
					htmlPrint += (`
						<li class="print_space_list_msm" data-type = "${sasb[i].uploadParameter}" data-src = "${sasb[i].url}" >
	            			<div class="print_space_name">${sasb[i].buyName}</div>
	            			<div class="print_space_money_msm">
	            				<span class="print_space_money_msm">链接地址：${urls}</span>
	            			</div>
	            			<div class="sta">状态：</div>
	            			<i class="print_space_delete"></i>
	            			<i class="print_space_preview"></i>
	            			<i class="print_space_blur"></i>
	            		</li>	
					`)
					$(".print_space_list").html(htmlPrint)
				}
				//微信票夹
				if(sasb[i].uploadParameter == "wecat") {
					//在这里解时间戳
					var timer = sasb[i].timer
					var date = new Date(timer * 1000); //时间戳为10位需*1000，时间戳为13位的话不需乘1000
					var Y = date.getFullYear() + '年';
					var M = (date.getMonth() + 1 < 10 ? '0' + (date.getMonth() + 1) : date.getMonth() + 1) + '月';
					var D = date.getDate() + '日';
					var timers = Y + M + D
					htmlPrint += (`
						<li data-id = "${sasb[i].id}" class="print_space_list_wx" data-type = "${sasb[i].uploadParameter}" data-src = "${sasb[i].url}" >
	            			<div class="print_space_name">${sasb[i].name}</div>
	            			<div class="">
	            				<span class="print_space_money">金额：${sasb[i].money}</span>
	            				<span class="print_space_dateTime">时间：${timers}</span>
	            			</div>
	            			<div class="print_space_buyName">抬头：${sasb[i].title}</div>
	            			<div class="sta">状态：</div>
	            			<i class="print_space_delete"></i>
	            			<i class="print_space_preview"></i>
	            			<i class="print_space_blur"></i>
	            		</li>	
					`)
					$(".print_space_list").html(htmlPrint)
				}
			}
		}
		//在这里执行一次电池，
		battery()
	}
	template()
	//删除打印发票事件
	$(".print_space_list ").on("tap", "li .print_space_delete", function() {
		$(".print_space_blur").css("display", "block")
		var Index = $(this).parent().index()
		sasb.splice(Index, 1);
		sessionStorage.setItem("allSpace", JSON.stringify(sasb));
		$(this).parent().animate({
			transform: "translateX(-140%)"
		}, 300, function() {
			$(this).animate({
				height: "0rem"
			}, 640, cubicBezier, function() {
				$(this).remove()
				$(".print_space_blur").css("display", "none")
				battery()
			})
		})
	})
	//本地上传事件
	$(".main").on("touchstart", function() {
		var status = $(".munber_status").html()
		if(status != "正常") {
			$(".munber_img").attr("src", "../img/public/cuo@2x.png")
			lockers(status)
			return false;
		}
	})

	$(".loca_space").on("change", function(e) {
		$(".bendi").attr("src", "../img/bendifapiao@2x.gif");
		setTimeout(function(){
			var file = e.target.files[0] //拿到change的文件
			if(!Suffix(file)) return;

			var len = $(".print_space_list").children("li").length
			if(len == 5) {
				lockers("发票最大数为5")
				return false;
			}
			var reader = new FileReader();
			
			if(credentials == true) {
				reader.onload = function(e) {
					SpaceBox({
						Url: e.target.result,
						name: file.name,
						size: Math.round(file.size / 1024) + "kb",
						uploadParameter: "file"
					})
					template()
				}
			}

			reader.readAsDataURL(file);
			location.href = "#print"
			setTimeout(function() {
				$(".loca_space").val("")
			}, 300)
			$(".bendi").attr("src", "../img/public/bendifapiao@2x.png");
		},1000)
		
	})


	//按钮开关与事件

	function hidBtn() {
		if(off == true) {
			$('.input_blur_img').animate({
				transform: " rotate(0deg)"
			}, 550, cubicBezier, function() {
				off = false
			})
			$('.input_msm').animate({
				"transform": "translate(0rem,0rem) scale(0.5)"
			}, 250)
			$('.input_wx').animate({
				"transform": "translate(0rem,0rem) scale(0.5)"
			}, 180)
			$('.input_loca').animate({
				"transform": "translate(0rem,0rem) scale(0.5)"
			}, 140)
		}
	}

	function alertBtn() {
		if(off == false) {
			$('.input_blur_img').animate({
				transform: " rotate(225deg)"
			}, 550, cubicBezier, function() {
				off = true
			})
			$('.input_msm').animate({
				"transform": "translate(0,-6.3rem) scale(1)"
			}, 500, cubicBezier)
			$('.input_wx').animate({
				"transform": "translate(0,-4.3rem) scale(1)"
			}, 300, cubicBezier)
			$('.input_loca').animate({
				"transform": "translate(0,-2.3rem) scale(1)"
			}, 200, cubicBezier)
		}
	}

	$('.push_btn').on("touchstart", function() {
		var status = $(".munber_status").html()
		if(status != "正常") {
			lockers("打印机状态错误")
			return false;
		}
	})
	$('.push_btn').on("tap", function() {
		var len = $(".print_space_list").children("li").length
		if(len == 5) {
			lockers('最多选择5张发票');
			return false;
		}
		hidBtn()
		alertBtn()
		$(".msm_prin_btn").children("div").attr("class", "msm_true")
		$(".msm_prin_ttitle").html("请输入短信链接")
		return false;
	})

	$("body").on("tap", function() {
		hidBtn()
	})
	//按钮开关结束

	//微信发票
	// 注意！！拉微信发票的时候只会弹一次框

	$(".input_wx_function").on("tap", function() {
		$(".weixin").attr("src", "../img/weixinkabao@2x.gif");
			var number = sessionStorage.getItem("printNumber");
			var datas;
			$.ajax({
				type: "GET",
				url: constants.getcont() + number,
				complete: function(xhr) {
					datas = JSON.parse(JSON.parse(xhr.responseText).data)
					//				console.log(JSON.parse(datas).公司名称)
					//			alert(datas)
				}
			});

			//alert(location.href.split('#')[0]);
			$.ajax({
				url: constants.config(),
				type: 'GET',
				data: {
					//   url: 'https://yun.dascomyun.cn/eip/hangxin/html/index.html',
					url: location.href.split('#')[0],
					appid: APPID //@todo 重要：后台需要获取签名使用
				},
				timeout: 10000,
				dataType: 'json',
				success: function(res) {
//					console.log(res)
					wx.config({
						beta: true,
						debug: false, // 开启调试模式,调用的所有api的返回值会在客户端alert出来，若要查看传入的参数，可以在pc端打开，参数信息会通过log打出，仅在pc端时才会打印。
						appId: res.appid, // 必填，公众号的唯一标识
						timestamp: res.timestamp, // 必填，生成签名的时间戳
						nonceStr: res.nonceStr, // 必填，生成签名的随机串
						signature: res.signature, // 必填，签名，见附录1
						jsApiList: ['chooseInvoice', 'scanQRCode'], // 必填，需要使用的JS接口列表，所有JS接口列表见附录2
					});
				},
				complete: function(xhr) {

					console.log('微信配置：', xhr);
					var status = xhr.status;
					if(status != 200) {

						if(status == 0) {

							lockers('配置失败：');
						}
						//					failModal({
						//						data: '配置失败:是否重新配置？',
						//						cancelText: '否',
						//						confirmText: '是',
						//					});
					} else {
						//alert(APPID);
						$.ajax({
							url: constants.ticketSign(),
							dataType: 'json',
							type: 'POST',
							data: {
								appid: APPID
							},
							success: function(res) {
								
								///拉取发票列表
								////////
								// alert("第一次配置请求成功");
								//alert(res.cardSign);
								setTimeout(function() {
									wx.invoke('chooseInvoice', {
											timestamp: res.timestamp, //卡券签名时间戳
											nonceStr: res.nonceStr, //卡券签名随机串
											signType: 'SHA1', //签名方式，默认'SHA1'
											cardSign: res.cardSign, //卡券签名
										},
										function(res) {
											//alert(res.err_msg);
											var msg = res.err_msg;
											if(res.choose_invoice_info) {
												var invoiceInfo = JSON.parse(res.choose_invoice_info);
												for(var i = 0; i < invoiceInfo.length; i++) {
													delete invoiceInfo[i].app_id
												}
											}
											if(!/ok/.test(msg)) {
												$(".weixin").attr("src", "../img/public/weixinkabao@2x.png");
												//console.warn('拉取发票失败或是取消,choose_invoice_info 为空');
												// location.href = "#print" //用户操作 上一页按钮
												// 手机返回键
												return false;
											}
											// invoiceInfo = JSON.parse(res.choose_invoice_info);

											//for (var i = 0; i < invoiceInfo.length; i++) {
											//   delete invoiceInfo[i].app_id
											//  }
											// alert(JSON.stringify(invoiceInfo))

											//alert('拉取发票的信息：' + JSON.stringify(res))
											//alert(JSON.parse(invoiceInfo).length === 0)
											$.ajax({
												url: constants.fetchTicket(),
												data: JSON.stringify(invoiceInfo),
												type: 'POST',
												dataType: 'json',
												//拉取回来的 choose_invoice_info
												headers: {
													'Content-Type': 'application/json',
												},
												success: function(res) {
													$(".weixin").attr("src", "../img/public/weixinkabao@2x.png");
													var wecatSpace = []
													var sec = []
													for(var i = 0; i < res.length; i++) {
														//alert(i);
														var res1 = JSON.parse(res[i])
														var wecatList = [];
														wecatList.push(res1.user_info.pdf_url);
														//alert(res1.payee)
														if(datas != undefined) {
															if(datas.纳税人识别号 != "" && datas.公司名称 !=""){
																if(res1.user_info.buyer_number == "" && res1.user_info.title == "" && res1.payee == "" && res1.user_info.seller_number == "") {
																	lockers('打印失败：限制打印！');
																	return false;
																}
																if(res1.user_info.buyer_number == datas.纳税人识别号 || res1.user_info.title == datas.公司名称 || res1.user_info.seller_number == datas.纳税人识别号 || res1.payee == datas.公司名称) {
	
																} else {
																	lockers('打印失败：限制打印！');
																	return false;
																}
															}
														}

														if(credentials == true) {
															wecatSpace.push({
																name: res1.payee,
																timer: res1.user_info.billing_time,
																id: res1.card_id,
																Url: res1.user_info.pdf_url,
																title: res1.user_info.title,
																money: res1.user_info.fee / 100,
																openid: res1.openid,
																uploadParameter: "wecat"
															})
														} else {
															wecatSpace.push({
																name: res1.payee,
																timer: res1.user_info.billing_time,
																id: res1.card_id,
																url: wecatList,
																title: res1.user_info.title,
																money: res1.user_info.fee / 100,
																openid: res1.openid,
																uploadParameter: "wecat"
															})
														}

														//alert(JSON.stringify(wecatSpace))

														SpaceBox(wecatSpace[i])
														template()
														location.href = "#print"
														//														var aaa = JSON.stringify(sessionStorage.getItem("allSpace"))
														//														lockers(aaa)
													}

													console.log('请求发票列表数据成功');
													//渲染发票数据
													/////
													//不存在，返回不操作
													if(0 == res.length) {
														//
														lockers('拉取数据为空!');
														return false;
													}
													//alert(res)
												},
												complete: function(xhr) {
													console.log('请求发票列表数据complete: ', xhr);
													var status = xhr.status;
													if(200 != status) {

														lockers('拉取数据失败！' + status);
													}
												},
											});

											//一定要 解析为 JSON 对象
											//
											//数据为空
											//alert("微信发票信息"+invoiceInfo);
											if(0 === JSON.parse(invoiceInfo).length) {}
											//点击"确定"
											// 先不用管 数据是否为空
											//拉取发票起效

										});

								}, 100)

							},
							complete: function(xhr) {
								console.log('发票签名！', xhr);
								var status = xhr.status;
								if(status != 200) {
									lockers('发票签名失败，无法拉取！');
								}
							},
						});
					}

				},
			});
	})

	//短信打印
	$(".input_msm_function").on("tap", function() {
		$(".duanxin").attr("src", "../img/duanxindayin@2x.gif");
		setTimeout(function() {

			$(".msm_print_box").animate({
				transform: "scale(1)"
			}, 200, cubicBezier)
			maskS()
			$(".duanxin").attr("src", "../img/public/duanxindayin@2x.png");
		}, 1000);
	})
	$(".msm_false").on("tap", function() {
		msmH()
	})

	function msmH() {
		$(".msm_print_box").animate({
			transform: "scale(0)"
		}, 200, cubicBezier)
		$(".msm_print_val").val("")
		maskH()
	}

	$(".msm_prin_btn").on("tap", ".msm_true", function() {
		$(".blurs").css("display", "block")
		setTimeout(function() {
			$(".blurs").css("display", "none")
		}, 3000);
		var values = $(".msm_print_val").val()
		var isFileExtension = values.toLowerCase();
		if(values == "") {
			$(".msm_prin_ttitle").html("链接不能为空").css("color", "red")
			setTimeout(function() {
				$(".msm_prin_ttitle").html("请输入短信链接").css("color", "black")
			}, 3000)
		}
		//		else if(isFileExtension.indexOf(".png") != -1 || isFileExtension.indexOf(".jpg") != -1 || isFileExtension.indexOf(".jpeg") != -1 || isFileExtension.indexOf(".gif") != -1) {
		//			$(".msm_prin_ttitle").html("请输入正确的URL").css("color", "red")
		//			setTimeout(function() {
		//				$(".msm_prin_ttitle").html("请输入短信链接").css("color", "black")
		//			}, 3000)
		//		} 
		else {
			//截取短信里的url
			var Url, ap, bba, we, be, be2, ap, https = 'https://'
			var url = JSON.stringify(values);
			var uurl = values;
			console.log()
			var nn = url.substr(url.length - 3, 2);
			if(nn == "\\n") {
				url = url.split('\\n')[0] + '"';
			}
			be = url.split('http')[1];
			be2 = url.split('nnfp')[1];
			if(be) {
				Url = "http";
				we = url.split('http')[1];
				console.log(we)
				ap = Url + we;
			} else if(be2) {
				Url = "nnfp";
				we = url.split('nnfp')[1];
				ap = https + Url + we;
			} else {
				$(".msm_prin_ttitle").html('请输入正确的URL').css("color", "red");
				setTimeout(function() {
					$(".msm_prin_ttitle").html("请输入短信链接").css("color", "black")
				}, 3000);
				return false;
			}

			if(ap.indexOf('"') != -1) {
				bba = ap.split('"')[0];
			}
			if(ap.indexOf("，") != -1) {
				bba = ap.split("，")[0];
			}
			if(ap.indexOf(',') != -1) {
				bba = ap.split(',')[0];
			}
			if(ap.indexOf('  ') != -1) {
				bba = ap.split('  ')[0];
			}
			if(ap.indexOf(" ") != -1) {
				bba = ap.split(" ")[0];
			}
			if(ap.indexOf('[') != -1) {
				bba = ap.split('[')[0];
			}
			if(ap.indexOf('\\n') != -1) {
				bba = ap.split('\\n')[0];
			}
			if(ap.indexOf('，') != -1) {
				bba = ap.split('，')[0];
			}
			if(bba == undefined) {
				bba = uurl;
			}
			bba = bba.replace("”。", "");
			if(bba.length > 101 && bba.indexOf("http://pis.baiwang.com/invoice?param=") != -1) {
				bba = bba.substring(0, 101);
			}

			//			if (we == undefined) {
			//				$('.mask-loading-wrap').css('display', 'none');
			//				alertModal('请输入正确的URL');
			//				return false;
			//			} else {
			var obj = {};
			obj.url = bba;
			//return false;

			$.ajax({
				type: "post",
				url: constants.urlstatus(),
				async: true,
				data: JSON.stringify(obj),
				headers: {
					'Content-Type': 'application/json'
				},
				complete: function complete(xhr) {

					var res = xhr.responseText;
					var code = JSON.parse(res).code
					var data = JSON.parse(res).data
					var fun = []
					var bbalist = [];
					bbalist.push(bba);
					//后台bug,临时手段
					if(code == 0 || data == "url返回状态码:414") { //0是成功
						if(credentials == true) {
							fun.push({
								Url: bba,
								buyName: "短信链接发票",
								uploadParameter: "msm",
							})
							//把url装进缓存盒子里面去，然后在调用模板方法
							SpaceBox(fun[0])
						} else {
							fun.push({
								url: bbalist,
								buyName: "短信链接发票",
								uploadParameter: "msm",
							})
							//把url装进缓存盒子里面去，然后在调用模板方法
							SpaceBox(fun[0])
						}

						template()

						msmH()
						location.href = "#print"
					} else {
						$(".msm_prin_ttitle").html('该url无法解析').css("color", "red")
						setTimeout(function() {
							$(".msm_prin_ttitle").html("请输入短信链接").css("color", "black")
						}, 3000)
						return false;
					}
				}
			});
		}

	})

	//点击打印 时触发
	function printReturn() {
		$(".print_blur_txt").html("发送打印中，请稍等")
		$(".print_blur").animate({
			transform: "scale(1)"
		}, 200, cubicBezier)
	}
	//打印成功吼掉这个
	function printbtn() {
		$(".print_blur_txt").html("打印完成")
		$(".aj_print_btn").animate({
			transform: "scale(1)"
		}, 600, cubicBezier)
		$("#printmian").html("true")
		$("#printover").html("false")
	}
	//这里要写删除发票的代码
	$(".aj_print_btn").on("tap", function() {

		AllSpaceRem()
		$("#printover").html("true")
	})

	function AllSpaceRem() {
		//删除不清空sasb,所以做个空的传进去
		sasb = []
		sessionStorage.setItem("allSpace", JSON.stringify(sasb));
		$(".print_space_list").children("li").animate({
			transform: "translateX(-140%)"
		}, 300, function() {
			$(this).remove()
			battery()
		})
		$(".print_blur").animate({
			transform: "scale(0)"
		}, 200, cubicBezier)
		$(".aj_print_btn").animate({
			transform: "scale(0)"
		}, 600, cubicBezier)
	}

	//打印按钮
	$(".print_btn").on("tap", function() {
		var len = $(".print_space_list").children("li").length
		if(len == 0) {
			lockers("请先点击底部 + 号添加发票")
			return false;
		} else {
			var spac = JSON.parse(sessionStorage.getItem("allSpace"))

			if(spac.length == 0) {
				lockers("请先点击底部 + 号添加发票")
				return false;
			} else {
				var num = 0
				//    printPlliing() //调这个方法的时候穿个1进去，会启动抽屉插件，不然不会
				if($(".munber_status").html() != "正常") {
					lockers($(".munber_status").html())
					return false;
				} else {

					var number = sessionStorage.getItem("printNumber")
					if(!number) return false;
					$(".sta").html("状态：等待中...")
					printReturn()
					if(credentials == true) {
						setTimeout(function() {
							$("#printmian").html("false")
							$("#printover").html("false")
							PrintService(num)
						}, 140)
					} else {
						setTimeout(function() {
							$("#printmian").html("false")
							$("#printover").html("false")
							Print(num)
						}, 140)
					}

				}

			}

		}
	})

	//后端打印模块
	function PrintService(num) {
		var len = JSON.parse(sessionStorage.getItem("allSpace")).length,
			space = JSON.parse(sessionStorage.getItem("allSpace")),
			number = sessionStorage.getItem("printNumber"),
			formData = new FormData(),
			printUrl, spaceUrl = space[num].Url,
			spaceType
		var thr = space[num].thr
		var isAdBlock = space[num].isAdBlock
		if(!thr) {
			thr = "178"
		}
		if(!isAdBlock){
			isAdBlock = false
		}
		//		var numb = 0;
		//				var ssdd = setInterval(function(){
		//					numb++
		//					console.log(numb)
		//					if(numb == 150){
		//						$(".sta").eq(num).html('状态：打印机离线，请重新连接')
		//						$(".sta").eq(num).css("color", "red")
		//						printbtn()						
		//						clearInterval(ssdd)
		//					}
		//				},1000)
		formData.append('threshold', thr)
		formData.append('number', number)
		formData.append('isAdBlock', isAdBlock)
		formData.append('timeOut', 120000)

		//		console.log("第" + num + "张开始打印")
		$(".sta").eq(num).html("状态：打印中...")
		if(thr != 178) {
			formData.append('imageAlgorithm', "binarization")
		}
		var types = space[num].uploadParameter

		//		alert(ssd)

		if(types == "file") {
			var geshi = space[num].name.split(".");
			var ssd = geshi[geshi.length - 1];
			printUrl = constants.printAll() //12.18
			formData.append('file', dataURItoBlob(spaceUrl))
			if(ssd == "pdf") {
				spaceType = "pdf"
			} else {
				spaceType = "photo"
			}
		} else if(types == "wecat"){
			spaceType = "url_pdf"
			printUrl = constants.printAll()
			formData.append('url', spaceUrl)
			formData.append('isFilterMsg', false)
		} else {
			if(spaceUrl.indexOf("mpeg") != -1 || spaceUrl.indexOf("jpeg") != -1 || spaceUrl.indexOf("gif") != -1 || spaceUrl.indexOf("jpg") != -1 || spaceUrl.indexOf("bmp") != -1 || spaceUrl.indexOf("png") != -1) {
				spaceType = "url_photo"
			} else {
				spaceType = "url_pdf"
			}
			printUrl = constants.printAll() //12.18
			formData.append('url', spaceUrl)			
		}

		$.ajax({
			url: printUrl + number,
			type: 'POST',
			dataType: 'json',
			cache: false, //cache设置为false，上传文件不需要缓存
			processData: false, //data值是FormData对象，不需要对数据做处理
			contentType: false, //已经声明了属性enctype="multipart/form-data"，所以这里设置为false
			data: formData, //FormData对象
			headers: {
				'File-Type': spaceType,
				//				'File-Type'：application/jpg(仅支持jpg,png) 或 application/pdf
			},
			complete: function(xhr) {
				var res = JSON.parse(xhr.response)
				//设置信息res.data
				var bs = [],
					ks = [],
					info, html = "";
				for(var i in res.data) {
					bs += res.data[i]
					info = bs.substring(0, bs.length)
				}
				if(info.indexOf("打印成功") != -1) {
					info = '打印成功'
				} else if(info.indexOf("设备离线") != -1 || info.indexOf("打印机离线") != -1) {
					info = '无法打印，设备已离线'
				} else if(info.indexOf("限制打印不包含关键字") != -1) {
					info = '无法打印，发票不包含限制的公司名称或纳税人识别号'
				} else if(info.indexOf("不在工作时间") != -1) {
					info = '无法打印，非工作时间'
				} else if(info.indexOf("文件格式不支持") != -1) {
					info = '无法打印，文件格式不支持'
				} else if(info.indexOf("格式发票图片") != -1) {
					info = '打印失败，只能打印pdf格式发票'
				} else if(info.indexOf("data=处理超时") != -1) {
					info = '打印失败，打印超时'
				} else {
					info = '打印失败，请重新打印'
				}

				$(".sta").eq(num).html('状态：' + info)
				var green = $(".sta").eq(num).html()
				if(green == "状态：打印成功") {
					$(".sta").eq(num).css("color", "limegreen")
				} else {
					$(".sta").eq(num).css("color", "red")
				}
				num++
				if(num > len - 1) {
					num = 0
					printbtn()
					return false;
				}
				PrintService(num) //这个是自己调自己，小心！
			}
		})

	}
	//前端打印模块
	function Print(num) {
		$(".sta").eq(num).html("状态：打印中...")
		var len = JSON.parse(sessionStorage.getItem("allSpace")).length,
			space = JSON.parse(sessionStorage.getItem("allSpace")),
			number = sessionStorage.getItem("printNumber"),
			printUrl, spaceUrl, spaceType
		var thr = space[num].thr
		var isAdBlock = space[num].isAdBlock
		if(!thr) {
			thr = "178"
		}
		if(!isAdBlock){
			isAdBlock = false
		}
		console.log("第" + num + "张开始打印")

		//本地文件之外都是调url的接口
		//printUrl是ajax发送数据的url，根据文件类型来确定应该用哪个链接
		var page = space[num].url.length;
		for(var i = 0; i < page; i++) {
			var formData = new FormData()

			formData.append('threshold', thr)
			formData.append('number', number)
			formData.append('isAdBlock', isAdBlock)
			if(thr != 178) {
				formData.append('imageAlgorithm', "binarization")
			}

			var types = space[num].uploadParameter

			if(types == "msm" || types == "wecat") {
				printUrl = constants.printAll() //12.18
				formData.append('url', space[num].url)
				if(types == "wecat") {
					formData.append('isFilterMsg', false)
				}
				spaceType = "url_photo"
			} else {
				spaceUrl = dataURItoBlob(space[num].url[i])
				printUrl = constants.uploadFile()
				formData.append('file', spaceUrl)
				spaceType = "photo"
			}
			$.ajax({
				url: printUrl + number,
				type: 'POST',
				dataType: 'json',
				cache: false, //cache设置为false，上传文件不需要缓存
				processData: false, //data值是FormData对象，不需要对数据做处理
				contentType: false, //已经声明了属性enctype="multipart/form-data"，所以这里设置为false
				data: formData, //FormData对象
				async: false,
				headers: {
					'File-Type': spaceType,
					//File-Type：application/jpg(仅支持jpg,png) 或 application/pdf
				},
				complete: function(xhr) {
					var res = JSON.parse(xhr.response)
					//设置信息res.data
					var jsona = JSON.stringify(res.data)
					var jsons = jsona.replace(/[\ |\~|\`|\!|\@|\#|\$|\%|\^|\&|\*|\(|\)|\-|\_|\+|\=|\||\\|\[|\]|\{|\}|\;|\:|\"|\'|\,|\<|\.|\>|\/|\?]/g, "");
					var html = "";
					if(i == page - 1) {
						$(".sta").eq(num).html('状态：' + jsons)
						var green = $(".sta").eq(num).html()
						if(green == "状态：打印成功") {
							$(".sta").eq(num).css("color", "limegreen")
						} else {
							$(".sta").eq(num).css("color", "red")
						}
						num++
						if(num > len - 1) {
							num = 0
							//printLog()
							printbtn()
							return false;
						} else {
							Print(num) //这个是自己调自己，小心！
						}

					}

				}
			})
		}
	}
	//添加打印记录

	//缓存盒子，存储发票信息
	//模板方法要关联在一起
	function SpaceBox(fun) {
		var lens = sasb.length
		if(lens < 5) {
			sasb.push(fun)
		} else {

			lockers("最多只能添加5张")
		}

		//console.log(JSON.stringify(sasb))
		sessionStorage.setItem('allSpace', JSON.stringify(sasb))
	}

	function previewH() {
		$(".preview_img").attr("src", "")
		$(".print_img_preview").animate({
			"opacity": "0",
			"transform": "rotate(90deg) translateY(100%);"
		}, 600, cubicBezier)
	}

	//发票打印预览的大小
	$(function() {
		var height = document.body.clientHeight
		var width = document.body.clientWidth
		$(".print_img_preview").css({
			"width": height,
			"height": width
		})
		//		$(".preview_img").css("height", $(window).height() * 0.88)
		$(".preview_img").css("height", $(window).width() * 0.92)
		$(".preview").css("height", $(window).width()  * 0.92)
		$(".method").css("width", $(window).width())
		setTimeout(function() {
			var img_h = $(".preview_img").height() / 2
			$(".preview_img").css("margin-left", "-" + img_h + "px")
		}, 10)
	})

	//点击阈值调节事件
	$(".click_data_try").children("li").on("touchstart", function() {
		$(".lodin_box").css("transform", "rotate(90deg)")
		var threshold = $(this).attr("data-try"),
			index = sessionStorage.getItem("index"),
			spacePreview = JSON.parse(sessionStorage.getItem("allSpace")),
			formData, pdfType, src = $(".print_space_list").children("li").eq(index).attr("data-src")
		
		var isAdBlockds;	
		var thr = spacePreview[index].thr
		
		if($("#quxiao").hasClass("blue")){
			isAdBlockds = true
		}else{
			isAdBlockds = false
		}

		$(this).attr("class", "try_in").siblings("li").attr('class', "")
		$(".try-by").html($(this).html())
		if(credentials == true) {
			if(spacePreview[index].uploadParameter != "file") {
				formData = new FormData()
				pdfType = "url_pdf"
				formData.append('url', spacePreview[index].Url)
				formData.append('threshold', threshold)
				if(thr != 178) {
					formData.append('imageAlgorithm', "binarization")
				}
				formData.append('isAdBlock', isAdBlockds)
			} else {
				formData = new FormData()
				pdfType = "pdf"
				formData.append('file', dataURItoBlob(spacePreview[index].Url))
				formData.append('threshold', threshold)
				if(thr != 178) {
					formData.append('imageAlgorithm', "binarization")
				}
				formData.append('isAdBlock', isAdBlockds)
			}

		} else {
			if(spacePreview[index].uploadParameter == "wecat" || spacePreview[index].uploadParameter == "msm") {
				formData = new FormData()
				pdfType = "url_pdf"
				formData.append('url', spacePreview[index].url[0])
				formData.append('threshold', threshold)
				if(thr != 178) {
					formData.append('imageAlgorithm', "binarization")
				}
				formData.append('isAdBlock', isAdBlockds)
			} else {
				formData = new FormData()
				pdfType = "photo"
				formData.append('file', dataURItoBlob(spacePreview[index].url[0]))
				formData.append('threshold', threshold)
				if(thr != 178) {
					formData.append('imageAlgorithm', "binarization")
				}
				formData.append('isAdBlock', isAdBlockds)
			}
		}

		preview(formData, pdfType)

	})

	//阈值界面的保存与取消
	$(".img_save").on("tap", function() {
		var Index = $(".try_in").attr("data-try")
		var index = sessionStorage.getItem("index"),
			spacePreview = JSON.parse(sessionStorage.getItem("allSpace"))
//		sessionStorage.setItem("threshold", Index)
		spacePreview[index].isAdBlock = isAdBlock;
		spacePreview[index].thr = Index;
		sessionStorage.setItem("allSpace",JSON.stringify(spacePreview))
		$(".click_data_try").children("li").eq(index).attr("class", "try_in").siblings("li").attr('class', "")
		$(".try-by").html($(".try_in").html())
		xhd.abort();
		previewH()
	})
	$(".img_cancel").on("tap", function() {
		xhd.abort();
		previewH()
	})
	$(".method").children("div").on("touchstart", function() {
		$(".lodin_box").css("transform", "rotate(0deg)")
	})

	//阈值界面设置
	function previewS() {
		setTimeout(function() {
			var img_w = $(".preview_img").width() / 2
			$(".preview_img").css("margin-bottom", "-" + img_w + "px")
		}, 10)
		$(".print_img_preview").animate({
			"opacity": "1",
			"transform": "rotate(90deg) translateY(0%)"
		}, 600, cubicBezier)
	}

	//阈值调整结束

	//阈值预览
	var xhd;
	function preview(formData, pdfType) {
		var number = sessionStorage.getItem("printNumber")
		if(formData == "") {
			lockers("url发生错误")
			return false;
		}

		xhd = $.ajax({
			url: constants.preview() + number,
			type: 'POST',
			dataType: 'json',

			cache: false, //cache设置为false，上传文件不需要缓存
			processData: false, //data值是FormData对象，不需要对数据做处理
			contentType: false, //已经声明了属性enctype='multipart/form-data'，所以这里设置为false
			data: formData, //FormData对象
			headers: {
				'File-Type': pdfType, //item.headerFileType,	//url预览还是pdf预览
			},
			complete: function(xhr) {
				var code = JSON.parse(xhr.response).code,
					base64Image = JSON.parse(xhr.responseText).data

				if(0 === code) {
					$(".preview_img").attr("src", base64Image)
					previewS()
				} else {
					if(JSON.parse(xhr.response).data) {
						lockers(JSON.parse(xhr.response).data)
					} else {
						lockers(JSON.stringify(xhr.response))
					}
				}

			},

		});
	}
	// 阈值 控制栏 (油墨浓度 控制栏)
	$(".print_space_list").on("tap", "li .print_space_preview", function() {
		var Index = $(this).parent().index()
		var src = $(this).parent().attr("data-src")
		var type = $(this).parent().attr("data-type")
//		var thr = sessionStorage.getItem("threshold")
		var space = JSON.parse(sessionStorage.getItem("allSpace"))
		sessionStorage.setItem("index", Index)
		var thr = space[Index].thr
		var isAdBlocks = space[Index].isAdBlock
		
		if(!thr) thr = 178
		if(isAdBlocks == true){
			$("#quxiao").addClass("blue")
			$("#quxiao").attr("src","../img/right.jpg")
		}else{
			$("#quxiao").removeClass("blue")
			$("#quxiao").attr("src","../img/left.jpg")
		}

		//用thr来调整谁是in
		if(thr == 98) $(".click_data_try").children("li").eq(0).attr("class", "try_in").siblings("li").attr('class', "")
		if(thr == 125) $(".click_data_try").children("li").eq(1).attr("class", "try_in").siblings("li").attr('class', "")
		if(thr == 152) $(".click_data_try").children("li").eq(2).attr("class", "try_in").siblings("li").attr('class', "")
		if(thr == 178) $(".click_data_try").children("li").eq(3).attr("class", "try_in").siblings("li").attr('class', "")
		if(thr == 203) $(".click_data_try").children("li").eq(4).attr("class", "try_in").siblings("li").attr('class', "")
		if(thr == 228) $(".click_data_try").children("li").eq(5).attr("class", "try_in").siblings("li").attr('class', "")
		if(thr == 250) $(".click_data_try").children("li").eq(6).attr("class", "try_in").siblings("li").attr('class', "")
		$(".try-by").html($(".try_in").html())
		if(credentials == true) {
			if(space[Index].uploadParameter != "file") {
				var formData = new FormData()
				var pdfType = "url_pdf"
				var Url = space[Index].Url
				formData.append('url', Url)
				formData.append('threshold', thr)
				if(thr != 178) {
					formData.append('imageAlgorithm', "binarization")
				}
				formData.append('isAdBlock', isAdBlock)
			} else {
				var formData = new FormData()
				if(space[Index].name.split(".")[1] != "pdf"){
					var pdfType = "photo"
				}else{
					var pdfType = "pdf"
				}
				
				var Url = dataURItoBlob(space[Index].Url)
				formData.append('file', Url)
				formData.append('threshold', thr)
				if(thr != 178) {
					formData.append('imageAlgorithm', "binarization")
				}
				formData.append('isAdBlock', isAdBlock)
			}
		} else {
			if(space[Index].uploadParameter == "wecat" || space[Index].uploadParameter == "msm") {
				var formData = new FormData()
				var pdfType = "url_pdf"
				var Url = space[Index].url[0]
				formData.append('url', Url)
				formData.append('threshold', thr)
				if(thr != 178) {
					formData.append('imageAlgorithm', "binarization")
				}
				formData.append('isAdBlock', isAdBlock)
			} else {
				var formData = new FormData()
				var pdfType = "photo"
				var Url = dataURItoBlob(space[Index].url[0])
				formData.append('file', Url)
				formData.append('threshold', thr)
				if(thr != 178) {
					formData.append('imageAlgorithm', "binarization")
				}
				formData.append('isAdBlock', isAdBlock)
			}
		}
		preview(formData, pdfType)

	})
	$(".try-by").on("tap", function() {
		if($(".click_data_try").is(":hidden")) {
			$(".click_data_try").show()
		} else {
			$(".click_data_try").hide()
		}

	})
	$(window).on("tap", function(e) {
		if(e.target.id != "tryby") {
			$(".click_data_try").hide()
		}
	})

	//去广告
	var isAdBlock = false;
	$("#quxiao").on("tap", function() {
		if($(this).hasClass("blue")) {
			$(this).removeClass("blue")
			$(this).attr("src", "../img/left.jpg")
			isAdBlock = false;
		} else {
			$(this).addClass("blue")
			$(this).attr("src", "../img/right.jpg")
			isAdBlock = true;
		}
		var space = JSON.parse(sessionStorage.getItem("allSpace"))
//		var thr = sessionStorage.getItem("threshold")
		var Index = sessionStorage.getItem("index")
		var thr = space[Index].thr
		if(!thr) thr = 178
		if(credentials == true) {
			if(space[Index].uploadParameter != "file") {
				var formData = new FormData()
				var pdfType = "url_pdf"
				var Url = space[Index].Url
				formData.append('url', Url)
				formData.append('threshold', thr)
				if(thr != 178) {
					formData.append('imageAlgorithm', "binarization")
				}
				formData.append('isAdBlock', isAdBlock)
			} else {
				var formData = new FormData()
				var pdfType = "pdf"
				var Url = dataURItoBlob(space[Index].Url)
				formData.append('file', Url)
				formData.append('threshold', thr)
				if(thr != 178) {
					formData.append('imageAlgorithm', "binarization")
				}
				formData.append('isAdBlock', isAdBlock)
			}
		} else {
			if(space[Index].uploadParameter == "wecat" || space[Index].uploadParameter == "msm") {
				var formData = new FormData()
				var pdfType = "url_pdf"
				var Url = space[Index].url[0]
				formData.append('url', Url)
				formData.append('threshold', thr)
				if(thr != 178) {
					formData.append('imageAlgorithm', "binarization")
				}
				formData.append('isAdBlock', isAdBlock)
			} else {
				var formData = new FormData()
				var pdfType = "photo"
				var Url = dataURItoBlob(space[Index].url[0])
				formData.append('file', Url)
				formData.append('threshold', thr)
				if(thr != 178) {
					formData.append('imageAlgorithm', "binarization")
				}
				formData.append('isAdBlock', isAdBlock)
			}
		}
		preview(formData, pdfType)
	})

});