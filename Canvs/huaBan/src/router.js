import Vue from 'vue'
import Router from 'vue-router'

const Home = () => import('./views/Home/Home.vue')

Vue.use(Router)
const routes = [
  {
    path: '/',
    redirect: '/home'
  },
  {
    path: '/home',
    name: 'home',
    component : Home
  },
  ]
export default new Router({
  mode:'history',
  routes
})
