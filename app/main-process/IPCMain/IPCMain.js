const {ipcMain} = require('electron');
const BackEnd = require('./../BackEndManager/BackEndManager');

ipcMain.on('LaunchBackEnd', () => {
    console.log('[DEBUG] IPC signal received by main process');
    console.log('        Launching back-end');
    BackEnd.launch();
});

ipcMain.on('open-od', () => {
    console.log('[DEBUG] IPC signal received by main process');
    console.log('        open-od');
});

ipcMain.on('Generate-C-code', () => {
    console.log('[DEBUG] IPC signal received by main process');
    console.log('        Generate-C-code');
});

ipcMain.on('Generate-OD-description-file', () => {
    console.log('[DEBUG] IPC signal received by main process');
    console.log('        Generate-OD-description-file');
});

ipcMain.on('GetODJSON', () => {
    console.log('[DEBUG] IPC signal received by main process');
    console.log('        GetODJSON');

    /* Send request to the back-end */
    return BackEnd.getODJSON('IO-Example');
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
