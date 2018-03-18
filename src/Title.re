let component = ReasonReact.statelessComponent("Title");

let make = _children => {
  ...component,
  render: _self => {
    let basePath = Utils.basePath;
    <a className="no-underline text-black" href={j|$basePath|j} title="Home">
      <h1 className="sm:text-5xl mb-6 test-app-title">
        (ReasonReact.stringToElement({js|🍺|js} ++ " What's with dinner?"))
      </h1>
    </a>;
  }
};
