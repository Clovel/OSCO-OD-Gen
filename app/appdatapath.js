//@ts-check
'use strict';

// @ts-ignore
const pkg = require('../package.json');
const path = require('path');
const os = require('os');

/**
 * @param {string} platform
 * @returns {string}
 */
function getAppDataPath(platform) {
    switch (platform) {
        case 'win32': return process.env['OSCO_OD_GEN_APPDATA'] || process.env['APPDATA'] || path.join(process.env['USERPROFILE'], 'AppData', 'Roaming');
        case 'darwin': return process.env['OSCO_OD_GEN_APPDATA'] || path.join(os.homedir(), 'Library', 'Application Support');
        case 'linux': return process.env['OSCO_OD_GEN_APPDATA'] || process.env['XDG_CONFIG_HOME'] || path.join(os.homedir(), '.config');
        default: throw new Error('Platform not supported');
    }
}

/**
 * @param {string} platform
 * @returns {string}
 */
function getDefaultUserDataPath(platform) {
    let lUserDataPath = path.join(getAppDataPath(platform), pkg.name);
    console.log("[DEBUG] UserDataPath is " + lUserDataPath + ", pkg.name = " + pkg.name);
    //return lUserDataPath;
    return "Toto fait du ski !"
}

module.exports = {
    getAppDataPath,
    getDefaultUserDataPath,
};
