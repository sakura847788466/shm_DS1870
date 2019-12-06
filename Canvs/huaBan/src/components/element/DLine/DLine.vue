<template>
  <div id="line">
    <div :id="id"
         style="position: absolute;width: 100px; height: 10px;background-color: #000;"
         draggable="true"
         @dragstart="dragstart"
         @dragend="dragend"></div>
  </div>
</template>

<script>
export default {
  name: "DLine",
  data () {
    return {
      id: Date.now() + '',
      move_x: 0,
      move_y: 0,
    }
  },
  methods: {
    dragstart (event) {
      event.dataTransfer.effectAllowed = "move";
      event.dataTransfer.setData("Text", event.target.id);
      event.dataTransfer.setDragImage(event.target, 0, 0);
      console.log(event)
    },
    dragend () {
      this.createLine()
    },
    createLine () {
      const id = Date.now() + ''
      const line = document.querySelector('#line')
      const len = line.childNodes.length
      if (len === 0) {
        const div = document.createElement('div')
        console.log(div.style)
        div.style.position = 'absolute'
        div.style.width = 100 + 'px'
        div.style.height = 10 + 'px'
        div.style.backgroundColor = '#000'

        div.draggable = true
        div.id = id
        div.addEventListener('dragstart', this.dragstart)
        div.addEventListener('dragend', this.dragend)
        line.appendChild(div)
      }
    },
  },
  components: {},
  props: {}

}
</script>

<style scoped>
.left-item {
  /*flex: 1;*/
  /*border: 1px solid #ddd;*/
}
</style>