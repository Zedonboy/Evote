<template>
  <div class="take-screen valign-wrapper">
    <div class="container">
      <div class="row">
        <div class="col s2"></div>
        <div class="col s8">
          <div class="card-panel blue-grey lighten-5 center-align">
            <p class="flow-text" v-text="message"></p>
            <p class="flow-text" v-if="showPleaseWait">Please wait</p>
            <div v-if="showPleaseWait" class="progress">
              <div class="indeterminate"></div>
            </div>
            <div v-if="!showPleaseWait">
              <a class="btn" @click="authing">Retry</a>
            </div>
          </div>
        </div>
        <div class="col s2"></div>
      </div>
    </div>
  </div>
</template>
<script>
import Evote from "../util/Evote";
import { setTimeout, clearInterval } from "timers";
export default {
  data() {
    return {
      showPleaseWait: true,
      message: "Systems is trying to identify you"
    };
  },
  methods: {
    popback() {
      this.$router.pop();
    },

    authing() {
      this.showPleaseWait = true
      var canvas = document.createElement("canvas");
      let ctx = canvas.getContext("2d");
      ctx.putImageData(this.$store.state.faceImageData, 0, 0);
      canvas.toBlob(blob => {
        var evoteApi = new Evote();
        evoteApi
          .authenticateUserAsync(blob, this.$store.state.userIdFromBarcode)
          .then(resp => {
            if (resp.status == 200) {
              this.$store.commit("setUser", resp.data);
              this.$router.push("/main");
            } else {
              this.showPleaseWait = false;
              this.message = "Our Systems couldn't identify you";
            }
          })
          .catch(e => {
            this.showPleaseWait = false;
            this.message = "Error trying to connect to server";
          });
      }, "image/png");
    }
  },
  mounted() {
    this.authing();
  }
};
</script>

