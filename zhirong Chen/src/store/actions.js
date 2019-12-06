/*
* 通过mutation间接更新state的多个方法的对象
* */

import {GET_WHITELIST,SAVE_IP} from './mutations-type'
import {getAll} from '../api'

export default {
  async getWhiteList({commit}){
    const result = await getAll()
    if(result.code==0){
      let i = 1
      let whiteList = {}
      whiteList.ip = result.ip.map(item => ({
        id:i++,
        list: item,
        type: 'ip'
      }))

      whiteList.number = result.number.map(item => ({
        id:i++,
        list: item.number,
        main:item.main,
        type: 'number'
      }))

      commit(GET_WHITELIST,{whiteList} )
    }
  },
  saveIp({commit},ip){
    commit(SAVE_IP,{ip})
  }


}
