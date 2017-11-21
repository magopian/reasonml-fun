/* A Reason component */
[%bs.raw {|require('./app.css')|}];

/* Styling of antd components using the photon-ant theme */
[%bs.raw {|require('photon-ant')|}];

[@bs.module] external logo : string = "./logo.svg";

module Card = {
  /* Import a React (in JS) component from antd */
  [@bs.module "antd"] external card : ReasonReact.reactClass = "Card";
  /* Wrap the React component so it's usable by Reason */
  let make = (~title: option(string)=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=card,
      ~props={"title": Js.Nullable.from_opt(title)},
      children
    );
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
        <h2> (ReasonReact.stringToElement(message)) </h2>
      </div>
      <p className="App-intro">
        (ReasonReact.stringToElement("To get started, edit"))
        <code> (ReasonReact.stringToElement(" src/App.re ")) </code>
        (ReasonReact.stringToElement("and save to reload."))
      </p>
      <Card title="I'm an antd card title">
        (ReasonReact.stringToElement("and I'm an antd card content!"))
      </Card>
    </div>
};

/* Wrap the Reason component so it's usable in React component in JS */
let jsComponent =
  ReasonReact.wrapReasonForJs(~component, (jsProps) => make(~message=jsProps##message, [||]));
