<template>
  <div style="position: relative;">
    <div class="left" :class="{oldLeft:!fade}">
      <div class="title">
        <span>白名单</span>
        <i class="el-icon-d-arrow-left left-icon" @click="shrink" title="收起白名单"></i>
      </div>
      <el-tabs v-model="activeName" type="card" stretch>
        <el-tab-pane label="IP" name="ip">
          <el-table :data="ipDataPage" style="width: 100%;min-height: 618px;" v-show="fadeTable" height="618">
            <el-table-column fixed prop="id" label="序号" width="60">
            </el-table-column>
            <el-table-column fixed prop="list" label="IP" width="140">
            </el-table-column>
            <el-table-column fixed="right" label="操作" width="60">
              <template slot-scope="scope">
                <el-button @click.native.prevent="deleteRow(scope.$index, newIp)"
                           type="text"
                           size="small">
                  删除
                </el-button>
              </template>
            </el-table-column>
          </el-table>
          <div class="pagination">
            <el-pagination
              @handleChange="ipHandleChange"
              @current-change="ipHandleCurrentChange"
              :current-page.sync="ipCurrentPage"
              :page-size="pageNum"
              layout="prev, pager, next, jumper"
              :total="ipData.length">
            </el-pagination>
          </div>
        </el-tab-pane>

        <el-tab-pane label="Number" name="number">
          <el-table :data="newNumber" style="width: 100%;min-height: 618px;" v-show="fadeTable" height="618">
            <el-table-column fixed prop="list" label="Number" width="200">
            </el-table-column>
            <el-table-column fixed="right" label="操作" width="80">
              <template slot-scope="scope">
                <el-button @click.native.prevent="deleteRow(scope.$index, newNumber)"
                           type="text"
                           size="small">
                  删除
                </el-button>
              </template>
            </el-table-column>
          </el-table>
          <div class="pagination">
            <!--<el-pagination
              @handleChange="handleChange"
              @current-change="handleCurrentChange"
              :current-page.sync="numCurrentPage"
              :page-size="pageNum"
              layout="prev, pager, next, jumper"
              :total="number.length">
            </el-pagination>-->
          </div>
        </el-tab-pane>
      </el-tabs>
    </div>

    <div v-show="!fade" class="minleft">
      <i class="el-icon-d-arrow-right right-icon" @click="shrink" title="展开白名单"></i>
    </div>
  </div>

</template>

<script>
  import {mapGetters, mapState} from 'vuex'

  import {del,getAll} from '../../api'

  export default {
    name: "Left",
    mounted(){
      // this.$store.dispatch('')
      this.ipData = this.whiteList.ip
      console.log(this.ip);
      this.ipDataPage = this.ipData.slice(0, this.pageNum)
    },
    data() {
      return {
        activeName: 'ip',
        fade: true,
        fadeTable: true,

        ipData: [],//总打印记录
        ipDataPage: [],//分页展示数据
        ipCurrentPage: 1,
        numCurrentPage: 1,
        pageNum: 10,
      }
    },
    methods: {
      deleteRow(index, rows) {
        del(rows[index])
          .then(res => {
            if (res.code == 0) {
              this.$message({
                message: res.data,
                type: 'error'
              });
              rows.splice(index, 1);
            }
          })
          .catch(res => {
            console.log(res);
          })
      },
      shrink() {
        if (this.fade) {
          this.fade = !this.fade
          this.fadeTable = !this.fadeTable
        } else {
          this.fade = !this.fade
          setTimeout(() => {
            this.fadeTable = !this.fadeTable
          }, 190)
        }

      },

      //ip分页数据
      //分页
      ipHandleChange(val) {
        console.log(123);
        this.ipDataPage = this.ipData.slice(0, val)
      },
      ipHandleCurrentChange(val) {
        let last = this.pageNum * val;
        let first = last - this.pageNum;
        this.ipDataPage = []
        this.ipDataPage = this.ipData.slice(first, last)
      }
    },
    computed: {
      ...mapState(['whiteList']),
      ...mapGetters(['ip', 'number']),
      // newIp() {
      //   try {
      //     this.ipData = this.ip
      //     this.ipDataPage = this.ip.slice(0, this.pageNum)
      //     return ''
      //   } catch (e) {
      //
      //   }
      // },
      newNumber() {
        return this.number

      }
    },
    watch:{
      ipData(){

      }
    }
  }
</script>

<style scoped>
  .left {
    width: 300px;
    min-height: 800px;
    border-right: 1px solid #ddd;
    opacity: 1;
    transition: .3s;
  }

  .oldLeft {
    width: 0;
    border: none;
    opacity: 0;
  }

  .minleft {
    position: absolute;
    left: 0;
    top: 0;
    width: 50px;
    min-height: 800px;
    text-align: center;
    border-right: 1px solid #ddd;
    background-color: #2196f3;
    transition: .3s;
  }

  .right-icon {
    margin-top: 8px;
    font-size: 24px;
    color: white;
    cursor: pointer;
  }

  .title {
    display: flex;
    justify-content: space-around;
    width: 100%;
    height: 50px;
    line-height: 50px;
    color: white;
    font-size: 18px;
    border-bottom: 1px solid #ffffff;
    background-color: #2196f3;
  }

  .left-icon {
    line-height: 49px;
    cursor: pointer;
    margin-left: 180px
  }

</style>
