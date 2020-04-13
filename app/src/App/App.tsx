import './App.css';
import 'semantic-ui-css/semantic.min.css'
import React from 'react';

import MainSideBar from './../components/MainSideBar/MainSideBar';
import MainContainer from './../components/MainContainer/MainContainer';

function App() {
    return (
        <div className="App">
            <MainContainer />
            <div>
                <MainSideBar />
            </div>
        </div>
    );
}

export default App;
