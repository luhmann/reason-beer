let component = ReasonReact.statelessComponent("Beer");

type brew = {
  id: int,
  name: string,
  tagline: string,
  image: string,
  description: string,
  abv: float,
  ibu: int,
  ebc: int,
  foodPairing: array(string)
};

let make =
    (
      ~name,
      ~tagline,
      ~description,
      ~abv,
      ~ibu,
      ~ebc,
      ~foodPairing,
      ~image=?,
      _children
    ) => {
  ...component,
  render: _self => {
    let imageItem =
      switch image {
      | None => ReasonReact.nullElement
      | Some(img_url) =>
        let url =
          Utils.getFilename(img_url)
          |> Js.Option.getWithDefault(img_url)
          |> Utils.generateImgUrl;
        <div
          className="bg-contain bg-top bg-no-repeat h-48 sm:h-auto beerImg-width test-beer-card-img"
          style=(ReactDOMRe.Style.make(~backgroundImage={j|url($url)|j}, ()))
        />;
      };
    <div
      className="shadow-lg rounded mb-4 overflow-hidden max-w-md p-3 sm:flex test-beer-card">
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
          <Tag>
            ...(
                 ReasonReact.stringToElement(
                   "ABV " ++ string_of_float(abv) ++ "%"
                 )
               )
          </Tag>
          <Tag>
            ...(ReasonReact.stringToElement("IBU " ++ string_of_int(ibu)))
          </Tag>
          <Tag>
            ...(ReasonReact.stringToElement("EBC " ++ string_of_int(ebc)))
          </Tag>
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
