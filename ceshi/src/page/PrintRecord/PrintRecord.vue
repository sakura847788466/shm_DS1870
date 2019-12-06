<template>
  <div class="right">
    <div class="box">
      <div class="title" v-if="tab">
        <span>打印记录</span>
        <el-input style="width: 250px;height: 100%;" v-model="search" placeholder="请输入number号搜索"
                  suffix-icon="el-icon-search"/>
      </div>
      <div class="title" v-else>
        <div style="display: flex;align-items: center">
          <span style="margin-right: 40px">打印记录</span>
          <MyPopover :custom-list="customList" :defaultFun="defaultFun" :confirmFun="confirmFun"/>
        </div>

        <el-button type="danger" @click="back" style="height: 32px;width: 60px;padding: 0">返回</el-button>
      </div>
      <div class="body">
        <el-table v-show="tab" style="width: 100%;height: 578px;color: #999;font-size: 16px"
                  :header-row-style="{color:'#666;'}" max-height="578" row-class-name="table-row"
                  :data="printDataNumber.filter(data => !this.search || data.number.toLowerCase().includes(this.search.toLowerCase()))">
          <el-table-column label="序号" prop="id" width="210"/>
          <el-table-column label="打印机编号" prop="number" width="210"/>
          <el-table-column label="打印总数" prop="allCount" align="center"/>
          <el-table-column label="操作" align="center" width="140">
            <template slot-scope="scope">
              <el-button type="primary" :loading="scope.row.loading" size="small" @click="handleFinder(scope.row)">
                查看更多
              </el-button>
            </template>
          </el-table-column>
        </el-table>
        <div v-show="tab" class="pagination">
          <el-pagination @handleChange="handleChange" @current-change="handleCurrentChange"
                         :current-page.sync="currentPage"
                         :page-size="pageNum" layout="prev, pager, next, jumper" :total="printData.length"/>
          <span style="margin-left: 18px">每页显示行数：</span>
          <el-input-number v-model="pageNum" size="mini" @change="handleChange" :min="1" label="描述文字"
                           style="width: 110px"/>
        </div>
        <div v-show="!tab">
          <div style="" class="date-nav">
            <p>当前打印机：{{printNumber}}</p>
            <el-date-picker
              v-model="printDate" :editable="false"
              type="daterange" @change="selectPrintData"
              range-separator="至" value-format="yyyyMMdd"
              start-placeholder="开始日期"
              end-placeholder="结束日期"/>
          </div>
          <el-table show-summary
                    :data="numberData"
                    max-height="525" style="width: 100%">
            <el-table-column prop="date" label="日期" />
            <el-table-column align="center" prop="failureCount" label="打印失败次数" v-if="custom.failureCount"/>
            <el-table-column align="center" prop="successCount" label="打印成功次数" v-if="custom.successCount"/>
            <el-table-column align="center" label="打印总次数" prop="total" v-if="custom.allCount"/>
          </el-table>
        </div>
      </div>

    </div>
  </div>
</template>

<script>
  import {getAllcount, getNumcount} from "../../api/index";
  import {formatDate} from "../../util/tool";
  import {searchPrintData} from "../../api";
  import MyPopover from "../../components/MyPopover/MyPopover";

  export default {
    name: "PrintRecord",
    components: {MyPopover},
    mounted() {
      getAllcount()
        .then(res => {
          for (let i = 0; i < res.data.length; i++) {
            this.printData.push({id: i + 1, number: res.data[i].number, allCount: res.data[i].allCount, loading: false})
          }
          /* this.printData.push(...this.printData,...this.printData,
             {allCount:9,
               id:1,
               loading:false,
               number:"007BBE7350027B00"
             },
             {allCount:9,
               id:1,
               loading:false,
               number:"007BBE7350027B00"
             },
           )*/
          this.printDataNumber = this.printData.slice(0, this.pageNum)

        })
        .catch(res => {
          console.log(res);
        })
    },
    data() {
      return {
        printData: [],//总打印记录
        printDataNumber: [],//分页展示数据
        currentPage: 1,
        pageNum: 10,
        numberData: [],//根据number查找的单条打印机记录
        backNumberData: [],//备份number的打印记录
        search: '',//搜索字段
        printNumber: '',//点击查看更多的打印机number
        loading: false,//是否显示按钮的加载
        tab: true,//切换显示总的记录或显示子记录
        printDate: '',
        customList: [
          {name: '失败次数', state: true, value: 'failureCount'},
          {name: '成功次数', state: true, value: 'successCount'},
          {name: '总次数', state: true, value: 'allCount'},
        ],
        custom: {
          successCount: true,
          failureCount: true,
          allCount: true,
        }
      }
    },
    methods: {
      myMessage(type, msg, duration = 3000) {
        this.$message({
          message: msg,
          type,
          duration,
          showClose: true,
          offset: 54,
        });
      },

      async handleFinder(row) {
        this.printDataNumber[row.id - 1].loading = true
        let result = await getNumcount(row.number)
        if (result.code == 0) {
          /* const data = [
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},
             {date: '20190904', failureCount: 1, successCount: 20},

           ]*/
          result.data.forEach(item => {
            item.total = item.failureCount + item.successCount//设置打印的每天总数
            formatDate(item.date).then(res => {
              item.date = res
            })
          })
          this.numberData = result.data
          this.backNumberData = result.data
          // this.numberData.reverse()//反转数据
          this.printNumber = row.number
          setTimeout(() => {
            this.tab = false
            this.printDataNumber[row.id - 1].loading = false
          }, 300)
        } else {
          this.myMessage('error', '打印记录读取失败')
        }
      },
      back() {
        this.tab = true
        this.printDate = null
        this.printDateOne = ''
      },

      //分页
      handleChange(val) {
        this.printDataNumber = this.printData.slice(0, val)
      },
      handleCurrentChange(val) {
        let last = this.pageNum * val;
        let first = last - this.pageNum;
        this.printDataNumber = []
        this.printDataNumber = this.printData.slice(first, last)
        this.search = ''//点击另一页清空搜索内容
      },

      //日期区间选择展示的日期
      async selectPrintData(val) {
        if (val == null) {
          this.numberData = []
          this.numberData = this.backNumberData
          return
        }
        const data = {
          number: this.printNumber,
          startdate: this.printDate[0],//开始日期
          enddate: this.printDate[1],//结束日期
        }
        searchPrintData(data)
          .then(res => {
            for (let item of res.data) {
              item.total = item.failureCount + item.successCount//设置打印的每天总数
              formatDate(item.date).then(res => {
                item.date = res
              })
            }
            this.numberData = res.data
          })
          .catch(res => {
            this.numberData = []
            this.myMessage('error', '当前日期区间没有打印记录')
          })
        // console.log(this.printDate)
      },

      //自定义显示列
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
      }
    }
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
    width: 905px;
    height: 750px;
  }

  .title {
    position: relative;
    box-sizing: content-box;
    display: flex;
    justify-content: space-between;
    align-items: center;
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
    margin-top: 12px;
  }

  .date-nav {
    display: flex;
    justify-content: space-between;
    align-items: center;
    height: 55px;
    font-size: 16px;
    color: #666;
    border-bottom: 1px solid rgba(231, 231, 231, 1);
  }

  @media (max-width: 1200px) {
    .box {
      width: 90%;
    }
  }
</style>
