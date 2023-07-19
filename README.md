# therappeye

Eye, vision and coordination exercises.

(documentation is a work in progress)

## The story

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

## Usage

To use this engine, simply compile and run the `main.cpp` file located in the `src` directory.

## Prerequisites

In Linux, make sure you have:

Ubuntu, Debian:
* `sudo apt-get install libsfml-dev`

> **Devcontainer:** the development container image takes care of `libsfml-dev` library installation. If you choose such dev scenario, the prereq will be satisfied already.

## How to run
* Clone
* Prerequisites
* (linux) `g++ src/main.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system`. Then `./sfml-app`

Once running, press letter `n` from the keyboard to move to 'n'ext scene (exercise). Once you reach the end, press `q`  to 'q'uit and terminate the program.

## Contributing

Feel free to contribute to this project by submitting a pull request.
