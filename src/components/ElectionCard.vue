<template>
    <div style="padding : 15px" class="card">
      <div class="card-image waves-effect waves-block waves-light"></div>
      <div class="card-content">
        <span class="card-title activator grey-text text-darken-4" v-text="showText">
          <i class="material-icons right">more</i>
        </span>
        <p>
          <a href="#">This is a link</a>
        </p>
      </div>
      <div class="card-reveal">
        <span class="card-title grey-text text-darken-4">
          <button @click="getCandidates" class="btn">Start</button>
          <i class="material-icons right">close</i>
        </span>
      </div>
    </div>
</template>
<script>
import Evote from "../util/Evote"
export default {
  props: ["election"],
  data() {
    return {
      electionObj : this.election,
      showText: this.election.name_of_election
    };
  },
  methods : {
    getCandidates () {
      let evote = new Evote();
      evote.getCandidates(electionObj.Id).then(resp => {
        if(resp.status == 200 && resp.data.length > 0){
          this.$store.commit("setCandidates", resp.data);
          this.$router.push("/candidate")
        }
      })
    }
  }
};
</script>
