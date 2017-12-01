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

type state = {
  logoUrl: option(string),
  pubDate: option(string)
};

type action =
  | InfoRequested
  | NewInfo(option(string), option(string))
  | ErrRequestingInfo(string);

type doc;

let requestInfo = (reduce, url) => {
  Js.log("requesting info");
  Js.Promise.(
    Fetch.fetch("https://cors-anywhere.herokuapp.com/" ++ url)
    |> then_(Fetch.Response.text)
    |> then_(
         (text) =>
           {
             let domParser: string => doc = [%bs.raw
               {| function (content) {
                    return new DOMParser().parseFromString(content, "text/html")
                  }
                |}
             ];
             let doc = domParser(text);
             let querySelectorProperty: (doc, string, string) => Js.nullable(string) = [%bs.raw
               {|
                  function (doc, selectors, property) {
                      var element = doc.querySelector(selectors);
                      return element[property];
                  }
                |}
             ];
             let logoUrl: option(string) =
               Js.Nullable.to_opt(querySelectorProperty(doc, ".main-content .cover-image", "src"));
             let pubDate =
               Js.Nullable.to_opt(
                 querySelectorProperty(
                   doc,
                   ".details-section-contents [itemprop=datePublished]",
                   "innerHTML"
                 )
               );
             reduce(() => NewInfo(logoUrl, pubDate), ());
             ()
           }
           |> resolve
       )
    |> catch(
         (error) =>
           {
             Js.log(error);
             reduce(() => ErrRequestingInfo("Error while getting the response"), ());
             ()
           }
           |> resolve
       )
    |> ignore
  )
};

let component = ReasonReact.reducerComponent("BuildInfo");

/* Implement the Reason component */
let make = (~product, ~url, ~version, _children) => {
  ...component,
  initialState: () => {logoUrl: None, pubDate: None},
  reducer: (action, _state) =>
    switch action {
    | InfoRequested =>
      ReasonReact.UpdateWithSideEffects(
        {logoUrl: Some("loading logo"), pubDate: Some("loading pubdate")},
        ((self) => requestInfo(self.reduce, url))
      )
    | NewInfo(maybeLogoUrl, maybePubDate) =>
      Js.log("received new info");
      ReasonReact.Update({logoUrl: maybeLogoUrl, pubDate: maybePubDate})
    | ErrRequestingInfo(error) =>
      Js.log("error!");
      ReasonReact.Update({logoUrl: Some(error), pubDate: Some(error)})
    },
  didMount: (self) => {
    self.reduce(() => InfoRequested, ());
    ReasonReact.NoUpdate
  },
  render: ({state}) => {
    let logoUrl =
      switch state.logoUrl {
      | None => ""
      | Some(url) => url
      };
    let pubDate =
      switch state.pubDate {
      | None => ""
      | Some(date) => date
      };
    <Card>
      <a href=url>
        <img src=logoUrl alt="logo" />
        <h3> (str(product)) </h3>
        <p> <strong> (str(version)) </strong> (str(" " ++ pubDate)) </p>
      </a>
    </Card>
  }
};

/* Wrap the Reason component so it's usable in React component in JS */
let jsComponent =
  ReasonReact.wrapReasonForJs(
    ~component,
    (jsProps) =>
      make(~product=jsProps##message, ~url=jsProps##url, ~version=jsProps##version, [||])
  );
