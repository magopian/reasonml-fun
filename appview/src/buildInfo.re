let str = ReasonReact.stringToElement;

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

let component = ReasonReact.statelessComponent("BuildInfo");

/* Implement the Reason component */
let make = (~product, ~logo, ~pubDate, ~version, _children) => {
  ...component,
  render: (_self) =>
    <Card>
      <img src=logo alt="logo" />
      <h3> (str(product)) </h3>
      <p> <strong> (str(version)) </strong> (str(pubDate)) </p>
    </Card>
};

/* Wrap the Reason component so it's usable in React component in JS */
let jsComponent =
  ReasonReact.wrapReasonForJs(
    ~component,
    (jsProps) =>
      make(
        ~product=jsProps##message,
        ~logo=jsProps##logo,
        ~pubDate=jsProps##pubDate,
        ~version=jsProps##version,
        [||]
      )
  );
