<template>
  <div>
    <header>
      <div class="nav max">
        <li :class="{in:isCurrent('/')}"
            @click="goTo('/')"><span>白名单</span></li>
        <li :class="{in:isCurrent('/deviceState')}"
            @click="goTo('/deviceState')"><span>设备状态</span></li>
        <li :class="{in:isCurrent('/aquipmentConfig')}"
            @click="goTo('/aquipmentConfig')"><span>设备配置信息</span></li>
        <li :class="{in:isCurrent('/printRecord')}"
            @click="goTo('/printRecord')"><span>打印记录</span></li>
        <li :class="{in:isCurrent('/log')}"
            @click="goTo('/log')"><span>日志信息</span></li>

        <li class="move"
            :class="{in:isCurrent('/hotDeploy')||isCurrent('/firmware')||isCurrent('/backups')||isCurrent('/deviceInfo')}">更多
          <i class="el-icon-arrow-down"></i>
          <ul class="hide-move">
            <li @click="goTo('/hotDeploy')"
                :style="isCurrent('/hotDeploy')?'color:#409EFF':''"><span>热部署</span></li>
            <li @click="goTo('/firmware')"
                :style="isCurrent('/firmware')?'color:#409EFF':''"><span>固件升级</span></li>
            <li @click="goTo('/backups')"
                :style="isCurrent('/backups')?'color:#409EFF':''"><span>数据备份</span></li>
            <li><span @click="updateIP">请求服务</span></li>
            <li @click="goTo('/deviceInfo')"
                :style="isCurrent('/deviceInfo')?'color:#409EFF':''">服务配置信息</li>
            <li @click="goTo('/voiceInfo')"
                :style="isCurrent('/voiceInfo')?'color:#409EFF':''">引导配置信息</li>
          </ul>
        </li>
        <li :class="{in:isCurrent('/help')}"
            @click="goTo('/help')"><span>打印测试</span></li>
      </div>

    </header>
    <UpdateServer v-if="isShowUpdatServer"
                  :active="active"
                  :close="close" />
  </div>

</template>

<script>
import myLocalStorage from '../../util/localStorage'
import UpdateServer from "../UpdataServer/UpdateServer";

export default {
  name: "Header",
  mounted () {

  },
  data () {
    return {
      isShowUpdatServer: false,
      active: '',
    }
  },
  methods: {

    goTo (path) {
      this.$router.replace(path)
    },
    isCurrent (path) {
      return this.$route.path === path
    },

    //修改请求服务设置
    updateIP () {
      const server = JSON.parse(myLocalStorage.get('server'))
      this.isShowUpdatServer = true
      if (server.type == 'ip') {
        this.active = 'ip'
      } else {
        this.active = 'url'
      }
    },
    //关闭请求服务设置
    close () {
      this.isShowUpdatServer = false
    },
  },
  components: { UpdateServer },
}
</script>

<style scoped>
header {
  display: flex;
  width: 100%;
  margin-bottom: 95px;
  background-color: #333;
}

.nav {
  display: flex;
  align-items: flex-end;
  margin: 0 auto;
  height: 100%;
}

.nav > li {
  position: relative;
  margin-right: 20px;
  width: 110px;
  height: 55px;
  line-height: 55px;
  text-align: center;
  cursor: pointer;
  font-size: 14px;
  color: #fff;
}

.nav > li:hover {
  color: #409eff;
  border-bottom: 3px solid #409eff;
}

.move:hover {
  color: #409eff;
}

.move:hover .hide-move {
  display: block;
}

.hide-move {
  z-index: 1000;
  box-sizing: border-box;
  position: absolute;
  padding-top: 3px;
  /*padding: 12px 0;*/
  width: 120px;
  display: none;
  text-align: center;
  font-size: 14px;
  /*background-color: #505050;*/
}

.hide-move > li {
  box-sizing: border-box;
  width: 100%;
  height: 35px;
  line-height: 35px;
  color: #fff;
  background-color: #505050;
  cursor: pointer;
  transition: 0.3s;
}

.hide-move > li:hover {
  display: block;
  background-color: #333333;
}

.more:hover .hide-more {
  display: block;
}

.in {
  color: #409eff !important;
  border-bottom: 3px solid #409eff;
}

/*@media (max-width: 1222px){*/
/*.nav{*/
/*display: flex;*/
/*align-items: flex-end;*/
/*justify-content: flex-end;*/
/*margin-right: 80px;*/
/*width: 100%;*/
/*height: 100%;*/
/*}*/
/*.max {*/
/*display: none;*/
/*}*/

/*}*/

/*@media (min-width: 1222px) {*/

/*.min {*/
/*display: none;*/
/*}*/

/*}*/
</style>
