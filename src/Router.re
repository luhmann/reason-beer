type children = (~searchTerm: option(string)) => ReasonReact.reactElement;

type state = {searchTerm: option(string)};

type action =
  | SET_SEARCH_TERM(string)
  | CLEAR_SEARCH_TERM;

let component = ReasonReact.reducerComponent("Router");

let getInitialUrl = () => {
  let searchTerm = ReasonReact.Router.dangerouslyGetInitialUrl().hash;
  switch searchTerm {
  | "" => None
  | term => Some(term)
  };
};

let make = (children: children) => {
  ...component,
  initialState: () => {searchTerm: getInitialUrl()},
  reducer: (action, _state) =>
    switch action {
    | SET_SEARCH_TERM(searchTerm) =>
      ReasonReact.Update({searchTerm: Some(searchTerm)})
    | CLEAR_SEARCH_TERM => ReasonReact.Update({searchTerm: None})
    },
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          switch url.hash {
          | "" => self.send(CLEAR_SEARCH_TERM)
          | searchTerm => self.send(SET_SEARCH_TERM(searchTerm))
          }
        ),
      ReasonReact.Router.unwatchUrl
    )
  ],
  render: ({state}) => children(~searchTerm=state.searchTerm)
};
