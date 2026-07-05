# Mint's header-only libraries

## Usage
Download whatever headers you need and include them wherever you need. That's it. \
Headers do not use features from C++20 or newer. \
The libraries are only tested on Linux. `mbox` does not work on Windows. \
The API is still unstable. Bugs will be fixed immediately if reported.

## Documentation
The code is the documentation. \
Just read the example and the comments. There isn't much else to know.

## Headers
- `mlog` - C++ logging library; output to stdin/stderr (colored) or a file.
- `mbox` - Advanced POSIX terminal I/O inspired with `termbox2`.
- `mcfg` - INI reader and writer with a reasonable API.