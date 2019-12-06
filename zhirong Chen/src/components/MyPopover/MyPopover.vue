<template>
  <div class="custom-box">
    <button class="custom" @click="onCustom" :style="isCustom?'border: 1px solid rgba(64, 158, 255, 1);':''">
      <i class="el-icon-s-tools" style="margin-right:8px;color: #333;font-size: 18px;"></i>
      <span>自定义显示列</span>
    </button>
    <el-collapse-transition>
      <div class="custom-content"
           v-show="isCustom">
        <div class="custom-content-title">
          <span>自定义显示列</span>
          <i class="el-icon-error"
             style="color: #999;font-size: 17px;cursor: pointer;"
             @click.stop="closeCustom"/>
        </div>
        <div class="custom-content-body">
          <el-checkbox style="text-align:left;width: 110px;margin-right: 0"
                       v-for="(item,index) in customList"
                       :key="index"
                       v-model="customList[index].state">{{item.name}}
          </el-checkbox>
        </div>
        <div class="custom-content-footer">
          <span class="custom-content-btn custom-content-btn-primary"
                @click.stop="handleCustomDefault">恢复默认</span>
          <div style="display:flex;">
            <span class="custom-content-btn custom-content-btn-info"
                  @click.stop="closeCustom">取消</span>
            <span class="custom-content-btn custom-content-btn-danger"
                  @click.stop="handleCustom">确认</span>
          </div>
        </div>
      </div>
    </el-collapse-transition>
  </div>
</template>

<script>
  export default {
    name: "MyPopover",
    mounted() {
      this.backupsCustom = JSON.parse(JSON.stringify(this.customList))
    },
    data() {
      return {
        isCustom: false,
        backupsCustom: [],
        custom:[]
      }
    },
    methods: {
      //自定义显示列
      //点击
      onCustom() {
        if (this.isCustom) {
          this.isCustom = false
        } else {
          this.isCustom = true
        }
      },
      //点击取消
      closeCustom() {
        this.$emit('closeCustom', JSON.parse(JSON.stringify(this.backupsCustom)))
        this.isCustom = false
      },
      handleCustom() {
        this.isCustom = false
        this.backupsCustom = JSON.parse(JSON.stringify(this.customList))
        this.$emit('confirmFun', this.customList)
      },

      //自定义显示列恢复默认
      handleCustomDefault() {
        this.isCustom = false
        for (let item of this.customList) {
          item.state = true
        }
        this.backupsCustom = JSON.parse(JSON.stringify(this.customList))
        this.$emit('defaultFun', this.customList)
      },
    },
    watch:{
      // customList(){
      //   this.backupsCustom = this.customList
      //   this.custom =  JSON.parse(JSON.stringify(this.customList))
      // }
    },
    props: {
      customList: {
        type: Array,
        required: true
      },

    }

  }
</script>

<style scoped>
  .custom-box {
    position: relative;
  }

  .custom {
    display: flex;
    align-items: center;
    justify-content: center;
    width: 140px;
    height: 40px;
    line-height: 40px;
    text-align: center;
    font-size: 14px;
    color: rgba(96, 98, 102, 1);
    background-color: #ffffff;
    border: 1px solid #dcdfe6;
    border-radius: 5px;
    cursor: pointer;
  }

  .custom:hover {
    border: 1px solid rgba(64, 158, 255, 1);
  }

  .custom-content {
    z-index: 111;
    position: absolute;
    left: 40px;
    top: 49px;
    width: 375px;
    /*height: 185px;*/
    background: rgba(255, 255, 255, 1);
    border: 1px solid rgba(228, 231, 237, 1);
    box-shadow: 1px 2px 5px 0px rgba(0, 0, 0, 0.08);
    border-radius: 4px;
  }

  .custom-content:after {
    content: "";
    position: absolute;
    top: -10px;
    left: 22px;
    width: 0;
    height: 0;
    border: 5px solid transparent;
    border-bottom-color: #fff;
  }

  .custom-content:before {
    content: "";
    position: absolute;
    top: -14px;
    left: 20px;
    width: 0;
    height: 0;
    border: 7px solid transparent;
    border-bottom-color: #e4e7ee;
  }

  .custom-content-title {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin: 17px 21px 10px;
    height: 17px;
    font-size: 14px;
    font-weight: bold;
    color: rgba(96, 98, 102, 1);
  }

  .custom-content-body {
    box-sizing: border-box;
    display: flex;
    flex-wrap: wrap;
    margin: 0 21px;
    padding-bottom: 10px;
    font-size: 14px;
    font-weight: bold;
    color: #666;
    border-bottom: 1px solid rgba(243, 243, 243, 1);
  }

  .custom-content-footer {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin: 10px 21px;
    font-size: 12px;
  }

  .custom-content-btn {
    height: 25px;
    line-height: 25px;
    text-align: center;
    border-radius: 4px;
    color: #fff;
    cursor: pointer;
  }

  .custom-content-btn-primary {
    width: 66px;
    background: rgba(64, 158, 255, 1);
  }

  .custom-content-btn-info {
    width: 45px;
    color: rgba(192, 196, 204, 1);
    border: 1px solid rgba(220, 223, 230, 1);
  }

  .custom-content-btn-danger {
    margin-left: 10px;
    width: 45px;
    background: rgba(245, 108, 108, 1);
  }
</style>
