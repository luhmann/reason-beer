let component = ReasonReact.statelessComponent("App");

let make = _children => {
  ...component,
  render: _self =>
    <div className="container mx-auto p-4">
      <Search
        placeholderText="Enter a food you want to pair with a beer, eg. 'Burger'"
        onSubmit=(searchText => Js.log2("outside", searchText))
      />
    </div>
};
