<template>
  <div class="take-screen valign-wrapper">
    <div id="particles-js" class="particle-screen"></div>
    <div class="container">
      <div class="row">
          <h2 class="center-align">Account created successfully</h2>
        <div class="col s4"></div>
        <div class="col s4">
          <div class="flexbox">
            <div class="success-panel card-panel center-align blue-grey lighten-5 col s12">
              <img id="profile-print" class="printed-profile" src="assets/img/inec.png">
              <blockquote>Obiukwu Nnadozie Declan</blockquote>
              <svg id="barcode"></svg>
              <div class="row">
                <div class="col s6">
                  <img class="printed-profile" src="assets/img/inec.png">
                </div>
                <div class="col s6">
                  <img class="printed-profile" src="assets/img/coat.png">
                </div>
                <p class="small-text">Registered under section 123 of the electoral act</p>
              </div>
            </div>
          </div>
        </div>
        <div class="col s4"></div>
      </div>
    </div>
  </div>
</template>
<script>
import jsbarcode from "jsbarcode";
export default {
  data () {
    return {
      user : this.$store.state.user
    }
  },
  methods : {
    showProfile () {
      var canvas = document.createElement("canvas")
      var ctx = canvas.getContext("2d");
      var img = document.getElementById("profile-print")
      if (this.$store.state.imageData == null) return;
      ctx.putImageData(this.$store.state.imageData, 0, 0)
      img.src = canvas.toDataURL();
    }
  },
  mounted() {
    if (document.getElementById("particles-js")) {
      particlesJS.load(
        "particles-js",
        "assets/json/particles.json",
        function() {
          console.log("callback - particles.js config loaded");
        }
      );
    }

    this.showProfile();
    jsbarcode("#barcode", user.userID, {
      lineColor: "#222831",
      height: 100
    });
  }
};
</script>

<style>
.small-text {
    font-size: 8px;
}
#barcode {
  max-width: 270px;
}
.printed-profile {
  border-radius: 50%;
  width: 80px;
  height: 80px;
  max-width: 100px;
  max-height: 100px;
}
.success-panel {
  padding: 30px;
  max-width: 300px;
  max-height: 500px;
}
.flexbox {
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
  align-items: center;
}

.particle-screen {
  overflow: hidden;
  position: absolute;
  width: 100%;
  height: 100%;
  max-width: 100%;
  max-height: 100%;
}
.take-screen {
  width: 100%;
  background-color: #222831;
  height: -webkit-fill-available;
}
</style>
