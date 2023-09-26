cmake_minimum_required(VERSION 3.27)
project(SpaceInvaders)

set(PROJECT_WARNINGS "${SANITIZER_FLAGS};${GENERAL_COMPILER_WARNINGS};${SPECIFIC_COMPILER_WARNINGS}")

add_executable(SpaceInvaders)

add_subdirectory(libs)

target_compile_options(SpaceInvaders PRIVATE ${PROJECT_WARNINGS})
set_property(TARGET SpaceInvaders PROPERTY COMPILE_WARNING_AS_ERROR ON)
target_compile_features(SpaceInvaders PRIVATE cxx_std_23)
target_include_directories(SpaceInvaders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SpaceInvaders PRIVATE ${LINKER_FLAGS} ${SANITIZER_FLAGS} SDL3::SDL3 SDL3_image::SDL3_image-static SDL3_ttf::SDL3_ttf-static)
target_sources(SpaceInvaders
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/components/AICmp.h
${CMAKE_CURRENT_SOURCE_DIR}/components/CollisionCmp.h
${CMAKE_CURRENT_SOURCE_DIR}/components/HPCmp.h
${CMAKE_CURRENT_SOURCE_DIR}/components/InputCmp.h
${CMAKE_CURRENT_SOURCE_DIR}/components/PhysicsCmp.h
${CMAKE_CURRENT_SOURCE_DIR}/components/RenderCmp.h
${CMAKE_CURRENT_SOURCE_DIR}/game/Map.h
${CMAKE_CURRENT_SOURCE_DIR}/game/MenuState.h
${CMAKE_CURRENT_SOURCE_DIR}/systems/InputSys.h
${CMAKE_CURRENT_SOURCE_DIR}/systems/RenderSys.h
${CMAKE_CURRENT_SOURCE_DIR}/tinyECS/Component.h
${CMAKE_CURRENT_SOURCE_DIR}/tinyECS/ComponentStorage.h
${CMAKE_CURRENT_SOURCE_DIR}/tinyECS/Entity.h
${CMAKE_CURRENT_SOURCE_DIR}/tinyECS/EntityManager.h
${CMAKE_CURRENT_SOURCE_DIR}/tinyECS/GameContext.h
${CMAKE_CURRENT_SOURCE_DIR}/tinyECS/StateManager.h
${CMAKE_CURRENT_SOURCE_DIR}/tinyECS/utils.h
PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/components/AICmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/components/CollisionCmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/components/HPCmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/components/InputCmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/components/PhysicsCmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/components/RenderCmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/game/Map.cpp
${CMAKE_CURRENT_SOURCE_DIR}/game/MenuState.cpp
${CMAKE_CURRENT_SOURCE_DIR}/systems/InputSys.cpp
${CMAKE_CURRENT_SOURCE_DIR}/systems/RenderSys.cpp
${CMAKE_CURRENT_SOURCE_DIR}/tinyECS/EntityManager.cpp
${CMAKE_CURRENT_SOURCE_DIR}/tinyECS/StateManager.cpp
${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

message("Copying Assets folder into: ${CMAKE_BINARY_DIR}/Assets")
file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR}/)