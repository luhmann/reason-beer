let component = ReasonReact.statelessComponent("IntroText");

let make = _children => {
  ...component,
  render: _self =>
    <section className="text-grey-darkest">
      (
        ReasonReact.stringToElement(
          {| Everyone needs a nice fresh brew with their favorite dinner.
            This app searches through the catalogue of Brewdog Beers to find a good companion
            for your food tonight.
          |}
        )
      )
    </section>
};
