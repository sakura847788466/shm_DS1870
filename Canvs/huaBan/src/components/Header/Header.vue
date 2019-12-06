<template>
  <div class="header">
    <header>
      <div class="logo">HuaTu</div>
      <ul class="nav">
        <li :class="{active:isCurrent('/home')}" @click="goTo('/home')">首页</li>
        <!--<li :class="{active:isCurrent('/wx')}" @click="goTo('wx')">微信开票</li>-->
      </ul>
    </header>
  </div>
</template>

<script>
  export default {
    name: "Header",
    data() {
      return {}
    },
    methods: {
      goTo(path) {
        this.$router.push(path)
      },
      isCurrent(path) {
        return this.$route.path === path
      },
    },
    components: {},
    props: {}

  }
</script>

<style scoped>
  .header {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 55px;
    background-color: #f8f8f8;
    border-bottom: 1px solid #dddddd;
    box-shadow: 0 2px 5px #dddddd;
    z-index: 1;
  }

  header {
    display: flex;
    margin: 0 auto;
    padding-left: 20px;
    width: 80%;
    line-height: 55px;
  }

  .logo {
    font-family: Arial !important;
    font-size: 24px;
    color: lightcoral;
  }

  .nav {
    display: flex;
    align-items: center;
    margin-left: 100px;
    font-size: 16px;
    color: #f09999;
  }

  .nav li {
    margin-right: 10px;
    padding-bottom: 2px;
    width: 80px;
    height: 40px;
    line-height: 40px;
    text-align: center;
    cursor: pointer;
  }

  .nav li:hover {
    border-bottom: 2px solid lightcoral;
    color: lightcoral;
  }

  .active {
    border-bottom: 2px solid lightcoral;
    color: lightcoral;
  }
</style>