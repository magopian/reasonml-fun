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
