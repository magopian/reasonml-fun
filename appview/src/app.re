/* A Reason component */
[%bs.raw {|require('./app.css')|}];

/* Styling of antd components using the photon-ant theme */
[%bs.raw {|require('photon-ant')|}];

[@bs.module] external logo : string = "./logo.svg";

let str = ReasonReact.stringToElement;

module Row = {
  /* Import a React (in JS) component from antd */
  [@bs.module "antd"] external row : ReasonReact.reactClass = "Row";
  /* Wrap the React component so it's usable by Reason */
  let make = (~gutter: int, children) =>
    ReasonReact.wrapJsForReason(~reactClass=row, ~props={"gutter": gutter}, children);
};

module Col = {
  /* Import a React (in JS) component from antd */
  [@bs.module "antd"] external col : ReasonReact.reactClass = "Col";
  /* Wrap the React component so it's usable by Reason */
  let make = (~span: int, children) =>
    ReasonReact.wrapJsForReason(~reactClass=col, ~props={"span": span}, children);
};

/* Declare the Reason component */
let component = ReasonReact.statelessComponent("App");

/* Implement the Reason component */
let make = (~message, _children) => {
  ...component,
  render: (_self) =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> (str(message)) </h2>
      </div>
      <p className="App-intro">
        (str("To get started, edit"))
        <code> (str(" src/App.re ")) </code>
        (str("and save to reload."))
      </p>
      <div className="Apps-Grid">
        <Row gutter=16>
          <Col span=6>
            <BuildInfo
              product="Firefox"
              url="https://play.google.com/store/apps/details?id=org.mozilla.firefox"
              version="57.0"
            />
          </Col>
          <Col span=6>
            <BuildInfo
              product="Firefox Focus"
              url="https://play.google.com/store/apps/details?id=org.mozilla.focus"
              version="57.0"
            />
          </Col>
          <Col span=6>
            <BuildInfo
              product="Firefox Beta"
              url="https://play.google.com/store/apps/details?id=org.mozilla.firefox_beta"
              version="58.0b5"
            />
          </Col>
          <Col span=6>
            <BuildInfo
              product="Firefox Nightly"
              url="https://play.google.com/store/apps/details?id=org.mozilla.fennec_aurora"
              version="59.0"
            />
          </Col>
        </Row>
      </div>
    </div>
};

/* Wrap the Reason component so it's usable in React component in JS */
let jsComponent =
  ReasonReact.wrapReasonForJs(~component, (jsProps) => make(~message=jsProps##message, [||]));
