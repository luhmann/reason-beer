type fetchState =
  | NOT_ASKED
  | LOADING
  | ERROR
  | SUCCESS;

type beerFetcher = {
  status: fetchState,
  beers: list(Beer.brew),
  searchTerm: option(string),
  errors: list(option(exn))
};

type state = {
  id: fetchState,
  beers: list(Beer.brew),
  searchTerm: option(string),
  errors: list(option(exn))
};

type action =
  | FETCH_BEERS(string)
  | SET_BEERS(list(Beer.brew))
  | SET_ERROR(option(exn))
  | CLEAR_BEERS;

let component = ReasonReact.reducerComponentWithRetainedProps("FetchBeers");

let fetchBeers = (self, searchTerm) =>
  Js.Promise.(
    Api.fetchBeersForFoodPairing(searchTerm)
    |> then_(beers => resolve(self.ReasonReact.send(SET_BEERS(beers))))
    |> catch(error =>
         resolve(self.ReasonReact.send(SET_ERROR(Utils.jsErrorToExn(error))))
       )
  );

let createSearchBeerAction = (state, searchTerm) =>
  ReasonReact.UpdateWithSideEffects(
    {...state, id: LOADING, searchTerm: Some(searchTerm)},
    self => fetchBeers(self, searchTerm) |> ignore
  );

let shouldFetch = stateId => stateId !== LOADING;

let make = (~searchTerm: option(string), children) => {
  ...component,
  didMount: ({state}) =>
    switch searchTerm {
    | None => ReasonReact.NoUpdate
    | Some(searchTerm) => createSearchBeerAction(state, searchTerm)
    },
  didUpdate: ({oldSelf, newSelf}) =>
    if (oldSelf.retainedProps !== searchTerm) {
      switch searchTerm {
      | None => newSelf.send(CLEAR_BEERS)
      | Some(searchTerm) => newSelf.send(FETCH_BEERS(searchTerm))
      };
    },
  initialState: () => {id: NOT_ASKED, beers: [], searchTerm: None, errors: []},
  retainedProps: searchTerm,
  reducer: (action, state) =>
    switch action {
    | FETCH_BEERS(searchTerm) when shouldFetch(state.id) =>
      createSearchBeerAction(state, searchTerm)
    | FETCH_BEERS(_) => ReasonReact.NoUpdate
    | SET_BEERS(beers) => ReasonReact.Update({...state, id: SUCCESS, beers})
    | CLEAR_BEERS => ReasonReact.Update({...state, beers: []})
    | SET_ERROR(errors) =>
      ReasonReact.Update({...state, id: ERROR, errors: [errors]})
    },
  render: ({state}) =>
    children(
      ~beerFetcher={
        beers: state.beers,
        status: state.id,
        searchTerm: state.searchTerm,
        errors: state.errors
      }
    )
};
