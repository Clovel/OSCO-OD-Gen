/* To launch the back-end */
const child = require('child_process');
const fs = require('fs');

/* To make requests to the back-end */
const httpClient = require('http');

/* Back-end class (singleton) */
var BackEnd = function() {
    var configFile = './config.json';

    var backEndExe = null;
    var backEndLibDir = null;
    var backEndPort = null;
    var edsFile = null;

    var isOn = false;

    var launch = () => {
        var lConfig = JSON.parse(fs.readFileSync(configFile, 'utf8'));

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
            isOn = false;
        });

        isOn = true;

        return;
    };

    var _sendRequest = (pRequestPath, pMethod) => {
        switch(pMethod) {
            case 'GET':
            case 'PUT':
            case 'POST':
            case 'DELETE':
                break;
            default:
                console.log("[ERROR] <BackEnd::sendRequest> Unknown method " + pMethod);
                return;
        }

        /* Set up REST request */
        const lRequestOptions = {
            method: pMethod,
            protocol: 'http:',
            hostname: 'localhost',
            port: 4000,
            path: 'OSCO-OD-Gen/' + pRequestPath,
        };

        var lBackEndResponse = '';

        /* Use a promise to send the request.
         * We will be able to wait for the answer */
        return new Promise((pResolve, pReject) => {
            /* Send REST request */
            const lRequest = httpClient.request(lRequestOptions, pResult => {
                pResult.setEncoding('utf8');
                
                /* Data reception event */
                pResult.on('data', (pChunk) => {
                    // console.log('[DEBUG] <BackEnd::sendRequest> Got chunk');
                    // console.log(pChunk);
                    lBackEndResponse = lBackEndResponse + pChunk;
                });
                
                /* Data reception complete event */
                pResult.on('end', () => {
                    //console.log('[ERROR] <BackEnd::sendRequest> Got response : ' + lBackEndResponse);

                    /* Resolve the response */
                    pResolve(lBackEndResponse);
                });
            });
    
            lRequest.on('error', (pError) => {
                console.log('[ERROR] <BackEnd::sendRequest> Got error ' + pError);
                pReject(error);
            });
    
            lRequest.end(() => {
                //console.log('[DEBUG] <BackEnd::sendRequest> Finished sending the request');
            });
        });


    };

    var getODJSON = async (pODName) => {
        // now to program the "usual" way
        // all you need to do is use async functions and await
        // for functions returning promises
        try {
            const lPromise = await _sendRequest(pODName, 'GET');
    
            /* We get a promise from the previous call */

            return lPromise;
        } catch (error) {
            console.error('[DEBUG] <BackEnd::getODJSON> ERROR:');
            console.error(error);
        }
    };

    return {
        launch: launch,
        getODJSON: getODJSON,
    };
}();

module.exports = BackEnd;
