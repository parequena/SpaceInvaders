cmake_minimum_required(VERSION 3.26)
project(SpaceInvaders)

set(PROJECT_WARNINGS "${SANITIZER_FLAGS};${GENERAL_COMPILER_WARNINGS};${SPECIFIC_COMPILER_WARNINGS}")

add_executable(SpaceInvaders)

add_subdirectory(libs)

target_compile_options(SpaceInvaders PRIVATE ${PROJECT_WARNINGS})
set_property(TARGET SpaceInvaders PROPERTY COMPILE_WARNING_AS_ERROR ON)
target_compile_features(SpaceInvaders PRIVATE cxx_std_23)
target_include_directories(SpaceInvaders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(SpaceInvaders PRIVATE ${LINKER_FLAGS} ${SANITIZER_FLAGS} SDL3::SDL3 SDL3_image::SDL3_image-static Freetype::Freetype SDL3_ttf::SDL3_ttf-static)
target_sources(SpaceInvaders
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/src/components/AICmp.h
${CMAKE_CURRENT_SOURCE_DIR}/src/components/CollisionCmp.h
${CMAKE_CURRENT_SOURCE_DIR}/src/components/HPCmp.h
${CMAKE_CURRENT_SOURCE_DIR}/src/components/InputCmp.h
${CMAKE_CURRENT_SOURCE_DIR}/src/components/PhysicsCmp.h
${CMAKE_CURRENT_SOURCE_DIR}/src/components/RenderCmp.h
${CMAKE_CURRENT_SOURCE_DIR}/src/game/Map.h
${CMAKE_CURRENT_SOURCE_DIR}/src/game/MenuState.h
${CMAKE_CURRENT_SOURCE_DIR}/src/systems/InputSys.h
${CMAKE_CURRENT_SOURCE_DIR}/src/systems/RenderSys.h
${CMAKE_CURRENT_SOURCE_DIR}/src/tinyECS/Component.h
${CMAKE_CURRENT_SOURCE_DIR}/src/tinyECS/ComponentStorage.h
${CMAKE_CURRENT_SOURCE_DIR}/src/tinyECS/Entity.h
${CMAKE_CURRENT_SOURCE_DIR}/src/tinyECS/EntityManager.h
${CMAKE_CURRENT_SOURCE_DIR}/src/tinyECS/GameContext.h
${CMAKE_CURRENT_SOURCE_DIR}/src/tinyECS/StateManager.h
${CMAKE_CURRENT_SOURCE_DIR}/src/tinyECS/utils.h
PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/src/components/AICmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/components/CollisionCmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/components/HPCmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/components/InputCmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/components/PhysicsCmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/components/RenderCmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/game/Map.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/game/MenuState.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/systems/InputSys.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/systems/RenderSys.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/tinyECS/EntityManager.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/tinyECS/StateManager.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

message("Copying Assets folder into: ${CMAKE_BINARY_DIR}/Assets")
file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR}/)