let component = ReasonReact.statelessComponent("Error");

let make = _children => {
  ...component,
  render: _self =>
    <section className="bg-red-darker text-white p-6 text-center">
      (
        ReasonReact.stringToElement(
          "Something went wrong! We are very sorry. Please try again later."
        )
      )
    </section>
};
