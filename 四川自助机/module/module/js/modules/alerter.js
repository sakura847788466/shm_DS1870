//alerter.js文件
// 定义有依赖的模块
define(['dataService'], function(dataService) {
  let name = 'Ada'
  function showMsg() {
    console.log(dataService.getMsg() + ', ' + name)
  }
  function configIp() {
    const API = 'http://192.168.11.30003'
  }
  // 暴露模块
  return { showMsg, configIp }
})
