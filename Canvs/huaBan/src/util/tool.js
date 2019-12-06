//验证ip是否正确
import myLocalStorage from './localStorage'

export const verificationIp = (ip) => {
  return ven.isIP(ip)
}

export const verificationPort = (port) => {
  return ven.isPort(port)
}
export const verificationUrl = (url) => {
  return ven.isUrl(url)
}
//验证number
export const verificationNumber = (number) => {
  const pattern = /^(?=.*[A-Z])(?=.*\d)[A-Z\d]{16}$/
  return pattern.test(number)
}

const ven = {
  isValue: function (value) {
    if (!value) {
      return {type: false, msg: '请输入'}
    }
  },
  isIP: function (value) {
    const pattern = /(2(5[0-5]{1}|[0-4]\d{1})|[0-1]?\d{1,2})(\.(2(5[0-5]{1}|[0-4]\d{1})|[0-1]?\d{1,2})){3}/g
    if (!value) {
      return '请输入IP'
    }
    if (!pattern.test(value)) {
      return 'IP格式错误'
    }
  },
  isPort: function (value) {
    const pattern = /^\d+$/;
    if (!value) {
      return '请输入端口号'
    }
    if (!pattern.test(value)) {
      return '端口号格式错误'
    }
  },
  isUrl: function (value) {
    const pattern = /^((https?|ftp|file|http):\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$/;
    if (!value) {
      return '请输入URL'
    }
    if (!pattern.test(value)) {
      return 'URL格式错误'
    }
  },
  checkPort: (value) => {//数字验证
    let pattern = /^[0-9]+.?[0-9]*/;
    if (value == '') {
      return '不能为空'
    } else if (!pattern.test(value)) {
      return '请输入数字'
    } else if (value > 65535) {
      return '不能大于65535'
    }
    return
  }

}

export const formatDate = (date) => {
  return new Promise((resolve, reject) => {
    const year = date.slice(0, 4)
    const mouth = date.slice(4, 6)
    const day = date.slice(6, 8)
    resolve(year + '-' + mouth + '-' + day)
  })
}

export const conversionLog = (data) => {
  let result = data.toString()
  result = result.replace(/\[INFO\]/g, '[INFO]<br/>')
  return result.replace(/\n/g, '<br/><br/>')
}

export const streamData = (data, callback) => {
  let err = ''
  if (data == '') {
    err = 'data不能为空'
    callback(err, data)
    return
  }
  callback(err, data.slice(0, 10000))
}
export const getUrl = () => {
  try {
    const server = JSON.parse(myLocalStorage.get('server'))
    if (server.type == 'ip') {
      return server.http
    } else {
      return server.http.replace(/http:\/\/|https:\/\//, '')
    }
  } catch (e) {
    this.$message.error('请求服务地址出错了')
  }
}


//清除异常的空格
export const noSpace = (data) => {
  for (let item in data) {
    if (data[item] != '') {
      if (typeof data[item] == 'string') {
        data[item] = space(data[item])
      }
    }
  }
  return data
}

function space(data) {
  let result = data.split("")
  let res = []
  for (let item of result) {
    if (item.charCodeAt(0) != 0) {
      res.push(item)
    }
  }
  return res.join('')
}

//转换名称
export const transitionFileName = (fileName) => {
  if (fileName === '异常日志') {
    return 'error.log'
  } else if (fileName === '打印日志') {
    return 'info.log'
  } else if (fileName === '警告日志') {
    return 'warn.log'
  } else {
    return fileName
  }
}


//转换版本号

export const transitionWifiFirmwareVersion = (data) => {
  const rep = /[.]$/
  if (rep.test(data)) {
    return data.substr(0, data.length - 1)
  } else {
    return data
  }
}

//生成uuid全球唯一标识
export function generateUUID() {
  let d = new Date().getTime();
  if (window.performance && typeof window.performance.now === "function") {
    d += performance.now(); //use high-precision timer if available
  }
  let uuid = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
    let r = (d + Math.random() * 16) % 16 | 0;
    d = Math.floor(d / 16);
    return (c == 'x' ? r : (r & 0x3 | 0x8)).toString(16);
  });
  return uuid;
}