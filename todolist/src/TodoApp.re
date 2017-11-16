let str = ReasonReact.stringToElement;
type item = {
  title: string,
  completed: bool
};

type state = {
  items: list(item)
};
type action =
  | AddItem;

let component = ReasonReact.reducerComponent("TodoApp");
let newItem = () => {
    title: "foobar",
    completed: false
};

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, children) => {
    ...component,
    render: (self) =>
      <div className="item">
        <input
          _type="checkbox"
          checked=(Js.Boolean.to_js_boolean(item.completed))
          /* TODO make interactive */
        />
        (str(item.title))
      </div>
  };
};

let make = (children) => {
  ...component,
  initialState: () => {
    items: [
      { title: "Write some things to do", completed: false}
    ]
  },
  reducer: (action, {items}) =>
    switch action {
      | AddItem => ReasonReact.Update({items: [newItem(), ...items]})
    },
  render: ({state: {items}, reduce}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title">
        (str("What to do"))
        <button onClick=(reduce((event) => AddItem))>(str("Add something"))</button>
      </div>
      <div className="items">(
      items
        |> List.map((item) => <TodoItem item />)
        |> Array.of_list
        |> ReasonReact.arrayToElement
      )</div>
      <div className="footer">(str(string_of_int(numItems) ++ (numItems > 1 ? " items" : " item")))</div>
    </div>
    }
};
