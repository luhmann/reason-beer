let component = ReasonReact.statelessComponent("tag");

let make = (children: ReasonReact.reactElement) => {
  ...component,
  render: _self =>
    <span
      className="bg-blue-lighter text-blue-dark text-xs font-bold py-1 px-2 rounded-full mr-1">
      children
    </span>
};
