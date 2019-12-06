import Vue from 'vue'
import Router from 'vue-router'

const WhiteList = () => import('../page/WhiteList/WhiteList')
const DeviceState = () => import('../page/DeviceState/DeviceState')
const DeviceInfo = () => import('../page/DeviceInfo/DeviceInfo')
const PrintRecord = () => import('../page/PrintRecord/PrintRecord')
const Log = () => import('../page/Log/Log')
const Firmware = () => import('../page/Firmware/Firmware')
const AquipmentConfig = () => import('../page/AquipmentConfig/AquipmentConfig')
const Backups = () => import('../page/Backups/Backups')
const HotDeploy = () => import('../page/HotDeploy/HotDeploy')
const Help = () => import('../page/Help/Help')
const VoiceInfo = () => import('../page/VoiceInfo/VoiceInfo')

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'whiteList',
      component: WhiteList
    },
    {
      path: '/deviceState',
      name: 'deviceState',
      component: DeviceState
    },
    {
      path: '/deviceInfo',
      name: 'deviceInfo',
      component: DeviceInfo
    },
    {
      path: '/printRecord',
      name: 'printRecord',
      component: PrintRecord
    },
    {
      path: '/log',
      name: 'Log',
      component: Log
    },
    {
      path: '/firmware',
      name: 'Firmware',
      component: Firmware
    },
    {
      path: '/aquipmentConfig',
      name: 'AquipmentConfig',
      component: AquipmentConfig
    },
    {
      path: '/backups',
      name: 'backups',
      component: Backups
    },
    {
      path: '/hotDeploy',
      name: 'hotDeploy',
      component: HotDeploy
    },
    {
      path: '/help',
      name: 'help',
      component: Help
    },
    {
      path: '/voiceInfo',
      name: 'voiceInfo',
      component: VoiceInfo
    }
  ]
})
