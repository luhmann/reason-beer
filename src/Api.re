let getFoodParingUrl = searchTerm : string => {j|https://api.punkapi.com/v2/beers?food=$searchTerm|j};

let mapBeerResponse = beerResponse =>
  Array.to_list(
    Js.Array.map(
      beer => {
        let item: Beer.brew = {
          id: beer##id,
          name: beer##name,
          description: beer##description,
          image: beer##image_url
        };
        item;
      },
      beerResponse
    )
  );

let fetchBeersForFoodPairing = searchTerm =>
  Js.Promise.(
    Axios.get(getFoodParingUrl(searchTerm))
    |> then_(response => resolve(mapBeerResponse(response##data)))
  );
