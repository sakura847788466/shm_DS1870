<template>

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
