const {ipcMain} = require('electron')
const backEndLauncher = require('./../BackEndLauncher/BackEndLauncher.js')

ipcMain.on('LaunchBackEnd', () => {
    console.log('[DEBUG] IPC signal received by main process');
    console.log('        Launching back-end');
    backEndLauncher.launchBackEnd();
});

ipcMain.on('home', () => {
    console.log('[DEBUG] IPC signal received by main process');
    console.log('        home');
});

ipcMain.on('Generate-C-code', () => {
    console.log('[DEBUG] IPC signal received by main process');
    console.log('        Generate-C-code');
});

ipcMain.on('Generate-OD-description-file', () => {
    console.log('[DEBUG] IPC signal received by main process');
    console.log('        Generate-OD-description-file');
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
