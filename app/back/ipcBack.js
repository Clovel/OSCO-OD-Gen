const {ipcMain} = require('electron')

ipcMain.on('test-button-signal', () => {
    console.log('[DEBUG] IPC signal received by main process');
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
