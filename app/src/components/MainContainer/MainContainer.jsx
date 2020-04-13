import React from 'react';
import './MainContainer.css'

// import ReactHome from './../ReactHome/ReactHome';
import {Container} from 'semantic-ui-react';
import ODTab from './../ODTab/ODTab';

class MainContainer extends React.Component {
    render() {
        return (
            <div class="MainContainer" className="MainContainer">
                <Container>
                    {/* <ReactHome /> */}
                    <ODTab />
                </Container>
            </div>
        );
    }
}

export default MainContainer;
