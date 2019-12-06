<template>
  <div class="home">
    <Left />
    <div class="right">
      <div class="canvas"
           @drop="drop"
           @dragover="dragover"></div>
      <div class="vline"
           style="left: 1449px; background-color: rgb(0, 144, 255);">
        <i class="iconfont icon-error delVline"
           style="top: 1945px;"></i></div>
    </div>
  </div>
</template>

<script>
import Left from "../Left/Left";

export default {
  name: "Home",
  data () {
    return {
      move_x: 0,
      move_y: 0,
    }
  },
  methods: {
    drop (event) {
      event.preventDefault();
      const id = event.dataTransfer.getData("Text");
      const el = document.getElementById(id)
      this.move_x = event.offsetX
      this.move_y = event.offsetY
      el.style.left = this.move_x + 'px'
      el.style.top = this.move_y + 'px'
      event.target.appendChild(el);
    },
    dragover (event) {
      event.preventDefault();
    },
  },
  components: { Left },
  props: {}

}
</script>

<style scoped>
.home {
  display: flex;
  padding-top: 55px;
  height: 100%;
  background-color: #e5e5e5;
}

.right {
  display: flex;
  justify-content: center;
  align-items: center;
  width: calc(100% - 250px);
  height: 100%;
}

.canvas {
  position: relative;
  width: 1000px;
  height: 500px;
  background-color: #ffffff;
  cursor: crosshair;
}
.vline {
  position: absolute;
  z-index: 100;
  background-clip: content-box;
  top: 0;
  pointer-events: all;
  height: 100%;
  width: 1px;
  padding: 0 4px;
}
</style>