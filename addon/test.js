const addon = require("./build/Debug/addon.node")
const fs = require("fs")
var contents = fs.readFileSync("../img.json", 'utf8')
var imgdata = JSON.parse(contents);
let pixelData = []
for (const key in imgdata.pixelArray) {
    pixelData.push(parseInt(imgdata.pixelArray[key]))
}
imgdata.pixelArray = new Uint8ClampedArray(pixelData);
addon.getFace(imgdata).then(rsl => {
    fs.writeFileSync("imgA.json", JSON.stringify(rsl))
}).catch(e => {
    console.log(e)
})

// console.log(addon.test());