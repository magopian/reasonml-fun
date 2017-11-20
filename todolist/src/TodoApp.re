let str = ReasonReact.stringToElement;

let valueFromEvent = (evt) : string => (
                                         evt
                                         |> ReactEventRe.Form.target
                                         |> ReactDOMRe.domElementToObj
                                       )##value;

type item = {
  id: int,
  title: string,
  completed: bool
};

type state = {items: list(item)};

type action =
  | AddItem(string)
  | ToggleItem(int);

let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);

let newItem = (text) => {
  lastId := lastId^ + 1;
  {id: lastId^, title: text, completed: false}
};

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, ~onToggle, _children) => {
    ...component,
    render: (_self) =>
      <div className="item" onClick=((_event) => onToggle()) id=(string_of_int(item.id))>
        <input _type="checkbox" checked=(Js.Boolean.to_js_boolean(item.completed)) />
        (str(item.title))
      </div>
  };
};

module Input = {
  type state = string;
  let component = ReasonReact.reducerComponent("Input");
  let make = (~onSubmit, _) => {
    ...component,
    initialState: () => "",
    reducer: (newText, _text) => ReasonReact.Update(newText),
    render: ({state: text, reduce}) =>
      <input
        value=text
        _type="text"
        placeholder="Write something to do"
        onChange=(reduce((evt) => valueFromEvent(evt)))
        onKeyDown=(
          (evt) =>
            if (ReactEventRe.Keyboard.key(evt) == "Enter") {
              onSubmit(text);
              (reduce(() => ""))()
            }
        )
      />
  };
};

let make = (_children) => {
  ...component,
  initialState: () => {items: [{id: lastId^, title: "Write some things to do", completed: false}]},
  reducer: (action, {items}) =>
    switch action {
    | AddItem(text) => ReasonReact.Update({items: [newItem(text), ...items]})
    | ToggleItem(id) =>
      let items =
        List.map((item) => item.id === id ? {...item, completed: ! item.completed} : item, items);
      ReasonReact.Update({items: items})
    },
  render: ({state: {items}, reduce}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title">
        (str("What to do"))
        <Input onSubmit=(reduce((text) => AddItem(text))) />
      </div>
      <div className="items">
        (
          items
          |> List.map(
               (item) =>
                 <TodoItem
                   item
                   key=(string_of_int(item.id))
                   onToggle=(reduce(() => ToggleItem(item.id)))
                 />
             )
          |> Array.of_list
          |> ReasonReact.arrayToElement
        )
      </div>
      <div className="footer">
        (str(string_of_int(numItems) ++ (numItems > 1 ? " items" : " item")))
      </div>
    </div>
  }
};
