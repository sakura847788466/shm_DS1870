<template>
    <div ref="rectangle">
        <div :id="id" class="left-item"  @dragstart="dragstart" @dragend="dragend"></div>
    </div>
</template>

<script>
    export default {
        name: "Rectangle",
        data() {
            return {
                id:''
            }
        },
        methods: {
            dragstart(event){
                this.id = Date.now()
                event.dataTransfer.setData("Text",event.target.id);
            },
            dragend(event){
                console.log(this.$refs.line);
            }
        },
        components: {},
        props: {}
    }
</script>

<style scoped>
    .left-item{
        width: 100px;
        height: 30px;
        border: 2px solid black;
    }
</style>