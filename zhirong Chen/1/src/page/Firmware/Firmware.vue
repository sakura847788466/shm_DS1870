<template>
  <div class="right">
    <div class="box">
      <div class="title">
        <div style="display: flex;">
          <span style="margin-right: 40px">固件升级</span>
          <MyPopover :custom-list="customList" @defaultFun="defaultFun" @confirmFun="confirmFun" @closeCustom="closeCustom"/>
        </div>
        <el-input style="width: 250px;height: 100%;" v-model="search" placeholder="请输入number号搜索"
                  suffix-icon="el-icon-search"/>
      </div>
      <div class="body">
        <el-table ref="multipleTable"
                  :data="firmwareInfo.filter(data => !this.search || data.number.toLowerCase().includes(this.search.toLowerCase()))"
                  style="width: 100%;height: 558px" max-height="558">
          <el-table-column width="100">
            <template slot="header" slot-scope="scope">
              <el-checkbox :indeterminate="isIndeterminate" v-model="checkAll" @change="handleCheckAllChange"/>
            </template>
            <template slot-scope="scope">
              <el-checkbox v-model="scope.row.state" @change="oneSelect(scope.$index,scope.row.state)"/>
            </template>
          </el-table-column>
          <el-table-column label="序号" prop="id" width="100"/>
          <el-table-column label="打印机编号" prop="number" v-if="custom.number"/>
          <el-table-column label="版本号" prop="wifiFirmwareVersion" v-if="custom.wifiFirmwareVersion"/>
          <el-table-column label="IP" prop="ipsString" v-if="custom.ip"/>
          <el-table-column label="升级模式" v-if="custom.pattern" width="160">
            <template slot-scope="scope">
              <el-select v-model="scope.row.type" placeholder="请选择" style="width: 120px" size="small"
                         @change="setTime(scope.row.id-1,scope.row)">
                <el-option value="wecut" label="定时模式"/>
                <el-option value="force" label="强制模式"/>
                <el-option value="free" label="智能模式"/>
              </el-select>
            </template>
          </el-table-column>
          <el-table-column label="定时时间" width="240" v-if="custom.pattern">
            <template slot-scope="scope" v-if="scope.row.type==='wecut'">
              <el-date-picker v-model="scope.row.time" type="datetime" style="width:190px"
                              value-format="yyyy-MM-dd HH:mm:ss" size="small" placeholder="选择日期时间"/>
            </template>
          </el-table-column>
          <el-table-column label="操作" width="100" v-if="custom.handle">
            <template slot-scope="scope">
              <input :id="scope.row.id" type="file" style="display: none;"
                     @change="request($event,scope.row,'noAll')"/>
              <label slot="reference" :for="scope.row.id" class="btn one-btn" title="请导入.ota文件">
                升级
              </label>
            </template>
          </el-table-column>
        </el-table>
      </div>
      <div class="pagination">
        <div style="display: flex;align-items: center">
          <input id="allFirmware" type="file" style="display: none;"
                 @change="request($event,'','all')"/>
          <label for="allFirmware" class="btn all-btn" title="请导入.ota文件">
            批量升级
          </label>
          <el-select v-model="allType" placeholder="请选择" name="type"
                     style="width: 110px;margin-right: 10px;" size="small">
            <el-option value="wecut" label="定时模式">定时模式
              <el-popover placement="right" width="50" trigger="hover" popper-class="popover"
                          content="选择定时时间，当到达定时时间时，自动升级">
                <i slot="reference" :class="allType=='wecut'?'on-question':'question'"></i>
              </el-popover>
            </el-option>
            <el-option value="force" label="强制模式">强制模式
              <el-popover placement="right" width="50" trigger="hover" popper-class="popover"
                          content="无论设备在工作还是空闲，也能立即升级">
                <i slot="reference" :class="allType=='force'?'on-question':'question'"></i>
              </el-popover>
            </el-option>
            <el-option value="free" label="智能模式">智能模式
              <el-popover placement="right" width="50" trigger="hover" popper-class="popover"
                          content="当设备空闲时，自动升级">
                <i slot="reference" :class="allType=='free'?'on-question':'question'"></i>
              </el-popover>
            </el-option>
          </el-select>
          <el-date-picker v-model="allTime" type="datetime" style="width: 200px;margin-right: 18px;"
                          v-show="allType==='wecut'" size="small"
                          value-format="yyyy-MM-dd HH:mm:ss" placeholder="选择日期时间"/>
        </div>
        <div style="display: flex;align-items: center">
          <el-pagination
            @handleChange="handleChange"
            @current-change="handleCurrentChange"
            :current-page.sync="currentPage"
            :page-size="pageNum"
            layout="prev, pager, next, jumper"
            :total="firmwareInfoData.length">
          </el-pagination>
          <span style="margin-left: 18px">每页显示行数：</span>
          <el-input-number v-model="pageNum" size="mini" @change="handleChange" :min="1"
                           label="描述文字"/>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import {getFirmwareNormalinfo, updateFirmware} from '../../api'
  import MyPopover from '../../components/MyPopover/MyPopover'
  import {transitionWifiFirmwareVersion} from "../../util/tool";

  export default {
    name: "Firmware",
    mounted() {
      // const data = []
      // for (let i=0;i<11;i++){
      //   data.push({id:i,type:'force',time:'',wifiFirmwareVersion:'0.19.01.1',number:'000BBE735002700'+i,ipsString:'192.168.11.112',state:false})
      // }
      // this.firmwareInfoData = data
      // this.firmwareInfo = this.firmwareInfoData.slice(0, this.pageNum)
      getFirmwareNormalinfo()
        .then(res => {
          //给每一个number加上一个ID
          for (let i = 0; i < res.data.length; i++) {
            res.data[i].id = i + 1
            res.data[i].type = 'force'
            res.data[i].time = ''
            res.data[i].state = false
            res.data[i].wifiFirmwareVersion = transitionWifiFirmwareVersion(res.data[i].wifiFirmwareVersion)
          }
          this.firmwareInfoData = res.data
          this.firmwareInfo = this.firmwareInfoData.slice(0, this.pageNum)
        })
        .catch(res => {
          console.log(res);
        })
    },
    data() {
      return {
        search: '',//搜索
        firmwareData: '',//固件的base64数据
        firmwareInfo: [],//固件的信息
        //批量选择
        multipleSelection: [],//保存的批量数据
        isIndeterminate: false,
        checkAll: false,
        allType: 'force',//批量升级模式
        allTime: '',//批量定时升级时间
        lastTime1: 0,
        lastTime2: 0,
        /*分页数据*/
        pageNum: 10,
        currentPage: 1,
        firmwareInfoData: [],//分页总信息
        isCustom: false,//是否显示自定义列
        customList: [
          {name: '打印机编号', state: true, value: 'number'},
          {name: '版本号', state: true, value: 'wifiFirmwareVersion'},
          {name: 'IP', state: true, value: 'ip'},
          {name: '操作', state: true, value: 'handle'},
          {name: '升级模式', state: true, value: 'pattern'},
        ],
        custom: {
          number: true,
          ip: true,
          handle: true,
          pattern: true,
          wifiFirmwareVersion: true,
        }
      }
    },
    methods: {
      request(e, row, type) {
        const files = e.target.files[0];
        const reg = /(.ota|.bin)$/
        if (!reg.test(files.name)) {
          this.$message({
            type: 'error',
            message: '文件类型有误',
            duration: 3000,
            showClose: true
          })
          return
        }
        if (type != 'all') {
          this.firmwareInfo[row.id - 1].firmwareName = files.name
        }

        let reader = new FileReader()
        const that = this;
        reader.onload = function (e) {
          let result = e.target.result.split(',')
          if (type != 'all') {
            //单个升级
            that.handleFinder(row, result[1])
          } else {
            that.batchUpgradeFirmware(result[1])
          }
        }
        reader.readAsDataURL(files);
      },

      //单个升级
      handleFinder(row, result) {

        let data = {
          number: row.number,
          data: result,
          type: row.type
        }

        if (row.type === 'wecut') {
          data.timeStr = row.time
          updateFirmware(data)
            .then(res => {
              this.$message({
                type: 'success',
                message: '定时升级固件任务建立成功',
                duration: 3000,
                showClose: true
              })
            })
            .catch(res => {
              this.$message({
                type: 'error',
                message: res.data,
                duration: 3000,
                showClose: true
              })
            })
        } else {
          updateFirmware(data)
            .then(res => {
              this.$message({
                type: 'success',
                message: '固件正在升级',
                duration: 3000,
                showClose: true
              })
            })
            .catch(res => {
              this.$message({
                type: 'error',
                message: res.data,
                duration: 3000,
                showClose: true
              })
            })
        }

      },

      //获取多选的内容
      oneSelect(index, state) {
        if (state) {
          this.firmwareInfo[index].state = true
          this.multipleSelection.push(this.firmwareInfo[index])
          this.checkAll = this.multipleSelection.length === this.firmwareInfo.length;
          this.isIndeterminate = this.multipleSelection.length < this.firmwareInfo.length&&this.multipleSelection.length!=0;
        } else {
          const number = this.firmwareInfo[index].number
          for (let i = 0; i < this.multipleSelection.length; i++) {
            if (number === this.multipleSelection[i].number) {
              this.multipleSelection.splice(i, 1)
            }
          }
          this.isIndeterminate = this.multipleSelection.length < this.firmwareInfo.length&&this.multipleSelection.length!=0;
          this.checkAll = this.multipleSelection.length === 0;
        }
      },

      handleCheckAllChange(val) {
        if (val) {
          for (let i = 0; i < this.firmwareInfo.length; i++) {
            this.firmwareInfo[i].state = true
          }
          this.multipleSelection = []
          this.multipleSelection = [...this.firmwareInfo]
          this.isIndeterminate = false;
        } else {
          for (let i = 0; i < this.firmwareInfo.length; i++) {
            this.firmwareInfo[i].state = false
          }
          this.multipleSelection = []
          this.isIndeterminate = false;
        }

      },


      //批量升级
      batchUpgradeFirmware(result) {
        const firmwareList = this.multipleSelection
        if (firmwareList.length > 0) {
          if (this.allType === 'wecut') {//判断是不是定时模式
            for (let i = 0; i < firmwareList.length; i++) {
              let data = {
                number: firmwareList[i].number,
                data: result,
                type: this.allType,
                timeStr: this.allTime,//由于是定时模式就添加allTime字段
              }
              updateFirmware(data)//发送升级固件请求
                .then(res => {
                  this.$message({
                    type: 'success',
                    message: '批量定时升级固件任务建立成功',
                    duration: 3000,
                    showClose: true
                  })
                })
                .catch(res => {
                  this.$message({
                    type: 'error',
                    message: data.number + res.data,
                    duration: 3000,
                    showClose: true
                  })
                })
            }
          } else {
            for (let i = 0; i < firmwareList.length; i++) {
              let data = {//如果不是定时模式就不用增加timeStr自动
                number: firmwareList[i].number,
                data: result,
                type: this.allType,
              }
              updateFirmware(data)//发送升级固件请求
                .then(res => {
                  this.$message({
                    type: 'success',
                    message: '批量升级开始',
                    duration: 3000,
                    showClose: true
                  })
                })
                .catch(res => {
                  this.$message({
                    type: 'error',
                    message: data.number + res.data,
                    duration: 3000,
                    showClose: true
                  })
                })
            }
          }
        } else {
          this.$message({
            type: 'error',
            message: '请选择要升级的打印机',
            duration: 3000,
            showClose: true
          })
        }


      },

      setTime(index, row) {
        if (row.type !== 'wecut') {
          this.firmwareInfo[index].time = ''
        }

      },

      timeOut(lastTimeName) {
        const nowTime = Date.now()
        if (nowTime - this.lastTime1 < 2000) {
          console.log(1);
          this[lastTimeName] = nowTime
          return false
        } else {
          this[lastTimeName] = nowTime
          return true
        }
      },

      //分页
      handleChange(val) {
        this.firmwareInfo = this.firmwareInfoData.slice(0, val)
      },
      handleCurrentChange(val) {
        this.multipleSelection = []
        this.checkAll = false
        for(let i =0;i<this.firmwareInfo.length;i++){
          this.firmwareInfo[i].state = false
        }
        let last = this.pageNum * val;
        let first = last - this.pageNum;
        this.firmwareInfo = []
        this.firmwareInfo = this.firmwareInfoData.slice(first, last)
      },

      defaultFun(data) {
        this.custom = {}
        for (let item of data) {
          this.custom[item.value] = item.state
        }
      },
      confirmFun(data) {
        this.custom = {}
        for (let item of data) {
          this.custom[item.value] = item.state
        }
        this.customList = data
      },
      closeCustom(data) {
        this.customList = []
        this.customList = data
      }
    },

    components: {MyPopover}
  }
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
    width: 1200px;
    height: 700px;
  }

  .title {
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

  .btn {
    display: block;
    margin: 0;
    height: 30px;
    line-height: 30px;
    background: rgba(64, 158, 255, 1);
    border-radius: 4px;
    white-space: nowrap;
    text-align: center;
    box-sizing: border-box;
    outline: 0;
    transition: .1s;
    font-weight: 500;
    -moz-user-select: none;
    color: #FFF;
    border-color: #409EFF;
    font-size: 14px;
    cursor: pointer;
  }

  .one-btn {
    width: 60px;
  }

  .all-btn {
    margin-left: 10px;
    margin-right: 22px;
    width: 80px;
  }

  .btn:hover {
    background: #66b1ff;
    border-color: #66b1ff;
    color: #FFF;
  }

  .pagination {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-top: 10px;
  }

  .question {
    display: inline-block;
    margin-left: 10px;
    width: 12px;
    height: 12px;
    background: url("../../assets/问号1.png") no-repeat;
    background-size: 100% 100%;
  }

  .on-question {
    display: inline-block;
    margin-left: 10px;
    width: 12px;
    height: 12px;
    background: url("../../assets/问号2.png") no-repeat;
    background-size: 100% 100%;
  }

  @media (max-width: 1200px) {
    .box {
      width: 90%;
    }
  }
</style>
