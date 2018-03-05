let component = ReasonReact.statelessComponent("Beer");

type brew = {
  id: int,
  name: string,
  image: string,
  description: string,
  foodPairing: array(string)
};

let make = (~name, ~description, ~foodPairing, ~image=?, _children) => {
  ...component,
  render: _self => {
    let imageItem =
      switch image {
      | None => ReasonReact.nullElement
      | Some(i_) =>
        <div
          className="bg-contain bg-center flex-grow bg-no-repeat h-48 w-32 sm:h-auto sm:w-64"
          style=(
            ReactDOMRe.Style.make(
              ~backgroundImage={j|url($i_)|j},
              ~minWidth="8rem",
              ()
            )
          )
        />
      };
    <div
      className="shadow-lg rounded mb-4 overflow-hidden max-w-md p-3 sm:flex">
      imageItem
      <div className="p-4">
        <h2 className="font-black mb-3 tracking-wide">
          (ReasonReact.stringToElement(name))
        </h2>
        <p className="text-sm text-gray-dark mb-4">
          (ReasonReact.stringToElement(description))
        </p>
        <h3> (ReasonReact.stringToElement("Food Pairings")) </h3>
        <ul className="text-sm text-gray-dark list-reset">
          (
            ReasonReact.arrayToElement(
              foodPairing
              |> Array.map(pairing =>
                   <li> (ReasonReact.stringToElement(pairing)) </li>
                 )
            )
          )
        </ul>
      </div>
    </div>;
  }
};
