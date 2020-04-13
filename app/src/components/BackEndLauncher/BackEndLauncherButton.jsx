const React = require('react');
const { ipcRenderer } = window.require('electron');

var CustomButtonStyle = {
    margin: '10px 10px 10px 0'
};

class BackEndLauncherButton extends React.Component {
    render() {
        return (
            <button className="CustomButton"
                    style={CustomButtonStyle}
                    // onClick={ipcRenderer.send('LaunchBackEnd')}
                    >
                Launch C++ back-end
            </button>
        );
    }
}

module.exports = BackEndLauncherButton;
