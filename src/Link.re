let component = ReasonReact.statelessComponent("Link");

let make = (~href, children) => {
  ...component,
  render: _self =>
    <a className="no-underline text-blue-light" href> children </a>
};
