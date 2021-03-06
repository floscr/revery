open Reglfw;

type reducer('s, 'a) = ('s, 'a) => 's;

type t('s, 'a) = {
  reducer: reducer('s, 'a),
  mutable state: 's,
  mutable windows: list(Window.t),
  mutable needsRender: bool,
};

/* If no state is specified, just use unit! */
let defaultState = ();

/* If no reducer is specified, just pass through state */
let defaultReducer: reducer(unit, unit) = (_s, _a) => ();

type appInitFunc('s, 'a) = t('s, 'a) => unit;

type startFunc('s, 'a) = ('s, reducer('s, 'a), appInitFunc('s, 'a)) => unit;

let getWindows = (app: t('s, 'a)) => app.windows;

let getState = (app: t('s, 'a)) => app.state;

let quit = (code: int) => exit(code);

let dispatch = (app: t('s, 'a), action: 'a) => {
  let newState = app.reducer(app.state, action);
  app.state = newState;
  app.needsRender = true;
};

let createWindow =
    (~createOptions=Window.defaultCreateOptions, app: t('s, 'a), windowName) => {
  let w = Window.create(windowName, createOptions);
  /* Window.render(w) */
  app.windows = [w, ...app.windows];
  w;
};

let _anyWindowsDirty = (app: t('s, 'a)) =>
  List.fold_left(
    (prev, w) => prev || Window.isDirty(w),
    false,
    getWindows(app),
  );

let startWithState: startFunc('s, 'a) =
  (
    initialState: 's,
    reducer: reducer('s, 'a),
    initFunc: appInitFunc('s, 'a),
  ) => {
    let appInstance: t('s, 'a) = {
      reducer,
      state: initialState,
      windows: [],
      needsRender: true,
    };

    let _ = Glfw.glfwInit();
    let _ = initFunc(appInstance);

    let appLoop = (_t: float) => {
      Glfw.glfwPollEvents();
      if (appInstance.needsRender || _anyWindowsDirty(appInstance)) {
        Performance.bench("renderWindows", () => {
          List.iter(w => Window.render(w), getWindows(appInstance));
          appInstance.needsRender = false;
        });
      } else {
        Environment.sleep(Milliseconds(1.));
      };
      false;
    };

    Glfw.glfwRenderLoop(appLoop);
  };

let start = (initFunc: appInitFunc(unit, unit)) =>
  startWithState(defaultState, defaultReducer, initFunc);
