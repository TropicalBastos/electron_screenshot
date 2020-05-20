# Electron Screenshot

Electron/Node module for taking screenshots from the current device context. Simply call ```takeScreenshot``` and the returned value will be the base64 encoded png value of the screen. Platforms currently supported and working are:

- Windows
- macOS

Support for Linux is under development.

The module uses native code bindings for more performant output of base64 encoded screenshots, see below for usage.

## Installation

```npm install electron-base64-screenshot --save```

## Usage
```javascript
const electronScreenshot = require('electron-base64-screenshot');

let base64 = electronScreenshot.takeScreenshot();
```

It's that simple!

## Note

Because of this being a native module, one would need to call this function in the main process of electron. If you want to take a screenshot as a result of a UI driven event ```ipcRenderer``` and ```ipcMain``` are your best friends.
