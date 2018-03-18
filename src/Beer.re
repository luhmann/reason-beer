let component = ReasonReact.statelessComponent("Beer");

type brew = {
  id: int,
  name: string,
  tagline: string,
  image: string,
  description: string,
  abv: float,
  ibu: int,
  foodPairing: array(string)
};

let make =
    (
      ~name,
      ~tagline,
      ~description,
      ~abv,
      ~ibu,
      ~foodPairing,
      ~image=?,
      _children
    ) => {
  ...component,
  render: _self => {
    let imageItem =
      switch image {
      | None => ReasonReact.nullElement
      | Some(url) =>
        /* <div
             className="bg-contain bg-top flex-grow bg-no-repeat h-48 sm:h-auto beerImg-width"
             style=(ReactDOMRe.Style.make(~backgroundImage={j|url($i_)|j}, ()))
           />
            */
        <div className="h-48 sm:h-auto beerImg-width overflow-hidden">
          <img
            className="object-contain object-top sm:max-h-full sm:max-w-full"
            src=url
          />
        </div>
      };
    <div
      className="shadow-lg rounded mb-4 overflow-hidden max-w-md p-3 sm:flex items-stretch test-beer-card">
      imageItem
      <div className="pb-4 pr-4 pl-4 pt-4 sm:pt-0">
        <h2
          className="font-black tracking-wide leading-tight test-beer-card-name">
          (ReasonReact.stringToElement(name))
        </h2>
        <div className="mb-3 text-grey-darker italic test-beer-card-tagline">
          (ReasonReact.stringToElement(tagline))
        </div>
        <p className="text-sm mb-3 test-beer-card-description">
          (ReasonReact.stringToElement(description))
        </p>
        <div className="mb-6 test-beer-card-tags">
          <span
            className="bg-blue-lighter text-blue-dark text-xs font-bold py-1 px-2 rounded-full mr-1">
            (
              ReasonReact.stringToElement("ABV " ++ string_of_float(abv) ++ "%")
            )
          </span>
          <span
            className="bg-blue-lighter text-blue-dark text-xs font-bold py-1 px-2 rounded-full">
            (ReasonReact.stringToElement("IBU " ++ string_of_int(ibu)))
          </span>
        </div>
        <h3 className="mb-1">
          (ReasonReact.stringToElement("Food Pairings"))
        </h3>
        <ul className="text-sm list-reset sm:leading-loose">
          (
            ReasonReact.arrayToElement(
              foodPairing
              |> Array.map(pairing =>
                   <li
                     key=(Utils.keyHasher(pairing))
                     className="test-beer-card-food-pairing">
                     (ReasonReact.stringToElement(pairing))
                   </li>
                 )
            )
          )
        </ul>
      </div>
    </div>;
  }
};
