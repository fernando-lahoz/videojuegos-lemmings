#pragma once

#include <vector>

#include "geometry/point.hpp"

namespace Utils
{
  // ANIMATIONS
  const int LIQUID_N_FRAMES[7] = {7, 8, 8, 7, 8, 9, 6};

  // LEMMINGS CONSTANTS
  const int STATE_IS_LOOP_ANIMATION[14] = {false, true, true, true, true, true, true, false, true, true, true, false, false, false}; // indicates if the animation is loop
  const int STATE_N_FRAMES[14] = {8, 9, 4, 16, 16, 16, 8, 30, 16, 32, 24, 8, 16, 16};                                                // number of frames of each animation
  const float STATE_ANIMATION_DURATION[14] = {1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};   // duration of each animation in seconds
  const float MAX_DISTANCE_FALL = 130.0f;

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
  const Point3f positions[12] = {Point3f(10320, -148, 3), Point3f(10032, -148, 3), Point3f(10064, -148, 3), Point3f(10096, -148, 3), Point3f(10128, -148, 3), Point3f(10160, -148, 3), Point3f(10192, -148, 3), Point3f(10224, -148, 3), Point3f(10256, -148, 3), Point3f(10288, -148, 3), Point3f(10352, -148, 3)};

  enum HUD
  {
    HUD_PAUSE = 0,
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
    HUD_MINIMAP = 18,
    HUD_CURSOR = 19,
    HUD_VELOCITY = 20,
  };

  const int NO_OPTION_SELECTED = 11;

  const int HUD_TO_SKILL[21] = {NO_SKILLS, NO_SKILLS, CLIMB, FLOAT, EXPLODE, BLOCK, BUILD, BASH, MINE, DIG, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS, NO_SKILLS};

  // CREDITS CONSTANTS
  const std::string CREDIT_NAMES = "                                                                                        LEMMINGS CLON by                                                Hugo Mateo Trejo                                             Juan Lorente Guarnieri                                          Fernando Lahoz Bernad                                             Jaime Bielsa Uche                                            Eryka Rimacuna Castillo                                           Saul Daniel Soriano                       ";

  // TEXT CONSTANTS
  enum TEXT_TYPE
  {
    STATS_GAME = 0,
    LEMMING_COUNTDOWN = 1,
    SKILL_COUNTER = 2,
    MAIN_TEXT = 3
  };

  const std::string TEXT_RED_1[4] = {"ROCK BOTTOM! I hope for your sake", "SPOT ON. You can't get much closer", "That level seemed no problem to you on", "Superb! You rescued every lemming on"};
  const std::string TEXT_RED_2[4] = {"that you nucked that level", "than that. Let's try the next....", "that attempt. Onto the next....", "that level. Can you do it again....?"};

  const std::string TEXT_BLUE_1[3] = {"Press left button to try again", "", "Press left button to continue"};
  const std::string TEXT_BLUE_2[3] = {"Press right button for menu", "Press mouse button to continue", "Press right button for menu"};

  const std::string DIFFICULTY_NAME[4] = {"Fun", "Tricky", "Taxing", "Mayhem"};
  const std::string LEVEL_NAME[4][31] = {{"Este mapa es de prueba", "Just dig!", "Only floaters can survive this", "Tailor-made for blockers", "Now use miners and climbers", "You need bashers this time", "A task for blockers and bombers", "Builders will help you here", "Not as complicated as it looks", "As long as you try your best", "Smile if you love Lemmings", "Keep your hair on Mr. Lemming", "Patience", "We all fall down", "Origins and Lemmings", "Don't let your eyes deceive you", "Don't do anything too hasty", "Easy when you know how", "Let's block and blow", "Take good care of my Lemmings", "We are now at LEMCON ONE", "You Live and Lem", "A Beast of a level", "I've lost that Lemming feeling", "Konbanwa Lemming San", "Lemmings Lemmings everywhere", "Nightmare on Lem Street", "Let's be careful out there", "If only they could fly", "worra lorra Lemmings", "Lock up your Lemmings"},
                                         {"?", "This should be a doddle!", "We all fall down", "A ladder would be handy", "Here's one I prepared earlier", "Careless clicking costs lives", "Lemmingology", "Been there, seen it, done it", "Lemming sanctuary in sight", "They just keep on coming", "There's a lot of them about", "Lemmings in the attic", "Bitter Lemming", "Lemming Drops", "MENACING !!", "Ozone friendly Lemmings", "Luvly Jubly", "Diet Lemmingaid", "It's Lemmingentry Watson", "Postcard from Lemmingland", "One-way digging to freedom", "All the 6's", "Turn around young lemmings!", "From The Boundary Line", "Tightrope City", "Cascade", "I have a cunning plan", "The Island of the Wicker people", "Lost something?", "Rainbow Island", "The Crankshaft"},
                                         {"?", "If at first you don't succeed..", "Watch out, there's traps about", "Heaven can wait (we hope!!!!)", "Lend a helping hand....", "The Prison!", "Compression Method 1", "Every Lemming for himself!!!", "The Art Gallery", "Perseverance", "Izzie Wizzie lemmings get busy", "The ascending pillar scenario", "Livin' On The Edge", "Upsidedown World", "Hunt the Nessy....", "What an AWESOME level", "Mary Poppins' land", "X marks the spot", "Tribute to M.C.Escher", "Bomboozal", "Walk the web rope", "Feel the heat!", "Come on over to my place", "King of the castle", "Take a running jump.....", "Follow the leader...", "Triple Trouble", "Call in the bomb squad", "POOR WEE CREATURES!", "How do I dig up the way?", "We all fall down"},
                                         {"?", "Steel Works", "The Boiler Room", "It's hero time!", "The Crossroads", "Down, along, up. In that order", "One way or another", "Poles Apart", "Last one out is a rotten egg!", "Curse of the Pharaohs", "Pillars of Hercules", "We all fall down", "The Far Side", "The Great Lemming Caper", "Pea Soup", "The Fast Food Kitchen...", "Just a Minute...", "Stepping Stones", "And then there were four....", "Time to get up!", "No added colours or Lemmings", "With a twist of lemming please", "A BeastII of a level", "Going up...", "All or Nothing", "Have a nice day!", "The Steel Mines of Kessel", "Just a Minute (Part Two)", "Mind the step.....", "Save Me", "Rendezvous at the Mountain"}};

  // LEVEL DATA
  const int LEVEL_N_LEMMINGS[31] = {1, 10, 10, 50, 10, 50, 50, 50, 100, 100, 20, 60, 80, 20, 80, 100, 80, 50, 70, 100, 50, 100, 100, 80, 30, 100, 2, 50, 100, 100, 60};
  const int LEVEL_SAVE_LEMMINGS[31] = {7, 1, 1, 5, 10, 5, 10, 25, 95, 90, 10, 50, 40, 20, 60, 80, 50, 20, 50, 70, 40, 60, 80, 20, 20, 50, 2, 25, 60, 60, 40};
  const double LEVEL_TIME_LIMIT[31] = {60.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 180.f, 360.f, 480.f, 480.f, 300.f, 300.f, 300.f, 300.f, 480.f, 300.f, 480.f, 300.f, 300.f, 300.f, 300.f, 300.f, 480.f, 300.f};
  const int LEVEL_SPAWN_VELOCITY[31] = {1, 50, 50, 50, 1, 50, 50, 50, 88, 99, 50, 50, 99, 1, 20, 40, 1, 99, 80, 20, 10, 50, 50, 50, 99, 99, 30, 1, 80, 90, 10};
  const float LEVEL_CAMERA_POS_INI[31] = {320, 2000, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584, 1584};
  const std::vector<int> LEVEL_SKILLS_AMOUNT[31] = {
      {1, 2, 3, 4, 5, 6, 7, 8},
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
  const int SKILL_TO_SKILLS_AMOUNT[8] = {0, 1, 2, 3, 4, 7, 5, 6};

  // MENU CONSTANTS

  enum DIFFICULTY_TYPE
  {
    FUN = 0,
    TRICKY = 1,
    TAXING = 2,
    MAYHEM = 3
  };
  enum MENU_TYPE
  {
    TITLE = 0,
    LEVEL_SELECTOR = 1,
    LEVEL_INTRO = 2,
    LEVEL_OUTRO = 3
  };
  enum BUTTON_TYPE
  {
    PLAYER_SOLO = 0,
    PLAYER_VS_IA = 1,
    SOUND_EFFECTS = 2,
    EXIT = 4
  };
  enum ACTIONS
  {
    NO_ACTION = 0,
    GO_MENU = 1,
    GO_LEVEL = 2,
  };
  enum STATE
  {
    MENU = 0,
    GAME = 1,
  };
}