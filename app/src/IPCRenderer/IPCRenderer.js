const { ipcRenderer } = window.require('electron');

// let callCounter = 0;
// const createCallId = () => callCounter++;

// export const Methods = new Proxy({}, {
//     get: (obj, method) => (...args) => new Promise((resolve, reject) => {
//         const callId = createCallId();

//         ipcRenderer.on(`methodReply-${callId}`, (event, { response, error }) => {
//             if (error) {
//                 reject(error);
//             }
//             else {
//                 resolve(response);
//             }
//         });

//         ipcRenderer.send('methodCall', {
//             method,
//             callId,
//             args,
//         });
//     }),
// });
