<template>

</template>

<script>
import { getNormalonline } from "../../api/index";
import MyPopover from "../../components/MyPopover/MyPopover";
import { transitionWifiFirmwareVersion } from "../../util/tool";

export default {
  name: "DeviceState",
  mounted () {
    this.getStateInfo(this.statetype);
  },
  data () {
    return {
      search: '',//搜索
      numberData: [], //总数据
      number: [], //分页数据
      statetype: "正常", //查询状态
      other: ["正常", "错误", "警告", "离线"],
      currentPage: 1,
      pageNum: 10,
      //自定义系列number
      customList: [
        { name: '打印机编号', state: true, value: 'number' },
        { name: '版本号', state: true, value: 'wifiFirmwareVersion' },
        { name: 'IP', state: true, value: 'ip' },
        { name: '状态', state: true, value: 'state' },
      ],
      custom: {
        number: true,
        state: true,
        ip: true,
        wifiFirmwareVersion: true
      }
    };
  },
  methods: {
    async toggleState () {
      const result = await getNormalonline(this.statetype);
      if (result.code == 0) {
        if (result.data.length < 1) {
          this.number = [];
          this.$message({
            type: "error",
            message: `沒有显示${this.statetype}状态的设备`,
            duration: 3000,
            showClose: true
          });
        } else {
          for (let i = 0; i < result.data.length; i++) {
            result.data[i].id = i + 1;
            result.data[i].wifiFirmwareVersion = transitionWifiFirmwareVersion(result.data[i].wifiFirmwareVersion)
          }
          this.numberData = result.data;
          this.number = this.numberData.slice(0, this.pageNum);
        }
      } else {
        this.$message({
          type: "error",
          message: "读取设备失败",
          duration: 3000,
          showClose: true
        });
      }
    },

    async getStateInfo (type) {
      const result = await getNormalonline(type);

      if (result.code == 0) {
        for (let i = 0; i < result.data.length; i++) {
          result.data[i].wifiFirmwareVersion = transitionWifiFirmwareVersion(result.data[i].wifiFirmwareVersion)
          result.data[i].id = i + 1;
        }
        /* const data = []
         for (let i=0;i<15;i++){
           data.push({
             id:i,
             ipsString: "10.1.168.192",
             main: "正常",
             number: "000BBE7350027000",
             wifiFirmwareVersion: "01.00.00.0C."
           })
         }*/

        this.numberData = result.data;
        this.number = this.numberData.slice(0, this.pageNum);
      }
    },

    //分页
    handleChange (val) {
      this.number = this.numberData.slice(0, val);
    },
    handleCurrentChange (val) {
      let last = this.pageNum * val;
      let first = last - this.pageNum;
      this.number = [];
      this.number = this.numberData.slice(first, last);
    },

    //自定义列
    defaultFun (data) {
      this.custom = {}
      for (let item of data) {
        this.custom[item.value] = item.state
      }
    },
    confirmFun (data) {
      this.custom = {}
      for (let item of data) {
        this.custom[item.value] = item.state
      }
      this.customList = data
    }
  },
  components: { MyPopover }
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
  width: 1000px;
  height: 700px;
  /*border: 1px solid #ddd;*/
}

.title {
  position: relative;
  box-sizing: content-box;
  display: flex;
  justify-content: space-between;
  padding-bottom: 10px;
  width: 100%;
  height: 40px;
  line-height: 40px;
  font-size: 24px;
  border-bottom: 1px solid rgba(231, 231, 231, 1);
}

.pagination {
  display: flex;
  justify-content: flex-end;
  align-items: center;
  padding-top: 16px;
}

@media (max-width: 1200px) {
  .box {
    width: 90%;
  }
}
</style>
