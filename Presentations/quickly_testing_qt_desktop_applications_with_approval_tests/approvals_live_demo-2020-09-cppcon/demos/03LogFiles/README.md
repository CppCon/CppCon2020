# 3 LogFiles

## Steps

### First pass

* `[logfiles_1]`
* Get a filename
* Create a stream to send the output to
* Do stuff, write to the file
* Close the file
* Approvals::verifyExistingFile()
* But test keeps failing!

```c++
    // Get a filename
    const auto filename =
        Approvals::getDefaultNamer()->getReceivedFile( ".log" );

    {
        // Open the output file:
        std::ofstream stream( filename );

        // Do stuff - write to the file
        stuff.doStuff( stream );

        // Close the file
    }

    Approvals::verifyExistingFile( filename );
```

### Second pass

* `const auto dateRegex = R"([A-Za-z]{3} [A-Za-z]{3} [\d ]\d \d\d:\d\d:\d\d \d\d\d\d)";`
* `Scrubbers::createRegexScrubber()`
    * could create a `date_regex` live template in CLion - **fake it until we make it**
* `[date_and_time]`

```c++
    // Example matches:
    // Mon Jun  2 14:07:34 2020
    // Mon Jun 22 14:07:34 2020
    const auto dateRegex =
        R"([A-Za-z]{3} [A-Za-z]{3} [\d ]\d \d\d:\d\d:\d\d \d\d\d\d)";

    const auto replacementText = "[date_and_time]";

    const auto scrubber =
        Scrubbers::createRegexScrubber( dateRegex, replacementText );

    Approvals::verifyExistingFile(
        filename, Options().withScrubber( scrubber ) );
```

## Key Points

* Approvals::verifyExistingFile() if you have written the file out already, and want to approve it
* If you have non-deterministic output, consider Scrubbers to make the output stable
