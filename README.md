<img src="./res/8ball.png" width="162"  align="left" />
# c8
> Chip8 - interpreter

[![Language](https://img.shields.io/badge/language-C++14-blue.svg?style=flat-square)](https://isocpp.org)
[![GitHub release](https://img.shields.io/github/release/dawikur/c8.svg?style=flat-square)](https://github.com/dawikur/c8/releases)
[![Linux Build Status](https://img.shields.io/travis/dawikur/c8/master.svg?label=linux&style=flat-square)](https://travis-ci.org/dawikur/c8)
[![WindowsBuild](https://img.shields.io/appveyor/ci/dawikur/c8.svg?label=windows&style=flat-square)](https://ci.appveyor.com/project/dawikur/c8)

> **CHIP-8** is an interpreted programming language, developed by Joseph Weisbecker. It was initially used on the COSMAC VIP and Telmac 1800 8-bit microcomputers in the mid-1970s. CHIP-8 programs are run on a CHIP-8 virtual machine. It was made to allow video games to be more easily programmed for said computers.
> > *Wikipedia*

<img src="./res/1.png" align="right" />

c8 is c++14 application and is maintained undef Windows and Linux. It uses [Nana C++][nanacpp] as the GUI library.

Features:
* **drag&drop** drag `rom` file on the binary file or on the display area
* **auto-resizing** the display area will automatically fit to the window's size
* **themes** you can choose display theme; `light`, `dark` or `matrix`
* **scaling** use [hqx][hqx] for scaling display up to `256x128 px`
* **clock** choose how fast clock should tick, between `64Hz` and `1024Hz`

[hqx]: https://en.wikipedia.org/wiki/Hqx
[nanacpp]: https://github.com/cnjinhao/nana

<img src="./res/2.png" align="center" />
