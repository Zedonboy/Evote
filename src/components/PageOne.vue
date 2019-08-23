<template>
    <div class="ev-flex take-screen">
      <div id="particles-js" class="particle-screen"></div>
  <!-- ################################################################################################ -->
  
  <!-- ################################################################################################ -->
  <!-- ################################################################################################ -->
  <!-- ################################################################################################ -->
  <transition>
    
  </transition>
  <section id="pageintro" class="hoc clear elevate-1">
    <div> 
      <!-- ################################################################################################ -->
      <p class="center-align typewrite"><h2 class="heading blue-grey lighten-5 typewriter" style="margin-bottom:0">Nigerian E-Voting Software </h2></p>
      <p class="center-align blue-grey lighten-5">Tired of staying in a long Que :), Then use this Innovation for your citizens, No Rigging and No foul play</p>
      <p class="center-align"><router-link to="/login"><a class="btn" href="#">Cast Vote</a></router-link> <router-link to="/create"><a class="btn" href="#">Register</a></router-link></p>
      <!-- ################################################################################################ -->
    </div>
  </section>
  <!-- ################################################################################################ -->
</div>
</template>
<script>
export default {
  mounted () {
    if (document.getElementById("particles-js")) {
      particlesJS.load(
        "particles-js",
        "assets/json/particles.json",
        function() {
          console.log("callback - particles.js config loaded");
        }
      );
    }

  }
}
</script>

<style>
.elevate-1 {
  z-index: 1;
}
.ev-flex {
  display: flex;
  align-items: center;
  justify-content: center;
}
.typewriter {
  overflow: hidden; /* Ensures the content is not revealed until the animation */
  border-right: .15em solid orange; /* The typwriter cursor */
  white-space: nowrap; /* Keeps the content on a single line */
  margin: 0 auto; /* Gives that scrolling effect as the typing happens */
  letter-spacing: .15em; /* Adjust as needed */
  animation: 
    typing 3.5s steps(40, end),
    blink-caret .75s step-end infinite;
}

/* The typing effect */
@keyframes typing {
  from { width: 0 }
  to { width: 100% }
}

/* The typewriter cursor effect */
@keyframes blink-caret {
  from, to { border-color: transparent }
  50% { border-color: orange; }
}
</style>

