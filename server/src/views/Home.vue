<template>
  <div class="home">
    <div class="columns is-mobile">
      <div class="column">
        <button class="button is-dark is-square">
          <b-icon icon="bell" size="is-large"> </b-icon>
        </button>
      </div>
      <div class="column">
        <button class="button is-info is-square">
          <b-icon icon="bell" size="is-large"> </b-icon>
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
// @ is an alias to /src

export default {
  name: 'Home',
  components: {},
  data: () => {
    return {
      conrols: [
        {
          name: '',
          title: '',
          icon: '',
        },
      ],
    }
  },

  methods: {
    getRandomColor() {
      return 'is-primary'
    },
  },
}
</script>
