set( BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE )

# SDL
# https://github.com/libsdl-org/SDL
# https://github.com/libsdl-org/SDL/blob/main/docs/README-cmake.md
set(SDL_SHARED OFF)
set(SDL_TEST_LIBRARY OFF)
set(SDL_TESTS OFF)
set(SDL_DISABLE_INSTALL ON)
set(SDL_DISABLE_INSTALL_DOCS ON)
set(SDL_INSTALL_TESTS OFF)
add_subdirectory( SDL )

# SDL_image
# https://github.com/libsdl-org/SDL_image
add_subdirectory( SDL_image )

# freetype (Windows fails)
# https://github.com/freetype/freetype
add_subdirectory( freetype )

# SDL_ttf
# https://github.com/libsdl-org/SDL_ttf
add_subdirectory( SDL_ttf )