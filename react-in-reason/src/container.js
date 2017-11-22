/* A very simple React component in JS (only acting as a dumb container).
 * It uses a Reason component by importing it (it's wrapped in app.re so it's
 * usable by a React component in JS).
 */
import * as React from 'react';
var App = require('./app').jsComponent;

export function AppContainer({message}) {
  return (
    <div>
      <p>
        Simple react container containing a reason component:
      </p>
      <App message={message} />
    </div>
  );
}

