{
  "targets": [
    {
      "target_name": "addon",
      "include_dirs":[
          "<!@(node -p \"require('node-addon-api').include\")",
              "include/"
      ],
      "libraries" : [
			  "<!@(node ./lib.js)"
      ],
      'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
      "sources": [ "nodeInterface.cc", "dataholder.cc", "main.cc"],
      "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ]
    }
  ]
}