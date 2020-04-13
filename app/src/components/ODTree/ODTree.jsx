import React from 'react';

const { ipcRenderer } = window.require('electron');

class GetODJSON extends React.Component {
    render () {
        return (
            <button onClick={() => {
                    ipcRenderer.send('GetODJSON');
                    }}>
                Get Object Dictionary JSON
            </button>
        );
    }
}

// a sample tree object
// node.children, node.collapsed, node.leaf properties are hardcoded
const treeContents = {
    indexes: [
        {
            index: "0x1001",
            subIndexes: [
                {
                    subIndex: "0x00",
                    attribute1: "Toto",
                    attribute2: "Titi",
                    attribute3: "font du ski",
                },
                {
                    subIndex: "0x01",
                    attribute1: "Test1",
                    attribute2: "Test2",
                    attribute3: "pour tester",
                },
            ],
        },
        {
            index: "0x1018",
            subIndexes: [
                {
                    subIndex: "0x00",
                    attribute1: "Toto",
                    attribute2: "Titi",
                    attribute3: "font du ski",
                },
                {
                    subIndex: "0x01",
                    attribute1: "Test1",
                    attribute2: "Test2",
                    attribute3: "pour tester",
                },
            ],
        }
    ],
};

class ODSubIndex extends React.Component {
    subIndex = this.props.subIndex;
    attribute1 = null;
    attribute2 = null;
    attribute3 = null;

    render() {
        return (
            <div>
                SubIndex {this.subIndex}
            </div>
        );
    }
}

class ODIndex extends React.Component {
    index = this.props.index;
    subIndexes = this.props.subIndexes;

    render() {
        return (
            <div>
                Index {this.index}
                <div>
                    {this.subIndexes.map(function(pSubIndex, pArrayIndex) {
                        return (
                            <ODSubIndex subIndex={pSubIndex.subIndex}/>
                        );
                    })}
                </div>
            </div>
        );
    }
}

class ODTree extends React.Component {
    state = {
        active: null,
    };

    tree = treeContents;

    render() {
        return(
            <div>
                ODTree placeholder
                <br/>
                <GetODJSON/>
                <br/>
                Example ODIndex :
                <ODIndex
                    index={this.tree.indexes[0].index}
                    subIndexes={this.tree.indexes[0].subIndexes}/>
                <br/>
                <br/>
                <br/>
                <br/>
                {this.tree.indexes.map(function(pIndex, pArrayIndex) {
                    return (
                        <ODIndex index={pIndex.index} subIndexes={pIndex.subIndexes}/>
                    );
                })}
            </div>
        );
    }
}

export default ODTree;
