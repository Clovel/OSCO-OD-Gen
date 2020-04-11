const React = require('react');

var CustomButtonStyle = {
    margin: '10px 10px 10px 0'
};

function BackEndLauncherButton (props) {
    return (
        <button className="CustomButton"
                style={CustomButtonStyle}>
            Launch C++ back-end
        </button>
    );
}

module.exports = BackEndLauncherButton;
