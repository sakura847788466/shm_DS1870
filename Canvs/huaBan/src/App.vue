<template>
  <div id="app">
    <Header/>
    <router-view/>
  </div>
</template>

<script>
  import Header from "./components/Header/Header";
  export default {
    name: "App",
    data() {
      return {}
    },
    methods: {},
    components: {Header},
    props: {}

  }
</script>

<style>
  #app{
    height: 100%;
  }

</style>