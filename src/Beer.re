let component = ReasonReact.statelessComponent("Beer");

type brew = {
  id: int,
  name: string,
  image: string,
  description: string
};

let make = (~name, ~description, ~image=?, _children) => {
  ...component,
  render: _self => {
    let imageItem =
      switch image {
      | None => ReasonReact.nullElement
      | Some(i_) => <img src=i_ />
      };
    <div>
      imageItem
      <div className="p-4">
        <h2 className="font-black mb-3">
          (ReasonReact.stringToElement(name))
        </h2>
        <p> (ReasonReact.stringToElement(description)) </p>
      </div>
    </div>;
  }
};
