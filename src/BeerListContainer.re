let component = ReasonReact.statelessComponent("BeerListContainer");

let renderBeers = beers =>
  beers
  |> List.map(beer => {
       let {id, name, tagline, description, ibu, abv, image, foodPairing}: Beer.brew = beer;
       <Beer
         key=(string_of_int(id))
         name
         tagline
         description
         ibu
         abv
         image
         foodPairing
       />;
     });

let make = (~beers: list(Beer.brew), _children) => {
  ...component,
  render: _self => {
    let beerItems =
      switch beers {
      | [] =>
        <div>
          (
            ReasonReact.stringToElement(
              "No matches. Please change your query and try again"
            )
          )
        </div>
      | _ => ReasonReact.arrayToElement(Array.of_list(renderBeers(beers)))
      };
    <section> beerItems </section>;
  }
};
