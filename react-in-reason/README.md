# React in Reason in React

This experiment is about using a React component (some
[antd](https://ant.design/) components) in a Reason component, and then using
this outer Reason component in a React app.


## Steps to reproduce

### Creating a reason app

```
$ yarn create react-app appview -- --scripts-version reason-scripts
$ cd appview
$ yarn start
```

This will create a reason app with all the goodness from create-react-app
(including hot-reloading!).


### Adding antd

```
$ yarn add antd
$ yarn add react-app-rewired --dev
$ yarn add babel-plugin-import --dev
```

Then rewire the scripts in `package.json`:

```diff
-    "start": "react-scripts start",
+    "start": "react-app-rewired start --scripts-version reason-scripts",
-    "build": "react-scripts build",
+    "build": "react-app-rewired build --scripts-version reason-scripts",
-    "test": "react-scripts test --env=jsdom",
+    "test": "react-app-rewired test --env=jsdom --scripts-version reason-scripts",
-    "eject": "react-scripts eject",
+    "eject": "react-app-rewired eject --scripts-version reason-scripts",
```

and add a `config-overrides.json` file:

```
module.exports = function override(config, env) {
  // do stuff with the webpack config...
  return config;
};
```


### Styling antd components with photon-ant

```
$ yarn add photon-ant
$ yarn add react-app-rewire-less --dev
```

Then modify the `config-overrides.js` file:

```diff
 const {injectBabelPlugin} = require('react-app-rewired');
+const rewireLess = require('react-app-rewire-less');

 module.exports = function override(config, env) {
   config = injectBabelPlugin(
-    ['import', {libraryName: 'antd', style: 'css'}],
+    ['import', {libraryName: 'antd', style: true}],
     config,
   );

+  config = rewireLess(config, env);
+
   return config;
 };
```

And finally add the photon-ant import at the top of your `src/app.re` file:

```Reason
[%bs.raw {|require('photon-ant')|}];
```


### Using an antd component in reason

You can use any antd component (or react component really) by creating the
appropriate bucklescript binding. Here's an example for the
[Card](https://ant.design/components/card/) component:

```Reason
module Card = {
  [@bs.module "antd"] external card : ReasonReact.reactClass = "Card";
  let make = (~title: option(string)=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=card,
      ~props={"title": Js.Nullable.from_opt(title)},
      children
    );
};
```

And then in your reason component:

```Reason
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
      <Card title="I'm an antd card title"> (ReasonReact.stringToElement("and I'm an antd card content!")) </Card>
    </div>
};
```


## Using the reason component in react

To export our reason component and make it available, we can use the
`wrapReasonForJs` helper:

```Reason
let jsComponent =
  ReasonReact.wrapReasonForJs(
    ~component,
    (jsProps) => make(~message=jsProps##message, [||])
  );
```

The compiled version of the reason code down to javascript is in
`lib/js/src/app.js`. You can use it in your react app by importing it:

```Javascript
var MyReasonComponent = require('app').jsComponent;

<MyReasonComponent message="Some awesome message here" />
```

The minimum requirements for using this reason compiled to js file are:
- adding bs-platform, reason-react and reason-js to your package.json
- optionnally adding an eslint rule to ignore those files compiled by
  bucklescript (if you're seeing `Module build failed: TypeError: Cannot read
  property ‘node’ of undefined`)

If you want to also compile those files in your react project, you can check
[Bringing ReasonML into an existing react
app](https://medium.com/@alanhietala/bringing-reasonml-into-an-existing-react-app-d1006a72433b).
