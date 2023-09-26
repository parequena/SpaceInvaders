# Space Invaders

Space Invaders made with SDL2 on Windows using C++17 and ECS approach.

[Twitter](https://twitter.com/conPdePABLO)

[LinkedIn](https://www.linkedin.com/in/parequena/)

[GitHub](https://github.com/parequena)

## Features
- This repo has been updated on 26/09/2023, integrating some Sanitizers and all warnings enabled as errors, surely this code has not been revised, **I SAW SOME LEAK SANITIZER ERRORS** can I won't solve them right now.
- Using SDL2 just as graphic api.
- C++17 features:
    - Smart pointers.   
    - Lambdas.
    -   Algorithm lib.
    -   Etc...

## File Structure

- **Assets:** Assets files, to display on the screen (link below).
- **githubResource:** This is a folder with some images to this README.
- **components:** Components used on the game.
- **game:** Game files, as Main Menu, or Game State.
- **Libraries:** Libs to store SDL and dependencies.
- **systems:** Some systems.
- **tinyECS:** Core tinyECS.
- **main.cpp** main file.
 
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
$ mkdir build
$ cd build
$ cmake .. --preset gcc_release
$ cd gcc_release
$ cmake --build . -j
```

## Some Images
~~*TODO*~~

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
