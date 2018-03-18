## Write more components

*   [x] Links
*   [ ] Tags (ABV, IBU, etc)
*   [ ] Paragraphs

## Images

Images are not under our control but potentially large in size, they are all loaded right away, which is bad
especially on mobile. Consider:

*   Proxying images over a scaling server
*   Using lazy-loading

## Cancel async requests in Fetching-Components

Check how `bs-axios` is implemented. The component may be mounted/unmounted multiple times during render and fetching
is a side-effect, we may need to cancel requests here
