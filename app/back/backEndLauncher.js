const child  = require('child_process');
const config = require('../config.json')

/* Set the back-end's path */
const backEnd     = config.backEnd;
const backEndPort = config.backEndPort;
const edsFile     = config.edsFile;

function launchBackEnd() {
    var lParameters = [backEndPort, edsFile];
    child.execFile(backEnd, lParameters, function(err, data) {
        console.log(err);
        console.log(data.toString());
    });
}
