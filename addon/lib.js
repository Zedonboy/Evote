const readline = require("readline");
const win32 = process.platform == "win32";
const {resolvePath} = require("./util")
if(win32){
    const libFilePath = process.env.OPENCV_LIB_DIR
    if(libFilePath){
      console.log(resolvePath(libFilePath, "opencv_imgproc.lib"));
      console.log(resolvePath(libFilePath, "opencv_core.lib"))
      console.log(resolvePath(libFilePath, "opencv_objdectect.lib"))
      return
    }
}

const openlibdir = process.env.OPENCV_LIB_DIR
  ? process.env.OPENCV_LIB_DIR
  : process.env.OPENCV_LIB_DIR

console.log('-L' + openlibdir)
console.log('-lopencv_imgproc')
console.log('-lopencv_core')
console.log('-lopencv_objdetect')
console.log("-lopencv_highgui")
console.log('-Wl,-rpath,' + openlibdir)