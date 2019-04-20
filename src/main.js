import Vue from 'vue'
import App from './App.vue'
import router from './router'

import 'buefy/dist/buefy.css'
import '@mdi/font/css/materialdesignicons.min.css'

import './registerServiceWorker'
import './assets/main.scss'

import Buefy from 'buefy'

Vue.use(Buefy, {
  defaultTooltipAnimated: true,
})

Vue.config.productionTip = false

new Vue({
  router,
  render: h => h(App),
}).$mount('#app')
