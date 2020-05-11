//index.js
const electronScreenshot = require('./build/Release/electron-screenshot.node');
electronScreenshot.takeScreenshot();
module.exports = electronScreenshot;