<template>
  <div class="row">
    <div class="col s12">
      <div class="col s3">
        <p class="center-align heading">Biometric Details</p>
        <photo/>
        <div class="col s12 center">
          <a @click="startFingerPrint" class="btn waves-effect waves-light"> Take fingerprint</a>
        </div>
      </div>
      <div class="col s9">
        <h2 class="heading center-align">Evote Registration Form</h2>
        <div class="row">
          <!-- First Name -->
          <div class="input-field col s4">
            <input v-model="user.firstname" id="first_name" type="text" class="validate">
            <label for="first_name">First Name</label>
          </div>
          <!-- Middle Name -->
          <div class="input-field col s4">
            <input v-model="user.middlename" id="middle_name" type="text" class="validate">
            <label for="middle_name">Middle Name</label>
          </div>
          <!-- LAst name -->
          <div class="input-field col s4">
            <input v-model="user.lastname" id="last_name" type="text" class="validate">
            <label for="last_name">Last Name</label>
          </div>
          <!-- State -->
          <div class="input-field col s4">
            <input v-model="user.state" id="state" type="text" class="validate">
            <label for="state">State of Origin</label>
          </div>
          <!-- LGA -->
          <div class="input-field col s4">
            <input v-model="user.lga" id="lga" type="text" class="validate">
            <label for="lga">L.G.A</label>
          </div>

          <!-- State -->
          <div class="input-field col s4">
            <input v-model="user.phoneNo" id="phone_no" type="text" class="validate">
            <label for="phone_no">Phone Number</label>
          </div>
          <!-- LGA -->
          <div class="input-field col s4">
            <input v-model="user.email" id="email" type="text" class="validate">
            <label for="email">Email</label>
          </div>

          <div class="input-field col s4">
            <input v-model="user.address" id="address" type="text" class="validate">
            <label for="address">Address</label>
          </div>
          <!-- date of birth -->
          <div class="input-field col s4">
            <input v-model="user.dob" @click="showDate" type="text" class="datepicker" placeholder="Date of Birth">
          </div>
          <div class="input-field col s4">
            <p>
              <label>
                <input v-model="user.gender" name="male" type="radio" checked>
                <span>Male</span>
              </label>
            </p>
            <p>
              <label>
                <input name="male" type="radio">
                <span>Female</span>
              </label>
            </p>
          </div>
          <!-- date of birth -->
          <div class="input-field col s4">
            <p>
              <label>
                <input type="checkbox">
                <span>By check this box, you abide by the laws guiding voter</span>
              </label>
            </p>
          </div>
        </div>
        <div class="col s12">
          <p class="center-align">
            <a @click="register" class="waves-effect waves-light btn">Register</a>
          </p>
        </div>
        
      </div>
    </div>
  </div>
</template>
<style>
.inec {
  width: 200px;
  height: 200px;
}
.coat {
  max-width: 150px;
  max-height: 150px;
}
</style>

<script>
import addon from "../../addon/index"
import Evoter from "../util/Evote"
import photo from "./profilePhoto.vue";
import Evote from '../util/Evote';
export default {
  data() {
    return {
      datetime: null,
      user : {
        firstname : "",
        middlename : "",
        lga : "",
        state : "",
        dob : "",
        gender : true,
        phoneNo : "",
        address : "",
        email : ""
      }
    };
  },
  components : {photo},
  methods: {
    register () {
      var evote = new Evote("");
      var canvas = document.createElement("canvas");
      let ctx = canvas.getContext("2d")
      ctx.putImageData(this.$store.state.faceImageData, 0, 0)
      canvas.toBlob(faceBlob => {
        ctx.putImageData(this.$store.state.imageData, 0, 0)
        canvas.toBlob(profileBlob => {
            var evote = new Evote();
            this.user.userID = Date.now().toString();
            evote.createUser(this.user, faceBlob, profileBlob).then(resp => {
              if(resp.status == 200){
                this.$store.commit("setUser", this.user);
                this.$router.push("/create/success");
              }

              if(resp.status == 409){
                UIkit.notification("You cannot vote more than once"), {status : 'danger'}
              }
            }).catch(e => {
                UIkit.notification("Cannot Register You, try again", {status : 'danger'});
            })
        })
      })
    },

    showDate() {
      //datetime.open();
    },

    startFingerPrint () {
      const {spawn} = require("child_process");
      var fngrPrnt = spawn("fingerPrintCollector.exe", ["enroll"]);
      fngrPrnt.stdout.on("data", (data) => {
        this.user.templateString = data.toString();
      })
    }
  },
  mounted() {
    var elems = document.querySelectorAll(".datepicker");
    this.datetime = M.Datepicker.init(elems, {});
  }
};
</script>

