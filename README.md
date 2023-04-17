# Getting started
- Install modm following [the official installation guide](https://modm.io/guide/installation/)
- Clone this repository to the parent directory of your modm repo (with the `--recursive` flag for the DAQP submodule).
- To compile the example, `cd stm32-daqp/src`, then `lbuild build && scons -j8 program`
- use terminal emulator of your choice to see output, e.g., `picocom /dev/ttyACM0 -b 115200 --imap lfcrlf` (might be different `ttyXYZ` device on your system)