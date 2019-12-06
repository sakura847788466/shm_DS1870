<template>
  <div class="right">
    <div class="title">
      <span>设备配置信息</span>
      <el-input v-model="search"
                v-show="tab"
                class="search"
                placeholder="输入打印机编号搜索"
                suffix-icon="el-icon-search" />
    </div>
    <div class="line"></div>
    <div class="body">
      <el-table v-show="tab"
                max-height="598"
                style="width: 100%;min-height: 598px;;font-size: 16px;color: #999;"
                :data="numberListData.filter(data => !this.search || data.number.toLowerCase().includes(this.search.toLowerCase()))"
                :header-cell-style="{color:'#666'}"
                :cell-style="{height:'55px'}">
        <el-table-column label="序号"
                         prop="id" />
        <el-table-column label="打印机编号"
                         prop="number" />
        <el-table-column label="操作"
                         prop="name"
                         width="125px"
                         align="center">
          <template slot-scope="scope">
            <el-button type="primary"
                       :loading="scope.row.loading"
                       size="mini"
                       class="btn"
                       @click="handleFinder(scope.row.id-1,scope.row)">修改配置
            </el-button>
          </template>
        </el-table-column>
      </el-table>
      <div v-show="!tab">
        <div class="title-two">
          <p style="font-size: 16px;color: #666">当前打印机：{{numberData.number}}</p>
          <el-button type="danger"
                     size="small"
                     @click="back"
                     style="width: 60px;height:36px;border-radius:6px;font-size: 14px">返回
          </el-button>
        </div>
        <div>
          <div>
            <div class="item-title">网络参数</div>
            <div class="item-content">
              <span class="item-content-title">dhcp :</span>
              <el-switch v-model="numberData.dhcp"
                         :active-value="1" />
            </div>
            <div class="item-content">
              <span class="item-content-title">IP地址 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="15"
                        v-model.trim="numberData.localIpAddress"
                        :disabled="numberData.dhcp==1" />
            </div>
            <div class="item-content">
              <span class="item-content-title">子网掩码 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="15"
                        v-model.trim="numberData.localSubnetMask"
                        :disabled="numberData.dhcp==1" />
            </div>
            <div class="item-content">
              <span class="item-content-title">默认网关 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="15"
                        v-model.trim="numberData.localGateway"
                        :disabled="numberData.dhcp==1" />
            </div>
            <div class="item-content">
              <span class="item-content-title">WIFI信道 :</span>
              <el-select placeholder="请选择"
                         class="item-content-msg"
                         v-model="numberData.networkChannel">
                <el-option v-for="item in 11"
                           :key="item"
                           :value="item"
                           :label="item" />
              </el-select>
            </div>
            <div class="item-content">
              <span class="item-content-title">路由SSID :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="32"
                        v-model.trim="numberData.remoteRouteSsid" />
            </div>
            <div class="item-content">
              <span class="item-content-title">路由密码 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="32"
                        v-model.trim="numberData.remoteRoutePassword" />
            </div>
          </div>
          <div>
            <div class="item-title">打印服务器配置</div>
            <div class="item-content">
              <span class="item-content-title">dns :</span>
              <el-switch v-model="numberData.dns"
                         :active-value="1"
                         :inactive-value="0" />
            </div>
            <div class="item-content">
              <span class="item-content-title">服务器域名 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="32"
                        v-model.trim="numberData.domainName"
                        :disabled="numberData.dns!=1" />
            </div>
            <div class="item-content">
              <span class="item-content-title">首选DNS地址 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="15"
                        v-model.trim="numberData.mainDNSServerAddress"
                        :disabled="numberData.dns!=1" />
            </div>
            <div class="item-content">
              <span class="item-content-title">备选DNS地址 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="15"
                        v-model.trim="numberData.slaveDNSServerAddress"
                        :disabled="numberData.dns!=1" />
            </div>
            <div class="item-content">
              <span class="item-content-title">服务器IP :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="15"
                        v-model.trim="numberData.remoteServerAddress" />
            </div>
            <div class="item-content">
              <span class="item-content-title">广播端口 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="5"
                        v-model.trim="numberData.udpPort"
                        disabled />
            </div>
            <div class="item-content">
              <span class="item-content-title">控制端口 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="5"
                        v-model.number.trim="numberData.controlPort"
                        type="number" />
            </div>
            <div class="item-content">
              <span class="item-content-title">数据端口 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="5"
                        v-model.number.trim="numberData.dataPort"
                        type="number" />
            </div>
          </div>
          <div>
            <div class="item-title">代理服务配置</div>
            <div class="item-content">
              <span class="item-content-title">socket代理 :</span>
              <el-switch v-model="numberData.socketProxy"
                         :active-value="'1'"
                         :inactive-value="'0'"></el-switch>
            </div>
            <div class="item-content">
              <span class="item-content-title">代理Url :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="32"
                        v-model.trim="numberData.proxyUrl"
                        :disabled="numberData.socketProxy!=1" />
            </div>
            <div class="item-content">
              <span class="item-content-title">代理方式 :</span>
              <el-select placeholder="请选择"
                         class="item-content-msg"
                         v-model="numberData.proxyMode"
                         :disabled="numberData.socketProxy!=1">
                <el-option v-for="(item,index) in proxyMode"
                           :key="index"
                           :label="item.label"
                           :value="item.v" />
              </el-select>
            </div>
            <div class="item-content">
              <span class="item-content-title">代理IP:</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="15"
                        v-model.trim="numberData.proxyAddress"
                        :disabled="numberData.socketProxy!=1" />
            </div>
            <div class="item-content">
              <span class="item-content-title">代理端口 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="5"
                        v-model.number.trim="numberData.proxyPort"
                        type="number"
                        :disabled="numberData.socketProxy!=1" />
            </div>
            <div class="item-content">
              <span class="item-content-title">代理用户名 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="32"
                        v-model.trim="numberData.proxyUserName"
                        :disabled="numberData.socketProxy!=1" />
            </div>
            <div class="item-content">
              <span class="item-content-title">代理密码 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="32"
                        v-model.trim="numberData.proxyPassword"
                        :disabled="numberData.socketProxy!=1" />
            </div>
          </div>
          <div>
            <div class="item-title">设备相关</div>
            <div class="item-content">
              <span class="item-content-title">得实仿真 :</span>
              <el-select placeholder="请选择"
                         class="item-content-msg"
                         v-model="numberData.dsfz">
                <el-option v-for="(item,index) in dsfz"
                           :key="index"
                           :label="item.label"
                           :value="item.v" />
              </el-select>
              <!--<el-switch v-model="numberData.dsfz" :active-value="'1'" :inactive-value="'0'"/>-->
            </div>
            <!--<div class="item-content">-->
            <!--<span class="item-content-title">设备型号 :</span>-->
            <!--<el-input class="item-content-msg" suffix-icon="el-icon-edit" maxlength="32" v-model.trim="numberData.deviceModel"/>-->
            <!--</div>-->
            <div class="item-content">
              <span class="item-content-title">SPI通讯 :</span>
              <el-select placeholder="请选择"
                         class="item-content-msg"
                         v-model="numberData.spi">
                <el-option v-for="(item,index) in spi"
                           :key="index"
                           :label="item.label"
                           :value="item.v" />
              </el-select>
            </div>
            <div class="item-content">
              <span class="item-content-title">通信速度 :</span>
              <el-select placeholder="请选择"
                         class="item-content-msg"
                         v-model="numberData.dataTransmissionSpeed">
                <el-option v-for="(item,index) in dataTransmissionSpeed"
                           :key="index"
                           :label="item.label"
                           :value="item.v" />
              </el-select>
            </div>
            <div class="item-content">
              <span class="item-content-title">重连时长 :</span>
              <el-input class="item-content-msg"
                        suffix-icon="el-icon-edit"
                        maxlength="32"
                        type="number"
                        v-model.number.trim="numberData.reconnectionInterval" />
            </div>
          </div>

          <!--<div>
            <div class="item-title">其他</div>
            &lt;!&ndash;<div class="item-content">&ndash;&gt;
              &lt;!&ndash;<span class="item-content-title">设备号 :</span>&ndash;&gt;
              &lt;!&ndash;<el-input class="item-content-msg" suffix-icon="el-icon-edit"/>&ndash;&gt;
            &lt;!&ndash;</div>&ndash;&gt;
            <div class="item-content">
              <span class="item-content-title">设备名称 :</span>
              <el-input class="item-content-msg" suffix-icon="el-icon-edit" maxlength="32" v-model.trim="numberData.apModelSsid" />
            </div>
            <div class="item-content">
              <span class="item-content-title">设备密码 :</span>
              <el-input class="item-content-msg" suffix-icon="el-icon-edit" maxlength="32" v-model.trim="numberData.apModelPassword"/>
            </div>
            <div class="item-content">
              <span class="item-content-title">网络模式 :</span>
              <el-input class="item-content-msg" suffix-icon="el-icon-edit"/>
            </div>
          </div>-->
        </div>
        <div style="display:flex;justify-content: flex-end;margin-top: 12px;margin-bottom: 72px">
          <el-button size="small"
                     style="width: 60px;height: 36px;border-radius:6px;"
                     @click="cancelConfig">取消
          </el-button>
          <el-button size="small"
                     type="primary"
                     style="width: 60px;height: 36px;border-radius:6px;"
                     @click="saveConfig">保存
          </el-button>
        </div>
        <!--<div class="content">
          <div class="chunk prarim">
            <div class="chunk-item">
              <div class="chunk-name">apModelSsid:</div>
              <div class="chunk-value">{{numberData.apModelSsid}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">localGateway:</div>
              <div class="chunk-value">{{numberData.localGateway}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">localIpAddress:</div>
              <div class="chunk-value">{{numberData.localIpAddress}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">localSubnetMask:</div>
              <div class="chunk-value">{{numberData.localSubnetMask}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">apModelPassword:</div>
              <div class="chunk-value">{{numberData.apModelPassword}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">mainDNSServerAddress:</div>
              <div class="chunk-value">{{numberData.mainDNSServerAddress}}</div>
            </div>
          </div>

          <div class="chunk waring">
            <div class="chunk-item">
              <div class="chunk-name">number:</div>
              <div class="chunk-value">{{numberData.number}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">domainName:</div>
              <div class="chunk-value">{{numberData.domainName}}</div>
            </div>

            <div class="chunk-item">
              <div class="chunk-name">remoteRouteSsid:</div>
              <div class="chunk-value">{{numberData.remoteRouteSsid}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">remoteRoutePassword:</div>
              <div class="chunk-value">{{numberData.remoteRoutePassword}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">remoteServerAddress:</div>
              <div class="chunk-value">{{numberData.remoteServerAddress}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">slaveDNSServerAddress:</div>
              <div class="chunk-value">{{numberData.slaveDNSServerAddress}}</div>
            </div>
          </div>

          <div class="chunk prarim">
            <div class="chunk-item">
              <div class="chunk-name">proxyUrl:</div>
              <div class="chunk-value">{{numberData.proxyUrl}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">proxyPort:</div>
              <div class="chunk-value">{{numberData.proxyPort}}</div>
            </div>

            <div class="chunk-item">
              <div class="chunk-name">proxyMode:</div>
              <div class="chunk-value">{{numberData.proxyMode}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">proxyAddress:</div>
              <div class="chunk-value">{{numberData.proxyAddress}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">proxyPassword:</div>
              <div class="chunk-value">{{numberData.proxyPassword}}</div>
            </div>

            <div class="chunk-item">
              <div class="chunk-name">proxyUserName:</div>
              <div class="chunk-value">{{numberData.proxyUserName}}</div>
            </div>
          </div>

          <div class="chunk waring">
            <div class="chunk-item">
              <div class="chunk-name">dns:</div>
              <div class="chunk-value">{{numberData.dns}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">dsfz:</div>
              <div class="chunk-value">{{numberData.dsfz}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">dhcp:</div>
              <div class="chunk-value">{{numberData.dhcp}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">udpPort:</div>
              <div class="chunk-value">{{numberData.udpPort}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">dataPort:</div>
              <div class="chunk-value">{{numberData.dataPort}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">controlPort:</div>
              <div class="chunk-value">{{numberData.controlPort}}</div>
            </div>
          </div>

          <div class="chunk prarim">
            <div class="chunk-item">
              <div class="chunk-name">spi:</div>
              <div class="chunk-value">{{numberData.spi}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">socketProxy:</div>
              <div class="chunk-value">{{numberData.socketProxy}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">deviceModel:</div>
              <div class="chunk-value">{{numberData.deviceModel}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">networkMode:</div>
              <div class="chunk-value">{{numberData.networkMode}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">networkChannel:</div>
              <div class="chunk-value">{{numberData.networkChannel}}</div>
            </div>
            <div class="chunk-item">
              <div class="chunk-name">dataTransmissionSpeed:</div>
              <div class="chunk-value">{{numberData.dataTransmissionSpeed}}</div>
            </div>
          </div>
          <div class="chunk waring">
            <div class="chunk-item">
              <div class="chunk-name">reconnectionInterval:</div>
              <div class="chunk-value">{{numberData.reconnectionInterval}}</div>
            </div>
          </div>
        </div>-->
      </div>
    </div>
    <div v-show="tab"
         class="pagination">
      <el-pagination @handleChange="handleChange"
                     @current-change="handleCurrentChange"
                     :current-page.sync="currentPage"
                     :page-size="pageNum"
                     layout="prev, pager, next, jumper"
                     :total="numberList.length">
      </el-pagination>
      <span style="margin-left: 18px">每页显示行数：</span>
      <el-input-number v-model="pageNum"
                       size="mini"
                       style="width: 110px;"
                       @change="handleChange"
                       :min="1"
                       label="描述文字" />
    </div>
  </div>
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
      this.printNumber = row.number
      this.getConfig(row.number,index)
      setTimeout(() => {
        this.tab = false
        this.numberListData[index].loading = false
      }, 300);

    },
    getConfig (number) {
      getAquipmentConfigReadConfig(number)
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
          res.data.networkChannel = res.data.networkChannel + 1
          this.numberData = noSpace(res.data)
          this.cancelNumberData = { ...this.numberData }
          /*str.replace(/\s*!/g,"");*/


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
      if (!this.myVerification(this.numberData)) {
        return
      }
      this.numberData.networkChannel = this.numberData.networkChannel - 1
      saveAquipmentConfigReadConfig({ data: this.numberData })
        .then(res => {
          this.myMessage('success', '设备信息修改成功')
          this.getConfig(this.printNumber)
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
          if (value == null) {
            return
          }
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
                  return false
                }
              }

            }
          }
        }
        return true
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
      return init()
    }

  },

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
