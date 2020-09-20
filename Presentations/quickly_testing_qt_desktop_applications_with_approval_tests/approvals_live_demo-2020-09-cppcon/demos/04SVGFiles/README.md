# 4 SVGFiles

## Steps

* Run the demo - the test fails
    * **Does the change matter**?
    * Can create derived copies of your file
    * For better visualisation
    * Don't need to version-control the extra copies

## In longer demos

* Set the file extension
    * Want approved files to have natural file extension
    * Options have a fluent interface - chain steps together
* Recommend creating `verifyYourThing()` to encapsulate and re-use tests
* And add `const Options& options = Options()` argument to your verify functions
