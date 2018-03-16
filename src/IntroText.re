let component = ReasonReact.statelessComponent("IntroText");

let make = _children => {
  ...component,
  render: _self =>
    <section className="text-grey-darkest p-1">
      <p className="mb-4">
        (
          ReasonReact.stringToElement(
            {| Want to enjoy a nice fresh brew with your favorite dinner?
            This app searches through the catalogue of Brewdog Beers to find a good companion
            for your food tonight.
          |}
          )
        )
      </p>
      <p>
        (ReasonReact.stringToElement("Built using the"))
        (ReasonReact.stringToElement(" "))
        <a
          className="no-underline text-blue-light"
          href="https://punkapi.com/documentation/v2">
          (ReasonReact.stringToElement("PunkApi"))
        </a>
      </p>
    </section>
};
