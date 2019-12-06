<template>
  <p>

        <input type="file" id="files" style="display: none" onchange="fileImport();">

        <input type="button" id="fileImport" value="选择固件文件">

    </p>
</template>

<script>
export default {
  name: 'HelloWorld',
  data () {
    return {
      msg: '发送'
    }
  }

}

</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->

<style scoped>
@import url("../../static/css/reset.css");
h1,
h2 {
  font-weight: normal;
}
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
a {
  color: #42b983;
}
.page {
  width: 100%;
  height: 100%;
}

.container {
  margin: 0 auto;
  padding: 50px 5px 5px 5px;
  width: 80%;
  background-color: #b7bbb7e1;
}

.container .big {
  margin: 0 auto;
  height: 500px;
  width: 700px;
  border: 2px solid #4b4a4b;
  position: relative;
  background-color: #fff;
}

.container .big .title {
  position: absolute;
  top: -31px;
  left: -2px;
  display: inline-block;
  height: 30px;
  width: 80px;
  border: 2px solid #4b4a4b;
  border-bottom: 0px;
  background-color: #dad8da;
  text-align: center;
  line-height: 28px;
}

.container .send {
  margin: 0 auto;
  width: 700px;
  margin-top: 50px;
  position: relative;
}

.container .send .send_top {
  display: flex;
  align-items: center;
  justify-content: space-between;
  height: 50px;
}

.container .send .send_s {
  display: inline-block;
  border: 1px solid #4b4a4b;
  margin-top: 22px;
  height: 30px;
  width: 80px;
  text-align: center;
  line-height: 30px;
  background-color: #dad8da;
}

.container .send .send_top div {
  display: inline-block;
}

.container .send .right {
  height: 30px;
  width: 100px;
  margin-top: 22px;
}
.container .send .send_botton {
  height: 100px;
  display: flex;
  align-items: center;
}
.container .send textarea {
  flex: 4;
  height: 100px;
  float: left;
  border: 1px solid #4b4a4b;
}

.container .send .btn {
  flex: 1;
  height: 100px;
  color: #22c23d;
  font-size: 18px;
  border: 1px solid #4b4a4b;
}
</style>
