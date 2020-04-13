import React from 'react';

const { ipcRenderer } = window.require('electron');

class BackEndLauncherButton extends React.Component {
    render() {
        return (
            <button className="BackEndLauncherButton"
                    onClick={() => {ipcRenderer.send('LaunchBackEnd')}}
                    >
                Launch C++ back-end
            </button>
        );
    }
}

export default BackEndLauncherButton;
