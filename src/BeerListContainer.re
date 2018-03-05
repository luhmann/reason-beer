let component = ReasonReact.statelessComponent("BeerListContainer");

let make = (~beers: list(Beer.brew), _children) => {
  ...component,
  render: _self => {
    let beerItems =
      beers
      |> List.map(beer => {
           let {id, name, description, image}: Beer.brew = beer;
           <Beer key=(string_of_int(id)) name description image />;
         });
    <section>
      (ReasonReact.arrayToElement(Array.of_list(beerItems)))
    </section>;
  }
};
