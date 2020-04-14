import React from 'react';

const { ipcRenderer } = window.require('electron');

const PrettyPrintJson = ({data}) => {
    // data could be a prop for example
    // const { data } = this.props;
    return (
        <div>
            <pre>
                {JSON.stringify(data, null, 2) }
            </pre>
        </div>
    );
};

class GetODJSON extends React.Component {
    constructor() {
        super();
        this.state = {
            ODJSON: '',
        };
        console.log('[DEBUG] Setting GetODJSON-reply IPCRenderer callback');
        window.ipcRenderer.on('GetODJSON-reply', (pEvent, pArg) => {
            console.log('[DEBUG] <IPCRenderer::GetODJSON-reply> Got response : ' + pArg);
            this.setState({ODJSON: JSON.parse(pArg)});
        });
    }

    render () {
        return (
            <div>
                <button onClick={() => {
                        ipcRenderer.send('GetODJSON');
                        }}>
                    Get Object Dictionary JSON
                </button>
                <br/>
                {/* <code>
                    {JSON.stringify(this.state.ODJSON)}
                </code> */}
                <PrettyPrintJson data={this.state.ODJSON}/>
            </div>
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
