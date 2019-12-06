<template>
  <div class="content">
    <div class="left"
         v-show="isLogView">
      <p class="log-title">日志目录</p>
      <div v-for="(item,index) in directory"
           :key="index"
           class="directory-list">
        <div class="directory-list-title"
             @click.prevent="handleClick(index,item.isShow)">
          <img src="../../assets/文件夹icon.png"
               width="16"
               height="14"
               style="margin-right: 10px" />
          <p class="directory-list-name">{{item.date}}</p>
          <i @click.prevent="logDownload('one',item.date)"
             class="el-icon-download"
             style="margin-right: 0"
             :title="'下载'+item.date"></i>
        </div>
        <div v-for="(filename,i) in item.list"
             :key="i"
             class="directory-item"
             v-show="item.isShow"
             @click="onClickLog($event,filename)"
             ref="isColor">
          {{filename}}
          <i @click.prevent="logDownload('two',filename,item.date)"
             class="el-icon-download"
             style="margin-right: 0"
             :title="'下载'+filename"></i>
        </div>
      </div>

      <div class="other"
           v-for="(filename) in other"
           @click="onClickLog($event,filename.value,true)"
           ref="isColor"
           :style="filename.label=='打印日志'?'background:#eee':''">
        <!--<i class="el-icon-tickets" style="margin-right: 10px"></i>-->
        <img src="../../assets/文件.png"
             width="16"
             height="16"
             style="margin-right: 10px" />
        {{filename.label}}
        <i @click.prevent="logDownload('one',filename.label)"
           class="el-icon-download"
           style="position: absolute;right: 10px;top: 18px;"
           :title="'下载'+filename.label"></i>
      </div>
    </div>

    <div class="right"
         v-if="isLogView">
      <div class="box"
           style="position:relative;">
        <div class="title">
          <span>静态日志信息</span>
          <div>
            <el-button type="primary"
                       icon="el-icon-setting"
                       @click="goLogSetting">设置</el-button>
            <el-select v-model="value"
                       placeholder="实时日志信息"
                       @change="goNowLogInfo">
              <el-option v-for="(item,index) in other"
                         :key="index"
                         :label="item.label"
                         :value="item.value">
              </el-option>
            </el-select>
          </div>

        </div>
        <div class="log-view"
             v-html="info"
             ref="logView">

        </div>
        <div class="el-backtop"
             ref='backTop'
             style="position:absolute;right:26px;bottom:42px;"
             v-show="backT"><i class="el-icon-caret-top"></i></div>
        <div class="el-backbottom"
             ref='backBottom'
             style="position:absolute;right:26px;bottom:42px;"
             v-show="backbt"><i class="el-icon-caret-bottom"></i></div>
      </div>

    </div>

    <DynamicLogInfo :isShowLogView="isShowLogView"
                    :logType="logType"
                    v-else />

    <el-dialog title="日志设置"
               :visible.sync="isShowLogSetting"
               width="620px"
               top="203px"
               class="my_dialog">
      <p class="my-dialog-title">1.请选择定时删除日志方式</p>
      <p style="font-size: 14px;margin:20px 0 20px 16px;color: #000">
        <i class="el-icon-warning-outline"
           style="color: dodgerblue"></i>
        当前日志删除方式是：
        <span style="color: #F56C6C">{{timer.text}}</span>
      </p>
      <div class="my-dialog-body">
        <div class="my-dialog-body-title">
          <el-radio v-model="activeName"
                    label="month"
                    style="margin-right: 50px">月份和日期</el-radio>
          <el-radio v-model="activeName"
                    label="day">日期</el-radio>
        </div>
        <div v-show="activeName=='month'">
          <div class="my-dialog-body-content">
            <div>每隔
              <el-select v-model="timer.month"
                         placeholder=""
                         style="width: 60px"
                         size="mini">
                <el-option v-for="item in 12"
                           :key="item"
                           :value="item"></el-option>
              </el-select>
              个 月 的
            </div>
            <div>
              <el-select v-model="timer.day"
                         placeholder=""
                         style="width: 60px"
                         size="mini">
                <el-option v-for="item in 30"
                           :key="item"
                           :value="item"></el-option>
              </el-select>
              日
            </div>
          </div>
          <p style="margin-left: 16px">(提示：如果想设置每隔3个月的15号进行定时删除日志，如：
            <span style="color: #000;font-weight: 700">每隔3个月的第15日</span> )</p>
        </div>
        <div v-show="activeName=='day'">
          <div class="my-dialog-body-content">
            每隔
            <el-select v-model="timer.twoDay"
                       placeholder=""
                       style="margin:0 3px;width: 60px"
                       size="mini">
              <el-option v-for="item in 30"
                         :key="item"
                         :value="item"></el-option>
            </el-select>
            日
          </div>
          <p style="margin-left: 16px">( 提示：如果想设置每个月的15日进行定时删除日志，如：
            <span style="color: #000;font-weight: 700">每隔15日</span> )
          </p>
        </div>
      </div>
      <p class="my-dialog-title"
         style="margin-top: 28px;margin-bottom: 15px">2.请设置保留日志的天数</p>
      <el-select v-model="timer.saveDay"
                 placeholder=""
                 style="width: 60px;"
                 size="mini">
        <el-option v-for="item in 31"
                   :key="item"
                   :value="item">
        </el-option>
      </el-select>
      天
      <div class="dialog-footer">
        <el-button @click="isShowLogSetting=false">取 消</el-button>
        <el-button type="primary"
                   @click="updateSetting">确 定</el-button>
      </div>
    </el-dialog>
  </div>

</template>

<script>
import dayjs from 'dayjs'

import { getlog, getServerLog, printlog } from '../../api'
import { conversionLog, streamData, transitionFileName } from "../../util/tool";
import DynamicLogInfo from "../../components/DynamicLogInfo/DynamicLogInfo";
import { getConfig, setConfig } from "../../api";

export default {
  name: "Log",
  components: { DynamicLogInfo },

  mounted () {
    getServerLog()
      .then(res => {
        for (let item of res.data) {
          item.isShow = false
        }
        this.directory = res.data
      })
      .catch(res => {
        console.log(res);
      })

    getlog('info.log').then(res => {
      this.infoData = new Buffer(res.data)
      streamData(this.infoData, (err, data) => {
        if (err) {
          console.log(err);
          return
        }
        this.info = conversionLog(data)

      })
    }).catch(res => {
      console.log(res);
    })

    //利用滚动事件，实现日志懒加载
    this.logView = this.$refs.logView
    this.logView.addEventListener('scroll', this.loadLog)
    this.backTop = this.$refs.backTop
    this.backTop.addEventListener('click', this.BackTop)

    this.backBottom = this.$refs.backBottom
    this.backBottom.addEventListener('click', this.toBottom)

    this.getLogSetting()
    if (document.addEventListener) {
      document.addEventListener('DOMMouseScroll', this.scrollFunc, false);
    }
    window.onmousewheel = document.onmousewheel = this.scrollFunc;

  },
  data () {
    return {
      directory: [],
      other: [
        { label: '警告日志', value: 'warn.log' },
        { label: '打印日志', value: 'info.log' },
        { label: '异常日志', value: 'error.log' },
      ],
      //懒加载日志
      info: '',//日志展示
      infoData: '',//总日志
      logView: null,//窗口对象
      backTop: null,//置顶串口对象
      scrollTop: '',//滚动条头距离
      i: 1,//切换日志标识符

      value: '',
      logType: '',
      loading: false,//跳转的实时日志页面的按钮加载圈
      isLogView: true,
      hideLeft: false,
      isShowLogSetting: false,//设置日志定时删除
      timer: { month: '1', day: '1', saveDay: '7', twoDay: '1', text: '' },
      activeName: 'month',
      backT: false,//回到顶部显示
      backbt: false,
      botHeight: ''//底部距离
    }
  },
  methods: {

    //是否显示日志目录
    handleClick (index, isShow) {
      this.directory.forEach(item => {
        item.isShow = false
      })
      if (isShow) {
        this.directory[index].isShow = false
      } else {
        this.directory[index].isShow = true
      }

    },

    //点击日志
    async onClickLog ($event, filename, type = false) {
      this.info = ''
      this.i = 1
      this.tabDirectory($event)
      if (type) {
        this.directory.forEach(item => {
          item.isShow = false
        })
      }
      const loading = this.$loading({
        lock: true,
        text: '日志加载中...',
        spinner: 'el-icon-loading',
        background: 'rgba(0, 0, 0, 0.7)'
      });
      if (filename == '打印日志') {
        filename = 'info.log'
      } else if (filename == '警告日志') {
        filename = 'warn.log'
      } else if (filename == '异常日志') {
        filename = 'error.log'
      }
      const result = await getlog(filename)
      if (result.code == 0) {
        this.info = ''
        this.infoData = ''
        this.infoData = new Buffer(result.data)
        streamData(this.infoData, (err, data) => {
          if (err) {
            console.log(err);
            return
          }
          this.info = conversionLog(data)
        })
        loading.close();
      } else {
        this.$message({
          type: 'error',
          message: '网络出错了',
          duration: 3000,
          showClose: true
        })
        loading.close();
      }

    },

    //懒加载日志数据
    loadLog (e) {
      const scrollHeight = e.target.scrollHeight
      const sh = scrollHeight - e.target.scrollTop
      if (sh <= e.target.clientHeight) {
        const arr = this.infoData
        const len = Math.ceil(arr.length / 10000)
        if (this.i < len) {
          this.info = this.info + conversionLog(arr.slice(this.i * 10000 + 1, (this.i + 1) * 10000).toString())
          this.i += 1
        }
      }
    },
    //点击回到顶部
    BackTop () {
      let top = this.logView.scrollTop;
      // 实现滚动效果
      const timeTop = setInterval(() => {
        this.logView.scrollTop = this.logView.scrollTop = top -= 500;
        // console.log(this.logView.scrollTop)
        if (top <= 0) {
          clearInterval(timeTop);
          this.backT = false

        }
      }, 20);
    },
    scrollFunc (e) {
      e = e || window.event;
      if (e.wheelDelta) {
        if (e.wheelDelta > 0) {
          // console.log("滑轮向上滚动");
          const scrollHeight = e.target.scrollHeight//整个滚动条长
          const sh = e.target.scrollTop //上面的距离
          const croh = e.target.clientHeight//滚动条长
          const th = scrollHeight - sh - croh //下面的距离
          th <= 4000 ? (this.backbt = true) : (this.backbt = false) //向下键


        }
        if (e.wheelDelta < 0) {
          // console.log("滑轮向下滚动");
          const scrollHeight = e.target.scrollHeight
          const sh = scrollHeight - e.target.scrollTop
          sh <= 4000 ? (this.backT = true) : (this.backT = false)//向上键
        }
      } else if (e.detail) {
        if (e.detail > 0) {
          console.log("滑轮向上滚动");
        }
        if (e.detail < 0) {
          console.log("滑轮向下滚动");
        }
      }
    },


    // 点击回底部
    toBottom () {
      var clientHeight = this.logView.clientHeight;
      var scrollHeight = this.logView.scrollHeight;
      var scrollTop = this.logView.scrollTop;
      var height = scrollHeight - clientHeight - scrollTop; //超出窗口上界的值就是底部的scrolTop的值
      // console.log(clientHeight)
      // console.log(scrollHeight)
      // console.log(height)
      this.logView.scrollTop += 500;
      // console.log(scrollTop)
      var c = setTimeout(() => {
        this.toBottom()
      }, 20);
      if (height <= 0) {
        clearTimeout(c);
        this.backbt = false
        this.backT = true
      }
    },

    //跳转到动态日志页面
    goNowLogInfo () {
      this.logType = this.value
      const loading = this.$loading({
        lock: true,
        text: '日志加载中...',
        spinner: 'el-icon-loading',
        background: 'rgba(0, 0, 0, 0.7)'
      });
      setTimeout(() => {
        loading.close();
        this.isLogView = false
        this.hideLeft = false
        this.value = ''
      }, 3000)
    },

    //显示和关闭日志信息页面
    isShowLogView () {
      this.isLogView = true
    },

    //点击月份里的日志，让点击的元素变亮
    tabDirectory ($event) {
      const arr = this.$refs.isColor
      arr.forEach(item => {
        item.style.backgroundColor = ''
      })
      $event.target.style.backgroundColor = '#eee'
    },

    tabSmallDirectory ($event) {
      const arr = this.$refs.isSmallColor
      arr.forEach(item => {
        item.style.color = '#000'
      })
      $event.target.style.color = '#cf9236'
    },


    //下载日志
    logDownload (type, fileName, date) {
      let text
      if (type === 'one') {
        if (!/\d/.test(fileName)) {
          text = fileName + dayjs().format('YYYYMMDDHHmmss')
        }

        this.$prompt('请输入保存的日志名称', '提示', {
          confirmButtonText: '确定',
          cancelButtonText: '取消',
          inputValue: text
        }).then(({ value }) => {
          fileName = transitionFileName(fileName)
          const url = printlog({ fileName, saveName: value })
          window.location.href = url
        })

      } else {
        this.$prompt('请输入保存的日志名称', '提示', {
          confirmButtonText: '确定',
          cancelButtonText: '取消',
          inputValue: fileName
        }).then(({ value }) => {
          fileName = transitionFileName(fileName)
          const url = printlog({ fileName: date + '/' + fileName, saveName: value.toString() })
          window.location.href = url
        })

      }
    },

    //点击显示日志定时删除
    async goLogSetting () {
      this.isShowLogSetting = true
    },

    //初始化日志定时删除
    getLogSetting () {
      getConfig()
        .then(res => {
          const time = res.data.timingdellog.split(' ')
          this.configData = res.data
          if (time[4] == '*') {//设置日期
            this.activeName = 'day'
            let twoDay = time[3].split('/')
            this.timer.twoDay = twoDay[1]
            this.timer.text = `按日期，每隔${twoDay[1]}日`
          } else {
            this.timer.day = time[3]
            let month = time[4].split('/')
            this.timer.month = month[1]
            this.timer.text = `按月份和日期，每隔${month[1]}个月的${time[3]}日`
          }
          this.timer.saveDay = res.data.retainlogtime
        })
        .catch(res => {

        })
    },

    //设置日志定时删除
    updateSetting () {
      let text = ''
      this.configData.retainlogtime = this.timer.saveDay
      this.configData.timingdellog
      if (this.activeName == 'month') {
        this.configData.timingdellog = `0 0 0 ${this.timer.day} 1/${this.timer.month} *`
        text = `是否设置每隔${this.timer.month}个月的${this.timer.day}号定时删除日志`
        //0 0 0 1 1/2 *
      } else {
        this.configData.timingdellog = `0 0 0 1/${this.timer.twoDay} * *`
        text = `是否设置每个月的${this.timer.twoDay}号定时删除日志`
        //0 0 0 1/5 * *
      }
      this.$confirm(text, '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        const loading = this.$loading({
          lock: true,
          text: 'Loading',
          spinner: 'el-icon-loading',
          background: 'rgba(0, 0, 0, 0.7)'
        });
        setConfig(this.configData).then(res => {
          this.$message({
            type: 'success',
            message: res.data,
            duration: 3000,
            showClose: true
          })
          loading.close()
          this.getLogSetting()
          this.isShowLogSetting = false
        }).catch(res => {
          this.$message({
            type: 'error',
            message: '修改失败',
            duration: 3000,
            showClose: true
          })
          loading.close()
        })
      })


    }
  }
}
</script>

<style scoped>
/*定义滚动条高宽及背景
 高宽分别对应横竖滚动条的尺寸*/
.left::-webkit-scrollbar {
  width: 6px;
  height: 6px;
  background-color: #f8f8f8;
}

/*定义滚动条轨道
   内阴影+圆角*/
.left::-webkit-scrollbar-track {
  -webkit-box-shadow: inset 0 0 10px #f8f8f8;
  border-radius: 6px;
  background-color: #f8f8f8;
}
/*向下图标 */
.el-backbottom {
  position: fixed;
  background-color: #fff;
  width: 40px;
  height: 40px;
  border-radius: 50%;
  display: flex;
  -webkit-box-align: center;
  -ms-flex-align: center;
  align-items: center;
  -webkit-box-pack: center;
  -ms-flex-pack: center;
  justify-content: center;
  font-size: 20px;
  -webkit-box-shadow: 0 0 6px rgba(0, 0, 0, 0.12);
  box-shadow: 0 0 6px rgba(0, 0, 0, 0.12);
  cursor: pointer;
  z-index: 5;
}
/*定义滑块
   内阴影+圆角*/
.left::-webkit-scrollbar-thumb {
  border-radius: 6px;
  -webkit-box-shadow: inset 0 0 6px #ededed;
  background-color: #dcdcdc;
}

.content {
  box-sizing: border-box;
  display: flex;
  width: 100%;
  height: 100%;
  overflow: hidden;
}

.left {
  top: 55px;
  position: absolute;
  width: 266px;
  height: calc(100% - 55px);
  overflow: auto;
  background: #f9f9f9;
}

.log-title {
  width: 100%;
  height: 45px;
  text-align: center;
  line-height: 45px;
  font-size: 18px;
  color: #333;
  background: rgba(221, 221, 221, 1);
}

.directory-list {
  line-height: 45px;
  font-size: 16px;
  cursor: pointer;
  overflow-y: auto;
}

.directory-list-title {
  display: flex;
  align-items: center;
  padding: 0 20px;
}

.directory-list-name {
  flex-grow: 1;
}

.directory-list-title:hover {
  background-color: #eee;
}

.other:hover {
  background-color: #eee;
}

.directory-item {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0 28px 0 46px;
  width: 260px;
  font-size: 14px;
  color: #666;
  cursor: pointer;
}

.directory-item:hover {
  background-color: #eee;
}

.el-icon-download {
  margin-right: 10px;
}

.other {
  position: relative;
  display: flex;
  align-items: center;
  padding: 0 20px;
  height: 45px;
  line-height: 45px;
  font-size: 16px;
  color: #666;
  cursor: pointer;
}

.right {
  display: flex;
  justify-content: center;
  justify-items: center;
  margin-left: 427px;
  width: 1200px;
  /*min-height: 800px;*/
}

.box {
  box-sizing: content-box;
  width: 1200px;
  height: 660px;
}

.title {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding-bottom: 10px;
  width: 100%;
  font-size: 24px;
  border-bottom: 1px solid #e7e7e7;
}

.log-view {
  overflow-y: scroll;
  overflow-x: hidden;
  margin-top: 30px;
  padding: 30px 0 0 30px;
  width: 100%;
  height: 600px;
  background-color: #333333;
  border: 1px solid #dddddd;
  color: green;
  text-indent: 5px;
  word-wrap: break-word;
  line-height: 24px;
  font-size: 16px;
}

.my-dialog-title {
  font-size: 14px;
  font-weight: bold;
  color: #000;
}

.my-dialog-body {
  margin-left: 16px;
  width: 540px;
  height: 150px;
  color: #000;
  border: 1px solid rgba(220, 223, 230, 1);
  border-radius: 4px;
}

.my-dialog-body-title {
  margin: 0 15px;
  height: 45px;
  line-height: 45px;
  border-bottom: 1px solid #e4e7ed;
}

.my-dialog-body-content {
  display: flex;
  align-items: center;
  margin: 20px 15px;
}

.dialog-footer {
  display: flex;
  justify-content: flex-end;
  margin-top: 6px;
  margin-right: 5px;
}

@media (min-width: 1440px) {
  .right {
    margin-left: 360px;
    width: calc(100% - 500px);
  }
}

@media (max-width: 1440px) {
  .right {
    margin-left: 300px;
    width: calc(100% - 300px);
  }

  .box {
    width: 90%;
    height: 660px;
  }
}

@media (max-width: 1200px) {
  .right {
    margin-left: 200px;
    width: calc(100% - 200px);
  }
}

@media (max-width: 1024px) {
  .right {
    margin-left: 300px;
    width: calc(100% - 300px);
  }
}
</style>
