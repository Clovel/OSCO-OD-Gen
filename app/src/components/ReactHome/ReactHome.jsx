import React from 'react';

import './ReactHome.css';
import 'semantic-ui-css/semantic.min.css'

import BackEndLauncherButton from '../BackEndLauncherButton/BackEndLauncherButton'

const logo = require ('./../../logo.svg');

class ReactHome extends React.Component {
    render() {
        return (
            <header className="ReactHome-header">
                <img src={logo} className="ReactHome-logo" alt="logo" />
                <p>
                    Edit <code>src/App.tsx</code> and save to reload.
                </p>
                <BackEndLauncherButton />
                <a className="ReactHome-link" href="https://reactjs.org" target="_blank" rel="noopener noreferrer">
                    Learn React
                </a>
            </header>
        );
    }
}

export default ReactHome;
