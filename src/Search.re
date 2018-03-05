type state = {searchText: string};

type action =
  | Submit
  | KeyDown(int)
  | Change(string);

let component = ReasonReact.reducerComponent("Search");

let make = (~placeholderText: string, ~onSubmit: string => unit, _children) => {
  let handleSubmit = state =>
    switch (String.trim(state.searchText)) {
    | "" => ReasonReact.NoUpdate
    | nonEmptyValue =>
      ReasonReact.SideEffects((_self => onSubmit(nonEmptyValue)))
    };
  {
    ...component,
    initialState: () => {searchText: ""},
    reducer: action =>
      switch action {
      | Change(searchText) => (
          state => ReasonReact.Update({...state, searchText})
        )
      | Submit => handleSubmit
      | KeyDown(13) => handleSubmit
      | KeyDown(_) => (_state => ReasonReact.NoUpdate)
      },
    render: ({state, send}) =>
      <input
        className="border mb-2 p-2 rounded text-grey-darkest appearance-none w-full max-w-md"
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
