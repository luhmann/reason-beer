let component = ReasonReact.statelessComponent("Beer");

type brew = {
  id: int,
  name: string,
  tagline: string,
  image: string,
  description: string,
  foodPairing: array(string)
};

let make = (~name, ~tagline, ~description, ~foodPairing, ~image=?, _children) => {
  ...component,
  render: _self => {
    let imageItem =
      switch image {
      | None => ReasonReact.nullElement
      | Some(i_) =>
        <div
          className="bg-contain bg-center flex-grow bg-no-repeat h-48 sm:h-auto beerImg-width"
          style=(ReactDOMRe.Style.make(~backgroundImage={j|url($i_)|j}, ()))
        />
      };
    <div
      className="shadow-lg rounded mb-4 overflow-hidden max-w-md p-3 sm:flex">
      imageItem
      <div className="p-4">
        <h2 className="font-black tracking-wide leading-tight">
          (ReasonReact.stringToElement(name))
        </h2>
        <div className="mb-3 text-grey-darker italic">
          (ReasonReact.stringToElement(tagline))
        </div>
        <p className="text-sm mb-4">
          (ReasonReact.stringToElement(description))
        </p>
        <h3 className="mb-1">
          (ReasonReact.stringToElement("Food Pairings"))
        </h3>
        <ul className="text-sm list-reset sm:leading-loose">
          (
            ReasonReact.arrayToElement(
              foodPairing
              |> Array.map(pairing =>
                   <li key=(Utils.keyHasher(pairing))>
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
