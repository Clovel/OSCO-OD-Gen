const fs = require('fs');
const {dialog} = require('electron');

let configFile = './app/config.json';
let mandatoryConfigFields = [
    "backEndExe",
    "backEndLibDir",
    "backEndDynLibs",
    "backEndStatLibs",
    "odFileName",
    "backEndPort",
    "backEndAddr"
];

function checkConfigurationFile() {
    var lConfig = JSON.parse(fs.readFileSync(configFile, 'utf8'));
    var lResult = true;
    var lMissingFields = [];

    console.log("[INFO ] Checking configuration file : " + configFile);

    for(i = 0; i < mandatoryConfigFields.length; i++) {
        if(!lConfig.hasOwnProperty(mandatoryConfigFields[i])) {
            console.log("[ERROR] Configuration file field missing : " + mandatoryConfigFields[i]);
            lMissingFields.push(mandatoryConfigFields[i]);
            lResult = false;
        }
    }

    if(!lResult) {
        const lOptions = {
            type: 'error',
            buttons: ['Exit'],
            defaultId: 2,
            title: 'Configuration check error',
            message: '[ERROR] The configuration is invalid',
            detail: 'Missing fields : ' + lMissingFields
        };

        dialog.showMessageBoxSync(null, lOptions, (response) => {
            console.log(response);
        });

        return lResult;
    }

    /* Check the executable file */
    if(fs.existsSync(lConfig.backEndExe)) {
        const lExeStat = fs.statSync(lConfig.backEndExe);
        /* Check if the file is indeed a file */
        if(lExeStat.isFile()) {
            /* Check if file is executable */
            const lExeMode = lExeStat.mode;
            console.log("[DEBUG] lExeMode = " + '0' + (lExeMode & 0777).toString(8));
            if(0 != 00100 & lExeMode) {
                /* We (the owner) have exec rights */
            } else {
                /* File is not executable */

                const lOptions = {
                    type: 'error',
                    buttons: ['Exit'],
                    defaultId: 2,
                    title: 'Back-end executable file error',
                    message: '[ERROR] Back-end program is not executable',
                    detail: 'File mode (Unix style) : ' + (lExeMode & 0777).toString(8)
                };
        
                dialog.showMessageBoxSync(null, lOptions, (response) => {
                    console.log(response);
                });

                return false;
            }
        } else {
            const lOptions = {
                type: 'error',
                buttons: ['Exit'],
                defaultId: 2,
                title: 'Back-end executable file error',
                message: '[ERROR] The configuration is invalid',
                detail: 'Back-end executable file isn\'t really a file.'
            };

            dialog.showMessageBoxSync(null, lOptions, (response) => {
                console.log(response);
            });

            return false;
        }
    } else {
        const lOptions = {
            type: 'error',
            buttons: ['Exit'],
            defaultId: 2,
            title: 'Back-end executable file error',
            message: '[ERROR] The configuration is invalid',
            detail: 'Back-end executable file doesn\'t exist.'
        };

        dialog.showMessageBoxSync(null, lOptions, (response) => {
            console.log(response);
        });

        return false;
    }

    /* Check library directory path & contents */
    if(fs.existsSync(lConfig.backEndLibDir)) {
        /* Check if the directory is indeed a directory */
        const lDirStat = fs.statSync(lConfig.backEndLibDir);
        if(lDirStat.isDirectory()) {
            const lLibDirContents = fs.readdirSync(lConfig.backEndLibDir);

            /* TODO : Check if in Windows, there is a "lib" prefix */
            const lExpectedDynLibs = [
                "libOSCO-OD-Gen",
                "libRESTServer",
                "libinitools"
            ];

            const lExpectedStatLibs = [
            ];

            const lMissingLibs = [
            ];

            const lDynLibExtension = () => {
                if('darwin' == process.platform) {
                    return '.dylib'
                } else if ('linux' == process.platform) {
                    return '.so'
                } else if ('win32' == process.platform) {
                    return '.dll';
                }
            };

            const lStatLibExtension = () => {
                if('darwin' == process.platform) {
                    return '.a'
                } else if ('linux' == process.platform) {
                    return '.a'
                } else if ('win32' == process.platform) {
                    return '.lib';
                }
            };

            /* Check if the expected dynamic libraries are here */
            for(i = 0; i < lExpectedDynLibs.length; i++) {
                if(!lLibDirContents.includes(lExpectedDynLibs[i] + lDynLibExtension())) {
                    console.log("[ERROR] Missing dynamic lib : " + lExpectedDynLibs[i]);
                    lMissingLibs.push(lExpectedDynLibs[i]);
                    lResult = false;
                }
            }

            /* Check if the expected static libraries are here */
            for(i = 0; i < lExpectedStatLibs.length; i++) {
                if(!lLibDirContents.includes(lExpectedStatLibs[i] + lStatLibExtension())) {
                    console.log("[ERROR] Missing static lib : " + lExpectedStatLibs[i]);
                    lMissingLibs.push(lExpectedStatLibs[i]);
                    lResult = false;
                }
            }

            if(!lResult) {
                const lOptions = {
                    type: 'error',
                    buttons: ['Exit'],
                    defaultId: 2,
                    title: 'Back-end library error',
                    message: '[ERROR] The configuration is invalid',
                    detail: 'Back-end libraries are missing : ' + lMissingLibs
                };

                dialog.showMessageBoxSync(null, lOptions, (response) => {
                    console.log(response);
                });

                return false;
            }
        }
    }

    /* Check the back-end port */
    lConfig.backEndPort = parseInt(lConfig.backEndPort, 10)
    if(lConfig.backEndPort === parseInt(lConfig.backEndPort, 10)) {
        if(1024 <= lConfig.backEndPort) {
            /* Nothing to do */
        } else {
            const lOptions = {
                type: 'error',
                buttons: ['Exit'],
                defaultId: 2,
                title: 'Back-end port error',
                message: '[ERROR] The configuration is invalid',
                detail: 'Back-end port is under 1024 : ' + lConfig.backEndPort
            };
        
            dialog.showMessageBoxSync(null, lOptions, (response) => {
                console.log(response);
            });

            return false;
        }
    } else {
        const lOptions = {
            type: 'error',
            buttons: ['Exit'],
            defaultId: 2,
            title: 'Back-end port error',
            message: '[ERROR] The configuration is invalid',
            detail: 'Back-end port is not a number : ' + lConfig.backEndPort
        };
    
        dialog.showMessageBoxSync(null, lOptions, (response) => {
            console.log(response);
        });

        return false;
    }

    /* Check the backEndAddr */
    /* TODO */

    return lResult;
}

module.exports.check = checkConfigurationFile;
