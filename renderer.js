// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.
import Vue from "vue"
import "./src/assets/app.scss"
import store from "./src/util/store"
import router from "./src/util/router"
import App from "./src/components/App.vue"
import UIkit from "./src/assets/uikit"
window.UIkit = UIkit;
const app = new Vue({
    el : "#root",
    store,
    router,
    render : h => h(App)
})