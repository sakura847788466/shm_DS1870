<template>
  <div class="right">
    <div class="box">
      <div class="title">服务配置信息</div>
      <div class="line"></div>
      <div class="body">

        <!--<div>-->
        <!--<span style="margin-left: 58px;">回调url：</span>-->
        <!--<el-input size="medium " suffix-icon="el-icon-edit" v-model="info['address.url']" style="width: 723px;"/>-->
        <!--</div>-->

        <!--<div style="margin-top: 18px">-->
        <!--<span style="margin-left: 48px;">回调次数：</span>-->
        <!--<el-input-number size="medium " suffix-icon="el-icon-edit" :min="0" v-maxLength-->
        <!--v-model="info['address.reqcount']"/>-->
        <!--</div>-->
        <div>
          <span style="margin-left: 58px;">接收url：</span>
          <el-input size="medium "
                    suffix-icon="el-icon-edit"
                    v-model="info['address.url']"
                    style="width: 723px;" />
        </div>

        <div style="margin-top: 18px">
          <span style="margin-left: 58px;">返回url：</span>
          <el-input size="medium "
                    suffix-icon="el-icon-edit"
                    v-model="info['retaddress.url']"
                    style="width: 723px;" />
        </div>

        <div style="display: flex;">
          <div class="form-left">
            <div>
              <span>设备空闲时间：</span>
              <el-input-number size="medium "
                               suffix-icon="el-icon-edit"
                               :min="0"
                               v-maxLength
                               v-model="info['free.time']" />
              （s）
            </div>
            <div>
              <span>设备离线时间：</span>
              <el-input-number size="medium "
                               suffix-icon="el-icon-edit"
                               :min="0"
                               v-maxLength
                               v-model="info.allowofflinetime" />
              （s）
            </div>
            <div>
              <span>扫描间隔时间：</span>
              <el-input-number size="medium "
                               suffix-icon="el-icon-edit"
                               :min="0"
                               v-maxLength
                               v-model="info['apart.time']" />
              （s）
            </div>
            <div>
              <span>数据轮询时间：</span>
              <el-input-number size="medium "
                               suffix-icon="el-icon-edit"
                               :min="0"
                               v-maxLength
                               v-model="info['polling.timeout']" />
              （s）
            </div>
            <div>
              <span>等待结果时间：</span>
              <el-input-number size="medium "
                               suffix-icon="el-icon-edit"
                               :min="0"
                               v-maxLength
                               v-model="info['sleep.time']" />
              （s）
            </div>

            <div>
              <span>控制通道端口：</span>
              <el-input-number size="medium "
                               suffix-icon="el-icon-edit"
                               :min="0"
                               v-maxLength
                               v-model="info['control.port']" />
            </div>
            <div>
              <span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;服务端口：</span>
              <el-input-number size="medium "
                               suffix-icon="el-icon-edit"
                               :min="0"
                               v-maxLength
                               v-model="info['server.port']" />
            </div>
            <!-- ada -->
            <div style="display:flex;align-items:center;">
              <span style="height:37px;line-height:37px;margin-left:-10px;">定时备份数据时间：</span>
              <div class="my-dialog-body-content"
                   style="display:flex; height:37px;width:205px; line-height:37px;justify-content: space-between;border:1px solid #e7e7e7;border-radius: 4px;">
                <div>每隔
                  <el-select v-model="timer['month']"
                             placeholder=""
                             style="width: 53px"
                             size="mini"
                             disabled>
                    <el-option v-for="item in 12"
                               :key="item"
                               :value="item"></el-option>
                  </el-select>
                  个月的
                </div>
                <div>
                  <el-select v-model="timer['day']"
                             placeholder=""
                             style="width: 53px"
                             size="mini"
                             disabled>
                    <el-option v-for="item in 30"
                               :key="item"
                               :value="item"></el-option>
                  </el-select>
                  日
                </div>
              </div>
              <el-popover placement="right"
                          width="200"
                          trigger="hover"
                          popper-class="popover"
                          content="请前往 导航栏 更多 中 数据备份 中的 定时备份进行更改">
                <img slot="reference"
                     src="../WhiteList/img/question.png"
                     style="margin-left: -10px;width: 19px;height: 19px;background-size: 100% 100%; cursor: pointer;" />
              </el-popover>
            </div>
            <!-- ada -->
            <div>
              <span>&nbsp;&nbsp;&nbsp;白名单开关：</span>
              <el-switch v-model="info.whitelistswitch"
                         active-value="true"
                         inactive-value="false"
                         style="margin-right: 199px" />
            </div>
          </div>
          <div class="form-right">
            <div>
              <span>打印超时：</span>
              <el-input-number size="medium "
                               suffix-icon="el-icon-edit"
                               :min="0"
                               v-maxLength
                               v-model="info['print.timeout']" />
              （s）
            </div>
            <div>
              <span>客户端超时：</span>
              <el-input-number size="medium "
                               suffix-icon="el-icon-edit"
                               :min="0"
                               v-maxLength
                               v-model="info['client.timeout']" />
              （s）
            </div>
            <div>
              <span>控制通道心跳时间：</span>
              <el-input-number size="medium "
                               suffix-icon="el-icon-edit"
                               :min="0"
                               v-maxLength
                               v-model="info['control.timeout']" />
              （s）
            </div>
            <div>
              <span>设备认证超时时间：</span>
              <el-input-number size="medium "
                               suffix-icon="el-icon-edit"
                               :min="0"
                               v-maxLength
                               v-model="info['ident.time']" />
              （s）
            </div>
            <div>
              <span>数据通道超时：</span>
              <el-input-number size="medium "
                               suffix-icon="el-icon-edit"
                               :min="0"
                               v-maxLength
                               v-model="info['data.timeout']" />
              （s）
            </div>

            <div>
              <span>数据通道端口：</span>
              <el-input-number size="medium "
                               suffix-icon="el-icon-edit"
                               :min="0"
                               v-maxLength
                               style="margin-right: 39px"
                               v-model="info['data.port']" />
            </div>
            <div>
              <span>日志级别控制：</span>
              <el-select v-model="info['logging.level.root']"
                         placeholder="请选择"
                         style="margin-right: 39px">
                <el-option value="INFO"
                           label="打印日志" />
                <el-option value="WARN"
                           label="警告日志" />
                <el-option value="ERROR"
                           label="异常日志" />
              </el-select>
            </div>
            <!-- ada -->
            <div style="display:flex;align-items:center;">
              <span style="height:37px;line-height:37px;">定时删除日志时间：</span>
              <div class="my-dialog-body-content"
                   style="display:flex; height:37px;width:205px; line-height:37px;justify-content: space-between;border:1px solid #e7e7e7;border-radius: 4px;">
                <div>每隔
                  <el-select v-model="timer['month_l']"
                             placeholder=""
                             style="width: 53px"
                             size="mini"
                             disabled>
                    <el-option v-for="item in 12"
                               :key="item"
                               :value="item"></el-option>
                  </el-select>
                  个月的
                </div>
                <div>
                  <el-select v-model="timer['day_l']"
                             placeholder=""
                             style="width: 53px"
                             size="mini"
                             disabled>
                    <el-option v-for="item in 30"
                               :key="item"
                               :value="item"></el-option>
                  </el-select>
                  日
                </div>
              </div>
              <el-popover placement="right"
                          width="200"
                          trigger="hover"
                          popper-class="popover"
                          content="请前往 导航栏 更多 中 数据备份 中的 定时备份进行更改">
                <img slot="reference"
                     src="../WhiteList/img/question.png"
                     style="margin-left: 10px;width: 19px;height: 19px;background-size: 100% 100%; cursor: pointer;" />
              </el-popover>
            </div>
            <!-- ada -->
          </div>
        </div>
      </div>
      <div class="line"
           style="margin-top: 30px;margin-bottom: 17px" />
      <div style="display: flex;justify-content: space-between">
        <el-button size="small"
                   type="danger"
                   @click="restore">恢复默认</el-button>
        <div>
          <el-button size="small"
                     @click="close">取消</el-button>
          <el-button size="small"
                     type="primary"
                     @click="save">立即保存</el-button>
        </div>
      </div>

    </div>
  </div>
</template>

<script>
import { getConfig, setConfig, restoreConfig } from "../../api/index";

export default {
  name: "DeviceInfo",
  mounted () {
    getConfig()
      .then(res => {
        this.info = res.data;
        const deltime = this.info.timingbackup.split(' ')
        const logtime = this.info.timingdellog.split(' ')
        if (deltime[4] == "*") { //设置日时间  ["0", "0", "0", "2", "1/1", "*"]   0 0 0 1/3 * *
          // console.log("存在*号")
          let day = deltime[3].split('/')
          let day_log = logtime[3].split('/')
          this.timer.day_l = day_log[1]
          this.timer.month_l = day_log[0]
          this.timer.day = day[1]
          this.timer.month = day[0]

        } else {
          // console.log("不存在*号")
          let day = deltime[3]
          this.timer.day = day
          let month = deltime[4].split("/")
          this.timer.month = month[1]
          let day_log = logtime[3].split('/')
          this.timer.day_l = day_log[1]
          this.timer.month_l = day_log[0]
        }

      })
      .catch(res => {
        console.log(res);
      });
  },

  data () {
    return {
      info: {},
      timer: { month: '', day: '', twoDay: '', day_l: '', month_l: '' }
    };
  },

  methods: {
    save () {
      const info = this.info;
      for (let item in info) {
        if (typeof info[item] == "number") {
          this.info[item] = Math.floor(info[item]);
        }
      }
      setConfig(this.info)
        .then(res => {
          this.$alert(res.data, "保存成功").then(res => {
            getConfig().then(res => {
              this.info = res.data;
            });
          });
        })
        .catch(res => {
          this.$alert(res.data, "保存失败");
        });
    },

    close () {
      getConfig().then(res => {
        this.info = res.data;
      });
    },

    restore () {
      this.$confirm('是否还原到默认配置？', '提示', {
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
        restoreConfig().then(res => {
          this.$message({
            type: 'success',
            message: res.data,
            duration: 3000,
            showClose: true,
            offset: 52
          })
          getConfig()
            .then(res => {
              this.info = res.data;
            })
            .catch(res => {
              console.log(res);
            });
          loading.close()
        }).catch(res => {
          this.$message({
            type: 'error',
            message: '网络出错了',
            duration: 3000,
            showClose: true,
            offset: 52
          })
          loading.close()
        })
      })
    }
  },

  watch: {},

  directives: {
    maxLength: {
      inserted: function (el) {
        const e = el.children[2].children[0];
        e.maxLength = 8;
      }
    }
  }
};
</script>

<style scoped>
.right {
  display: flex;
  justify-content: center;
  justify-items: center;
  width: 100%;
}

.box {
  box-sizing: content-box;
  width: 906px;
  height: 564px;
}

.title {
  width: 100%;
  height: 50px;
  line-height: 50px;
  font-size: 24px;
  color: #333;
  font-weight: 400;
  /*border-bottom: 1px solid #ddd;*/
}

.line {
  margin-top: 7px;
  width: 100%;
  height: 1px;
  background-color: #e7e7e7;
}

.body {
  margin-top: 30px;
  font-size: 14px;
  color: #666;
}

.form-left > div,
.form-right > div {
  margin-top: 18px;
}

.form-left span {
  margin-left: 20px;
}

.form-right {
  text-align: right;
  font-size: 14px;
  margin-left: 130px;
}
</style>
