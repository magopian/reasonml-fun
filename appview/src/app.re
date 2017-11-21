[%bs.raw {|require('./app.css')|}];

[%bs.raw {|require('photon-ant')|}];

[@bs.module] external logo : string = "./logo.svg";

module Card = {
  [@bs.module "antd"] external card : ReasonReact.reactClass = "Card";
  let make = (~title: option(string)=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=card,
      ~props={"title": Js.Nullable.from_opt(title)},
      children
    );
};

let component = ReasonReact.statelessComponent("App");

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
