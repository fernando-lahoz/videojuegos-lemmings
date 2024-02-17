#pragma once

#include "geometry/point.hpp"

namespace Utils
{
  // LEMMINGS CONSTANTS
  const int STATE_IS_LOOP_ANIMATION[14] = {false, true, true, true, true, true, true, false, true, true, true, false, false, false}; // indicates if the animation is loop
  const int STATE_N_FRAMES[14] = {8, 9, 4, 16, 16, 16, 8, 30, 16, 32, 24, 8, 16, 16};                                                // number of frames of each animation
  const float STATE_ANIMATION_DURATION[14] = {1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};   // duration of each animation in seconds

  enum Lemming_Skills
  {
    NO_SKILLS = 0,
    CLIMB = 1,
    FLOAT = 2,
    EXPLODE = 4,
    SKILL_EGOIST = 8,
    BLOCK = 8,
    BUILD = 16,
    DIG = 32,
    BASH = 64,
    MINE = 128,
  };

  enum Lemming_State
  {
    IDLE = 0,
    WALKING = 1,
    FALLING = 2,
    BLOCKING = 3,
    BUILDING = 4,
    CLIMBING = 5,
    FLOATING = 6,
    EXPLODING = 7,
    DIGGING = 8,
    BASHING = 9,
    MINING = 10,
    ESCAPING = 11,
    DROWNING = 12,
    CRASHING = 13,
  };

  const std::string LEMMING_TYPE[15] = {"", "WALKER", "FALLER", "BLOCKER", "BUILDER", "CLIMBER", "FLOATER", "", "DIGGER", "BASHER", "MINER", "", "", "", "ATHLETE"};

  // HUD CONSTANTS
  const Point3f positions[12] = {Point3f(0.022, 0.8208333333, 3), Point3f(0.079, 0.8208333333, 3), Point3f(0.137, 0.8208333333, 3), Point3f(0.194, 0.8208333333, 3), Point3f(0.252, 0.8208333333, 3), Point3f(0.309, 0.8208333333, 3), Point3f(0.36666666665, 0.8208333333, 3), Point3f(0.424, 0.8208333333, 3), Point3f(0.482, 0.8208333333, 3), Point3f(0.539, 0.8208333333, 3), Point3f(0.597, 0.8208333333, 3), Point3f(-1, 0.8208333333, 3)};

  enum HUD
  {
    HUD_VELOCITY = 0,
    HUD_SPAWN = 1,
    HUD_CLIMBING = 2,
    HUD_FLOATING = 3,
    HUD_EXPLODE = 4,
    HUD_BLOCKING = 5,
    HUD_BUILDING = 6,
    HUD_BASH = 7,
    HUD_MINE = 8,
    HUD_DIG = 9,
    HUD_ALL_EXPLODE = 10,
    HUD_ADD_SPAWN_VELOCITY = 11,
    HUD_SUB_SPAWN_VELOCITY = 12,
    HUD_ADD_VELOCITY = 13,
    HUD_SUB_VELOCITY = 14,
    HUD_PLAY_PAUSE = 15,
    HUD_BACKGROUND = 17,
    HUD_MINIMAP = 18,
    HUD_CURSOR = 19,
  };

  const int NO_OPTION_SELECTED = 11;

  const int HUD_TO_SKILL[20] = {NO_SKILLS, NO_SKILLS, CLIMB, FLOAT, EXPLODE, BLOCK, BUILD, BASH, MINE, DIG, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS};

  // TEXT CONSTANTS
  enum TEXT_TYPE
  {
    STATS_GAME = 0,
    LEMMING_COUNTDOWN = 1,
    SKILL_COUNTER = 2
  };

  // LEVEL DATA
  const int LEVEL_N_LEMMINGS[31] = {20, 10, 10, 50, 10, 50, 50, 50, 100, 100, 20, 60, 80, 20, 80, 100, 80, 50, 70, 100, 50, 100, 100, 80, 30, 100, 2, 50, 100, 100, 60};
  const int LEVEL_SAVE_LEMMINGS[31] = {2, 1, 1, 5, 10, 5, 10, 25, 95, 90, 10, 50, 40, 20, 60, 80, 50, 20, 50, 70, 40, 60, 80, 20, 20, 50, 2, 25, 60, 60, 40};
  const double LEVEL_TIME_LIMIT[31] = {480.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 180.f, 360.f, 480.f, 480.f, 300.f, 300.f, 300.f, 300.f, 480.f, 300.f, 480.f, 300.f, 300.f, 300.f, 300.f, 300.f, 480.f, 300.f};
  const int LEVEL_SPAWN_VELOCITY[31] = {90, 50, 50, 50, 1, 50, 50, 50, 88, 99, 50, 50, 99, 1, 20, 40, 1, 99, 80, 20, 10, 50, 50, 50, 99, 99, 30, 1, 80, 90, 10};
  const int LEVEL_SKILLS_AMOUNT[31][10] = {
      {99, 99, 99, 99, 99, 99, 99, 99},
      {0, 0, 0, 0, 0, 0, 0, 10},
      {0, 10, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 10, 0, 0, 0, 0},
      {10, 0, 0, 0, 0, 0, 1, 0},
      {0, 0, 0, 0, 0, 50, 0, 0},
      {0, 0, 5, 5, 0, 0, 0, 0},
      {0, 0, 0, 0, 20, 0, 0, 0},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {0, 0, 0, 0, 0, 0, 0, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {0, 0, 20, 20, 0, 0, 0, 0},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {20, 20, 20, 20, 20, 20, 20, 20},
      {30, 30, 30, 30, 30, 30, 30, 30},
      {30, 30, 30, 30, 30, 30, 30, 30},
      {20, 20, 20, 20, 20, 20, 20, 20},
  };
}