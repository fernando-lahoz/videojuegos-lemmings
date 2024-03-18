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
  const float STATE_ANIMATION_DURATION[14] = {1.0f, 0.8f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.5f, 1.0f, 1.5f, 1.0f, 1.0f, 1.0f};   // duration of each animation in seconds
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

  const std::string LEMMING_TYPE[15] = {"WALKER", "WALKER", "FALLER", "BLOCKER", "BUILDER", "CLIMBER", "FLOATER", "", "DIGGER", "BASHER", "MINER", "", "", "", "ATHLETE"};

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
  const int LEVEL_N_LEMMINGS[4][31] = {{120, 10, 10, 50, 10, 50, 50, 50, 100, 100, 20, 60, 80, 20, 80, 100, 80, 50, 70, 100, 50, 100, 100, 80, 30, 100, 2, 50, 100, 100, 60},
                                       {120, 100, 40, 100, 100, 100, 5, 75, 100, 75, 100, 50, 50, 100, 80, 10, 50, 50, 10, 50, 100, 66, 100, 100, 80, 100, 100, 100, 100, 100, 100},
                                       {120, 100, 100, 100, 40, 60, 50, 100, 100, 20, 5, 50, 10, 100, 100, 100, 100, 100, 75, 70, 90, 20, 50, 100, 100, 100, 100, 100, 100, 100, 60},
                                       {120, 100, 100, 30, 100, 80, 75, 50, 100, 100, 75, 80, 75, 2, 80, 100, 50, 80, 100, 50, 50, 50, 100, 100, 50, 100, 100, 50, 1, 100, 80}};
  const int LEVEL_SAVE_LEMMINGS[4][31] = {{7, 1, 1, 5, 10, 5, 10, 25, 95, 90, 10, 50, 40, 20, 60, 80, 50, 20, 50, 70, 40, 60, 80, 20, 20, 50, 2, 25, 60, 60, 40},
                                          {120, 50, 40, 50, 20, 20, 4, 55, 60, 70, 94, 42, 40, 70, 70, 6, 40, 48, 9, 50, 95, 44, 90, 60, 74, 10, 100, 90, 90, 99, 90},
                                          {120, 99, 80, 100, 30, 45, 30, 98, 100, 20, 5, 50, 8, 99, 95, 80, 97, 90, 65, 64, 80, 20, 50, 95, 99, 90, 99, 60, 70, 95, 60},
                                          {120, 90, 90, 30, 100, 60, 75, 45, 90, 99, 60, 80, 75, 2, 74, 96, 50, 70, 90, 46, 50, 50, 85, 80, 50, 90, 90, 50, 1, 80, 60}};
  const double LEVEL_TIME_LIMIT[4][31] = {{60.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 300.f, 180.f, 360.f, 480.f, 480.f, 300.f, 300.f, 300.f, 300.f, 480.f, 300.f, 480.f, 300.f, 300.f, 300.f, 300.f, 300.f, 480.f, 300.f},
                                          {999.f, 240.f, 180.f, 360.f, 480.f, 300.f, 300.f, 300.f, 480.f, 300.f, 480.f, 480.f, 480.f, 480.f, 360.f, 300.f, 300.f, 300.f, 300.f, 300.f, 240.f, 360.f, 300.f, 300.f, 120.f, 300.f, 300.f, 300.f, 300.f, 240.f, 240.f},
                                          {999.f, 240.f, 300.f, 120.f, 420.f, 300.f, 180.f, 180.f, 240.f, 240.f, 300.f, 240.f, 300.f, 360.f, 480.f, 360.f, 180.f, 420.f, 300.f, 120.f, 300.f, 120.f, 180.f, 300.f, 180.f, 240.f, 300.f, 300.f, 300.f, 240.f, 180.f},
                                          {999.f, 480.f, 360.f, 60.f, 60.f, 300.f, 240.f, 300.f, 300.f, 240.f, 300.f, 180.f, 240.f, 300.f, 300.f, 120.f, 60.f, 240.f, 540.f, 300.f, 300.f, 300.f, 300.f, 540.f, 60.f, 300.f, 480.f, 60.f, 420.f, 300.f, 540.f}};
  const int LEVEL_SPAWN_VELOCITY[4][31] = {{1, 50, 50, 50, 1, 50, 50, 50, 88, 99, 50, 50, 99, 1, 20, 40, 1, 99, 80, 20, 10, 50, 50, 50, 99, 99, 30, 1, 80, 90, 10},
                                           {1, 50, 1, 50, 55, 20, 20, 20, 40, 50, 60, 20, 1, 1, 50, 50, 76, 50, 50, 50, 60, 66, 88, 99, 85, 99, 99, 60, 70, 70, 20},
                                           {1, 40, 70, 1, 50, 50, 99, 55, 20, 50, 50, 20, 1, 40, 30, 50, 50, 50, 50, 80, 50, 70, 1, 40, 50, 20, 80, 10, 1, 80, 1},
                                           {1, 15, 30, 99, 1, 80, 1, 1, 55, 90, 1, 1, 1, 50, 70, 60, 10, 50, 1, 1, 85, 1, 75, 70, 99, 1, 50, 10, 1, 50, 20}};
  const float LEVEL_CAMERA_POS_INI[4][31] = {{320, 1630.62, 1584, 1510.69, 1563.04, 1164.07, 1523.75, 1139.67, 1147.27, 1584, 1584, 1584, 1584, 1034.38, 934.507, 675, 1390.75, 1435, 1364.21, 1061, 1397.68, 734.727, 965.85, 1477.24, 1584, 1280.3, 1772.63, 1522.43, 1597.36, 2022.82, 1517.53},
                                             {1584, 1027.6, 1034.38, 1185.76, 1001.41, 1538.59, 1240.05, 1977.11, 1598, 1663.83, 1600, 1775, 1385, 1512, 912.615, 1630.62, 1164.07, 1523.75, 1584, 1139.67, 1147, 1356.45, 1147.27, 1584, 1083.21, 1080, 1584, 1115, 1311.31, 850, 934.66},
                                             {1584, 675, 1620.7, 1390.75, 1653.65, 1610.62, 1435, 1001.41, 1538.59, 1584, 1240.05, 1977.11, 1151.02, 2249.64, 548.323, 932, 1154.59, 1584, 1477.24, 1364.21, 632, 1564, 1522.43, 1598, 1126, 1061, 1584, 1508, 960, 1185.76, 1034.38},
                                             {1584, 1195, 1872, 1584, 1280.3, 1597.36, 1663.83, 1397.68, 1446.76, 2022.82, 1563, 1034.38, 1657.19, 1772.63, 1204.78, 1600, 1414.38, 1335, 1600, 1775, 1563.04, 1385, 1031, 2421.89, 1517.53, 1512, 734.727, 1414.38, 2488, 2656.72, 320}};
  const std::vector<int> LEVEL_SKILLS_AMOUNT[4][31] = {{
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
                                                       },
                                                       {
                                                           {99, 99, 99, 99, 99, 99, 99, 99},
                                                           {10, 10, 10, 10, 10, 10, 10, 10},
                                                           {0, 0, 0, 0, 0, 0, 0, 40},
                                                           {20, 20, 20, 20, 40, 20, 20, 20},
                                                           {40, 40, 40, 40, 40, 40, 40, 40},
                                                           {20, 20, 20, 20, 20, 20, 20, 20},
                                                           {20, 20, 20, 20, 20, 20, 20, 20},
                                                           {20, 20, 20, 20, 20, 20, 20, 20},
                                                           {0, 0, 0, 20, 50, 0, 0, 0},
                                                           {20, 20, 20, 20, 20, 20, 20, 20},
                                                           {20, 20, 20, 20, 20, 20, 20, 20},
                                                           {20, 20, 20, 20, 50, 20, 20, 20},
                                                           {50, 50, 20, 20, 20, 20, 20, 20},
                                                           {20, 20, 20, 20, 50, 20, 20, 20},
                                                           {10, 10, 15, 10, 15, 15, 15, 15},
                                                           {0, 0, 5, 0, 0, 0, 0, 0},
                                                           {0, 0, 10, 0, 0, 1, 1, 0},
                                                           {0, 0, 2, 0, 0, 0, 0, 0},
                                                           {0, 1, 1, 0, 2, 0, 0, 1},
                                                           {10, 10, 0, 0, 1, 1, 1, 1},
                                                           {3, 3, 6, 2, 2, 4, 2, 2},
                                                           {66, 66, 66, 66, 66, 66, 66, 66},
                                                           {0, 1, 15, 0, 20, 1, 0, 0},
                                                           {10, 10, 0, 0, 1, 2, 1, 1},
                                                           {5, 5, 5, 5, 3, 5, 5, 5},
                                                           {1, 10, 5, 0, 10, 1, 1, 5},
                                                           {2, 2, 5, 10, 20, 2, 2, 2},
                                                           {5, 0, 5, 5, 5, 5, 5, 5},
                                                           {10, 10, 10, 10, 10, 10, 10, 10},
                                                           {10, 10, 10, 10, 10, 10, 10, 10},
                                                           {10, 10, 10, 10, 10, 0, 10, 10},
                                                       },
                                                       {
                                                           {99, 99, 99, 99, 99, 99, 99, 99},
                                                           {2, 2, 2, 2, 8, 2, 2, 2},
                                                           {10, 5, 5, 10, 10, 5, 5, 5},
                                                           {30, 30, 30, 0, 30, 30, 30, 30},
                                                           {0, 0, 5, 4, 20, 2, 2, 2},
                                                           {0, 0, 5, 4, 20, 10, 0, 3},
                                                           {0, 0, 3, 3, 0, 5, 0, 1},
                                                           {1, 0, 5, 1, 6, 1, 0, 0},
                                                           {10, 10, 10, 0, 10, 10, 0, 0},
                                                           {2, 1, 1, 2, 2, 1, 1, 2},
                                                           {0, 0, 5, 5, 15, 5, 5, 5},
                                                           {2, 1, 0, 0, 20, 5, 5, 5},
                                                           {10, 10, 10, 2, 10, 10, 10, 10},
                                                           {1, 0, 10, 1, 2, 3, 4, 2},
                                                           {0, 0, 10, 10, 30, 2, 1, 1},
                                                           {20, 20, 20, 20, 20, 20, 20, 20},
                                                           {0, 4, 3, 3, 20, 0, 0, 0},
                                                           {5, 0, 5, 0, 20, 5, 6, 0},
                                                           {0, 1, 15, 0, 15, 1, 0, 0},
                                                           {0, 0, 15, 0, 0, 0, 0, 0},
                                                           {20, 20, 20, 20, 20, 20, 20, 20},
                                                           {3, 3, 3, 3, 4, 3, 3, 3},
                                                           {0, 2, 0, 1, 10, 1, 1, 2},
                                                           {0, 0, 0, 0, 20, 0, 0, 0},
                                                           {0, 0, 0, 0, 30, 0, 0, 0},
                                                           {0, 0, 10, 0, 7, 5, 0, 0},
                                                           {10, 10, 10, 10, 10, 10, 10, 10},
                                                           {0, 0, 10, 10, 10, 0, 0, 0},
                                                           {1, 1, 4, 4, 8, 3, 1, 0},
                                                           {10, 10, 10, 10, 5, 10, 10, 10},
                                                           {0, 0, 0, 0, 0, 0, 0, 60},
                                                       },
                                                       {
                                                           {99, 99, 99, 99, 99, 99, 99, 99},
                                                           {0, 5, 10, 5, 30, 0, 0, 5},
                                                           {10, 5, 10, 10, 30, 0, 0, 0},
                                                           {1, 1, 1, 1, 1, 1, 1, 1},
                                                           {0, 0, 10, 0, 0, 10, 0, 0},
                                                           {2, 2, 10, 10, 5, 1, 0, 5},
                                                           {0, 0, 10, 0, 15, 0, 5, 5},
                                                           {1, 10, 0, 0, 6, 4, 0, 4},
                                                           {5, 0, 5, 5, 10, 0, 5, 5},
                                                           {0, 0, 20, 1, 12, 5, 0, 1},
                                                           {2, 3, 4, 2, 20, 4, 0, 2},
                                                           {0, 0, 0, 0, 0, 0, 0, 80},
                                                           {2, 1, 0, 0, 20, 5, 5, 5},
                                                           {1, 1, 2, 2, 2, 10, 10, 10},
                                                           {0, 0, 10, 10, 30, 0, 0, 21},
                                                           {10, 10, 10, 10, 10, 10, 10, 10},
                                                           {0, 1, 5, 0, 0, 5, 0, 5},
                                                           {5, 2, 0, 2, 10, 5, 5, 5},
                                                           {2, 0, 20, 10, 30, 1, 2, 1},
                                                           {2, 0, 4, 0, 20, 0, 0, 0},
                                                           {2, 0, 0, 1, 1, 1, 2, 0},
                                                           {1, 50, 0, 0, 4, 1, 0, 1},
                                                           {10, 10, 10, 10, 15, 10, 10, 10},
                                                           {0, 1, 20, 20, 30, 5, 0, 0},
                                                           {0, 0, 0, 0, 0, 3, 0, 0},
                                                           {2, 2, 0, 2, 25, 1, 1, 1},
                                                           {0, 0, 10, 10, 10, 0, 0, 0},
                                                           {1, 1, 5, 0, 0, 5, 0, 5},
                                                           {0, 0, 0, 0, 25, 10, 0, 15},
                                                           {0, 0, 0, 6, 15, 2, 0, 2},
                                                           {10, 1, 10, 10, 30, 10, 10, 4},
                                                       }};
  const int SKILL_TO_SKILLS_AMOUNT[8] = {0, 1, 2, 3, 4, 7, 5, 6};

  // GAME CONSTANTS

  enum DOOR_TYPE
  {
    D_FOREST = 8,
    D_SHAFT_PINK = 4,
    D_SHAFT_BLUE = 2,
    D_DESSERT = 5,
    D_HELL = 3
  };
  const int LEVEL_DOOR_TYPE[4][31] = {{D_FOREST, D_FOREST, D_DESSERT, D_DESSERT, D_SHAFT_PINK, D_SHAFT_BLUE, D_HELL, D_SHAFT_PINK, D_DESSERT, D_SHAFT_PINK, D_DESSERT, D_SHAFT_PINK, D_DESSERT, D_HELL, D_DESSERT, D_DESSERT, D_HELL, D_SHAFT_PINK, D_HELL, D_SHAFT_PINK, D_SHAFT_PINK, D_FOREST, D_FOREST, D_HELL, D_SHAFT_PINK, D_SHAFT_BLUE, D_DESSERT, D_SHAFT_PINK, D_HELL, D_DESSERT, D_HELL},
                                      {D_FOREST, D_FOREST, D_HELL, D_FOREST, D_FOREST, D_SHAFT_BLUE, D_HELL, D_DESSERT, D_HELL, D_FOREST, D_HELL, D_SHAFT_PINK, D_SHAFT_PINK, D_DESSERT, D_HELL, D_FOREST, D_SHAFT_BLUE, D_HELL, D_DESSERT, D_SHAFT_PINK, D_HELL, D_HELL, D_DESSERT, D_DESSERT, D_SHAFT_PINK, D_DESSERT, D_SHAFT_PINK, D_FOREST, D_FOREST, D_SHAFT_PINK, D_DESSERT},
                                      {D_FOREST, D_DESSERT, D_FOREST, D_HELL, D_DESSERT, D_HELL, D_SHAFT_PINK, D_FOREST, D_SHAFT_BLUE, D_DESSERT, D_HELL, D_DESSERT, D_HELL, D_FOREST, D_FOREST, D_HELL, D_HELL, D_HELL, D_SHAFT_PINK, D_HELL, D_SHAFT_BLUE, D_HELL, D_SHAFT_PINK, D_HELL, D_HELL, D_SHAFT_PINK, D_HELL, D_DESSERT, D_SHAFT_BLUE, D_FOREST, D_HELL},
                                      {D_FOREST, D_FOREST, D_HELL, D_SHAFT_PINK, D_SHAFT_BLUE, D_HELL, D_FOREST, D_SHAFT_PINK, D_HELL, D_DESSERT, D_SHAFT_PINK, D_HELL, D_FOREST, D_DESSERT, D_SHAFT_PINK, D_HELL, D_SHAFT_PINK, D_SHAFT_PINK, D_FOREST, D_SHAFT_PINK, D_SHAFT_PINK, D_SHAFT_PINK, D_FOREST, D_SHAFT_BLUE, D_HELL, D_DESSERT, D_FOREST, D_SHAFT_PINK, D_SHAFT_PINK, D_DESSERT, D_FOREST}};

  const Point3f LEVEL_DOOR_POSITION[4][31] = {{Point3f(420, 20, 500), Point3f(1462.7, 73.5361, 500), Point3f(1302.94, 16.5413, 500), Point3f(1422.52, 9.87284, 500), Point3f(1403.21, 23.9217, 500), Point3f(987.409, 54.0332, 500), Point3f(1273.93, 43.2726, 500), Point3f(965.748, 158.484, 500), Point3f(1129.81, 73.1607, 500), Point3f(1395.32, 160.534, 500), Point3f(1544.38, 8.23047, 500), Point3f(1307.35, 146.715, 500), Point3f(1276.3, 157.29, 500), Point3f(736.777, 24.0139, 500), Point3f(814.29, 28.0416, 500), Point3f(442.924, 29.0666, 500), Point3f(1203.84, 192.863, 500), Point3f(1632.93, 71.9481, 500), Point3f(1087.03, 2.41112, 500), Point3f(941.84, 154.104, 500), Point3f(1275.41, 65.2479, 500), Point3f(549.387, 85.5787, 500), Point3f(696.153, 160.226, 500), Point3f(1254.74, 134.628, 500), Point3f(1275.02, 4.23079, 500), Point3f(1176.41, 200.15, 500), Point3f(1628.52, 18.1654, 500), Point3f(1302.33, 72.6464, 500), Point3f(1732.57, 6.88284, 500), Point3f(1976.31, 117.534, 500), Point3f(1533.2, 23.0913, 500)},
                                              {Point3f(1584.f, 100, 500), Point3f(849.666, 119.156, 500), Point3f(736.777, 24.0139, 500), Point3f(1153.52, 4.31593, 500), Point3f(918.772, 38.4679, 500), Point3f(1479, 110.091, 500), Point3f(1214.26, 67.2065, 500), Point3f(1920.49, 155.067, 500), Point3f(1794.53, 225.72, 500), Point3f(1606.45, 40.0331, 500), Point3f(932.122, 100.808, 500), Point3f(1557.45, 215.79, 500), Point3f(1263.46, 0.928468, 500), Point3f(1327.62, 79.2672, 500), Point3f(685.911, 177.717, 500), Point3f(1462.7, 73.5361, 500), Point3f(987.409, 54.0332, 500), Point3f(1273.93, 43.2726, 500), Point3f(1302.94, 16.5413, 500), Point3f(965.748, 158.484, 500), Point3f(1023.76, 137.306, 500), Point3f(1269.98, 150.906, 299), Point3f(1129.81, 73.1607, 500), Point3f(1270.82, 153.292, 500), Point3f(988.745, 96.6295, 500), Point3f(992.081, 219.933, 500), Point3f(1395.32, 160.534, 500), Point3f(928.804, -0.713818, 500), Point3f(1287.45, 160.093, 500), Point3f(664.993, 168.198, 500), Point3f(814.29, 28.0416, 500)},
                                              {Point3f(1584.f, 100, 500), Point3f(442.924, 29.0666, 500), Point3f(1398.38, 16.3206, 500), Point3f(1203.84, 192.863, 500), Point3f(1498.25, 199.799, 500), Point3f(1360.68, 120.025, 500), Point3f(1632.93, 71.9481, 500), Point3f(918.772, 38.4679, 500), Point3f(1479, 110.091, 500), Point3f(1544.38, 8.23047, 500), Point3f(1214.26, 67.2065, 500), Point3f(1920.49, 155.067, 500), Point3f(1161.08, 162.471, 500), Point3f(2224.14, 109.93, 500), Point3f(357.689, 121.659, 500), Point3f(703.226, 9.29263, 500), Point3f(936.257, 0, 500), Point3f(1254.74, 134.628, 500), Point3f(1307.35, 146.715, 500), Point3f(1087.03, 2.41112, 500), Point3f(381.868, 194.931, 500), Point3f(1281.7, 142.834, 500), Point3f(1302.33, 72.6464, 500), Point3f(1794.53, 225.72, 500), Point3f(972.207, 87.5296, 500), Point3f(941.84, 154.104, 500), Point3f(1319.84, 200.889, 500), Point3f(1319.93, 177.153, 500), Point3f(871.345, 48.2499, 500), Point3f(1153.52, 4.31593, 500), Point3f(736.777, 24.0139, 500)},
                                              {Point3f(1584.f, 100, 500), Point3f(976.934, 0.908981, 500), Point3f(1879.52, 109.209, 500), Point3f(1275.02, 4.23079, 500), Point3f(1176.41, 200.15, 500), Point3f(1732.57, 6.88284, 500), Point3f(1607.3, 40.0356, 500), Point3f(1275.41, 65.2479, 500), Point3f(1193.5, 142.217, 500), Point3f(1976.31, 117.534, 500), Point3f(1539.92, 19.1163, 500), Point3f(736.777, 24.0139, 500), Point3f(1502.61, 40.4967, 500), Point3f(1628.52, 18.1654, 500), Point3f(1014.48, 194.125, 500), Point3f(932.122, 100.808, 500), Point3f(1354.17, 87.4685, 500), Point3f(1149.14, 48.3647, 500), Point3f(1444.75, 0.622842, 500), Point3f(1557.45, 215.79, 500), Point3f(1403.21, 23.9217, 500), Point3f(1263.46, 0.928468, 500), Point3f(750.627, 138.392, 500), Point3f(2295.81, 232.367, 500), Point3f(1533.2, 23.0913, 500), Point3f(1327.62, 79.2672, 500), Point3f(549.387, 85.5787, 500), Point3f(1354.17, 87.4685, 500), Point3f(2270.89, 41.6663, 500), Point3f(2408.17, 173.303, 500), Point3f(39.1551, 143.913, 500)}};

  enum GATE_TYPE
  {
    G_FOREST = 0,
    G_SHAFT_PINK = 3,
    G_SHAFT_BLUE = 2,
    G_DESSERT = 1,
    G_HELL = 4
  };
  const float LEVEL_GATE_TIME_ANIMATION[5] = {0.8f, 0.8f, 0.8f, 0.8f, 0.3f};
  const int LEVEL_GATE_TYPE[4][31] = {{G_FOREST, G_FOREST, G_DESSERT, G_DESSERT, G_SHAFT_PINK, G_SHAFT_BLUE, G_HELL, G_SHAFT_PINK, G_DESSERT, G_SHAFT_PINK, G_DESSERT, G_SHAFT_PINK, G_DESSERT, G_HELL, G_DESSERT, G_DESSERT, G_HELL, G_SHAFT_PINK, G_HELL, G_SHAFT_PINK, G_SHAFT_PINK, G_FOREST, G_FOREST, G_HELL, G_SHAFT_PINK, G_SHAFT_BLUE, G_DESSERT, G_SHAFT_PINK, G_HELL, G_DESSERT, G_HELL},
                                      {G_FOREST, G_FOREST, G_HELL, G_FOREST, G_FOREST, G_SHAFT_BLUE, G_HELL, G_DESSERT, G_HELL, G_FOREST, G_HELL, G_SHAFT_PINK, G_SHAFT_PINK, G_DESSERT, G_HELL, G_FOREST, G_SHAFT_BLUE, G_HELL, G_DESSERT, G_SHAFT_PINK, G_HELL, G_HELL, G_DESSERT, G_DESSERT, G_SHAFT_PINK, G_DESSERT, G_SHAFT_PINK, G_FOREST, G_FOREST, G_SHAFT_PINK, G_DESSERT},
                                      {G_FOREST, G_DESSERT, G_FOREST, G_HELL, G_DESSERT, G_HELL, G_SHAFT_PINK, G_FOREST, G_SHAFT_BLUE, G_DESSERT, G_HELL, G_DESSERT, G_HELL, G_FOREST, G_FOREST, G_FOREST, G_HELL, G_HELL, G_SHAFT_PINK, G_HELL, G_SHAFT_BLUE, G_HELL, G_SHAFT_PINK, G_HELL, G_HELL, G_SHAFT_PINK, G_HELL, G_DESSERT, G_SHAFT_BLUE, G_FOREST, G_HELL},
                                      {G_FOREST, G_FOREST, G_HELL, G_SHAFT_PINK, G_SHAFT_BLUE, G_HELL, G_FOREST, G_SHAFT_PINK, G_HELL, G_DESSERT, G_SHAFT_PINK, G_HELL, G_FOREST, G_DESSERT, G_SHAFT_PINK, G_HELL, G_SHAFT_PINK, G_SHAFT_PINK, G_FOREST, G_SHAFT_PINK, G_SHAFT_PINK, G_SHAFT_PINK, G_FOREST, G_SHAFT_BLUE, G_HELL, G_DESSERT, G_FOREST, G_SHAFT_PINK, G_SHAFT_PINK, G_DESSERT, G_FOREST}};

  const Point3f LEVEL_GATE_POSITION[4][31] = {{Point3f(200, 130, 500), Point3f(1756.88, 162.742, 500), Point3f(1786.83, 194.386, 500), Point3f(1394.18, 202.782, 500), Point3f(1728.38, -8.13497, 500), Point3f(1935.42, 158.481, 500), Point3f(1746.58, 104.385, 500), Point3f(2050.54, 88.5411, 500), Point3f(1064.45, 98.347, 500), Point3f(1688.35, 144.29, 500), Point3f(1415.92, 186.71, 500), Point3f(1790.87, 168.578, 500), Point3f(1814.94, 138.479, 500), Point3f(1947.22, 136.837, 500), Point3f(2323.65, 105.015, 500), Point3f(2617.62, 22.738, 500), Point3f(1873.84, 32.5396, 500), Point3f(1890.52, 167.937, 500), Point3f(2014.15, 174.778, 500), Point3f(2860.95, 64.5198, 500), Point3f(1953.04, 105.043, 500), Point3f(2537.51, 170.078, 500), Point3f(2171.01, 34.7064, 500), Point3f(0.0158057, 8.93832, 500), Point3f(1822.42, 184.225, 500), Point3f(1874.37, 206.627, 1), Point3f(2167.66, 90.55, 500), Point3f(1657.57, 200.037, 500), Point3f(1122.54, 24.2606, 500), Point3f(859.625, 20.6917, 500), Point3f(1430.89, 192.7, 500)},
                                              {Point3f(1584.f, 100, 500), Point3f(2130.1, 129.972, 500), Point3f(1947.22, 136.837, 500), Point3f(2149.12, 2.13625, 500), Point3f(2452.57, 124.853, 500), Point3f(2622.83, 55.0826, 500), Point3f(1849.65, 168.914, 500), Point3f(958.085, 178.929, 500), Point3f(1279.2, 0.348938, 500), Point3f(1610.54, 178.091, 500), Point3f(1537.54, 32.7569, 500), Point3f(1910.24, 32.8758, 500), Point3f(1779.91, 119.898, 500), Point3f(1872.05, 75.0468, 500), Point3f(2397.4, 66.8453, 500), Point3f(1756.88, 162.742, 500), Point3f(1935.42, 158.481, 500), Point3f(1746.58, 104.385, 500), Point3f(1786.83, 194.386, 500), Point3f(2050.54, 88.5411, 500), Point3f(2205.64, 144.821, 500), Point3f(1843.06, 137.338, 299), Point3f(1064.45, 98.347, 500), Point3f(1814.94, 138.479, 500), Point3f(2048.1, 46.8729, 500), Point3f(1823.98, 107.393, 500), Point3f(1688.35, 144.29, 500), Point3f(1602.3, -4.50176, 500), Point3f(1608.98, 50.0881, 500), Point3f(2522.71, 200.17, 500), Point3f(2323.65, 105.015, 500)},
                                              {Point3f(1584.f, 100, 500), Point3f(2617.62, 22.738, 500), Point3f(760.483, 89.9639, 500), Point3f(1873.84, 32.5396, 500), Point3f(1563.87, -53.6483, 500), Point3f(1802.29, 17.8308, 500), Point3f(1890.52, 167.937, 500), Point3f(2452.57, 124.853, 500), Point3f(2622.83, 55.0826, 500), Point3f(1415.92, 186.71, 500), Point3f(1849.65, 168.914, 500), Point3f(958.085, 178.929, 500), Point3f(1827.79, 9.22238, 500), Point3f(851.436, 91.1705, 500), Point3f(3050.02, 92.4837, 500), Point3f(2379.09, -43.9708, 500), Point3f(1956.13, 144.995, 500), Point3f(0.0158057, 8.93832, 500), Point3f(1790.87, 168.578, 500), Point3f(2014.15, 174.778, 500), Point3f(2550.65, 207.787, 500), Point3f(1628.92, 120.158, 500), Point3f(1657.57, 200.037, 500), Point3f(1279.2, 0.348938, 500), Point3f(1545.31, 144.155, 500), Point3f(2860.95, 64.5198, 500), Point3f(1554.76, 88.3305, 500), Point3f(1670.5, 27.6365, 500), Point3f(2049.4, 46.7436, 500), Point3f(2149.12, 2.13625, 500), Point3f(1947.22, 136.837, 500)},
                                              {Point3f(1584.f, 100, 500), Point3f(2196.85, -53.998, 500), Point3f(1300.28, 24.2471, 500), Point3f(1822.42, 184.225, 500), Point3f(1874.37, 206.627, 500), Point3f(1122.54, 24.2606, 500), Point3f(1611.43, 179.119, 500), Point3f(1953.04, 105.043, 500), Point3f(1893.76, 199.935, 299), Point3f(859.625, 20.6917, 500), Point3f(967.888, 8.22437, 500), Point3f(1947.22, 136.837, 500), Point3f(1632.85, 42.5451, 500), Point3f(2167.66, 90.55, 500), Point3f(2043.61, 184.145, 500), Point3f(1537.54, 32.7569, 500), Point3f(1838.84, 119.993, 500), Point3f(1919.54, 32.6393, 500), Point3f(1545.68, 82.4331, 500), Point3f(1910.24, 32.8758, 500), Point3f(1728.38, -8.13497, 500), Point3f(1910.24, 32.8758, 500), Point3f(2225.08, 154.242, 500), Point3f(583.367, 189.813, 500), Point3f(1430.89, 192.7, 500), Point3f(1872.05, 75.0468, 500), Point3f(2537.51, 170.078, 500), Point3f(1838.84, 119.993, 500), Point3f(1089.25, 136.753, 500), Point3f(650.604, 178.342, 500), Point3f(1543.99, -38.0992, 500)}};

  enum BRICKS_TYPE
  {
    B_FOREST = 0,
    B_SHAFT = 1,
    B_DESSERT = 2,
    B_HELL = 3
  };
  const int LEVEL_BRICKS_TYPE[4][31] = {{B_FOREST, B_FOREST, B_DESSERT, B_DESSERT, B_SHAFT, B_SHAFT, B_HELL, B_SHAFT, B_DESSERT, B_SHAFT, B_DESSERT, B_SHAFT, B_DESSERT, B_HELL, B_DESSERT, B_DESSERT, B_HELL, B_SHAFT, B_HELL, B_SHAFT, B_SHAFT, B_FOREST, B_FOREST, B_HELL, B_SHAFT, B_SHAFT, B_DESSERT, B_SHAFT, B_HELL, B_DESSERT, B_HELL},
                                        {B_FOREST, B_FOREST, B_HELL, B_FOREST, B_FOREST, B_SHAFT, B_HELL, B_DESSERT, B_HELL, B_FOREST, B_HELL, B_SHAFT, B_SHAFT, B_DESSERT, B_HELL, B_FOREST, B_SHAFT, B_HELL, B_DESSERT, B_SHAFT, B_HELL, B_HELL, B_DESSERT, B_DESSERT, B_SHAFT, B_DESSERT, B_SHAFT, B_FOREST, B_FOREST, B_SHAFT, B_DESSERT},
                                        {B_FOREST, B_DESSERT, B_FOREST, B_HELL, B_DESSERT, B_HELL, B_SHAFT, B_FOREST, B_SHAFT, B_DESSERT, B_HELL, B_DESSERT, B_HELL, B_FOREST, B_FOREST, B_HELL, B_HELL, B_HELL, B_SHAFT, B_HELL, B_SHAFT, B_HELL, B_SHAFT, B_HELL, B_HELL, B_SHAFT, B_HELL, B_DESSERT, B_SHAFT, B_FOREST, B_HELL},
                                        {B_FOREST, B_FOREST, B_HELL, B_SHAFT, B_SHAFT, B_HELL, B_FOREST, B_SHAFT, B_HELL, B_DESSERT, B_SHAFT, B_HELL, B_FOREST, B_DESSERT, B_SHAFT, B_HELL, B_SHAFT, B_SHAFT, B_FOREST, B_SHAFT, B_SHAFT, B_SHAFT, B_FOREST, B_SHAFT, B_HELL, B_DESSERT, B_FOREST, B_SHAFT, B_SHAFT, B_DESSERT, B_FOREST}};

  // MENU CONSTANTS

  enum MENU_TYPE
  {
    TITLE = 0,
    LEVEL_SELECTOR = 1,
    LEVEL_INTRO = 2,
    LEVEL_OUTRO = 3,
    INTRO = 4
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