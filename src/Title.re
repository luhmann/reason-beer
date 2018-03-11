let component = ReasonReact.statelessComponent("Title");

let make = _children => {
  ...component,
  render: _self =>
    <h1 className="sm:text-5xl mb-6">
      (ReasonReact.stringToElement("What's with dinner?"))
    </h1>
};
