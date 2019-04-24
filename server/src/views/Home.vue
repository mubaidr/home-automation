<template>
  <div class="home">
    <div class="columns is-mobile">
      <div class="column">
        <button class="button is-dark is-square" @click="toggleBulb">
          <template v-if="bulbOn">
            <b-icon icon="lightbulb" size="is-large"></b-icon>
            <span>Turn Off</span>
          </template>
          <template v-else>
            <b-icon icon="lightbulb-outline" size="is-large"></b-icon>
            <span>Turn On</span>
          </template>
        </button>
      </div>
      <div class="column">
        <button class="button is-info is-square" @click="toggleDoor">
          <template v-if="bulbOn">
            <b-icon icon="door-open" size="is-large"></b-icon>
            <span>Close Door</span>
          </template>
          <template v-else>
            <b-icon icon="door-closed" size="is-large"></b-icon>
            <span>Open Door</span>
          </template>
        </button>
      </div>
      <div class="column">
        <button class="button is-primary is-square">
          <b-icon icon="bell" size="is-large"> </b-icon>
        </button>
      </div>
    </div>
    <div class="columns is-mobile">
      <div class="column">
        <button class="button is-success is-square">
          <b-icon icon="bell" size="is-large"> </b-icon>
        </button>
      </div>
      <div class="column">
        <button class="button is-warning is-square">
          <b-icon icon="bell" size="is-large"> </b-icon>
        </button>
      </div>
      <div class="column">
        <button class="button is-danger is-square">
          <b-icon icon="bell" size="is-large"> </b-icon>
        </button>
      </div>
    </div>
  </div>
</template>

<script>
import axios from 'axios'

// @ is an alias to /src

export default {
  name: 'Home',
  components: {},
  data: () => {
    return {
      bulbOn: false,
      doorOpen: false,
    }
  },

  methods: {
    getRandomColor() {
      return 'is-primary'
    },

    toggleBulb() {
      axios
        .get('http://192.168.10.222/light')
        .then(res => {
          console.log(res)
          this.bulbOn = !this.bulbOn
        })
        .catch(err => {
          console.log(err)
        })
    },

    toggleDoor() {
      axios
        .get('http://192.168.10.222/door')
        .then(res => {
          console.log(res)
          this.doorOpen = !this.doorOpen
        })
        .catch(err => {
          console.log(err)
        })
    },
  },
}
</script>
