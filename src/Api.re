let getFoodParingUrl = searchTerm : string => {j|https://api.punkapi.com/v2/beers?food=$searchTerm&per_page=80|j};

let mapBeerResponse = beerResponse : list(Beer.brew) =>
  Array.to_list(
    Js.Array.map(
      beer => {
        let item: Beer.brew = {
          id: beer##id,
          name: beer##name,
          tagline: beer##tagline,
          description: beer##description,
          image: beer##image_url,
          foodPairing: beer##food_pairing
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
