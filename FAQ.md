

# Why does FlightCrew keep telling me that `<svg>` elements are not allowed? #

You probably have an `<svg>` element as a direct child of the `<body>` element. That's not allowed (see [issue #1](https://code.google.com/p/flightcrew/issues/detail?id=#1)). Just wrap your `<svg>` in a `<div>` and it will validate just fine.

# Why does FlightCrew complain about my TrueType font media type? I thought the media type for TT fonts was not standardized. #

The _de facto_ standard is "application/x-font-ttf", also recognized by ISO/IEC JTC 1/SC34. FligthCrew enforces the use of that media type since it's an industry best practice. See [issue #2](https://code.google.com/p/flightcrew/issues/detail?id=#2) for more details.
