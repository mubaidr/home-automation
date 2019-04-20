import Vue from 'vue'
import App from './App.vue'
import router from './router'
import './registerServiceWorker'

import 'material-design-icons/iconfont/material-icons.css'
import './assets/main.sass'

import Buefy from 'buefy'
import 'buefy/dist/buefy.css'

Vue.use(Buefy, {
  defaultTooltipAnimated: true
})

Vue.config.productionTip = false

new Vue({
  router,
  render: h => h(App)
}).$mount('#app')
