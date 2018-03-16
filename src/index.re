[%bs.raw {|require('./css/main.css')|}];

ReactDOMRe.renderToElementWithId(
  <Router>
    ...(
         (~searchTerm) =>
           <FetchBeers searchTerm>
             ...((~beerFetcher) => <App beerFetcher />)
           </FetchBeers>
       )
  </Router>,
  "app"
);
