type item = {
  title: string,
  completed: bool
};

type state = {
  items: list(item)
};

let component = ReasonReact.reducerComponent("TodoApp");

let make = (children) => {
  ...component,
  initialState: () => {
    items: [
      { title: "Write some things to do", completed: false}
    ]
  },
  reducer: ((), _) => ReasonReact.NoUpdate,
  render: ({state: {items}}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title"> (ReasonReact.stringToElement("What to do")) </div>
      <div className="items"> (ReasonReact.stringToElement("Nothing")) </div>
      <div className="footer"> (ReasonReact.stringToElement(string_of_int(numItems) ++ (numItems > 1 ? " items" : " item"))) </div>
    </div>
    }
};
