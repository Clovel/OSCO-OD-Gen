import React from 'react';
import './ODTab.css';

import {Tab} from 'semantic-ui-react';

import ODView from './../ODView/ODView'

const panes = [
    {
        menuItem: {
            key: 'od-1',
            content: 'OD 1',
            icon: 'file code'
        },
        pane: {
            key: 'odview1',
            content: (
                <ODView/>
            )
        }
    },
    {
        menuItem: {
            key: 'od-2',
            content: 'OD 2',
            icon: 'file code'
        },
        pane: {
            key: 'odview2',
            content: (
                <ODView/>
            )
        }
    },
    {
        menuItem: {
            key: 'od-3',
            content: 'OD 3',
            icon: 'file code'
        },
        pane: {
            key: 'odview3',
            content: (
                <ODView/>
            )
        }
    },
];

class ODTab extends React.Component {
    render() {
        return (
            <Tab panes={panes} renderActiveOnly={false} />
        );
    }
}

export default ODTab;
