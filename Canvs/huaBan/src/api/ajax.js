/*
* 封装ajax函数
* 返回promise 对象（异步返回的数据是response.data）
* */
import axios from 'axios'



export default function ajax(url, data = {}, type = 'GET',from) {
  return new Promise(function (resolve, reject) {
    //执行异步ajax请求
    let promise
    if (type === 'GET') {
      //准备url query参数数据
      let dataStr = ''//数据拼接字符串
      Object.keys(data).forEach(key => {
        dataStr += key + '=' + data[key] + '&'
      })
      if (dataStr !== '') {
        dataStr = dataStr.substring(0, dataStr.lastIndexOf('&'));
        url = url + '?' + dataStr;
      }
      //发送get请求
      promise = axios.get(url);
    } else {
      //发送post请求
      if(from){
        promise = axios({
          method:'post',
          url,
          headers:{
            'Content-Type':'multipart/form-data;charset=UTF-8'
          },
          data
        });
      }else{
        promise = axios.post(url, data);
      }

    }
    promise.then(response => {
      let result = response.data
      if (result.code == 0) {
        resolve(result);
      } else {
        reject(result);
      }
    }).catch(error => {
      reject(error.response)
    })
  });
}
