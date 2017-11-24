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
              logo="https://lh3.googleusercontent.com/shH5ALdqmZysSU2F5SF52674W7NFP1xtLBZMuzUR5u6Uotbgql3ATFFFhtkJjBCm4R3i=w300"
              pubDate="2017-11-14"
              version="57.0"
            />
          </Col>
          <Col span=6>
            <BuildInfo
              product="Firefox Focus"
              logo="https://lh3.googleusercontent.com/uoqToM7l-x3lZNjFOzNkVxEilkKfEzGh9v8BB8b6pP1l9TltE4Sxd1XGJuiksjM4a1s=w300"
              pubDate="2017-11-17"
              version="57.0"
            />
          </Col>
          <Col span=6>
            <BuildInfo
              product="Firefox Beta"
              logo="https://lh3.googleusercontent.com/872N1-Q_qFJbvPmCTc1bvwa0NjY49HbUAC-F-yl2XEFyfePrnTGPthGH4C3FcYoP5Vc=w300"
              pubDate="2017-11-21"
              version="58.0b5"
            />
          </Col>
          <Col span=6>
            <BuildInfo
              product="Firefox Nightly"
              logo="https://lh3.googleusercontent.com/5ZYLS3ztW1XBfSf32onyhAVLq_uZQmJIYdhz8VlQwuvpB7x73jaDqtJlTtmxcsvit0I=w300"
              pubDate="2017-11-23"
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
