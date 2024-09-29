# Fifteenky

This is an implementation of a classic game Puzzle of 15 written in C++ and WinAPI using OOP principles.
__Features:__
- __Manual assembly__ of Puzzle 15.
- __Autoassembly__ of Puzzle 15 based on __the A* algorithm__.
- Ability to __generate random solvable positions__.
- Victory condition and congratulatory message.
_It is written as an educational project in C++ and WinAPI using OOP principles._

## Installation

Download and install [the latest release](https://github.com/serhii721/fifteenky/releases/tag/v1.0.0).

## Prerequisites

To run the application it is necessary to install [Microsoft Visual C++ 2017 Redistributable packages (x86)](https://aka.ms/vs/17/release/vc_redist.x86.exe).

## Configuration

In the settings, a user can:
- Choose the speed of autoassembly.
- Choose between roman and arabic numerals.
- Toggle nightmode.

## Screenshots

![Night mode](https://raw.github.com/serhii721/fifteenky/screenshots/Screenshots/screen1.jpg "Night mode")
![Roman font](https://raw.github.com/serhii721/fifteenky/screenshots/Screenshots/screen2.jpg "Roman font")

## Development notes

_Microsoft Visual Studio 2017 (15.9.59) is used for development._
There is the `AStar` class that contains algorithm methods.