import React from 'react';

import {Form, TextArea} from 'semantic-ui-react';


class CommentsForm extends React.Component {
    mLines = 0;

    countLines(pStr) {
        if(typeof pStr === 'string' || pStr instanceof String) {
            if("" === pStr) {
                console.log('[DEBUG] <CommentsForm::countLines> Got empty str');
                this.mLines = 0;
            } else {
                this.mLines = pStr.split(/\r\n|\r|\n/).length;
            }
        } else {
            this.mLines = 0;
            console.log('[DEBUG] <CommentsForm::countLines> Got non-string argument');
        }
    }

    render() {
        return (
            <Form>
                <h2>Comments :</h2>
                <p>
                    Here you can enter comments that will appear in the generated code and in the generated Object Dictionary description files.
                </p>
                <TextArea
                    placeholder='Enter OD comments here.'
                    onChange={
                        e => {
                            this.setState({
                                value: e.target.value
                            });
                            this.countLines(e.target.value);
                            if(3 <= this.mLines) {
                                e.target.rows = this.mLines;
                            } else {
                                e.target.rows = 3;
                            }
                        }
                    }
                    />
                <p>
                    Lines : {this.mLines}
                </p>
            </Form>
        );
    }
}

export default CommentsForm;
