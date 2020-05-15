# Electron Screenshot

Electron/Node module for taking screenshots from the current device context. Simply call ```takeScreenshot``` and the return value is the base64 encoded png value of the screen. Platforms currently supported and working are:

- Windows
- macOS

Support for Linux is under development.

The module uses native code bindings for more performant output of base64 encoded screenshots, see below for usage.

## Usage
```javascript
const electronScreenshot = require('electron-screenshot');

let base64 = electronScreenshot.takeScreenshot();
```

It's that simple!