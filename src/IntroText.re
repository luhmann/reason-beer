let component = ReasonReact.statelessComponent("IntroText");

let make = _children => {
  ...component,
  render: _self =>
    <section> (ReasonReact.stringToElement("IntroText")) </section>
};
