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
    BLOCK = 1,
    BUILD = 2,
    CLIMB = 4,
    FLOAT = 8,
    DIG_VERTICAL = 16,
    DIG_HORIZONTAL = 32,
    DIG_DIAGONAL = 64,
    EXPLODE = 128,
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
    DIGGING_VERTICAL = 8,
    DIGGING_HORIZONTAL = 9,
    DIGGING_DIAGONAL = 10,
    ESCAPING = 11,
    DROWNING = 12,
    CRASHING = 13,
  };

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
    HUD_DIG_HORIZONTAL = 7,
    HUD_DIG_DIAGONAL = 8,
    HUD_DIG_VERTICAL = 9,
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

  const int HUD_TO_SKILL[20] = {NO_SKILLS, NO_SKILLS, CLIMB, FLOAT, EXPLODE, BLOCK, BUILD, DIG_HORIZONTAL, DIG_DIAGONAL, DIG_VERTICAL, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS};
}