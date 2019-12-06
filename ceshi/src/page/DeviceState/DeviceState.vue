<template>
  <div class="right">
    <div class="box">
      <div class="title">
        <div style="display: flex;align-items: center">
          <span style="margin-right: 40px">正在显示的设备</span>
          <MyPopover :custom-list="customList"
                     @defaultFun="defaultFun"
                     @confirmFun="confirmFun"
                     @closeCustom="closeCustom" />
        </div>
        <el-input v-model="search"
                  suffix-icon="el-icon-search"
                  placeholder="输入number搜索"
                  style="width: 250px;height: 100%;" />

      </div>
      <div class="body">
        <el-table :data="number.filter(data => !this.search || data.number.toLowerCase().includes(this.search.toLowerCase()))"
                  style="width: 100%;height: 485px"
                  max-height="485px">

          <el-table-column label="序号"
                           prop="id" />
          <el-table-column label="打印机编号"
                           prop="number"
                           v-if="custom.number" />
          <el-table-column label="版本号"
                           prop="wifiFirmwareVersion"
                           v-if="custom.wifiFirmwareVersion" />
          <el-table-column label="本地ip"
                           prop="ipsString"
                           v-if="custom.ip" />
          <el-table-column label="状态"
                           prop="main"
                           v-if="custom.state"
                           width="200"
                           align="center"
                           style="height: 300px;">
            <template slot="header"
                      slot-scope="scope">
              <div style="display: flex;line-height: 40px"
                   class="select-box">
                状态
                <el-select v-model="statetype"
                           @change="toggleState"
                           size="small">
                  <el-option v-for="item in other"
                             :key="item"
                             :value="item" />
                </el-select>
              </div>
            </template>
          </el-table-column>
        </el-table>
      </div>
      <div class="pagination">
        <el-pagination @handleChange="handleChange"
                       @current-change="handleCurrentChange"
                       :current-page.sync="currentPage"
                       :page-size="pageNum"
                       layout="prev, pager, next, jumper"
                       :total="numberData.length" />
        <span style="margin-left: 18px">每页显示行数：</span>
        <el-input-number v-model="pageNum"
                         size="mini"
                         @change="handleChange"
                         :min="1"
                         label="描述文字"
                         style="width: 110px" />
      </div>
    </div>
  </div>
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
