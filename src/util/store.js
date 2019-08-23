import Vuex from "vuex"
import Vue from "vue"

Vue.use(Vuex)

export default new Vuex.Store({
    state : {
        imageData : new ImageData(new Uint8ClampedArray([255,255,255,255]), 1, 1),
        faceImageData : new ImageData(new Uint8ClampedArray([255,255,255,255]), 1, 1),
        userIdFromBarcode : null,
        candidateArray : [],
        user : null
    },

    mutations : {
        setImageData : (state, imgdata) => state.imageData = imgdata,
        setFace : (state, imgdata) => state.faceImageData = imgdata,
        setCandidates : (state, arr) => state.candidateArray = arr,
        setUser : (state, user) => state.user = user,
        setuserIdFromBarcode : (state, id) => state.userIdFromBarcode = id
    }
})