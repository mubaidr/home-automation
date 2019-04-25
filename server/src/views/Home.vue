<template>
  <div class="home">
    <div class="columns is-mobile">
      <div class="column">
        <button
          class="button is-square"
          :class="getRandomColor()"
          @click="toggleBulb"
        >
          <template v-if="status.bulb">
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
        <button
          class="button is-square"
          :class="getRandomColor()"
          @click="toggleDoor"
        >
          <template v-if="status.door">
            <b-icon icon="door-open" size="is-large"></b-icon>
            <span>Close Door</span>
          </template>
          <template v-else>
            <b-icon icon="door-closed" size="is-large"></b-icon>
            <span>Open Door</span>
          </template>
        </button>
      </div>
    </div>
    {{ this.$data }}
  </div>
</template>

<script>
import axios from 'axios'

export default {
  name: 'Home',
  data: () => {
    return {
      server: 'http://192.168.10.222',
      status: {
        bulb: false,
        door: false,
      },
    }
  },

  created() {
    axios
      .get(`${this.server}`)
      .then(res => {
        console.log(res.data)
        this.$set(this, 'status', res.data)
      })
      .catch(err => {
        console.log(err)
      })
  },

  methods: {
    getRandomColor() {
      const items = [
        'is-primary',
        'is-warning',
        'is-danger',
        'is-success',
        'is-dark',
      ]
      return items[Math.floor(Math.random() * items.length)]
    },

    toggleBulb() {
      axios
        .get(`${this.server}/light`)
        .then(res => {
          console.log(res.data)
          this.$set(this, 'status', res.data)
        })
        .catch(err => {
          console.log(err)
        })
    },

    toggleDoor() {
      axios
        .get(`${this.server}/door`)
        .then(res => {
          console.log(res.data)
          this.$set(this, 'status', res.data)
        })
        .catch(err => {
          console.log(err)
        })
    },
  },
}
</script>
