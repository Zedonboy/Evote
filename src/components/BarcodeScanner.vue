<template>
  <div class="take-screen valign-wrapper">
    <div class="container">
      <div class="row">
        <div class="col s4"></div>
        <div class="col s4 flex-center-horizontal">
          <!-- <transition >
            <p v-if="showVideo" class="center-align">
              <img class="scanning-icon scanning-animation" src="assets/img/eye.png" />
            </p>
            <video v-if="showVideo" id="video"></video>
            <div v-else class="card-panel col s8">
              <div class="input-field col s12">
                <input @keyup.enter="saveVoterNumber" placeholder="Press Enter after" v-model="userID" type="text" class="validate" />
              </div>
            </div>
          </transition> -->
          <div class="card-panel col s12">
              <div class="input-field col s12">
                <input @keyup.enter="saveVoterNumber" placeholder="Press Enter after" v-model="userID" type="text" class="validate" />
              </div>
            </div>
          <!-- <p class="center-align">
            <a @click="start_scan" class="btn">Start Scanning</a>
          </p>
          <p class="center-align">
            <a @click="start_scan" class="btn">Use Registration Number</a>
          </p> -->
        </div>
      </div>
      <div class="col s4"></div>
    </div>
  </div>
</template>
<script>
import takephoto from "./takePhoto.vue";
export default {
  //mixins: [takephoto],
  data() {
    return {
      showVideo: true,
      userID : ""
    };
  },
  methods : {
    saveVoterNumber (){
      console.log("saving")
      if(this.userID.length == 0) return
      this.$store.commit("setuserIdFromBarcode", this.userID)
      this.$router.push("/login/identifying")
    }
  }
};
</script>

<style>
.scanning-icon {
  max-width: 100px;
  max-height: 100px;
}
.scanning-animation {
  animation: blinking 1.5s ease-in-out infinite;
}
.card-image video {
  width: 100%;
  max-height: 80%;
  max-width: 100%;
  overflow: hidden;
}

@keyframes blinking {
  from {
    opacity: 0.3;
  }

  to {
    opacity: 0.3;
  }

  20% {
    opacity: 0.6;
  }

  50% {
    opacity: 0.9;
  }

  80% {
    opacity: 0.6;
  }
}
</style>
