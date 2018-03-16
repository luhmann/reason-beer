let component = ReasonReact.statelessComponent("Loading");

let make = _children => {
  ...component,
  render: _self =>
    <section className="spinner">
      <div className="bounce1" />
      <div className="bounce2" />
      <div className="bounce3" />
    </section>
};
