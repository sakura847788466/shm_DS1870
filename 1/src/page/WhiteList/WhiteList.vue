<template>
  <el-button size="medium">点击打印</el-button>
</template>

<script>
import { mapActions } from 'vuex'
import XLSX from 'xlsx'
import { add, del, getAll, getSearch, delAll, getConfig, setConfig } from '../../api/'
import { verificationIp, verificationNumber } from '../../util/tool'



export default {
  name: "PrintfTest",
  mounted () {



  },
  data () {
    return {




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
    }
  },
  components: {}
}
</script>

<style scoped>
</style>
