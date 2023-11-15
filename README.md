# therappeye

Eye, vision and coordination exercises.

(documentation is a work in progress)

## Latest Update

the original idea was to get the environment to run a Presentation -> Scenes -> Slides scheme.

Looking into the video-series (see "source playlist") we realized there was an opportunity for a new slide sligthly
based on the series-proposed game.

In a future version, tracking users eyes with CV, be it up close from a wereable glass or VR device would be great. First release will base on a mouse click, discrete or element-over.

> source playlist by Suraj Sharma (https://www.youtube.com/@SurajSharmaFourKnob) available at https://www.youtube.com/playlist?list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up

We're ditching the `presentation->scene->slide` infrastructure in favor of integrating an `slide` slice, basing the main loop on what's proposed in the series.


## The Story

Certain exercises and strategies that can help maintain and improve visual function and potentially mitigate the impact of vision problems.

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

## Usage

To use this engine, simply compile and run the `main.cpp` file located in the `src` directory.

> Once running, press the 'N' key to cycle through the slides, or the 'Q' to quit the app.

## Compiling for MacOS with provided Makefiles

If you are using MacOs along with having installed the `frameworks` for `SFML` (as suggested by their website):

* open a terminal.
* `cd` into `therappeye` folder.
* run command `make therappeye -f makeMac.mk`. The `-f` argument tells `make` which `makefile` to use.
* for now (08/09/2023) some warnings will be generated but program will compile.
* run command `./therappeye` to start program.

If you would like to clean the directory (remove object files, debug symbols), use command `make clean -f makeMac.mk` in the `therappeye` folder.

If you would like to remove the executable, use the command `rm -f therappeye` in the `therappeye` folder.

## Compiling for a Unix/Linux based platform with Provided Makefiles

If you are using a Unix/Linux based platform, which includes `Windows Subset for Linux (WSL)` on Windows and VSCode's integrated `bash` terminal. And have installed the `libraries` for `SFML`, do the following:

* open a terminal.
* `cd` into `therappeye` folder.
* run command `make therappeye -f makeUnix.mk`. The `-f` argument tells `make` which `makefile` to use.
* for now (08/09/2023) some warnings will be generated but program will compile.
* run command `./therappeye` to start program.

If you would like to clean the directory (remove object files, debug symbols), use command `make clean -f makeUnix.mk` in the `therappeye` folder.

If you would like to remove the executable, use the command `rm -f therappeye` in the `therappeye` folder.

## Prerequisites

In Linux, make sure you have:

Ubuntu, Debian:

* `sudo apt-get install libsfml-dev`

> **Devcontainer:** the development container image takes care of `libsfml-dev` library installation. If you choose such dev scenario, the prereq will be satisfied already.

## How to run

* Clone
* Prerequisites
* (linux) `g++ src/main.cpp src/engine.cpp src/slide.cpp -o therappeye -lsfml-graphics -lsfml-window -lsfml-system`. Then `./therappeye`

> For CUDA-LAB: `nvcc src/main.cu -o cuda-therappeye  -lsfml-graphics -lsfml-window -lsfml-system`. Then `./cuda-therappeye`

Once running, press letter `n` from the keyboard to move to 'n'ext scene (exercise). Once you reach the end, press `q`  to 'quit' and terminate the program.

## Contributing

You're free to contribute to this project by submitting a pull request.
