const fs = require('fs');
const {dialog} = require('electron');

let configFile = './app/config.json';
let mandatoryConfigFields = [
    "backEndExe",
    "backEndLibDir",
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
    
        dialog.showMessageBox(null, lOptions, (response) => {
            console.log(response);
        });
    }

    return lResult;
}

module.exports.check = checkConfigurationFile;
