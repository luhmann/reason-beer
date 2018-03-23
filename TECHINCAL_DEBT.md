## Write more components

*   [x] Links
*   [x] Tags (ABV, IBU, etc)
*   [ ] Paragraphs

## Cancel async requests in Fetching-Components

Check how `bs-axios` is implemented. The component may be mounted/unmounted multiple times during render and fetching
is a side-effect, we may need to cancel requests here
