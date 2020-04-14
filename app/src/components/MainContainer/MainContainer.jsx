import React from 'react';
import './MainContainer.css'

// import ReactHome from './../ReactHome/ReactHome';
import {Container} from 'semantic-ui-react';
import BackEndLauncherButton from './../BackEndLauncherButton/BackEndLauncherButton'
import ODTab from './../ODTab/ODTab';

class MainContainer extends React.Component {
    render() {
        return (
            <div className="MainContainer">
                <Container>
                    {/* <ReactHome /> */}
                    <BackEndLauncherButton/>
                    <ODTab />
                </Container>
            </div>
        );
    }
}

export default MainContainer;
