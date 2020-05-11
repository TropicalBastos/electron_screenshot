{
    "targets": [{
        "target_name": "electron-screenshot",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "src/main.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
        "conditions": [
            [
                "OS=='mac'", {
                "link_settings": {
                    "libraries": [
                        "-framework CoreGraphics",
                        "-framework CoreFoundation",
                        "-framework ImageIO",
                        "-framework Security",
                        "-framework AppKit"
                    ]
                },
                "sources": [
                    "src/main.mm"
                ],
                }
            ]
        ]
    }]
}