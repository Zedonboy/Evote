import VueRouter from "vue-router"
import Vue from "vue"
import PageOne from "../components/PageOne.vue"
import Create from "../components/Create.vue"
import Login from "../components/Login.vue"
import takePhoto from "../components/takePhoto.vue"
import form from "../components/form.vue"
import fingerPrint from "../components/fingerPrint.vue"
import success from "../components/Success.vue"
import facescanner from "../components/Facescanner.vue"
import fingerprint from "../components/fingerPrint.vue"
import barcodescanner from "../components/BarcodeScanner.vue"
import processing from "../components/Processing.vue"
import main from "../components/Main.vue"
import main_t from "../components/Main2.vue"
import test from "../components/test.vue"
Vue.use(VueRouter)

export default new VueRouter({
    routes : [
        {
            // change it back to PageOne
            path : "/",
            component : PageOne//main
        },
        {
            path : "/create",
            component : Create,
            children : [
                {
                    path : "",
                    component : takePhoto
                },
                {
                    path : "form",
                    name : "form",
                    component : form
                },
                {
                    path : "fingerPrint",
                    component : fingerPrint
                },
                {
                    path : "success",
                    component : success
                }
            ]
        },
        {
            path : "/login",
            component : Login,
            children : [
                {
                    path : "",
                    component : facescanner
                },
                {
                    path : "barcode",
                    component : barcodescanner,
                },
                {
                    path : "finger",
                    component : fingerprint
                },
                {
                    path : "identifying",
                    component : processing
                }
            ]
        },

        {
            path : "/main",
            component : main
        },
        {
            path : "/candidates",
            component : main_t
        }
    ]
})