const {app, BrowserWindow} = require('electron')

function createWindow() {
    /* Create the navigator's window */
    let lWindow = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            nodeIntegration: true
        }
    })

    /* Load the index.html of the application */
    lWindow.loadFile('index.html')

    /* Open devtools */
    lWindow = null
}

/* This method will be called when Electron
 * will be initialized and ready to create navigation
 * windows.
 * Some APIs can be used only once this event
 * is emitted. */
app.whenReady().then(createWindow)

/* Quit when all windows are closed */
app.on('window-all-closed', () => {
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
    if(lWindow === null) {
        createWindow
    }
})

/* In this file, you can include the rest of 
 * your apps's specific code to the main process.
 * You can also put it in other files 
 * and just include it here */
