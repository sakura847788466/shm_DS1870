export default {
  ip(state) {
    try {
      let i = 1
      return state.whiteList.ip.map(item => ({
        id:i++,
        list: item,
        type: 'ip'
      }))
    } catch (e) {
    }


  },
  number(state) {
    try {
      return state.whiteList.number.map(item => ({
        list: item,
        type: 'number'
      }))
    }catch (e) {

    }

  }
}
