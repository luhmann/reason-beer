let component = ReasonReact.statelessComponent("Error");

let make = _children => {
  ...component,
  render: _self => <section> (ReasonReact.stringToElement("Error")) </section>
};
