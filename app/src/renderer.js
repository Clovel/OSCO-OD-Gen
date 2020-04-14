// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.

const path = require('path');

/* Paths must be relative to the HTML page that will load this file */
const {getDefaultUserDataPath} = require(path.join(__dirname, '../../common/appdatapath.js'));

console.log('[DEBUG] <renderer.js> Used');
