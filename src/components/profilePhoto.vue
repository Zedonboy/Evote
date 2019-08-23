<template>
<div class="container col s12">
    <p class="center-align"><img id="profile" class="profile-photo center-align"/></p>
</div>
</template>
<script>
export default {
    mounted () {
        var canvas = document.createElement('canvas');
        canvas.width = 250;
        canvas.height = 250;
        var img = document.getElementById("profile")
        var ctx = canvas.getContext("2d");
        ctx.putImageData(this.$store.state.imageData ? this.$store.state.imageData : new ImageData(20, 20), 0, 0);
        img.src = canvas.toDataURL("image/png");
        
    }
}
</script>

<style>
.profile-photo {
    max-width: 50%;
    max-height: 100%;
    border-radius: 50%
}
</style>
