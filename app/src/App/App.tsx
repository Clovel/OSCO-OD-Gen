import './App.css';
import 'semantic-ui-css/semantic.min.css'

import MainSideBar from './../components/MainSideBar/MainSideBar';
import BackEndLauncherButton from './../components/BackEndLauncher/BackEndLauncherButton';

const React = require('react');
const logo = require ('./../logo.svg');


// var lButton = CustomButton;

function App() {
    return (
        <div className="App">
            <div>
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
            <div>
                <MainSideBar />
            </div>
        </div>
    );
}

export default App;
