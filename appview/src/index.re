[%bs.raw {|require('./index.css')|}];

[@bs.module "./registerServiceWorker"] external register_service_worker : unit => unit = "default";

module Container = {
  /* Import a React (in JS) component from container.js */
  [@bs.module "./container"] external container : ReasonReact.reactClass = "AppContainer";
  /* Wrap the React component so it's usable by Reason */
  let make = (~message, children) =>
    ReasonReact.wrapJsForReason(~reactClass=container, ~props={"message": message}, children);
};

/* This is the starting point: embed a React (in JS) container */
ReactDOMRe.renderToElementWithId(
  <Container message="Welcome to React in Reason in React (in Reason)" />,
  "root"
);

register_service_worker();
