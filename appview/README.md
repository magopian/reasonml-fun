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
