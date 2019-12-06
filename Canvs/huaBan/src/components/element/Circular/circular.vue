<template>
  <div ref="rectangle">
    <div :id="id"
         class="left-item"
         @dragstart="dragstart"
         @dragend="dragend"></div>
  </div>
</template>

<script>
export default {
  name: "circular",
  data () {
    return {
      id: ''
    }
  },
  methods: {
    dragstart (event) {
      this.id = Date.now()
      event.dataTransfer.setData("Text", event.target.id);
    },
    dragend (event) {
      console.log(this.$refs.line);
    }
  }
}
</script>

<style scoped>
.left-item {
  width: 35px;
  height: 35px;
  border: 2px solid black;
  border-radius: 50%;
}
</style>