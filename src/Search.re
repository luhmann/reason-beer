type state = {searchText: string};

type action =
  | Submit
  | KeyDown(int)
  | Change(string);

let component = ReasonReact.reducerComponentWithRetainedProps("Search");

let make =
    (
      ~placeholderText: string,
      ~initialValue: string,
      ~disabled: bool,
      ~onSubmit: string => unit,
      _children
    ) => {
  let handleSubmit = state =>
    switch (String.trim(state.searchText)) {
    | "" => ReasonReact.NoUpdate
    | nonEmptyValue =>
      ReasonReact.SideEffects((_self => onSubmit(nonEmptyValue)))
    };
  {
    ...component,
    initialState: () => {searchText: initialValue},
    retainedProps: initialValue,
    willReceiveProps: ({state, retainedProps}) =>
      if (retainedProps !== initialValue) {
        {searchText: initialValue};
      } else {
        state;
      },
    reducer: action =>
      switch action {
      | Change(searchText) => (
          _state => ReasonReact.Update({searchText: searchText})
        )
      | Submit => handleSubmit
      | KeyDown(13) => handleSubmit
      | KeyDown(_) => (_state => ReasonReact.NoUpdate)
      },
    render: ({state, send}) =>
      <input
        className=(
          Cn.make([
            "border",
            "mb-4",
            "p-2",
            "rounded",
            "text-grey-darkest",
            "appearance-none",
            "w-full",
            "max-w-md",
            "bg-grey-lighter" |> Cn.ifBool(disabled)
          ])
        )
        disabled=(Js.Boolean.to_js_boolean(disabled))
        _type="text"
        placeholder=placeholderText
        value=state.searchText
        onKeyDown=(event => send(KeyDown(ReactEventRe.Keyboard.which(event))))
        onChange=(
          event =>
            send(
              Change(
                ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value
              )
            )
        )
      />
  };
};
