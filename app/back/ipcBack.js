const {ipcMain} = require('electron')
const backEndLauncher = require('./backEndLauncher')

ipcMain.on('test-button-signal', () => {
    console.log('[DEBUG] IPC signal received by main process');
    console.log('        Launching back-end');
    backEndLauncher.launchBackEnd();
});

ipcMain.on('methodCall', async (event, { method, callId, args }) => {
    const result = {
        response: null,
        error: null,
    };

    try {
        result.response = await methods[method](...args);
    }
    catch (e) {
        result.error = e;
    }

    event.reply(`methodReply-${callId}`, result);
});
