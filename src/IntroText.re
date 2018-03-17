let component = ReasonReact.statelessComponent("IntroText");

let make = _children => {
  ...component,
  render: _self =>
    <section className="text-grey-darkest p-1">
      <p className="mb-6">
        (
          ReasonReact.stringToElement(
            {| Want to enjoy a nice fresh brew with your favorite dinner?
            This app searches through the catalogue of Brewdog Beers to find a good companion
            for your food tonight.
          |}
          )
        )
      </p>
      <p className="mb-4 text-sm">
        (ReasonReact.stringToElement("Built using"))
        (ReasonReact.stringToElement(" "))
        <Link href="https://reasonml.github.io/">
          ...(ReasonReact.stringToElement("ReasonML"))
        </Link>
        (ReasonReact.stringToElement(", "))
        <Link href="https://reasonml.github.io/reason-react/">
          ...(ReasonReact.stringToElement("ReasonReact"))
        </Link>
        (ReasonReact.stringToElement(" and "))
        <Link href="https://tailwindcss.com/">
          ...(ReasonReact.stringToElement("Tailwind"))
        </Link>
        (ReasonReact.stringToElement(". Many thanks to "))
        <Link href="https://punkapi.com/documentation/v2">
          ...(ReasonReact.stringToElement("PunkApi"))
        </Link>
        (
          ReasonReact.stringToElement(
            " for powering this project and providing the data."
          )
        )
      </p>
      <p className="mb-4 text-sm">
        (
          ReasonReact.stringToElement(
            "This project was written as an excercise. You can access the source-code on "
          )
        )
        <Link href="https://github.com/luhmann/reason-beer">
          ...(ReasonReact.stringToElement("Github"))
        </Link>
        (ReasonReact.stringToElement("."))
      </p>
    </section>
};
