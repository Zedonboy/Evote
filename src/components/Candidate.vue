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
        <button @click="vote" class="btn">Vote</button>
        <i class="material-icons right">close</i>
      </span>
    </div>
  </div>
</template>
<script>
import Evote from "../util/Evote";
export default {
  props: ["candidate"],
  data() {
    return {
      showText: this.candidate.Name + " " + this.candidate.politicalParty
    };
  },
  methods: {
    vote() {
      var evote = new Evote();
      evote
        .vote(this.$store.state.user.id, this.candidate.Id, this.candidate.electiontype)
        .then(resp => {
          if (resp.status == 200) {
            UIkit.notification("Your Vote Was Successfull", {status : 'success'});
          } else if (resp.status > 400){
            UIkit.notification(resp.data.message, {status : 'danger'})
          }
        })
        .catch();
    }
  }
};
</script>