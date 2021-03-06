QtStreamer
==========

QtStreamer is a simple dialog to graphically start
[Streamlink](https://streamlink.github.io/). Type in a stream you want to
watch, or select one from the list of streams you've watched before. The list
of streams is remembered and editable.

![QtStreamer GUI](qtstreamer.png)

To use you need to have Streamlink installed and available in `PATH` and
configured to use the video player of your choice (defaults to VLC). I
recommend using [Chocolatey](https://chocolatey.org/) and running `choco
install livestreamer vlc`.

To build you will need Qt and CMake.

*Note*: This used to use Livestreamer, which I have heard is now a dead
project. Changing the source to run `livestreamer` instead is trivial: Change
the value of the `program` string in the `Dialog` class.
