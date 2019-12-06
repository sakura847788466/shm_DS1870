<template>
  <div class="left">
    <div class="left-box">
      <div class="left-item">直线
        <DLine/>
      </div>
      <div class="left-item">矩形
        <Rectangle/>
      </div>
    </div>
    <div class="left-box">
      <div class="left-item">文本
        <TextBox/>
      </div>
      <div class="left-item">圆
        <Circular/>
      </div>
    </div>
  </div>
</template>

<script>
  import DLine from "../../components/element/DLine/DLine";
  import Rectangle from "../../components/element/Rectangle/Rectangle";
  import TextBox from "../../components/element/TextBox/TextBox";
  import Circular from "../../components/element/Circular/circular"
  export default {
    name: "Left",
    data() {
      return {}
    },
    methods: {},
    components: {DLine,Rectangle,TextBox,Circular},
    props: {}

  }
</script>

<style scoped>
  .left{
    width: 250px;
    height: 100%;
    background-color: #f5f5f5;
  }
  .left-box{
    display: flex;
    width: 100%;
    height: 50px;
  }
  .left-item{
    flex: 1;
    border: 1px solid #ddd;
  }
</style>