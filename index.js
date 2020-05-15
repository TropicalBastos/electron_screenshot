//index.js
const electronScreenshotNative = require('./build/Release/electron-screenshot.node');

const electronScreenshot = {

    /**
     * Take a screenshot of the current screen
     * @return {String} Base64 encoded png image of the screen buffer
     */
    takeScreenshot: function() {
        return electronScreenshotNative.takeScreenshot();
    }

}

module.exports = electronScreenshot;