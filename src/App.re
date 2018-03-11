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
  beers: list(Beer.brew)
};

type action =
  | FETCH_BEERS(string)
  | SET_BEERS(list(Beer.brew));

let component = ReasonReact.reducerComponent("App");

let shouldFetch = (stateId, searchText) =>
  stateId !== LOADING && Js.String.length(searchText) > 0;

let make = _children => {
  let fetchBeers = (self, searchTerm) =>
    Js.Promise.(
      Api.fetchBeersForFoodPairing(searchTerm)
      |> then_(beers => {
           self.ReasonReact.send(SET_BEERS(beers));
           resolve(beers);
         })
      |> then_(beers => resolve(Js.log(beers)))
      |> catch(error => resolve(Js.log(error)))
    );
  {
    ...component,
    initialState: () => {id: NOT_ASKED, beers: []},
    reducer: (action, state) =>
      switch action {
      | FETCH_BEERS(searchText) when shouldFetch(state.id, searchText) =>
        ReasonReact.UpdateWithSideEffects(
          {...state, id: LOADING},
          (self => fetchBeers(self, searchText) |> ignore)
        )
      | SET_BEERS(beers) => ReasonReact.Update({...state, id: SUCCESS, beers})
      },
    render: ({state, send}) => {
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
          placeholderText="Enter a food you want to pair with a beer, eg. 'Burger'"
          onSubmit=(searchText => send(FETCH_BEERS(searchText)))
        />
        container
      </main>;
    }
  };
};
