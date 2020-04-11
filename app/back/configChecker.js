const fs = require('fs');
const {dialog} = require('electron');

let configFile = './app/config.json';
let mandatoryConfigFields = [
    "backEndExe",
    "backEndLibDir",
    "backEndLibs",
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

    return lResult;
}

module.exports.check = checkConfigurationFile;
