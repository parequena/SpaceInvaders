/*
    Project: Space Invaders
    Author : Pablo Requena (Twitter: @conPdePABLO)
    GitHub : https://github.com/parequena/
    Date   : May 2020
*/

#pragma once

#include <optional>
#include <memory>
#include <unordered_map>
#include <chrono>
#include <array>

// Assets
constexpr std::array kAssets{ "Assets/Background/wall.png", "Assets/Background/background.jpg",
   "Assets/Player/spaceship.png", "Assets/Enemy/spaceship_enemy_red.png", "Assets/Player/bullet.png",
   "Assets/Enemy/bullet_enemy.png", "Assets/Aestroids/aestroid_brown.png" };

// FPS.
constexpr auto kFPS{ 60 };
constexpr auto kFRAMERATE{ std::chrono::milliseconds{ 1000 } / kFPS };

// Window.
constexpr auto kWindWidht{ 640UZ };
constexpr auto kWindHeight{ 480UZ };

// Sizes.
constexpr auto kSpaceShipSize{ 30UZ };
constexpr auto kAesteroidSize{ 80UZ };
constexpr auto kAesteroidPadding{ 130UZ };
constexpr auto kXAesteroidInit{ 80U };
constexpr auto kYAesteroidInit{ 300U };
constexpr auto kBulletSize{ 10U };
constexpr auto kBulletSpeed{ 8 };

// Enemies
constexpr auto kEnemiesPadding{ 20UZ };
constexpr auto kXEnemiesInit{ 40U };
constexpr auto kYEnemiesInit{ 40U };

// Menu
constexpr auto kTitle{ "SPACE INVADERS" };
constexpr auto kTitleWidth{ 420UZ };
constexpr auto kTitleHeight{ 130UZ };
constexpr auto kTitleXInit{ kWindWidht / 2 - kTitleWidth / 2 };
constexpr auto kTitleYInit{ 15UZ };

constexpr auto kMenuWidth{ 128UZ };
constexpr auto kMenuHeight{ 128UZ };
constexpr auto kMenuXInit{ kWindWidht / 2 - kMenuWidth / 2 };
constexpr auto kMenuYInit{ 150UZ };

// "Defines"
// Vector.
template <typename T> using vect_t = std::vector<T>;

// Hash table.
template <typename k, typename v> using hash_t = std::unordered_map<k, v>;

// Unique ptr.
template <typename T> using uptr_t = std::unique_ptr<T>;

// Reference wrapper.
template <typename T> using refWra_t = std::reference_wrapper<T>;

// Optional
template <typename T> using optRef_t = std::optional<refWra_t<T>>;