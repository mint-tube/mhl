# Mint's header-only libraries

## How do I use these

Download whatever headers you need and include them wherever you need. That's it. \
Headers may use features from C++17 but not anything newer. \
The libraries are not tested and might not even compile on Windows.

## Where can I find the documentation

The code is the documentation. Just read the example and the comments before \
methods. There isn't much else to know.

## List of avaliable headers

- `mlog` - The simplest possible C++ logging library; output to either stdin/stderr (colored) or specified path. 90 LOC.
- `mbox` - Advanced terminal I/O library inspired by `termbox2`. 2700 LOC.
<!-- - `mcfg` - TODO -->