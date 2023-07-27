# therappeye

Eye, vision and coordination exercises.

(documentation is a work in progress)

## The Story

Certain exercises and strategies that can help maintain and improve visual function, and potentially mitigate the impact of vision problems.

> It's important to note that the effectiveness of these exercises may vary depending on the individual and the progression of the disease. As always, this is not a space to seek medical answers.

Here are some general exercises that we may cover:

* Eye tracking exercises: These exercises involve following a moving object, such as a finger or a pen, with the eyes, and can help improve eye coordination and tracking abilities.
* Gaze stabilization exercises: These exercises aim to improve visual stability and reduce nystagmus. One example is to focus on an object while the head is moving slowly from side to side or up and down.
* Visual scanning exercises: These exercises involve looking systematically around the environment to improve visual attention and awareness of the surroundings.
* Saccade exercises: Saccades are rapid, voluntary eye movements that shift the gaze from one point to another. Practicing saccades can improve eye movement control.
* Visual acuity exercises: These exercises focus on improving the ability to see fine details. Reading, puzzles, or visual matching games can be helpful.
* Contrast sensitivity exercises: Working with different levels of contrast (e.g., using low-contrast charts) can improve the ability to distinguish objects in various lighting conditions.
* Photophobia management: For individuals with photophobia, using tinted lenses or wearing a hat or visor outdoors can help reduce light sensitivity.
* Adaptive strategies: Learning to adapt to visual changes by using lighting cues, contrasting colors, or modifying the environment can improve functional vision.

## Prerequisites

### SFML

`Therappeye` requires the Simple and Fast Multimedia Library (`SFML`).
`SFML` is an open source, multi-platform library that works on Windows, Linux, and MacOS (including the newer Apple Silicon chips). You can visit the `SFML` website at <https://www.sfml-dev.org/index.php> or go to the official `Github` repository at <https://github.com/SFML/SFML>. Their website contains the download instructions and all of the documentation for the libraries. See the directions below for a quick overview of getting `SFML` installed on your system.

> The minimum required version of SFML is: `2.6.0+`

#### * MacOs (M1/M2 chips)

#### * Macos (x86 intel chips)

#### * Linux (All distributions)

#### * Windows (10/11)

### C/C++ Compiler

`Therappeye` will require a C/C++ compiler to build the application. See below for a list of <u>recommended</u> compilers per Operating System:

* MacOS: `clang++` or `g++` (if available)
* Linux: `g++`
* Windows (option 1): install `MinGW` at <https://sourceforge.net/projects/mingw/> and then `g++`
* Windows (option 2): install Windows Subset for Linux (`WSL`) at <https://learn.microsoft.com/en-us/windows/wsl/install> using Debian/Ubuntu's `g++`

## How to run

* Clone
* Prerequisites
* (linux) `g++ src/main.cpp src/presentation.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system`. Then `./sfml-app`

> For CUDA-LAB: `nvcc src/<filename>.cu -o cusfml-app -lsfml-graphics -lsfml-window -lsfml-system`. Then `./cusfml-app`

## Contributing

Feel free to contribute to this project by submitting a pull request.
