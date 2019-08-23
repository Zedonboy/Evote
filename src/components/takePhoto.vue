<template>
  <div class="contentarea">
    <div class="photo-heading" id="pageintro">
      <p class="heading">Nigerian E-voting face scan</p>
    </div>
    <div class="camera">
      <video id="video">Video stream not available.</video>
      <button @click="takepicture" id="startbutton">Take photo</button>
    </div>
    <canvas id="canvas"></canvas>
    <div class="output">
      <img id="photo" alt="The screen capture will appear in this box." />
      <a :disabled="!takenPhoto" style="margin-top:45px" class="btn" @click="next_btn">Next</a>
    </div>
  </div>
</template>
<script>
import fs from "fs";
import addon from "../../addon/index";
import { debug } from "util";
export default {
  data() {
    return {
      takenPhoto: false,
      width: 320,
      height: 0,
      streaming: false
    };
  },
  methods: {
    destroy_Cam() {
      var video = document.getElementById("video");
      var stream = video.srcObject;
      var tracks = stream.getTracks();

      for (var i = 0; i < tracks.length; i++) {
        var track = tracks[i];
        track.stop();
      }

      video.srcObject = null;
    },
    next_btn() {
      var photo = document.getElementById("photo");
      var canvas = document.getElementById("canvas");
      var ctx = canvas.getContext("2d");
      var insertedImagdata = ctx.getImageData(
        photo.width / 8,
        0,
        photo.width,
        photo.height
      );
      this.$store.commit("setImageData", insertedImagdata);
      var imgdata = {
        height: insertedImagdata.height,
        width: insertedImagdata.width,
        pixelArray: insertedImagdata.data
      };

      addon
        .getFace(imgdata)
        .then(face => {
          var imageArray = new ImageData(
            face.pixelArray,
            face.width,
            face.height
          );
          this.$store.commit("setFace", imageArray);
          this.destroy_Cam();
          this.$router.push("/create/form");
        })
        .catch(e => {
          UIkit.notification(
            "There error getting user face, recapture with emphasis on the face",
            { status: "danger" }
          );
        });
    },

    setupCam() {
      var video = document.getElementById("video");
      var canvas = document.getElementById("canvas");
      var photo = document.getElementById("photo");
      var width = this.width;
      navigator.mediaDevices
        .getUserMedia({ video: true, audio: false })
        .then(function(stream) {
          video.srcObject = stream;
          video.play();
        })
        .catch(function(err) {
          console.log("An error occurred: " + err);
        });

      video.addEventListener(
        "canplay",
        function(ev) {
          if (!this.streaming) {
            var height = video.videoHeight / (video.videoWidth / width);
            this.height = height;
            video.setAttribute("width", width);
            video.setAttribute("height", height);
            if (canvas) {
              canvas.setAttribute("width", width);
              canvas.setAttribute("height", height);
            }
            this.streaming = true;
          }
        },
        false
      );
    },

    takepicture() {
      this.takenPhoto = true;
      var video = document.getElementById("video");
      var canvas = document.getElementById("canvas");
      var photo = document.getElementById("photo");
      var context = canvas.getContext("2d");
      canvas.width = this.width;
      canvas.height = video.height;
      context.drawImage(video, 0, 0, this.width, video.height);

      var data = canvas.toDataURL("image/png");
      photo.setAttribute("src", data);
    }
  },
  mounted() {
    this.setupCam();
  }
};
</script>

<style>
.photo-heading {
  grid-area: 1/1/2 / span 2;
}
#video {
  border: 1px solid black;
  box-shadow: 2px 2px 3px black;
  width: 320px;
  height: 240px;
}

#photo {
  border: 1px solid black;
  box-shadow: 2px 2px 3px black;
  width: 320px;
  height: 240px;
}

#canvas {
  display: none;
}

.camera {
  width: 340px;
  grid-area: 2/1/3/2;
  place-self: center;
}

.output {
  width: 340px;
  grid-area: 2/2/3/2;
  place-self: center;
}

#startbutton {
  display: block;
  position: relative;
  margin-left: auto;
  margin-right: auto;
  bottom: 32px;
  background-color: rgba(0, 150, 0, 0.5);
  border: 1px solid rgba(255, 255, 255, 0.7);
  box-shadow: 0px 0px 1px 2px rgba(0, 0, 0, 0.2);
  font-size: 14px;
  font-family: "Lucida Grande", "Arial", sans-serif;
  color: rgba(255, 255, 255, 1);
}

.contentarea {
  height: -webkit-fill-available;
  display: grid;
  grid-template-columns: auto auto;
  grid-template-rows: 10% 80% 10%;
}
</style>
