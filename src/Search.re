type state = {searchText: string};

type action =
  | Submit
  | Change(string);

let component = ReasonReact.reducerComponent("Search");

let make = (~onSubmit, _children) => {
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
      },
    render: ({state, handle, send}) =>
      <input
        className="border p-2 rounded text-grey-darker appearance-none w-1/2"
        _type="text"
        placeholder="Type a search-term eg. 'skull'"
        value=state.searchText
        onBlur=(_event => send(Submit))
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
