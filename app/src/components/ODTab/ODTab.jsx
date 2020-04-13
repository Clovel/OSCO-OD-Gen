import React from 'react';
import './ODTab.css';

import {Tab} from 'semantic-ui-react';

const panes = [
    {
        menuItem: {
            key: 'od-1',
            content: 'OD 1',
            icon: 'file code'
        },
        pane: 'OD 1 Content'
    },
    {
        menuItem: {
            key: 'od-2',
            content: 'OD 2',
            icon: 'file code'
        },
        pane: 'OD 2 Content'
    },
    {
        menuItem: {
            key: 'od-3',
            content: 'OD 3',
            icon: 'file code'
        },
        pane: 'OD 3 Content'
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
