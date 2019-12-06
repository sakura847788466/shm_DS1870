<template>
  <div class="content">

    <div class="right"
         :style="fade?'':'margin:0 auto;'">
      <!---->

      <div class="title">
        <div style="display:flex;justify-content: space-between;
    align-items: center;flex:1;">
          <span class="title-text"
                style="flex:2;display: inline-block;
    height: 50px;
    width: 80px;">白名单</span>
          <el-switch v-model="info.whitelistswitch"
                     active-value="true"
                     inactive-value="false"
                     @change="onWhiteList"
                     style="margin-left: 14px;flex:1;" />
        </div>
        <div style="display:flex;">
          <div class="my-radio-box">
            <el-radio v-model="radio"
                      label="IP"
                      style="margin-right:10px">IP
            </el-radio>
            <el-radio v-model="radio"
                      label="Number"
                      style="margin: 0">Number
            </el-radio>
          </div>
          <MyPopover :custom-list="customList"
                     v-if="radio=='IP'"
                     @defaultFun="defaultFun"
                     @confirmFun="confirmFun"
                     @closeCustom="closeCustom"
                     style="margin: 0 20px 0 0;" />
          <MyPopover :custom-list="customListT"
                     v-else
                     @defaultFun="defaultFun"
                     @confirmFun="confirmFun"
                     @closeCustom="closeCustom"
                     style="margin: 0 20px 0 0;" />
          <el-input placeholder="请输入内容"
                    v-model.trim="search"
                    type="text"
                    maxlength="20"
                    class="search"
                    style="display:flex;">
            <el-button slot="append"
                       icon="el-icon-search"
                       @click="goToSearch"
                       style="justify-content: center;align-items: center;display: flex;line-height: 40px;margin-left: -20px;margin-top: 0px; width: 40px;"></el-button>
          </el-input>
        </div>
      </div>
      <div class="body"
           v-if="radio=='IP'">
        <el-table :data="ipDataPage"
                  style="width: 100%;min-height: 481px;"
                  @selection-change="handleSelectionChange"
                  max-height="518"
                  empty-text="IP数据为空，请添加数据">
          <el-table-column type="selection"
                           width="55" />
          <el-table-column prop="id"
                           label="序号" />
          <el-table-column prop="list"
                           label="IP"
                           v-if="custom.ip" />
          <el-table-column prop="main"
                           label="状态"
                           width="120"
                           align="center"
                           v-if="false" />
          <el-table-column label="操作"
                           width="80"
                           align="center"
                           v-if="custom.handle">
            <template slot-scope="scope">
              <el-button @click.native.prevent="deleteRow(scope.row)"
                         type="danger"
                         size="mini">
                删 除
              </el-button>
            </template>
          </el-table-column>
        </el-table>
        <div class="pagination">
          <el-button type="primary"
                     size="small"
                     @click="derive">批量导出
          </el-button>
          <el-pagination small
                         :pager-count="pagerCount"
                         :hide-on-single-page="true"
                         style="display:flex;flex-wrap: wrap;justify-content: center"
                         @current-change="ipHandleCurrentChange"
                         :current-page.sync="ipCurrentPage"
                         :page-size="pageNum"
                         layout="total,prev, pager, next,jumper"
                         :total="ipData.length">
          </el-pagination>
        </div>
      </div>
      <div class="body"
           v-else>
        <el-table :data="numDataPage"
                  style="width: 100%;min-height: 481px;"
                  @selection-change="handleSelectionChange"
                  max-height="518"
                  empty-text="Number数据为空，请添加数据">
          <el-table-column type="selection"
                           width="55" />
          <el-table-column prop="id"
                           label="序号"
                           width="55" />
          <el-table-column prop="list"
                           label="number"
                           align="center"
                           v-if="customs.number" />
          <el-table-column prop="main"
                           label="状态"
                           width="120"
                           align="center"
                           v-if="customs.state" />
          <el-table-column label="操作"
                           width="80"
                           align="center"
                           v-if="customs.handle">
            <template slot-scope="scope">
              <el-button @click.native.prevent="deleteRow(scope.row)"
                         type="danger"
                         size="mini">
                删 除
              </el-button>
            </template>
          </el-table-column>
        </el-table>
        <div class="pagination">
          <el-button type="primary"
                     size="small"
                     @click="derive">批量导出
          </el-button>
          <el-pagination small
                         :pager-count="pagerCount"
                         :hide-on-single-page="true"
                         style="display:flex;flex-wrap: wrap;justify-content: center"
                         @current-change="numHandleCurrentChange"
                         :current-page.sync="numCurrentPage"
                         :page-size="pageNum"
                         layout="total,prev, pager, next,jumper"
                         :total="numData.length">
          </el-pagination>
        </div>
      </div>
    </div>
    <div style="position: relative;z-index: 2">
      <div class="left"
           :class="{oldLeft:!fade}">
        <div class="left-title">
          <span>添加白名单</span>
          <!-- <el-switch v-model="info.whitelistswitch"
                     active-value="true"
                     inactive-value="false"
                     @change="onWhiteList"
                     style="margin-left: 26px;margin-top: 3px" /> -->
        </div>
        <div style="display: flex;flex-direction: column;align-items: center;font-size: 16px;color: #666;">
          <!-- <el-input placeholder="请输入内容"
                    v-model="search"
                    type="text"
                    maxlength="20"
                    style="margin-top: 38px;width: 320px">
            <el-button slot="append"
                       icon="el-icon-search"
                       @click="goToSearch"></el-button>
          </el-input> -->
          <div style="margin-top: 35px;">
            <span style="margin-right: 30px">type:</span>
            <el-radio v-model="activeName"
                      label="ip">I P
            </el-radio>
            <el-radio v-model="activeName"
                      label="number">Number
            </el-radio>
          </div>
          <div style="display: flex;align-items:center; margin-top: 26px;"
               v-if="activeName=='number'">
            <span>Number：</span>
            <el-input type="text"
                      placeholder="请输入number"
                      style="width: 240px"
                      v-model="number"
                      maxlength="16"
                      show-word-limit />
          </div>
          <div style="display: flex;align-items:center;margin-top: 36px;"
               v-else>
            <span>IP：</span>
            <div style="display: flex;align-items:flex-end ;margin-left: 10px;text-align: center">
              <input type="text"
                     class="ip"
                     v-model.number="ip1"
                     maxlength="3"><span class="ip_point">.</span>
              <input type="text"
                     class="ip"
                     v-model.number="ip2"
                     maxlength="3"><span class="ip_point">.</span>
              <input type="text"
                     class="ip"
                     v-model.number="ip3"
                     maxlength="3"><span class="ip_point">.</span>
              <input type="text"
                     class="ip"
                     v-model.number="ip4"
                     maxlength="3">
            </div>
            <div class="ipAdd"
                 style="margin-left:5px;">
              <i class="el-icon-circle-plus"
                 style="color:#409EFF;cursor:pointer;"
                 @click="dialogVisible = true"></i>
            </div>
          </div>

          <el-button type="primary"
                     style="width: 200px;height: 40px;border-radius:20px;margin-top: 42px"
                     @click="submit">提 交
          </el-button>

          <div style="display: flex;align-items: center;justify-content: center;margin-top: 20px">
            <input id="file"
                   type="file"
                   style="display: none;"
                   accept=" application/vnd.openxmlformats-officedocument.spreadsheetml.sheet, application/vnd.ms-excel"
                   @change="request($event)" />
            <label for="file"
                   class="btn"
                   title="请导入xls或xlsx文件">
              批量导入
            </label>
            <el-popover placement="right"
                        width="200"
                        trigger="hover"
                        popper-class="popover"
                        content="请导入xls或xlsx文件，表格的第一行第一列填入list，然后把number和IP写在list下面">
              <img slot="reference"
                   src="./img/question.png"
                   style="margin-left: 20px;width: 19px;height: 19px;background-size: 100% 100%; cursor: pointer;" />
            </el-popover>
          </div>
          <el-button type="primary"
                     style="margin-top: 20px; width: 200px;height: 40px;border-radius:20px;"
                     @click="allDerive">全部导出
          </el-button>
          <a id="downlink"></a>
        </div>

      </div>
      <!--<span class="chunk offChunk" v-show="!fade" @click="shrink" title="展开白名单"></span>-->
    </div>
    <el-dialog title="IP添加"
               :visible.sync="dialogVisible"
               width="450px"
               :before-close="handleClose"
               :close-on-click-modal="false">
      <div class="content_ip"
           style="height:400px; ">
        <div class="ip_top"></div>
        <div class="ip_bottom"
             :style="ipAll.length > 6 ?'overflow-y:scroll;overflow-x: hidden;table-layout: fixed;word-wrap: break-word;word-break: break-all;border-bottom: 1px solid #f4f4f4;':''">
          <div class="ip-item"
               v-for="(item,index) in ipAll"
               :key="index"
               :value="index">
            <div class="ip_left">IP:</div>
            <div class="container_bl"
                 :style="ipAll.length>6?'flex:6;':''">
              <el-input v-model.trim="item.ipO"
                        @input="inputHandle1(item.ipO,index)"
                        v-bind:disabled="disabledInput"
                        maxlength="3"></el-input>
              <span class="ip_point">.</span>
              <el-input v-model.trim="item.ipT"
                        @input="inputHandle2(item.ipT,index)"
                        v-bind:disabled="disabledInputT"
                        maxlength="3"></el-input>
              <span class="ip_point">.</span>
              <el-input v-model.trim="item.ipTh"
                        @input="inputHandle3(item.ipTh,index)"
                        v-bind:disabled="disabledInputTh"
                        maxlength="3"></el-input>
              <span class="ip_point">.</span>
              <el-input v-model.trim="item.ipF"
                        @input="inputHandle4(item.ipF,index)"
                        maxlength="3"></el-input>
              <!--- ipF----->
            </div>
            <div class='anJian'>
              <div class="add"
                   @click="clickAdd">
                <i class="el-icon-circle-plus"></i>
              </div>
              <div :class="index == 0?'jian-hidden':'jian'"
                   @click="clickMin(index)"
                   ref="jian">
                <i class="el-icon-remove"></i>
              </div>
            </div>
          </div>
          <div :class="ipAll.length == 0?'hide':'lock'"
               @click="lock">
            <i :class="lockStatus == true?'el-icon-lock':'el-icon-unlock'"
               :style="lockStatus?'color:#409eff;':''"></i>
          </div>
          <div :class="ipAll.length == 0?'hide':'lockT'"
               @click="lockT">
            <i :class="lockStatusT == true?'el-icon-lock':'el-icon-unlock'"
               :style="lockStatusT?'color:#409eff;':''"></i>
          </div>
          <div :class="ipAll.length == 0?'hide':'lockTh'"
               @click="lockTh">
            <i :class="lockStatusTh == true?'el-icon-lock':'el-icon-unlock'"
               :style="lockStatusTh?'color:#409eff;':''"></i>
          </div>
          <div :class="ipAll.length == 0?'hide':'lockF'">
            <i class='el-icon-unlock'></i>
          </div>
        </div>
      </div>
      <span slot="footer"
            class="dialog-footer">
        <el-button @click="close">取 消</el-button>
        <el-button type="primary"
                   @click="addIP">提交</el-button>
      </span>
    </el-dialog>
  </div>

</template>

<script>
import { mapActions } from 'vuex'
import XLSX from 'xlsx'
import { add, del, getAll, getSearch, delAll, getConfig, setConfig } from '../../api/'
import { verificationIp, verificationNumber } from '../../util/tool'
import MyPopover from '../../components/MyPopover/MyPopover'// 自定义列组件


export default {
  name: "WhiteList",
  mounted () {
    this.outFile = document.getElementById('downlink')
    getAll()
      .then(res => {
        this.ipData = []
        this.ipDataPage = []
        for (let i = 0; i < res.ip.length; i++) {
          this.ipData.push({
            id: i + 1,
            list: res.ip[i],
            type: 'ip'
          })
        }
        this.ipDataPage = this.ipData.slice(0, this.pageNum)

        this.numData = []
        this.numDataPage = []
        for (let i = 0; i < res.number.length; i++) {
          this.numData.push({
            id: i + 1,
            list: res.number[i].number,
            main: res.number[i].main,
            type: 'number'
          })
        }
        this.numDataPage = this.numData.slice(0, this.pageNum)

      })

    getConfig()
      .then(res => {
        this.info = res.data;
      })
      .catch(res => {
        console.log(res);
      });

  },
  data () {
    return {
      /*左边*/
      activeName: 'ip',
      fade: true,
      outFile: '',  // 导出文件el
      multipleSelection: [],//选择批量的数据
      ipData: [],//ip总打印记录
      ipDataPage: [],//ip分页展示数据
      numData: [],//num总打印记录
      numDataPage: [],//num分页展示数据
      ipCurrentPage: 1,
      numCurrentPage: 1,
      pageNum: 10,
      pagerCount: 5,

      /*右边*/
      ip1: null,
      ip2: null,
      ip3: null,
      ip4: null,
      radio: 'IP',
      number: '',
      lastTime: 0,
      importDataInfo: {
        allList: [],
        errorList: [],
        successList: {
          ip: [],
          number: []
        }
      },//批量添加数据
      delDataInfo: {
        allList: [],
        errorList: [],
        successList: {
          ip: [],
          number: []
        }
      },//批量删除数据
      search: '',//搜索
      searchLastTime: 0,
      value: '',
      info: {},//白名单开关
      dialogVisible: false,
      input: '',
      lockStatus: false,
      lockStatusT: false,
      lockStatusTh: false,
      disabledInput: false,
      disabledInputT: false,
      disabledInputTh: false,
      ipAll: [{
        ipO: '',
        ipT: '',
        ipTh: '',
        ipF: '',

      }],//ip对象集合
      customList: [
        { name: 'ip', state: true, value: 'ip' },
        { name: '操作', state: true, value: 'handle' },
      ],
      customListT: [
        { name: 'number', state: true, value: 'number' },
        { name: '状态', state: true, value: 'state' },
        { name: '操作', state: true, value: 'handle' },
      ],
      custom: {
        handle: true,
        other: true,
        ip: true,
      },
      customs: {
        number: true,
        state: true,
        handle: true,
        other: true,
      },
      //自定义列
    }
  },
  methods: {
    ...mapActions(['getWhiteList']),
    myMessage (type, msg, duration = 3000) {
      this.$message({
        message: msg,
        type,
        duration,
        showClose: true,
        offset: 54,
      });
    },

    /*close*/
    handleClose (done) {
      this.$confirm('确认关闭？')
        .then(_ => {
          done();
          this.ipAll = [{ ipO: '', ipT: '', ipTh: '', ipF: '' }];
          this.lockStatus = false;
          this.lockStatusT = false;
          this.lockStatusTh = false;
          this.disabledInput = false;
          this.disabledInputT = false;
          this.disabledInputTh = false;
        })
        .catch(_ => {
        });
    },
    close () {
      // 取消
      this.ipAll = [{ ipO: '', ipT: '', ipTh: '', ipF: '' }];
      this.dialogVisible = false;
      this.lockStatus = false;
      this.lockStatusT = false;
      this.lockStatusTh = false;
      this.disabledInput = false;
      this.disabledInputT = false;
      this.disabledInputTh = false;
    },


    /*锁/解锁 */
    lock () {
      if (this.lockStatus == true) {
        // console.log("第一个lock_false解锁")
        this.lockStatus = !this.lockStatus;
        this.disabledInput = !this.disabledInput;
      } else {
        // console.log("第一个lock_true上锁")
        this.lockStatus = !this.lockStatus;
        this.disabledInput = !this.disabledInput;

      }
    },
    lockT () {
      if (this.lockStatusT == true) {
        // console.log("第二个lock_false解锁")
        this.lockStatusT = !this.lockStatusT;
        this.disabledInputT = !this.disabledInputT;
      } else {
        // console.log("第二个lock_true上锁")
        this.lockStatusT = !this.lockStatusT;
        this.disabledInputT = !this.disabledInputT;

      }
    },
    lockTh () {
      if (this.lockStatusTh == true) {
        // console.log("第三个lock_false解锁")
        this.lockStatusTh = !this.lockStatusTh;
        this.disabledInputTh = !this.disabledInputTh;
      } else {
        // console.log("第三个lock_true上锁")
        this.lockStatusTh = !this.lockStatusTh;
        this.disabledInputTh = !this.disabledInputTh;

      }
    },

    /*添加ip */
    addIP () {//单个数据，多个数据需要进行遍历 提交
      /*多个添加遍历数组 */
      var neIP = [];
      var ipAll = this.ipAll;
      for (var i = 0; i < ipAll.length; i++) {
        const nIP = ipAll[i].ipO + '.' + ipAll[i].ipT + '.' + ipAll[i].ipTh + '.' + ipAll[i].ipF;
        // console.log(nIP)
        if (ipAll[i].ipO == '' || ipAll[i].ipT == '' || ipAll[i].ipTh == '' || ipAll[i].ipF == '') {
          this.myMessage('warning', 'ip不能为空')
          return false;
        } else {
          neIP.push(nIP)
          const data = {
            list: neIP,
            type: this.activeName
          }
          console.log(data)
          add(data).then(res => {
            console.log(res)
            this.disabledInput1 = true;
            this.classStatus = true;
            // this.ipAll = " ";//清空
            this.ipAll = [{ ipO: '', ipT: '', ipTh: '', ipF: '' }];//保留一个空数组
            getAll().then(res => {
              console.log(res)
              this.myMessage('success', '添加成功')
              this.ipData = []
              this.ipDataPage = []
              for (let i = 0; i < res.ip.length; i++) {
                this.ipData.push({
                  id: i + 1,
                  list: res.ip[i],
                  type: 'ip'
                })
              }
              this.ipDataPage = this.ipData.slice(0, this.pageNum)

              this.numData = []
              this.numDataPage = []
              for (let i = 0; i < res.number.length; i++) {
                this.numData.push({
                  id: i + 1,
                  list: res.number[i].number,
                  main: res.number[i].main,
                  type: 'number'
                })
              }
              this.numDataPage = this.numData.slice(0, this.pageNum)

            }).catch(err => {
              console.log("导入失败")
            })
            this.dialogVisible = false;
          })
            .catch(err => {
              console.log(err)
            })
        }
      }

    },
    /*点击添加item*/
    clickAdd () {
      const twoIp = this.ipAll[0].ipT
      const firstIp = this.ipAll[0].ipO
      const thereIp = this.ipAll[0].ipTh
      if (this.lockStatus == true && this.lockStatusT == true && this.lockStatusTh == true) {
        const list = { ipO: firstIp, ipT: twoIp, ipTh: thereIp, ipF: '' }
        this.ipAll.push(list)
      }
      else if (this.lockStatus == true && this.lockStatusT == true) {//1-2

        const list = { ipO: firstIp, ipT: twoIp, ipTh: '', ipF: '' }
        this.ipAll.push(list)
      } else if (this.lockStatus == true && this.lockStatusTh == true) { //1-3

        const list = { ipO: firstIp, ipT: '', ipTh: thereIp, ipF: '' }
        this.ipAll.push(list)
      } else if (this.lockStatusT == true && this.lockStatusTh == true) { //1-3

        const list = { ipO: '', ipT: twoIp, ipTh: thereIp, ipF: '' }
        this.ipAll.push(list)
      } else if (this.lockStatus == true) {
        const list = { ipO: firstIp, ipT: '', ipTh: '', ipF: '' }
        this.ipAll.push(list)
      } else if (this.lockStatusT == true) {
        const list = { ipO: '', ipT: twoIp, ipTh: '', ipF: '' }
        this.ipAll.push(list)

      } else if (this.lockStatusTh == true) {
        const list = { ipO: '', ipT: '', ipTh: thereIp, ipF: '' }
        this.ipAll.push(list)
      }
      else {
        const list = { ipO: '', ipT: '', ipTh: '', ipF: '' }
        this.ipAll.push(list)
        return;
      }
    },
    /*点击减少 */
    clickMin (index) {
      if (index == 0) {
        //第一个不能点减少
        this.myMessage("fail", "最后一条语句不删改")
      } else {
        this.ipAll.splice(index, 1)
      }
    },
    //输入限制测试
    inputHandle1 (e, index) {
      const a = e.replace(/[^\d]/g, '');
      if (e > 255 || e < 0) {
        this.ipAll[index].ipO = 225;

      } else if (!a) {
        this.ipAll[index].ipO = ' '
      }
    },
    inputHandle2 (e, index) {
      const a = e.replace(/[^\d]/g, '');
      if (e > 255 || e < 0) {
        this.ipAll[index].ipT = 225;

      } else if (!a) {
        this.ipAll[index].ipT = ' '
      }
    },
    inputHandle3 (e, index) {
      const a = e.replace(/[^\d]/g, '');
      if (e > 255 || e < 0) {
        this.ipAll[index].ipTh = 225;

      } else if (!a) {
        this.ipAll[index].ipTh = ' '
      }
    },
    inputHandle4 (e, index) {
      const a = e.replace(/[^\d]/g, '');
      if (e > 255 || e < 0) {
        this.ipAll[index].ipF = 225;

      } else if (!a) {
        this.ipAll[index].ipF = ' '
      }
    },

    /*左边*/
    deleteRow (rows) {
      console.log(rows);
      const data = {
        list: rows.list,
        type: rows.type
      }
      del(data)
        .then(res => {
          if (res.code == 0) {
            this.myMessage('success', res.data)
            // rows.splice(index, 1);
            this.getAllWhite(rows.type)
          }
        })
        .catch(res => {
          this.myMessage('error', '删除失败')
        })
    },


    shrink () {
      if (this.fade) {
        this.fade = !this.fade
      } else {
        this.fade = !this.fade

      }
    },

    //分页
    handleSizeChange (val) {
      console.log(`每页 ${val} 条`);
    },
    ipHandleChange (val) {
      this.ipDataPage = this.ipData.slice(0, val)
    },
    ipHandleCurrentChange (val) {
      let last = this.pageNum * val;
      let first = last - this.pageNum;
      this.ipDataPage = []
      this.ipDataPage = this.ipData.slice(first, last)
    },
    //分页

    numHandleChange (val) {
      this.numDataPage = this.numData.slice(0, val)
    },
    numHandleCurrentChange (val) {
      let last = this.pageNum * val;
      let first = last - this.pageNum;
      this.numDataPage = []
      this.numDataPage = this.numData.slice(first, last)
    },
    //输入限制

    //提交数据       右边
    submit () {
      const nowTime = Date.now()
      const { activeName, number, lastTime } = this
      if (nowTime - lastTime > 2000) {
        this.lastTime = nowTime
        if (activeName == 'number') {
          const rep = /^(?=.*[A-Z])(?=.*\d)[A-Z\d]{16}$/;
          if (number) {
            if (!rep.test(number)) {
              this.myMessage('error', 'number格式不对')
              return
            }
            const data = {
              list: [number],
              type: activeName
            }
            add(data)
              .then(res => {
                if (res.code == 0) {
                  this.myMessage('success', res.data)
                  this.number = ''
                  getAll()
                    .then(res => {
                      this.numData = []
                      let i = 1
                      this.numData = res.number.map(item => ({
                        id: i++,
                        list: item.number,
                        main: item.main,
                        type: 'number'
                      }))
                      this.numDataPage = []
                      this.numDataPage = this.numData.slice(0, this.pageNum)
                    })
                }
              })
              .catch(res => {
                this.myMessage('error', '添加白名单失败')
              })
          } else {
            this.myMessage('error', '请输入number')
          }
        } else {
          const msg = verificationIp(this.ip)
          if (msg) {
            this.myMessage('error', msg)
            return
          }
          const data = {
            list: [this.ip],
            type: activeName
          }
          add(data)
            .then(res => {
              if (res.code == 0) {
                this.myMessage('success', res.data)
                getAll()
                  .then(res => {
                    let i = 1
                    this.ipData = res.ip.map(item => ({
                      id: i++,
                      list: item,
                      type: 'ip'
                    }))
                    this.ipCurrentPage = 1
                    this.ipDataPage = this.ipData.slice(0, this.pageNum)
                  })
              }
            })
            .catch(res => {
              this.myMessage('error', '添加白名单失败')
            })
        }
      }
    },

    //批量添加
    request (e) {
      const reg = /\.xlsx|\.xls$/
      const files = e.target.files;
      // console.log(files[0].name);
      const fileType = reg.test(files[0].name)
      const that = this
      if (!fileType) {
        this.myMessage('error', '文件类型不正确')
        return
      }
      let fileReader = new FileReader();
      let workbook;
      fileReader.onload = function (ev) {
        try {
          const data = ev.target.result//二进制数据
          workbook = XLSX.read(data, {
            type: 'binary'
          }); // 以二进制流方式读取得到整份excel表格对象
          // console.log(workbook);
        } catch (e) {
          console.log(e);
        }
        let sheetList = workbook.SheetNames
        sheetList.forEach(function (y) {
          let json = XLSX.utils.sheet_to_json(workbook.Sheets[y])
          // console.log(json);
          if (json.length > 0) {
            //具体如何处理看项目需求，我的项目其实只有一个sheet，在这里写成循环避免大家误会
            //数据处理与存放
            that.importDataInfo.allList = json
          }
        });
        that.addHandleData(that.importDataInfo.allList)
        e.target.value = ''

      };

      // 以二进制方式打开文件
      fileReader.readAsBinaryString(files[0]);


    },

    //处理批量添加的数据
    addHandleData (data) {
      this.importDataInfo.errorList = []
      this.importDataInfo.successList = {
        ip: [],
        number: []
      }
      if (data.length > 0) {
        data.forEach(item => {
          let list = item.list
          let msg = verificationIp(list)
          if (msg) {
            msg = verificationNumber(list)
            if (msg) {
              this.importDataInfo.successList.number.push(list)
            } else {
              this.importDataInfo.errorList.push(list)
            }
          } else {
            this.importDataInfo.successList.ip.push(list)
          }
        })
        this.openFullScreen()
      } else {
        this.myMessage('error', '导入数据有误')
      }
    },

    openFullScreen () {
      if (this.importDataInfo.errorList.length > 0) {
        this.myMessage('error', '导入数据有误')
        return
      }
      const loading = this.$loading({
        lock: true,
        text: 'Loading',
        spinner: 'el-icon-loading',
        background: 'rgba(0, 0, 0, 0.7)'
      });
      const { ip, number } = this.importDataInfo.successList
      if (ip.length > 0) {
        const IpData = {
          list: ip,
          type: 'ip'
        }
        add(IpData)
          .then(res => {
            loading.close();
            this.getAllWhite('ip')
            this.myMessage('success', 'IP数据导入成功')
          })
          .catch(res => {
            loading.close();
            this.getWhiteList()
            this.myMessage('error', res.data)
          })
      }

      if (number.length > 0) {
        const numberData = {
          list: number,
          type: 'number'
        }

        add(numberData).then(res => {
          loading.close();
          this.getAllWhite('number')
          this.myMessage('success', 'number数据导入成功')
        })
          .catch(res => {
            loading.close();
            this.getWhiteList()
            this.myMessage('error', 'number数据导入失败')
          })
      }


    },


    //批量删除
    delAll (e) {
      const reg = /\.xlsx|\.xls$/
      const files = e.target.files;
      // console.log(files[0].name);
      const fileType = reg.test(files[0].name)
      const that = this
      if (!fileType) {
        this.$message({
          type: 'error',
          message: '文件类型不正确',
          duration: 3000,
          showClose: true,
          offset: 54,
        })
        return
      }
      let fileReader = new FileReader();
      let workbook;
      fileReader.onload = function (ev) {
        try {
          const data = ev.target.result//二进制数据
          workbook = XLSX.read(data, {
            type: 'binary'
          }); // 以二进制流方式读取得到整份excel表格对象
          // console.log(workbook);
        } catch (e) {
          console.log(e);
        }
        let sheetList = workbook.SheetNames
        sheetList.forEach(function (y) {
          let json = XLSX.utils.sheet_to_json(workbook.Sheets[y])
          // console.log(json);
          if (json.length > 0) {
            //具体如何处理看项目需求，我的项目其实只有一个sheet，在这里写成循环避免大家误会
            //数据处理与存放
            that.delDataInfo.allList = json
          }
        });
        that.delHandleData(that.delDataInfo.allList)
        e.target.value = ''

      };

      // 以二进制方式打开文件
      fileReader.readAsBinaryString(files[0]);


    },

    //处理批量删除的数据
    delHandleData (data) {
      this.delDataInfo.errorList = []
      this.delDataInfo.successList = {
        ip: [],
        number: []
      }
      if (data.length > 0) {
        data.forEach(item => {
          let list = item.list
          let msg = verificationIp(list)
          if (msg) {
            msg = verificationNumber(list)
            if (msg) {
              this.delDataInfo.successList.number.push(list)
            } else {
              this.delDataInfo.errorList.push(list)
            }
          } else {
            this.delDataInfo.successList.ip.push(list)
          }
        })
        this.openDelFullScreen()
      } else {
        this.$message({
          type: 'error',
          message: '导入数据有误',
          duration: 3000,
          showClose: true,
          offset: 54,
        })
      }
    },


    openDelFullScreen () {
      if (this.delDataInfo.errorList.length > 0) {
        this.$message({
          type: 'error',
          message: '导入数据有误',
          duration: 3000,
          showClose: true,
          offset: 54,
        })
        return
      }
      const loading = this.$loading({
        lock: true,
        text: 'Loading',
        spinner: 'el-icon-loading',
        background: 'rgba(0, 0, 0, 0.7)'
      });
      const { ip, number } = this.delDataInfo.successList
      if (ip.length > 0) {
        const IpData = {
          list: ip,
          type: 'ip'
        }
        delAll(IpData)
          .then(res => {
            this.getAllWhite('ip', 'all')
            loading.close();
            this.$message({
              type: 'success',
              message: 'IP数据批量删除成功',
              duration: 3000,
              showClose: true,
              offset: 54,
            })
          })
          .catch(res => {
            loading.close();
            this.getAllWhite('ip', 'all')
            this.$message({
              type: 'error',
              message: res.data,
              duration: 3000,
              showClose: true
            })
          })
      }

      if (number.length > 0) {
        const numberData = {
          list: number,
          type: 'number'
        }
        console.log(numberData);
        delAll(numberData).then(res => {
          loading.close();
          this.getAllWhite('number', 'all')

          this.$message({
            type: 'success',
            message: 'number数据批量删除成功',
            duration: 3000,
            showClose: true
          })
        })
          .catch(res => {
            loading.close();
            this.getAllWhite('number', 'all')
            if (res.code == 1) {
              this.myMessage('warning', '使用批量删除将不能确保全部删除成功', 3000)

            } else {
              this.myMessage('error', '使用批量删除将不能确保全部删除成功', 3000)
            }

          })
      }


    },

    getAllWhite (type, count = 'one') {
      getAll()
        .then(res => {
          if (type == 'ip') {
            this.ipData = []
            this.ipDataPage = []
            for (let i = 0; i < res.ip.length; i++) {
              this.ipData.push({
                id: i + 1,
                list: res.ip[i],
                type: 'ip'
              })
            }

            if (count !== 'one') {//如果是批量删除每次都会返回第一页
              this.numCurrentPage = 1
            }

            //保存在当页里面，不用跳回第一页
            let last = this.pageNum * this.ipCurrentPage;
            let first = last - this.pageNum;
            this.ipDataPage = []
            this.ipDataPage = this.ipData.slice(first, last)
            if (this.ipDataPage.length == 0) {//如果最后页的数据删除为空后自动跳到上一个页面
              this.ipCurrentPage = this.ipCurrentPage - 1
              let last = this.pageNum * this.ipCurrentPage;
              let first = last - this.pageNum;
              this.ipDataPage = []
              this.ipDataPage = this.ipData.slice(first, last)
            }
          } else {
            this.numData = []
            this.numDataPage = []
            for (let i = 0; i < res.number.length; i++) {
              this.numData.push({
                id: i + 1,
                list: res.number[i].number,
                main: res.number[i].main,
                type: 'number'
              })
            }

            if (count !== 'one') {//如果是批量删除每次都会返回第一页
              this.numCurrentPage = 1
            }

            //保存在当页里面，不用跳回第一页
            let last = this.pageNum * this.numCurrentPage;
            let first = last - this.pageNum;
            this.numDataPage = []
            this.numDataPage = this.numData.slice(first, last)
            if (this.numDataPage.length == 0) {//如果最后页的数据删除为空后自动跳到上一个页面
              this.numCurrentPage = this.numCurrentPage - 1
              let last = this.pageNum * this.numCurrentPage;
              let first = last - this.pageNum;
              this.numDataPage = []
              this.numDataPage = this.numData.slice(first, last)
            }
            // this.numDataPage = this.numData.slice(0, this.pageNum)
          }
        })
    },

    //搜索服务
    goToSearch () {
      const nowTime = Date.now()
      if (nowTime - this.searchLastTime > 2000) {
        this.searchLastTime = nowTime
        let search = this.search
        if (search) {
          const result = verificationIp(search)
          let type;
          if (!result) {
            type = 'ip'
            getSearch({ list: search, type })
              .then(res => {
                this.$confirm(res.data + '是否删除？', '搜索成功', {
                  type: 'warning',
                  confirmButtonText: '删除',
                }).then(() => {
                  del({ list: search, type })
                    .then(() => {
                      this.myMessage('success', '删除成功')
                      window.location.reload()
                    })
                })
              })
              .catch(res => {
                this.$alert(res.data, '搜索失败', {
                  confirmButtonText: '确定',
                });
              })
          } else {
            type = 'number'
            const result = verificationNumber(search)
            if (!result) {
              this.myMessage('warning', '搜索失败，number格式有误')
              return
            }
            getSearch({ list: search, type })
              .then(res => {
                this.$confirm(res.data + '是否删除？', '搜索成功', {
                  type: 'warning',
                  confirmButtonText: '删除',
                }).then(() => {
                  del({ list: search, type })
                    .then(() => {
                      this.myMessage('success', '删除成功')
                      window.location.reload()
                    })
                })
              })
              .catch(res => {
                this.$alert(res.data, '搜索失败', {
                  confirmButtonText: '确定',
                });
              })
          }
        } else {
          this.myMessage('warning', '请输入搜索内容')
        }
      }

    },

    //获取多选的内容
    handleSelectionChange (val) {
      this.multipleSelection = val;
    },

    //开启白名单服务
    onWhiteList () {
      if (this.info.whitelistswitch != 'true') {
        this.$confirm('是否关闭白名单?', '提示', {
          confirmButtonText: '确定',
          cancelButtonText: '取消',
          type: 'warning'
        }).then(() => {
          setConfig(this.info).then(res => {
            this.myMessage('success', '关闭白名单成功')
          })
            .catch(res => {
              this.myMessage('error', '关闭白名单失败')
              this.info.whitelistswitch = 'true'
            })
        }).catch(() => {
          this.info.whitelistswitch = 'true'
        });
      } else {
        this.$confirm('是否开启白名单?', '提示', {
          confirmButtonText: '确定',
          cancelButtonText: '取消',
          type: 'warning'
        }).then(() => {
          setConfig(this.info).then(res => {
            this.myMessage('success', '开启白名单成功')
          })
            .catch(res => {
              this.myMessage('error', '开启白名单失败')
              this.info.whitelistswitch = 'false'
            })
        }).catch(() => {
          this.info.whitelistswitch = 'false'
        });
      }
    },

    //导出全部数据
    async allDerive () {
      const result = await getAll()
      const number = []

      if (result.code == 0) {
        for (let item of result.number) {
          number.push(item.number)
        }
        let data = result.ip.concat(number)
        let excel = [{ list: 'list' }]
        for (let item of data) {
          excel.push({ list: item })
        }
        this.$prompt('请输入导出的文件名称', '提示', {
          confirmButtonText: '确定',
          cancelButtonText: '取消',
        }).then(({ value }) => {
          this.downloadExl(excel, value)
        })
      } else {
        this.myMessage('error', '导出失败')
      }
    },

    //导出选中的数据
    derive () {
      if (this.multipleSelection.length < 1) {
        this.myMessage('error', '请选择导出的数据')
        return
      }
      let excel = [{ list: 'list' }]
      for (let item of this.multipleSelection) {
        excel.push({ list: item.list })
      }
      this.$prompt('请输入导出的文件名称', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
      }).then(({ value }) => {
        this.downloadExl(excel, value)
      })
    },
    downloadExl (data, downName, type) {
      let keyMap = [] // 获取键
      for (let k in data[0]) {
        keyMap.push(k)
      }
      let tmpdata = [] // 用来保存转换好的json
      data.map((v, i) => keyMap.map((k, j) => Object.assign({}, {
        v: v[k],
        position: (j > 25 ? this.getCharCol(j) : String.fromCharCode(65 + j)) + (i + 1)
      }))).reduce((prev, next) => prev.concat(next)).forEach(function (v) {
        tmpdata[v.position] = {
          v: v.v
        }
      })
      let outputPos = Object.keys(tmpdata)  // 设置区域,比如表格从A1到D10
      let tmpWB = {
        SheetNames: ['mySheet'], // 保存的表标题
        Sheets: {
          'mySheet': Object.assign({},
            tmpdata, // 内容
            {
              '!ref': outputPos[0] + ':' + outputPos[outputPos.length - 1] // 设置填充区域
            })
        }
      }
      let tmpDown = new Blob([this.s2ab(XLSX.write(tmpWB,
        { bookType: (type === undefined ? 'xlsx' : type), bookSST: false, type: 'binary' } // 这里的数据是用来定义导出的格式类型
      ))], {
        type: ''
      })  // 创建二进制对象写入转换好的字节流
      var href = URL.createObjectURL(tmpDown)  // 创建对象超链接
      this.outFile.download = downName + '.xlsx'  // 下载名称
      this.outFile.href = href  // 绑定a标签
      this.outFile.click()  // 模拟点击实现下载
      setTimeout(function () {  // 延时释放
        URL.revokeObjectURL(tmpDown) // 用URL.revokeObjectURL()来释放这个object URL
      }, 100)
    },
    getCharCol: function (n) { // 将指定的自然数转换为26进制表示。映射关系：[0-25] -> [A-Z]。
      let s = ''
      let m = 0
      while (n > 0) {
        m = n % 26 + 1
        s = String.fromCharCode(m + 64) + s
        n = (n - m) / 26
      }
      return s
    },
    s2ab: function (s) { // 字符串转字符流
      var buf = new ArrayBuffer(s.length)
      var view = new Uint8Array(buf)
      for (var i = 0; i !== s.length; ++i) {
        view[i] = s.charCodeAt(i) & 0xFF
      }
      return buf
    },
    //自定义列
    defaultFun (data) {
      if (this.radio == 'IP') {
        this.custom = {}
        for (let item of data) {
          this.custom[item.value] = item.state
        }
      } else {
        this.customs = {}
        for (let item of data) {
          this.customs[item.value] = item.state
        }
      }

    },
    confirmFun (data) {
      if (this.radio == 'IP') {
        this.custom = {}
        for (let item of data) {
          this.custom[item.value] = item.state
        }
      } else {
        this.customs = {}
        for (let item of data) {
          this.customs[item.value] = item.state
        }
      }

    },
    closeCustom (data) {
      if (this.radio == 'IP') {
        this.customList = []
        this.customList = data
      } else {
        this.customListT = []
        this.customListT = data
      }
    }
  },

  computed: {
    ip: function () {
      return `${this.ip1}.${this.ip2}.${this.ip3}.${this.ip4}`
    },
    tableData: function () {
      if (this.radio == 'IP') {
        return this.ipDataPage
      } else {
        return this.numDataPage
      }
    },
  },
  watch: {
    ip1: function (val) {
      if (!Number.isInteger(val)) {
        this.ip1 = null
      } else {
        if (val > 255 || val < 0) {
          this.ip1 = 255
        }
      }

    },
    ip2: function (val) {
      if (!Number.isInteger(val)) {
        this.ip2 = null
      } else {
        if (val > 255 || val < 0) {
          this.ip2 = 255
        }
      }
    },
    ip3: function (val) {
      if (!Number.isInteger(val)) {
        this.ip3 = null
      } else {
        if (val > 255 || val < 0) {
          this.ip3 = 255
        }
      }
    },
    ip4: function (val) {
      if (!Number.isInteger(val)) {
        this.ip4 = null
      } else {
        if (val > 255 || val < 0) {
          this.ip4 = 255
        }
      }
    },
    //
    // radio: function (val) {
    //   if (val == 'IP') {
    //     this.$refs.ruleForm.resetFields();
    //   }
    // },
  },
  components: { MyPopover }/*自定义列组件 */
}
</script>

<style scoped>
.content {
  display: flex;
  justify-content: space-between;
  text-align: center;
}

/*自定义列 */
.hide {
  display: none;
}

/*------------------------中间添加ip部分 *-----------------------*/
.content_ip {
  height: 400px;
  padding: 10px 5px 10px 10px;
  display: flex;
  flex-direction: column;
  justify-content: space-between;
  align-items: center;
  position: relative;
}

.content_ip .ip_top {
  flex: 1;
  width: 100%;
}

.content_ip .ip_bottom {
  flex: 6;
  width: 380px;
  /* border-bottom: 1px solid #f4f4f4; */
}

.content_ip .ip_bottom .ip-item {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 10px;
}

.content_ip .ip_bottom .ip-item .ip_left {
  flex: 0.5;
  height: 40px;
  text-align: center;
  line-height: 40px;
}

.content_ip .ip_bottom .ip-item .container_bl {
  flex: 4;
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.content_ip .ip_bottom .ip-item .container_bl .el-input {
  width: 60px;
  height: 40px;
}

.content_ip .ip_bottom .ip-item .anJian {
  flex: 1;
  display: flex;
  justify-content: space-around;
  align-items: center;
}

.content_ip .ip_bottom .lock {
  position: absolute;
  top: 44px;
  left: 67px;
}

.content_ip .ip_bottom .lockT {
  position: absolute;
  top: 44px;
  left: 145px;
}

.content_ip .ip_bottom .lockTh {
  position: absolute;
  top: 44px;
  left: 224px;
}

.content_ip .ip_bottom .lockF {
  position: absolute;
  top: 44px;
  left: 304px;
}

.content_ip .ip_bottom .ip-item .lock i,
.content_ip .ip_bottom .ip-item .lockT,
.content_ip .ip_bottom .ip-item .lockTh {
  /* color: #409eff; */
  width: 18px;
  height: 18px;
  cursor: pointer;
  display: inline-block;
}

.content_ip .ip_bottom .add i,
.content_ip .ip_bottom .jian i {
  color: #409eff;
  width: 18px;
  height: 18px;
  cursor: pointer;
  display: inline-block;
}

.jian-hidden {
  visibility: hidden;
}

.content_ip .ip_bottom .ip-item .lockF {
  /* color: #409eff; */
  width: 18px;
  height: 18px;
  cursor: pointer;
  display: inline-block;
}

/*------------------------------- 添加ip部分------------------*/
.left {
  width: 390px;
  height: 530px;
  /* margin-left: 167px; */
  background: rgba(255, 255, 255, 1);
  box-shadow: 9px 0px 29px 0px rgba(0, 0, 0, 0.09);
  border-radius: 0px 18px 20px 0px;
  opacity: 1;
  transition: 0.1s;
}

.oldLeft {
  width: 0;
  height: 0;
  opacity: 0;
}

.chunk {
  position: absolute;
  display: block;
  top: 223px;
  width: 24px;
  height: 100px;
  font-size: 18px;
  color: #ffffff;
  cursor: pointer;
  background: rgba(51, 51, 51, 1);
  border-radius: 0px 5px 5px 0px;
}

.onChunk {
  z-index: 2;
  right: -25px;
  opacity: 0.2;
}

/* .offChunk {

    } */

.onChunk::after {
  position: absolute;
  content: url("./img/zuojiantou.png");
  margin-top: 40px;
  margin-left: 3px;
}

.offChunk::after {
  position: absolute;
  content: url("./img/youjiantou.png");
  margin-top: 40px;
  margin-left: 3px;
}

.left-title {
  display: flex;
  align-items: center;
  justify-content: center;
  width: 100%;
  height: 62px;
  color: white;
  font-size: 24px;
  border-radius: 18px 0px 0px 0px;
  background-color: #333;
}

.right {
  display: flex;
  flex-direction: column;
  justify-content: center;
  width: 905px;
  /* margin-left: 230px; */
  margin: 0 auto;
}

.body {
  width: 100%;
}

.title {
  display: flex;
  justify-content: space-between;
  align-items: center;
  width: 100%;
  padding-bottom: 10px;
  line-height: 50px;
  font-size: 24px;
  border-bottom: 1px solid #ddd;
}

.my-radio-box {
  display: flex;
  align-items: center;
  justify-content: center;
  margin: 0 20px 0 60px;
  padding: 0 10px;
  width: 176px;
  height: 40px;
  border: 1px solid rgba(220, 223, 230, 1);
  border-radius: 5px;
}

.ip {
  padding-left: 5px;
  width: 42px;
  height: 30px;
  font-size: 16px;
  border: none;
  border-bottom: 1px solid rgba(102, 102, 102, 0.3);
}

.ip_point {
  margin: -3px 8px;
  color: rgba(102, 102, 102, 0.3);
}

.btn {
  display: inline-block;
  padding: 12px 20px;
  margin-left: 40px;
  width: 200px;
  height: 40px;
  line-height: 1;
  white-space: nowrap;
  -webkit-appearance: none;
  text-align: center;
  -webkit-box-sizing: border-box;
  box-sizing: border-box;
  outline: 0;
  -webkit-transition: 0.1s;
  transition: 0.1s;
  font-weight: 500;
  -moz-user-select: none;
  color: #fff;
  background-color: #409eff;
  border-color: #409eff;
  font-size: 14px;
  border-radius: 20px;
  cursor: pointer;
}

.btn:hover {
  background: #66b1ff;
  border-color: #66b1ff;
  color: #fff;
}

.pagination {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-top: 16px;
}

@media (max-width: 1600px) {
  .right {
    display: flex;
    flex-direction: column;
    justify-content: center;
    box-ordinal-group: 1;
    /* margin: 0 auto; */
    width: 705px;
    /*width: calc(100% - 700px);*/
    /*min-height: 800px;*/
  }
}

@media (max-width: 1200px) {
  .right {
    display: flex;
    flex-direction: column;
    justify-content: center;
    margin: 0 auto;
    width: 605px;
    /*width: calc(100% - 700px);*/
    /*min-height: 800px;*/
  }
}
</style>
