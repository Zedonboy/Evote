<template>
  <img />
</template>
<script>
import fs from "fs";
export default {
  mounted() {
    var content = fs.readFileSync("addon/imgA.json", "utf8");
    var imgdata = JSON.parse(content);
    let pixelData = [];
    for (const key in imgdata.pixelArray) {
      pixelData.push(parseInt(imgdata.pixelArray[key]));
    }
    var canvasImgData = new ImageData(new Uint8ClampedArray(pixelData), imgdata.width, imgdata.height)
    var canvas = document.createElement("canvas")
    var ctx = canvas.getContext("2d")
    ctx.putImageData(canvasImgData,0,0)
    debugger
    var img = document.getElementsByTagName("img")[0];
    img.src = canvas.toDataURL()
  }
};
</script>
