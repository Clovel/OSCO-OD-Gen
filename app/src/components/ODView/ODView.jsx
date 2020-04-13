import React from 'react'
import {Tab} from 'semantic-ui-react';

import CommentsForm from './../CommentsForm/CommentsForm';

const panes = [
    { 
        menuItem: {
            key: 'general',
            content: 'General settings',
            icon: 'settings'
        },
        pane: 'General settings'
    },
    {
        menuItem: {
            key: 'contents',
            content: 'OD contents',
            icon: 'file code'
        },
        pane: 'OD Contents'
    },
    {
        menuItem: {
            key: 'misc',
            content: 'Misc.',
            icon: 'code'
        },
        pane: 'Misc.'
    },
    {
        menuItem: {
            key: 'comments',
            content: 'Comments',
            icon: 'file alternate'
        },
        pane: {
            key: 'comments',
            content: (
                <CommentsForm />
            )
        }
    },
];

class ODView extends React.Component {
    render() {
        return(
            <Tab panes={panes} renderActiveOnly={false} />
        );
    }
}

export default ODView;
