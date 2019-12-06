# equipment-whitelist

> A Vue.js project

## Build Setup

``` bash
# install dependencies
npm install

# serve with hot reload at localhost:8080
npm run dev

# build for production with minification
npm run build

# build for production and view the bundle analyzer report
npm run build --report
```

For a detailed explanation on how things work, check out the [guide](http://vuejs-templates.github.io/webpack/) and [docs for vue-loader](http://vuejs.github.io/vue-loader).


# 打包的方法


>1.打开main.js 把 ``` import './plugins/element'```  注释掉

>2.打开index.html 把下面的注释开启
```
<!--<script src="https://cdn.bootcss.com/xlsx/0.14.3/xlsx.full.min.js"></script>-->
<!--<script src="https://cdn.bootcss.com/axios/0.19.0/axios.min.js"></script>-->
<!--<script src="https://cdn.bootcss.com/vue/2.6.10/vue.min.js"></script>-->
<!--<script src="https://cdn.bootcss.com/vue-router/3.0.1/vue-router.min.js"></script>-->
<!--<script src="https://cdn.bootcss.com/vuex/3.1.1/vuex.min.js"></script>-->
<!--<script src="https://unpkg.com/element-ui/lib/index.js"></script>-->
```
>3.打开build文件夹，打开webpack.base.conf.js开启下面的注释
````
 externals: {
    // 'vue': 'Vue',
    // 'vuex': 'Vuex',
    // 'vue-router': 'VueRouter',
    // 'xlsx': 'XLSX',
    // 'axios': 'axios',
    // 'element': 'element-ui',
  },
````
>4.出版本时打开index.html，根据实际版本修改```console.info('4002-versions is v01.19.09.03_beta(前端)')``

>5.在控制台执行 npm run build 命令，生成的打包文件存在whiteList文件夹中

