const child  = require('child_process');
const fs     = require('fs');

let backEnd;

function launchBackEnd() {
    let backEndExe;
    let backEndLibDir;
    let backEndPort;
    let edsFile;

    var lConfig = JSON.parse(fs.readFileSync('./src/config/config.json', 'utf8'));

    /* Set the configuration variables */
    backEndExe    = lConfig.backEndExe;
    backEndPort   = lConfig.backEndPort;
    backEndLibDir = lConfig.backEndLibDir;
    edsFile       = lConfig.odFileName;


    console.log('backEndExe    : ' + backEndExe    + ' (' + typeof(backEndExe) + ')');
    console.log('backEndLibDir : ' + backEndLibDir + ' (' + typeof(backEndLibDir) + ')');
    console.log('backEndPort   : ' + backEndPort   + ' (' + typeof(backEndPort) + ')');
    console.log('edsFile       : ' + edsFile       + ' (' + typeof(edsFile) + ')');

    var lEnv = Object.create(process.env);
    lEnv.LD_LIBRARY_PATH = backEndLibDir;

    var lParameters = [backEndPort, edsFile];
    console.log('[INFO ] Launching back-end :' + backEndExe + ' ' + backEndPort + ' ' + edsFile);
    backEnd = child.spawn(backEndExe, lParameters, { env: lEnv }, function(error, stdout, stderr) {
        if(error) {
            console.log(error);
            return;
        }

        console.log(stdout);
        console.log(stderr);
    });

    backEnd.stdout.on('data', function(data) {
        console.log('[B-END] stdout: ' + data.toString('utf-8'));
    });
    
    backEnd.stderr.on('data', function(data) {
        console.log('[B-END] stderr: ' + data.toString('utf8'));
    });
    
    backEnd.on('exit', function(code) {
        console.log('[B-END] child process exited with code ' + code.toString('utf-8'));
    });

    return;
}

module.exports.launchBackEnd = launchBackEnd;
