<template>
  <div class="take-screen valign-wrapper">
    <div class="container">
      <div class="row">
        <div class="col s4"></div>
        <div class="col s4 flex-center-horizontal">
              <p class="center-align"><img class="scanning-icon" src="assets/img/finger.png"/></p>
              <p class="center-align"><a id="scanbutton" class="btn">Get finger Print</a></p>
          </div>
        </div>
        <div class="col s4"></div>
      </div>
    </div>
</template>
<script>
export default {
  mounted() {
  }
};
</script>

<style>
.scanning-icon {
  max-width: 200px;
  max-height: 200px;
}
.scanning-animation {
  animation: blinking 1.5s ease-in-out infinite ;
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

  50%{
    opacity: 0.9;
  }

  80% {
    opacity: 0.6;
  }
}
</style>
