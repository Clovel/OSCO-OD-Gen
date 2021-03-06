const {app, BrowserWindow, nativeTheme, ipcMain} = require('electron')
const path = require('path')
const {getDefaultUserDataPath} = require('./AppDataPath/AppDataPath.js')
const configChecker = require('./ConfigChecker/configChecker.js')
const isDev = require("electron-is-dev");

function createWindow() {
    /* Check configuration file */
    if(!configChecker.check()) {
        console.log("[ERROR] Configuration file is invalid");
        process.exit(1);
    }

    /* Create the navigator's window */
    var lWindow = new BrowserWindow({
        width: 900,
        height: 680,
        webPreferences: {
            nodeIntegration: true,
            preload: path.join(__dirname, 'preload.js')
        }
    })

    lWindow.loadURL(
        isDev
        ? "http://localhost:3000"
        : `file://${path.join(__dirname, "../build/index.html")}`
    );

    /* Load the index.html of the application */
    console.log("[DEBUG] App Data path is : " + getDefaultUserDataPath(process.platform))

    /* Open devtools */
    //lWindow.webContents.openDevTools()
}

/* This method will be called when Electron
 * will be initialized and ready to create navigation
 * windows.
 * Some APIs can be used only once this event
 * is emitted. */
app.on('ready', createWindow)

/* Quit when all windows are closed */
app.on('window-all-closed', function () {
    console.log("[DEBUG] Closing window...")
    /* On macOS, it is common for an app and it's menu bar
     * to stay active until the user has explicitly close
     * the app. */
    if(process.platform !== 'darwin') {
        app.quit()
    }
})

app.on('activate', () => {
    /* On macOS, it is common to recreate the app's
     * window when the Dock icon is clicked
     * and no other windows are opened. */
    if(BrowserWindow.getAllWindows().length === 0) {
        createWindow()
    }
})

/* In this file, you can include the rest of 
 * your apps's specific code to the main process.
 * You can also put it in other files 
 * and just include it here */

/* Manage Dark mode themes with the OS's settings */
require('./ThemeHandler/ThemeHandler.js');

/* IPC signal handling */
require('./IPCMain/IPCMain.js');
