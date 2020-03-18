const {ipcMain} = require('electron')

/* Test IPC signal handling */
const ipc = ipcMain;

ipc.on('test-button-signal', () => {
    console.log('[DEBUG] IPC signal received by main process');
})
