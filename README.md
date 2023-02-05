# Your take-home test
## Why
We need to see your code, so we can get a better understanding of your coding skills and habits. This test is one way to get there. We are happy to discuss alternatives.

## Prerequisites
You will need a C++ compiler that supports C++17 or later as well as CMake 3.14 or later on MacOS, Windows or Linux.
We've seen successful builds on other platforms as well.

## What

Your input data is a JSON file that contains a set of 2-D line segments. Some line segments may be merged: they are
parallel and share an endpoint. You need to find all mergeable lines and merge them. We have provided some code to get
you started.

## How
Use this code to set up a project. Be sure to create a local Git repository so your commits are tracked. Implement, push to a private repository on GitHub, BitBucket or similar and give us access to that repository. On GitHub, we are at *glodon-usa-hiring*.

Setup and build instructions [here](BUILD.md).

The code should compile and run under a C++20 or a C++17 compliant compiler under MacOs, Windows or Linux.

Setting up the environment should take less than an hour, depending on your current setup. We suggest time-boxing the
coding part of the exercise to about four hours. We are not looking for a perfect implementation - limit the scope to
the best of your judgment. We might, however, ask you to do further work on your code during the face-to-face interview.


## What we are looking for
This test is designed, in part, to access your fit as a team member. As a team, we place significant value on well designed, properly tested, self-documented code. You will get extra points for:
* Good engineering judgment
* Clean, maintainable code
* Thoughtful test coverage
* History of commits: we'd like to see your path to the solution.
* A half-page writeup with your thoughts on the test, suggestions and concerns.

## Other

* This project was created in JetBrains CLion on MacOS. It was verified to work in MS Visual Studio Community edition on
  Windows 10 and 11, as well as with gcc on Ubuntu 18.04-22.04.
* Use of CMake is intentional - we want the test to work under MacOS, Windows and Linux. The root CMakeLists.txt is
  pretty self-explanatory.
* When in doubt, use your judgment. If stuck or need help, ping us.

Thank you for your time. We can't wait to see your implementation.

Good luck and have fun!

#### Acknowledgments and credits
This project uses Catch2 test framework by [Martin Hořeňovský](https://github.com/catchorg/) and RapidJSON by Tencent. All 3rd party components are property of the respective owners and are used according to their licenses.


