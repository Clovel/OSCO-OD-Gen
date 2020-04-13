import './MainSideBar.css'
import React from 'react';
import { Sidebar, Grid, Icon, GridColumn, Menu, List, ListItem } from 'semantic-ui-react';

const { ipcRenderer } = window.require('electron');

var lVisible = true;

class MainSideBar extends React.Component {
    render() {
        return (
            <Sidebar
                as={Menu}
                animation='overlay'
                icon='labeled'
                inverted
                onHide={() => {lVisible = false;}}
                vertical
                visible={lVisible}
                width='thin'>
                <Menu.Item
                    as='a'
                    onClick={() => {ipcRenderer.send('open-od')}}>
                    <Icon name='folder open'/>
                    Open OD
                </Menu.Item>
                <Menu.Item
                    as='a'
                    onClick={() => {ipcRenderer.send('Generate-C-code')}}>
                    <Icon name='cog'/>
                    Generate C code
                </Menu.Item>
                <Menu.Item
                    as='a'
                    onClick={() => {ipcRenderer.send('Generate-OD-description-file')}}>
                    <Icon name='save'/>
                    Generate OD description file
                </Menu.Item>
            </Sidebar>
        );
    }
}

// function MainSideBar(props) {
//     return(
//         <Grid>
//             <GridColumn>
//                 <Menu.Item as='a'>
//                     <Icon name='home'/>
//                     Home
//                 </Menu.Item>
//                 <Menu.Item as='a'>
//                     <Icon name='cog'/>
//                     Generate C code
//                 </Menu.Item>
//                 <Menu.Item as='a'>
//                     <Icon name='save'/>
//                     Generate OD description file
//                 </Menu.Item>
//                 <Menu.Item as='a'>
//                     <Icon name='camera'/>
//                     Channels
//                 </Menu.Item>
//             </GridColumn>
//             <GridColumn>
//                 <Menu.Item as='a'>
//                     <Icon name='home'/>
//                     Home
//                 </Menu.Item>
//                 <Menu.Item as='a'>
//                     <Icon name='cog'/>
//                     Generate C code
//                 </Menu.Item>
//                 <Menu.Item as='a'>
//                     <Icon name='save'/>
//                     Generate OD description file
//                 </Menu.Item>
//                 <Menu.Item as='a'>
//                     <Icon name='camera'/>
//                     Channels
//                 </Menu.Item>
//             </GridColumn>
//         </Grid>
//     )
// }

// function MainSideBar(props) {
//     var lVisible = true;

//     return (
//         // <Sidebar.Pushable as={Segment}>
//             <Sidebar
//                 as={Menu}
//                 animation='overlay'
//                 icon='labeled'
//                 inverted
//                 onHide={() => {lVisible = false;}}
//                 vertical
//                 visible={lVisible}
//                 width='thin'>
//                 <Menu.Item as='a'>
//                     <Icon name='home'/>
//                     Home
//                 </Menu.Item>
//                 <Menu.Item as='a'>
//                     <Icon name='cog'/>
//                     Generate C code
//                 </Menu.Item>
//                 <Menu.Item as='a'>
//                     <Icon name='save'/>
//                     Generate OD description file
//                 </Menu.Item>
//                 <Menu.Item as='a'>
//                     <Icon name='camera'/>
//                     Channels
//                 </Menu.Item>
//             </Sidebar>
//         // </Sidebar.Pushable>
//     )
// }

export default MainSideBar;
