type appState =
  | NOT_ASKED
  | LOADING
  | ERROR
  | SUCCESS;

type foodPairingResponse = {
  id: int,
  name: string,
  description: string,
  image_url: string,
  food_pairing: array(string)
};

type state = {
  id: appState,
  beers: list(Beer.brew),
  searchTerm: option(string)
};

type action =
  | FETCH_BEERS(string)
  | SET_BEERS(list(Beer.brew));

let component = ReasonReact.reducerComponent("App");

let shouldFetch = stateId => stateId !== LOADING;

let make = (~searchTerm: option(string), _children) => {
  let fetchBeers = (self, searchTerm) =>
    Js.Promise.(
      Api.fetchBeersForFoodPairing(searchTerm)
      |> then_(beers => resolve(self.ReasonReact.send(SET_BEERS(beers))))
      |> catch(error => resolve(Js.log(error)))
    );
  let createSearchBeerAction = (state, searchTerm) =>
    ReasonReact.UpdateWithSideEffects(
      {...state, id: LOADING, searchTerm: Some(searchTerm)},
      self => fetchBeers(self, searchTerm) |> ignore
    );
  {
    ...component,
    initialState: () => {id: NOT_ASKED, beers: [], searchTerm},
    didMount: ({state}) =>
      switch state.searchTerm {
      | None => ReasonReact.NoUpdate
      | Some(searchTerm) => createSearchBeerAction(state, searchTerm)
      },
    reducer: (action, state) =>
      switch action {
      | FETCH_BEERS(searchTerm) when shouldFetch(state.id) =>
        createSearchBeerAction(state, searchTerm)
      | FETCH_BEERS(_) => ReasonReact.NoUpdate
      | SET_BEERS(beers) => ReasonReact.Update({...state, id: SUCCESS, beers})
      },
    render: ({state}) => {
      let container =
        switch state.id {
        | NOT_ASKED => <IntroText />
        | LOADING => <Loading />
        | SUCCESS => <BeerListContainer beers=state.beers />
        | ERROR => <Error />
        };
      <main className="mx-auto p-4 font-sans leading-normal max-w-md">
        <Title />
        <Search
          disabled=(state.id === LOADING)
          initialValue=(Js.Option.getWithDefault("", searchTerm))
          placeholderText="Enter a food you want to pair with a beer, eg. 'Burger'"
          onSubmit=(searchText => ReasonReact.Router.push({j|/#$searchText|j}))
        />
        container
      </main>;
    }
  };
};
