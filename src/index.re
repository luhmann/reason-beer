[%bs.raw {|require('./css/main.css')|}];

ReactDOMRe.renderToElementWithId(
  <Router> ...((~searchTerm) => <App searchTerm />) </Router>,
  "app"
);
