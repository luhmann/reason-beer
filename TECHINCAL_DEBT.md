## Write more components

*   [x] Links
*   [ ] Tags (ABV, IBU, etc)
*   [ ] Paragraphs

## Images

Images are not under my control but are potentially huge, they are all loaded right away, which is bad
especially on mobile. Consider:

*   Proxying images over a scaling server
*   Using lazy-loading

## Cancel async Fetching-Component

Check how `bs-axios` is implemented. The component may be mounted/unmounted multiple times during render and fetching
is a side-effect, we may need to cancel requests here
