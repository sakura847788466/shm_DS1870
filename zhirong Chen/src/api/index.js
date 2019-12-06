import ajax from './ajax'
import myLocalStorage from '../util/localStorage'

let URL
try {
  const server = JSON.parse(myLocalStorage.get('server'))
  if (server.type == 'ip') {
    URL = `http://${server.http}`
  } else {
    URL = `${server.http}`
  }
} catch (e) {}

// const URL = 'http://192.168.11.107:40003/whitelist/'

export const getAll = () => ajax(URL + '/whitelist/getAll') //获取所有白名单列表

export const getSearch = data => ajax(URL + '/whitelist/search', data, 'POST') //搜索单个白名单

export const del = data => ajax(URL + '/whitelist/del', data, 'POST') //删除白名单
export const delAll = data => ajax(URL + '/whitelist/batchdel', data, 'POST') //批量删除白名单

export const add = data => ajax(URL + '/whitelist/put', data, 'POST') //添加白名单

export const getConfig = () => ajax(URL + '/config/getconfig') //获取服务配置信息

export const restoreConfig = () => ajax(URL + '/config/restoreconfig') //还原服务配置信息

export const setConfig = data =>
  ajax(URL + '/config/updateconfig', data, 'POST') //修改服务配置信息

export const getNormalonline = statetype =>
  ajax(URL + '/device/normalonline', { statetype }) //获取所有设备状态

export const getAllcount = () => ajax(URL + '/printlog/getallcount') //获取所有打印日志

export const getNumcount = number =>
  ajax(URL + '/printlog/getnumcount', { number }) //获取一个打印日志

export const searchPrintData = data => ajax(URL + '/printlog/periodcount', data) //获取一个打印日志

export const getServerLog = () => ajax(URL + '/printlog/getfilelevel') //获取服务日志目录

export const getlog = filename => ajax(URL + '/printlog/getlog', { filename }) //获取服务日志目录getlog?filename=error-2019-06-25-2.log

// export const updateFirmware = (data) => ajax(URL+'/device/updatefirmware',data,'POST')//固件升级

export const getFirmwareNormalinfo = () =>
  ajax(URL + '/device/normalonline', { updateversion: true, statetype: '正常' }) ////固件升级onlinenum

export const getAquipmentConfigOnlinenum = () => ajax(URL + '/device/onlinenum') //读取设备

export const getAquipmentConfigReadConfig = number =>
  ajax(URL + '/device/readConfig', { number }) //读取设备配置信息

export const saveAquipmentConfigReadConfig = data =>
  ajax(URL + '/device/updateConfig', data, 'POST') //修改设备配置信息

export const updateFirmware = data =>
  ajax(URL + '/firmware/updatefirmware', data, 'POST') //固件升级

export const getFilelevel = () => ajax(URL + '/mongodata/getfilelevel') //获取已经备份的数据列表

export const backup = () => ajax(URL + '/mongodata/backup') //数据备份

export const delBackData = deldataname =>
  ajax(URL + '/mongodata/delbackdata', { deldataname }) //数据备份

export const recovery = recoveryname =>
  ajax(URL + '/mongodata/recovery', { recoveryname }) //固件升级

export const printlog = data => {
  return (
    URL +
    `/printlog/getlogzip?fileName=${data.fileName}&saveName=${data.saveName}`
  )
} //日志下载

export const getCollections = () => ajax(URL + '/mongodata/getcollections') //获取数据备份的数组

export const getCollecjson = () => ajax(URL + '/mongodata/getcollecjson') //获取数据导入的数组

export const importData = (name, data) =>
  ajax(URL + `/mongodata/importdata?collection=${name}`, data, 'POST', 'form') //获取数据导入的数组

export const exportData = data => {
  return (
    URL +
    `/mongodata/exportdata?collection=${data.collection}&saveName=${data.saveName}`
  )
} //数据导出

//热部署
export const getVersion = () => ajax(URL + '/config/getVersion') //获取版本号
export const deploy = data => ajax(URL + '/config/deploy', data, 'POST', 'form') //上传热部署

//声音信息
export const getVoiceInfo = () => ajax(URL + '/config/getglobalConf') //获取声音信息   目前先使用本地api  全局的开关
//更改服务端配置
export const upDataVoiceInfo = data =>
  ajax(URL + '/config/updGlobalConf', data, 'POST')
//获取所有的Voice信息
export const getAllVoiceConfig = () => ajax(URL + '/devconfig/getall') //获取所有声音信息
//批量删除声音信息
export const delSomeThing = data =>
  ajax(URL + '/devconfig/remove', data, 'POST')
//批量更改
export const upDataSome = data =>
  ajax(URL + '/devconfig/batchupdate', data, 'POST')
//获取所有的语音信息句段
export const getAllVoice = () => ajax(URL + '/voice/getallseg', 'GET')
//更新语音句段
export const upDataVoice = data => ajax(URL + '/voice/updateseg', data, 'POST')
