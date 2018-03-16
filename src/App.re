let component = ReasonReact.statelessComponent("App");

let make = (~beerFetcher: FetchBeers.beerFetcher, _children) => {
  ...component,
  render: _self => {
    let container =
      switch beerFetcher.status {
      | NOT_ASKED => <IntroText />
      | LOADING => <Loading />
      | SUCCESS => <BeerListContainer beers=beerFetcher.beers />
      | ERROR => <Error />
      };
    <main className="mx-auto p-4 font-sans leading-normal max-w-md">
      <Title />
      <Search
        disabled=(beerFetcher.status === LOADING)
        initialValue=(Js.Option.getWithDefault("", beerFetcher.searchTerm))
        placeholderText="Enter a food you want to pair with a beer, eg. 'Burger'"
        onSubmit=(searchText => ReasonReact.Router.push({j|/#$searchText|j}))
      />
      container
    </main>;
  }
};
