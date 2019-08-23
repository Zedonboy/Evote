<template>
  <div class="take-screen valign-wrapper">
    <div class="container">
      <div class="row">
        <div class="col s4"></div>
        <div class="col s4 flex-center-horizontal">
          <p class="center-align">
            <img class="scanning-icon scanning-animation" src="assets/img/face-scan.png" />
          </p>
          <video id="video"></video>
          <p class="center-align">
            <a @click="start_scan" class="btn">Start Scanning</a>
          </p>
        </div>
      </div>
      <div class="col s4"></div>
    </div>
  </div>
</template>
<script>
import addon from "../../addon/index";
import takephoto from "./takePhoto.vue";
import fs from "fs";
export default {
  mixins: [takephoto],
  methods: {
    start_scan() {
      var video = document.getElementById("video");
      var canvas = document.createElement("canvas");
      canvas.setAttribute("height", video.height);
      var ctx = canvas.getContext("2d");
      ctx.drawImage(video, 0, 0, video.width, video.height);
      var img = ctx.getImageData(video.width / 8, 0, video.width, video.height);
      var imgObject = {
        height: img.height,
        width: img.width,
        pixelArray: img.data
      };
      fs.writeFileSync('img.json', JSON.stringify(imgObject))
      addon
        .getFace(imgObject)
        .then(face => {
          var imgdata = new ImageData(face.pixelArray, face.width, face.height);
          this.$store.commit("setFace", imgdata);
          this.destroy_Cam()
          this.$router.push("/login/barcode");
        })
        .catch(e => {
          UIkit.notification("Still Cant get Your Face, try again", {
            status: "danger"
          });
        });
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