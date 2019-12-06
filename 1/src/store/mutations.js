/*
* 直接更新state的多个方法的对象
* */
import Vue from 'vue'

import {
  GET_WHITELIST,
  SAVE_IP
} from './mutations-type'

export  default {
  [GET_WHITELIST](state,{whiteList}){
    state.whiteList = whiteList
  },
  [SAVE_IP](state,{ip}){
    state.ip = ip
  },
}
