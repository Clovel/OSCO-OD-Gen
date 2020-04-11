import React from 'react';
import logo from './../logo.svg';
import './App.css';
import 'semantic-ui-css/semantic.min.css'

import BackEndLauncherButton from './../components/BackEndLauncher/BackEndLauncherButton';

// var lButton = CustomButton;

function App() {
    return (
        <div className="App">
            <header className="App-header">
                <img src={logo} className="App-logo" alt="logo" />
                <p>
                    Edit <code>src/App.tsx</code> and save to reload.
                </p>
                <BackEndLauncherButton />
                <a className="App-link" href="https://reactjs.org" target="_blank" rel="noopener noreferrer">
                    Learn React
                </a>
            </header>
        </div>
    );
}

export default App;
