//index.js
const electronScreenshot = require('./build/Release/electron-screenshot.node');
let base64 = electronScreenshot.takeScreenshot();
console.log(base64);
module.exports = electronScreenshot;