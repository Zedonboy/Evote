const native_addon = require("../addon/build/Release/addon.node");
module.exports = {
    getFace (imageData) {
        return new Promise((resolve, reject) => {
            native_addon.getFace(imageData).then(data => {
                resolve(data);
            }).catch(e => {
                reject(e);
            })
        })
    }
}