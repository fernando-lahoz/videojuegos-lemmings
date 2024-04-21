#ifndef LEMMINGS_MEMORY
#define LEMMINGS_MEMORY

#pragma once

#include <cstdint>
#include "engine/IO.hpp"

#define NUMBER_OF_MODS 3
#define LEVELS_PER_MOD 30

class LemmingsLevelData {

	uint8_t wonAndRewards,	// bit0 is won, bit1 time reward
							// bit2 percentage reward, bit3 levvils reward
			min,			// minutes of best time
			sec,			// seconds of best time
			perc;			// highest percentage of lemmings saved

public:
	LevelData(uint8_t wonAndRewards, uint8_t min, uint8_t sec, uint8_t perc) :
		wonAndRewards(wonAndRewards), min(min), sec(sec), perc(perc) {}

	LevelData(bool won, bool timeReward, bool percentageReward, bool levelsReward,
				uint8_t min, uint8_t sec, uint8_t perc) :
		wonAndRewards((won ? 0x01 : 0x00)
					| (timeReward ? 0x02 : 0x00)
					| (percentageReward ? 0x04 : 0x00)
					| (levelsReward ? 0x08 : 0x00)),
		min(min), sec(sec), perc(perc) {}

	bool isWon() const { return wonAndRewards & 0x01; }
	bool hasTimeReward() const { return wonAndRewards & 0x02; }
	bool hasPercentageReward() const { return wonAndRewards & 0x04; }
	bool hasLevelsReward() const { return wonAndRewards & 0x08; }
	uint8_t getMin() const { return min; }
	uint8_t getSec() const { return sec; }
	uint8_t getPerc() const { return perc; }

};

class LemmingsMemory {

	uint8_t won[NUMBER_OF_MODS];
	uint8_t levels[NUMBER_OF_MODS][LEVELS_PER_MOD];
	EngineIO::InputEvent abilities[17];
	// 10 abilities + 2 plus + 2 minus + 2 movement

public:

	LemmingsMemory() {
		for (int i = 0; i < NUMBER_OF_MODS; i++) {
			won[i] = 0;
		}
	}

	LemmingsMemory(std::string filename) {
		std::ifstream file(filename);

	bool isWon(int mod, int level) const { return won[mod] >= level; }


	uint8_t getLevels(int mod) const { return levels[mod]; }
	LevelData getLevelData(int mod, int level) const {
		return LevelData(levels[mod][level]);
	}

	void setWon(int mod, bool value) { won[mod] = value; }
	void setLevels(int mod, uint8_t value) { levels[mod] = value; }
	void setLevelData(int mod, int level, LevelData value) {
		levels[mod][level] = value;
	}

};