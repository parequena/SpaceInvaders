# Space Invaders

Space Invaders made with SDL2 (Updated to SDL3) on Windows using VisualStudio2019-C++17 (Updated into CMake-C++23) and ECS approach.

## Some Images
![Image displaying Main Menu](/githubResource/Screenshot_1.png "Menu")
![Image displaying Main Game](/githubResource/Screenshot_2.png "Game")


## Features
- This repo has been updated on 26/09/2023, integrating some Sanitizers and all warnings enabled as errors, surely this code has not been revised, **I SAW SOME LEAK SANITIZER ERRORS** can I won't solve them right now.
- Using SDL3 just as graphic api.
- C++17 features:
    - Smart pointers.   
    - Lambdas.
    -   Algorithm lib.
    -   Etc...

## File Structure

- **Assets:** Assets files, to display on the screen (link below).
- **githubResource:** This is a folder with some images to this README.
- **src/components:** Components used on the game.
- **src/game:** Game files, as Main Menu, or Game State.
- **libs:** Libs to store SDL and dependencies.
- **src/systems:** Some systems.
- **src/tinyECS:** Core tinyECS.
- **src/main.cpp:** main file.
 
## Installation and compilation
### Dependencies
* CMake 3.27 or later
* A build tool like Ninja, GNU Make or Visual Studio
* A C++23-compliant compiler, such as:
  * GCC 13 or later
  * Clang 16 or later
  * Visual Studio 2022 or later

#### Using CMake (preferred):
##### CMake presets:
* gcc:
    * gcc_debug
    * gcc_release
* clang:
    * clang_debug
    * clang_release
* Windows MVSC (Visual Studio 2022):
    * wind_debug
    * wind_release
* Windows Clang (Visual Studio 2022):
    * wind_clang_debug
    * wind_clang_release

Let's see an example with `gcc_release` as preset, but you can choose another from this list.
```
$ git clone --recurse-submodules https://github.com/parequena/SpaceInvaders
#               git submodule update --init # if fails
$ mkdir build
$ cd build
$ cmake .. --preset gcc_release
$ cd gcc_release
$ cmake --build . -j
```

##### Windows
As we don't have freetype on Windows, we need it for compiling
```
$ git clone --recurse-submodules https://github.com/parequena/SpaceInvaders
#               git submodule update --init # if fails
$ cd libs/SDL_ttf/
$ git submodule update --init external/freetype/
$ cd ../..
$ mkdir build
$ cd build
$ cmake .. --preset wind_release
$ cd wind_release
$ cmake --build . -j
```

## TODO
- Create AI system.
- Create Collision system.
- Create HP system.
- Physics system.
- Improve menu.
- Improve string render (SDL_ttf).
- Changing the GameContext_t to another approach.

# Resources
- **tinyECS inspiration:** [Profesor Retroman C++ : Programación de Videojuegos [2019/20] - Youtube List](https://www.youtube.com/playlist?list=PLmxqg54iaXrhTqZxylLPo0nov0OoyJqiS) << Very changed.
- **Graphical Assets:** https://opengameart.org/content/complete-spaceship-game-art-pack
- **Font:** https://www.dafont.com/es/pokemon-x-and-y.font
