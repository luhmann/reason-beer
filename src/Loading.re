let component = ReasonReact.statelessComponent("Loading");

let make = _children => {
  ...component,
  render: _self =>
    <section className="spinner test-loading-indicator">
      <div className="bounce1" />
      <div className="bounce2" />
      <div className="bounce3" />
    </section>
};
