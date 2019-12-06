<template>
  <div class="content">
    <div class="right"
         :style="fade?'':'margin:0 auto;'">
      <div class="title">
        <div style="display:flex;justify-content: space-between;
    align-items: center;flex:1;">
          <span class="title-text"
                style="flex:2;display: inline-block;
    height: 50px; font-size:21px;
    ">设备列表</span>
        </div>
        <div style="display:flex;flex:6;">
        </div>
      </div>
      <div class="body">
        <el-table :data="ipDataPage"
                  style="width: 100%;min-height: 481px;"
                  @selection-change="handleSelectionChange"
                  max-height="518"
                  empty-text="数据为空，未拿到数据">
          <el-table-column type="selection"
                           width="55" />
          <el-table-column prop="id"
                           label="序号" />
          <el-table-column prop="number"
                           label="Number"
                           width="200"
                           align="center" />
          <el-table-column prop="voiceswitch"
                           label="声音提示开关"
                           align="center">
            <template slot-scope="scope">
              <el-switch v-model="scope.row.voiceswitch"
                         :status="scope.row.voiceswitch"
                         style="margin-left: 14px;flex:1;"
                         @change="upStatus(scope.row)" />
            </template>
          </el-table-column>

          <el-table-column prop="printtipswitch"
                           label="打印提示开关"
                           align="center">
            <template slot-scope="scope">
              <el-switch v-model="scope.row.printtipswitch"
                         style="margin-left: 14px;flex:1;"
                         @change="upStatus(scope.row)" />
            </template>
          </el-table-column>
          <el-table-column label="操作"
                           width="80"
                           align="center">
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
                     @click="delSome">批量删除</el-button>
          <el-pagination small
                         :pager-count="pagerCount"
                         :hide-on-single-page="true"
                         style="display:flex;flex-wrap: wrap;justify-content: center"
                         :current-page.sync="ipCurrentPage"
                         :page-size="pageNum"
                         layout="total,prev, pager, next,jumper"
                         :total="ipData.length">
          </el-pagination>
        </div>
      </div>
    </div>
    <div style="position: relative;z-index: 2">
      <div class="left"
           :class="{oldLeft:!fade}">
        <div class="left-title">
          <span style="display:inline-block;margin:0 auto">引导配置信息</span>

        </div>
        <div style="font-size: 16px;color: #666;">
          <div class="top_R">
            <div style="width:100%;height:40px;margin-top:20px;line-heigth:40px;"><span style="margin-left:16px;font-weight: bolder;line-height:40px;">开关设置:</span></div>
            <div class="top_l">
              <div class="top_swi"
                   style="margin:20px 0px 20px 0px;"><span>语音提示总开关</span>
                <el-switch v-model="VoiceInfo['voiceswitch']"
                           style="flex:1;"
                           @change="voiceStatus($event,VoiceInfo['voiceswitch'])" />
              </div>
              <el-dialog title="提示"
                         :visible.sync="dialogVisible"
                         width="30%"
                         :before-close="handleClose"
                         :modal-append-to-body='false'
                         :close-on-click-modal='false'>
                <span>打印提示总开关已经</span>
                <span slot="footer"
                      class="dialog-footer">
                  <el-button @click="dialogVisible = false">取 消</el-button>
                  <el-button type="primary"
                             @click="dialogVisible = false">确 定</el-button>
                </span>
              </el-dialog>
              <div class="top_swi">
                <span>打印提示总开关</span>
                <el-switch v-model="VoiceInfo['printtipswitch']"
                           style="flex:1;"
                           @change="printfStatus($event,VoiceInfo['printtipswitch'])" />
              </div>
            </div>
            <!-- <div class="top_r">
            </div> -->
          </div>
          <div class="voiceInfo">
            <div class="titleInfo">
              <span style="height:40px;flex:2;text-align:center;line-height:40px;margin-left:16px;font-weight: bolder;">语音播报句段信息:</span>
            </div>
            <div class="titleInfo">
              <span style="height:40px;flex:2;text-align:center;line-height:40px;margin-left:16px;">句段编号</span>
            </div>
            <div class="vioce"
                 style="height:40px;flex:2;text-align:center;line-height:40px;margin-left:16px;">
              <div class="vioce_c">
                <div class="vioce_num">
                  <span class="s_num">{{juDuanNum}}</span>
                </div>
                <input type="text"
                       maxlength="20"
                       class="voice_num"
                       v-model="Info" />
                <div class="updataC"
                     style="flex:1;">
                  <el-button type="primary"
                             size="small"
                             class="option_brn"
                             @click="upDataVoice_click">修改</el-button>
                </div>
              </div>
              <div class="vioce_c">
                <div class="vioce_num">
                  <span class="s_num">{{juDuanNum1}}</span>
                </div>
                <input type="text"
                       maxlength="20"
                       class="voice_num"
                       v-model="Info1" />
                <div class="updataC"
                     style="flex:1;">
                  <el-button type="primary"
                             size="small"
                             class="option_brn"
                             @click="upDataVoice_clickT">修改</el-button>
                </div>

              </div>
            </div>
          </div>
          <div class="option">
            <!-- <el-button type="primary"
                       size="small"
                       class="option_brn"
                       @click="upDataVoice_click">句段修改</el-button> -->
          </div>

          <a id="downlink"></a>
        </div>

      </div>
    </div>
  </div>
</template>

<script>
import { getVoiceInfo, getAllVoiceConfig, delSomeThing, upDataSome, upDataVoice, getAllVoice, upDataVoiceInfo } from "../../api/index";


export default {
  name: "VoiceInfo",
  mounted () {
    getVoiceInfo()//全局总开关
      .then(res => {
        this.VoiceInfo = res.data;
        this.voiceStatu = res.data.voiceswitch;
        this.printfStatu = res.data.printtipswitch;
        console.log(this.voiceStatu)
        console.log(this.printfStatu)
      })
      .catch(res => {
        console.log(res);
      });
    getAllVoice()//获取全部的语音句段
      .then(res => {
        this.allVoice = res.data
        this.Info = res.data[0].voicedata
        this.Info1 = res.data[1].voicedata
        this.juDuanNum = res.data[0].segmentno
        this.juDuanNum1 = res.data[1].segmentno
      })
      .catch(err => {
        console.log(err)
      })

    getAllVoiceConfig() //获取所有的语音配置信息
      .then(res => {
        this.ipData = []
        this.ipDataPage = []
        for (let i = 0; i < res.data.length; i++) {
          this.ipData.push({
            id: i + 1,
            number: res.data[i].number,
            voiceswitch: res.data[i].voiceswitch,
            printtipswitch: res.data[i].printtipswitch,
            // type: 'Number'
          })
        }
        this.ipDataPage = this.ipData.slice(0, this.pageNum)
      }).catch(res => {
        console.log(res)
      })


  },

  data () {
    return {
      VoiceInfo: [],
      Info: '',
      Info1: '',
      juDuanNum: '',
      juDuanNum1: '',
      allVoice: [],//所有的语音句段
      activeName: 'ip',
      fade: true,
      multipleSelection: [],//选择批量的数据
      ipData: [],//设备数
      ipDataPage: [],//设备分页展示数据
      numData: [],//num总打印记录
      numDataPage: [],//num分页展示数据
      ipCurrentPage: 1,
      numCurrentPage: 1,
      pageNum: 10,
      pagerCount: 5,
      printfStatu: '',
      voiceStatu: '',
      dialogVisible: false,
      openAclose: ''
    };
  },

  methods: {
    myMessage (type, msg, duration = 3000) {
      this.$message({
        message: msg,
        type,
        duration,
        showClose: true,
        offset: 54,
      });
    },
    // 确认提示框
    handleClose (done) {
      this.$confirm('确认关闭？')
        .then(_ => {
          done();
        })
        .catch(_ => { });
    },
    //打印总开关更改状态
    printfStatus (val, printf) {
      this.dialogVisible = true
      this.printfStatu = printf;

      const data = {
        voiceswitch: this.voiceStatu,
        printtipswitch: this.printfStatu
      }
      upDataVoiceInfo(data)
        .then(res => {
          // this.myMessage("success", res.data)
          this.dialogVisible = true
        }).catch(err => {
          this.myMessage("fail", res.data)
        })

    },
    //声音总开关更改状态
    voiceStatus (val, voice) {
      this.voiceStatu = voice;
      const data = {
        voiceswitch: this.voiceStatu,
        printtipswitch: this.printfStatu
      }
      upDataVoiceInfo(data)
        .then(res => {
          this.myMessage("success", res.data)
        }).catch(err => {
          this.myMessage("fail", res.data)
        })
    },
    //更改设备开关状态
    upStatus (rows) {
      const item = rows;
      const listItem = [];
      listItem.push(item)
      const data = {
        list: listItem
      }
      upDataSome(data)
        .then(res => {
          this.myMessage('success', res.data)  //更改提示框样式
          getAllVoiceConfig()
            .then(res => {
              this.ipData = []
              this.ipDataPage = []
              for (let i = 0; i < res.data.length; i++) {
                this.ipData.push({
                  id: i + 1,
                  number: res.data[i].number,
                  voiceswitch: res.data[i].voiceswitch,
                  printtipswitch: res.data[i].printtipswitch,
                  // type: 'Number'
                })
              }
              this.ipDataPage = this.ipData.slice(0, this.pageNum)
            }).catch(res => {
              console.log(res)
            })
        }).catch(err => {
          this.myMessage('fail', res.data)
        })
    },
    //获取多选的内容
    handleSelectionChange (val) {
      this.multipleSelection = val;
    },
    //批量更改
    //单删除
    deleteRow (rows) {
      this.$confirm('此操作将永久删除该数据, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        const rowsN = [rows.number]
        const data = {
          list: rowsN,
        }
        delSomeThing(data)
          .then(res => {
            if (res.code == 0) {
              getAllVoiceConfig()
                .then(res => {
                  this.$message({
                    type: 'success',
                    message: '删除成功!'
                  });
                  this.ipData = []
                  this.ipDataPage = []
                  for (let i = 0; i < res.data.length; i++) {
                    this.ipData.push({
                      id: i + 1,
                      number: res.data[i].number,
                      voiceswitch: res.data[i].voiceswitch,
                      printtipswitch: res.data[i].printtipswitch,
                      // type: 'Number'
                    })
                  }
                  this.ipDataPage = this.ipData.slice(0, this.pageNum)
                }).catch(res => {
                  console.log(res)
                })
            }
          })
          .catch(res => {
            this.$message({
              type: 'info',
              message: '已取消删除'
            });
          })

      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除'
        });
      });

    },
    //批量删除
    delSome () {
      if (this.multipleSelection.length < 1) {
        this.myMessage('error', '请选择所要删除的数据')
        return
      }
      let numberList = []
      for (let item of this.multipleSelection) {
        numberList.push(item.number)
      }
      console.log(numberList) //['1ajdadj','2jdakjd']
      const data = { list: numberList }
      delSomeThing(data).then(() => {
        getAllVoiceConfig()
          .then(res => {
            this.myMessage('success', '删除成功')
            this.ipData = []
            this.ipDataPage = []
            for (let i = 0; i < res.data.length; i++) {
              this.ipData.push({
                // id: i + 1,
                number: res.data[i].number,
                voiceswitch: res.data[i].voiceswitch,
                printtipswitch: res.data[i].printtipswitch,
                // type: 'Number'
              })
            }
            this.ipDataPage = this.ipData.slice(0, this.pageNum)
          }).catch(res => {
            console.log(res)
          })
      }).catch(() => {
        this.myMessage('fail', '删除失败')
      })

    },
    //更新句段信息
    upDataVoice_click () {
      const data = {
        segmentno: 1,
        voicedata: this.Info
      }
      upDataVoice(data)
        .then(res => {
          console.log(res)
          //请求成功但是没有走.then()

        })
        .catch(err => {
          console.log(err)
          if (err.code == 1002) {
            this.myMessage("success", "修改成功")

          } else {
            this.myMessage("fail", "修改失败")
          }
        })
    },
    upDataVoice_clickT () {
      const data = {
        segmentno: 2,
        voicedata: this.Info1
      }
      upDataVoice(data)
        .then(res => {
          console.log(res)

        })
        .catch(err => {
          console.log(err)
          if (err.code == 1002) {
            this.myMessage("success", "修改成功")

          } else {
            this.myMessage("fail", "修改失败")
          }
        })
    }
  },

  watch: {},


};
</script>

<style scoped>
.content {
  display: flex;
  justify-content: space-between;
  /* text-align: center; */
}
/*自定义列 */
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

/* .onChunk::after {
  position: absolute;
  content: url("./img/zuojiantou.png");
  margin-top: 40px;
  margin-left: 3px;
} */

/* .offChunk::after {
  position: absolute;
  content: url("./img/youjiantou.png");
  margin-top: 40px;
  margin-left: 3px;
} */

.left-title {
  display: flex;
  align-items: center;
  justify-content: space-between;
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

.top_R {
  display: flex;
  justify-content: space-between;
  flex-direction: column;
  align-items: center;
}
.top_R .top_l,
.top_R .top_r {
  flex: 1;
  height: 82px;
}
.top_l {
  display: flex;
  flex-direction: column;
  justify-content: space-between;
  align-items: center;
}
.top_l .top_ltitle {
  margin: 20px 60px 20px 0;
}

.voiceInfo {
  margin-top: 40px;
}
.voiceNum {
  display: flex;
  justify-content: space-between;
  align-items: center;
}
.voice_num {
  flex: 3;
  border: none;
  height: 40px;
  border-bottom: 1px solid rgba(102, 102, 102, 0.3);
  font-size: 16px;
  color: rgb(102, 102, 102);
}
.vioce_num .s_num {
  display: inline-block;
  height: 20px;
  width: 20px;
  border-radius: 10px;
  background: rgb(190, 187, 187);
  text-align: center;
  line-height: 20px;
}
.vioce_c {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-right: 16px;
}
.vioce_c .vioce_num {
  flex: 1;
  height: 40px;
  text-align: center;
  line-height: 40px;
}

.option {
  margin-top: 20px;
  height: 50px;
  width: 100%;
  line-height: 50px;
  position: relative;
}
.option .el-button {
  position: absolute;
  top: 10px;
  right: 39px;
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
