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
