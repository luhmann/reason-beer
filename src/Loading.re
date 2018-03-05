let component = ReasonReact.statelessComponent("Loading");

let make = _children => {
  ...component,
  render: _self =>
    <section> (ReasonReact.stringToElement("Loading")) </section>
};
