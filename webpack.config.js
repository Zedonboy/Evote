const VueLoaderPlugin = require('vue-loader/lib/plugin')
const path = require("path");
const extractCss = require("mini-css-extract-plugin")

module.exports = {
    entry : "./renderer.js",
    mode: "development",
    target : "node",
    output: {
        filename: 'main.js',
        path: path.resolve(__dirname, 'dist')
    },
   
    module: {
        rules: [
            {
                test: /\.(sass|scss)$/,
                use: [
                  process.env.NODE_ENV !== 'production' ? 'style-loader' : extractCss.loader,
                  'css-loader',
                  'sass-loader'
                ],
              },
            {
                test: /\.node$/,
                use: 'node-loader'
            },
            {
                test: /\.js$/,
                exclude: /node_modules/,
                loader: 'babel-loader'
            },
            {
                test : /\.vue$/,
                exclude : /node_modules/,
                loader : "vue-loader",
                options : {
                    optimizeSSR: false
                }
            },
            {
                test : /\.css/,
                exclude: /node_modules/,
                use : [{
                    loader : extractCss.loader
                },
                'css-loader'
                ]
            }
        ]
    },

    resolve: {
        alias: {
        //   'vue$': 'vue/dist/vue.runtime.min.js', // 'vue/dist/vue.common.js' for webpack 1
        //   'vue-router$': 'vue-router/dist/vue-router.min.js',
        //   'vuex$':"vuex/dist/vuex.min.js"
        'uikit-util': path.resolve(__dirname, 'node_modules/uikit/src/js/util')
        }
      },

    plugins: [
        // make sure to include the plugin!
        new VueLoaderPlugin(),
        new extractCss({
            filename: 'style.css'
        })
      ]
};