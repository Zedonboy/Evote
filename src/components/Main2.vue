<template>
  <div class="row">
    <div class="col s2"></div>
    <div class="col s10">
      <div class="row">
        <div class="col s12 valign-wrapper searchBoxContainer">
          <div class="col s2"></div>
          <div class="card-panel col s8">
            <div class="input-field col s12">
              <input placeholder="Search" id="first_name" type="text" class="validate">
            </div>
          </div>
          <div class="col s2"></div>
        </div>
        <div class="col s12">
          <div class="row">
            <div class="col s4" v-for="item in electionItems">
              <CandidatesCard :candidate="item"></CandidatesCard>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
<style>
.searchBoxContainer {
  height: 200px;
}
</style>
<script>
import Evote from "../util/Evote"
import CandidatesCard from "./Candidate.vue";
export default {
  data() {
    return {
      electionItems : ["Senator Election", "Presidential Election", "Gubernatorial Election", "House of Assembly"]
    };
  },
  components: { CandidatesCard },
  mounted () {
    let evote = new Evote();
    evote.getElections().then(resp => {
      if(resp.status == 200){
        this.electionItems = resp.data
      }
    })
  }
};
</script>
