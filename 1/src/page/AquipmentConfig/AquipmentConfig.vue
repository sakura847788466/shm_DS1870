<template>

</template>

<script>
import { getAquipmentConfigOnlinenum, getAquipmentConfigReadConfig, saveAquipmentConfigReadConfig } from "../../api";
import { noSpace } from "../../util/tool";

export default {
  name: "AquipmentConfig",
  mounted () {
    getAquipmentConfigOnlinenum()
      .then(res => {
        for (let i = 0; i < res.data.length; i++) {
          this.numberList.push({ id: i + 1, number: res.data[i], loading: false })
        }
        this.numberListData = this.numberList.slice(0, this.pageNum)

      })
      .catch(res => {
        console.log(res);
      })
  },
  data () {
    return {
      numberList: [],//总正常number列表
      numberListData: [],//分页数据
      numberData: {},//根据number查找的配置信息
      cancelNumberData: {},//点击取消恢复为原来
      search: '',//搜索字段
      printNumber: '',//点击查看更多的打印机number
      loading: false,//是否显示按钮的加载
      tab: true,//切换显示总的记录或显示子记录
      spi: [{ v: '0', label: '1字节' }, { v: '1', label: '8字节' }],
      proxyMode: [{ v: '0', label: '域名代理' }, { v: '1', label: 'IP代理' }],
      dsfz: [{ v: '0', label: '不支持' }, { v: '1', label: '支持' }],
      dataTransmissionSpeed: [{ v: 0, label: '低' }, { v: 2, label: '正常' }, { v: 3, label: '高' }],
      /*分页*/
      currentPage: 1,
      pageNum: 10
    }
  },
  methods: {
    myMessage (type, msg, duration = 3000) {
      this.$message({
        message: msg,
        type,
        duration,
        showClose: true,
        offset: 54,
      });
    },
    handleFinder (index, row) {
      this.numberListData[index].loading = true
      getAquipmentConfigReadConfig(row.number)
        .then(res => {
          if (res.data.dsfz) {
            res.data.dsfz.toString()
          }
          if (res.data.socketProxy) {
            res.data.socketProxy.toString()
          }
          if (res.data.dsfz == '0' || res.data.dsfz == null) {
            res.data.dsfz = '0'
          }
          if (res.data.proxyMode == '0' || res.data.proxyMode == null) {
            res.data.proxyMode = '0'
          }
          if (res.data.spi == '0' || res.data.spi == null) {
            res.data.spi = '0'
          }
          this.numberData = noSpace(res.data)
          this.cancelNumberData = { ...this.numberData }
          /*str.replace(/\s*!/g,"");*/

          setTimeout(() => {
            this.tab = false
            this.numberListData[index].loading = false
          }, 300);
        })
        .catch(res => {
          this.myMessage('error', '读取失败')
        })

    },
    back () {
      this.tab = true
    },
    //分页
    handleChange (val) {
      this.numberListData = this.numberList.slice(0, val)
    },
    handleCurrentChange (val) {
      let last = this.pageNum * val;
      let first = last - this.pageNum;
      this.numberListData = []
      this.numberListData = this.numberList.slice(first, last)
      this.search = ''
    },
    //修改保存设备信息
    saveConfig () {
      this.myVerification(this.numberData)
      saveAquipmentConfigReadConfig({ data: this.numberData })
        .then(res => {
          this.myMessage('success', '设备信息修改成功')
        })
        .catch(res => {
          this.myMessage('error', res.data)
        })
    },
    //恢复设备信息
    cancelConfig () {
      this.numberData = null
      this.numberData = { ...this.cancelNumberData }
      this.myMessage('success', '已取消')
    },

    //验证信息是否正确
    myVerification (data) {
      const { dns, dhcp, socketProxy } = data
      const veriData = {}
      const verificationIsValue = (value, msg) => {
        if (value == '' || value == null) {
          throw (msg)
        }
      }
      const verificationIp = (value, msg) => {
        const pattern = /(2(5[0-5]{1}|[0-4]\d{1})|[0-1]?\d{1,2})(\.(2(5[0-5]{1}|[0-4]\d{1})|[0-1]?\d{1,2})){3}/g
        if (!pattern.test(value)) {
          throw (msg)
        }
      }
      const checkPass = (value, msg) => {//ip验证
        let pattern = /^[A-Za-z0-9]+$/;
        if (value != '') {
          if (value == null) return

          if (value.length <= 7) {
            throw (msg + '不能小于8位字符')
          } else if (!pattern.test(value)) {
            throw (msg + '只能是数字和字母')
          }
        }
      }
      const checkMask = (value, msg) => {//子网掩码验证
        let pattern = /^(254|252|248|240|224|192|128|0)\.0\.0\.0$|^(255\.(254|252|248|240|224|192|128|0)\.0\.0)$|^(255\.255\.(254|252|248|240|224|192|128|0)\.0)$|^(255\.255\.255\.(254|252|248|240|224|192|128|0))$/
        if (!pattern.test(value)) {
          throw (msg)
        }
      }
      const checkPort = (value, msg) => {
        let pattern = /^[0-9]+.?[0-9]*/;
        if (!pattern.test(value)) {
          throw (msg + '只能为数字')
        } else if (value > 65535) {
          throw (msg + '值不能大于65535')
        }
      }

      const init = () => {
        for (let item in data) {
          for (let ven in veriData) {
            if (item == ven) {
              for (let i of veriData[ven]) {
                try {
                  i.func(data[item], i.msg)
                } catch (e) {
                  this.$alert(e, '错误提示', { type: "error" })
                  return
                }
              }
            }
          }
        }
      }

      veriData.remoteRouteSsid = [
        {
          func: verificationIsValue,
          msg: '请输入路由SSID'
        }]
      veriData.remoteRoutePassword = [
        {
          func: checkPass,
          msg: '路由密码'
        }]
      veriData.remoteServerAddress = [
        {
          func: verificationIsValue,
          msg: '请输入服务器IP'
        },
        {
          func: verificationIp,
          msg: '服务器IP格式有误'
        }
      ]
      veriData.controlPort = [
        {
          func: verificationIsValue,
          msg: '请输入控制端口'
        },
        {
          func: checkPort,
          msg: '控制端口'
        }
      ]
      veriData.dataPort = [
        {
          func: verificationIsValue,
          msg: '请输入数据端口'
        },
        {
          func: checkPort,
          msg: '数据端口'
        }
      ]
      veriData.reconnectionInterval = [
        {
          func: verificationIsValue,
          msg: '请输入重连时长(s)'
        }
      ]


      if (dhcp != 1) {
        veriData.localIpAddress = [
          {
            func: verificationIsValue,
            msg: '请输入IP地址'
          },
          {
            func: verificationIp,
            msg: 'IP地址格式错误'
          }
        ]
        veriData.localGateway = [
          {
            func: verificationIsValue,
            msg: '请输入默认网关'
          },
          {
            func: verificationIp,
            msg: '默认网关格式错误'
          }
        ]
        veriData.localSubnetMask = [
          {
            func: verificationIsValue,
            msg: '请输入子网掩码'
          }]

      }
      if (dns == 1) {
        veriData.domainName = [
          {
            func: verificationIsValue,
            msg: '请输入服务器域名'
          }
        ]
        veriData.mainDNSServerAddress = [
          {
            func: verificationIsValue,
            msg: '请输入首选DNS地址'
          },
          {
            func: verificationIp,
            msg: '首选DNS地址格式错误'
          }
        ]
        veriData.slaveDNSServerAddress = [
          {
            func: verificationIsValue,
            msg: '请输入备选DNS地址'
          },
          {
            func: verificationIp,
            msg: '备选DNS地址格式错误'
          }
        ]

      }
      if (socketProxy == 1) {
        veriData.proxyUrl = [
          {
            func: verificationIsValue,
            msg: '请输入代理URL'
          }
        ]
        veriData.proxyAddress = [
          {
            func: verificationIsValue,
            msg: '请输入代理IP'
          },
          {
            func: verificationIp,
            msg: '代理IP格式有误'
          }
        ]
        veriData.proxyPort = [
          {
            func: verificationIsValue,
            msg: '请输入代理端口'
          },
          {
            func: checkPort,
            msg: '代理端口'
          }
        ]
        veriData.proxyUserName = [
          {
            func: verificationIsValue,
            msg: '请输入代理用户名'
          }
        ]
        veriData.proxyMode = [
          {
            func: verificationIsValue,
            msg: '请选择代理方式'
          }
        ]
        veriData.proxyPassword = [
          {
            func: checkPass,
            msg: '代理密码'
          }
        ]
      }
      init()
    }

  }
}
</script>

<style scoped>
.right {
  display: flex;
  flex-direction: column;
  margin: 0 auto;
  width: 905px;
}

.title {
  display: flex;
  justify-content: space-between;
  align-items: center;
  width: 100%;
  font-size: 24px;
  /*border-bottom: 1px solid #ddd;*/
}

.search {
  box-sizing: border-box;
  width: 250px;
  height: 38px;
}

.line {
  margin-top: 11px;
  width: 100%;
  height: 1px;
  background-color: #e7e7e7;
}

.table-color {
  color: #333 !important;
}

.btn {
  padding: 7px 10px;
  font-size: 14px;
}

.pagination {
  display: flex;
  justify-content: flex-end;
  align-items: center;
  margin-top: 12px;
}

/*设置配置*/
.title-two {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 10px 0;
  border-bottom: 1px solid #e7e7e7;
}

.item-title {
  padding-left: 147px;
  width: 906px;
  height: 54px;
  line-height: 54px;
  font-size: 20px;
  color: #333;
  background: rgba(249, 249, 249, 1);
  /*border-top: 1px solid #E7E7E7;*/
  border-bottom: 1px solid #e7e7e7;
}

.item-content {
  display: flex;
  align-items: center;
  padding-left: 147px;
  height: 54px;
  /*line-height: 54px;*/
  border-bottom: 1px solid #e7e7e7;
}

.item-content-title {
  padding-left: 10px;
  width: 200px;
  font-size: 14px;
  color: #666;
}

.item-content-msg {
  width: 400px;
}

.content {
  display: flex;
  justify-content: space-between;
  flex-wrap: wrap;
  width: 100%;
  height: 550px;
}

.chunk {
  display: flex;
  flex-direction: column;
  align-items: center;
  margin-bottom: 10px;
  width: 380px;
  height: 250px;
  border-radius: 15px;
  font-size: 14px;
  box-shadow: 5px 5px 5px #f5f5f5, -2px -5px 5px #f5f5f5;
}

.prarim {
  border: 1px solid #d9ecff;
  background-color: #ecf5ff;
  color: #409eff;
}

.prarim > .chunk-item {
  border: 1px solid #409eff;
}

.waring {
  border: 1px solid #faecd8;
  background-color: #fdf6ec;
  color: #e6a23c;
}

.waring > .chunk-item {
  border: 1px solid #e6a23c;
}

.chunk-item {
  display: flex;
  justify-content: space-between;
  margin-top: 10px;
  width: 90%;
  height: 30px;
}

.chunk-item:hover {
  background-color: #fff;
  cursor: pointer;
}

.chunk-name {
  width: 50%;
  height: 100%;
  line-height: 30px;
  text-align: right;
}

.chunk-value {
  margin-left: 18px;
  width: 50%;
  height: 100%;
  line-height: 30px;
}

@media (max-width: 1200px) {
  .box {
    width: 90%;
  }
}
</style>
