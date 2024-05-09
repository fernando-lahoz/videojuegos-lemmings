#ifndef LEMMINGS_LEVELINFO
#define LEMMINGS_LEVELINFO
#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#define NUMBER_OF_MODS 4
#define LEVELS_PER_MOD 30
#define AI_MODS 2
#define AI_LEVELS_MOD_1 2
#define AI_LEVELS_MOD_2 1
#define AI_LEVELS_MOD_MAX 2

class LevelInfo {

	bool    won;            // true if the level was won
	uint8_t min,			// minutes of best time
			sec,			// seconds of best time
			perc;			// highest percentage of lemmings saved

public:

	LevelInfo(){}
	LevelInfo(bool won, uint8_t min, uint8_t sec, uint8_t perc) :
		won(won), min(min), sec(sec), perc(perc) {}

	bool isWon() const { return won; }
	void setWon(bool won) { this->won = won; }
	uint8_t getMin() const { return min; }
	void setMin(uint8_t min) { this->min = min; }
	uint8_t getSec() const { return sec; }
	void setSec(uint8_t sec) { this->sec = sec; }
	uint8_t getPerc() const { return perc; }
	void setPerc(uint8_t perc) { this->perc = perc; }

};

class LevelsInfo {

	uint8_t won[NUMBER_OF_MODS];
	uint8_t aiWon[AI_MODS];
	LevelInfo levels[NUMBER_OF_MODS][LEVELS_PER_MOD];
	LevelInfo aiLevels[AI_MODS][AI_LEVELS_MOD_MAX];

public:

	LevelsInfo() {
		readLevelsInfoFile();
	}

	void readLevelsInfoFile() {

		std::ifstream file("levelsInfo.txt");
		if (!file.is_open()) {
			std::cerr << "Error opening levels info file. Creating it." << std::endl;
			setDefaultLevelsInfo();
			return;
		}

		bool wonLv;
		unsigned min, sec, perc;
		std::string line;

		// Read won levels per mod.
		for (int i = 0; i < NUMBER_OF_MODS; i++) {
			std::getline(file, line);
			won[i] = std::stoi(line);
		}

		// Read level info.
		for (int i = 0; i < NUMBER_OF_MODS; i++) {
			for (int j = 0; j < LEVELS_PER_MOD; j++) {
				std::getline(file, line);
				std::stringstream ss(line);
				ss >> wonLv >> min >> sec >> perc;
				// std::cout << "Read level " << i << " " << j << " " << wonLv << " " << min << " " << sec << " " << perc << std::endl;
				levels[i][j] = LevelInfo(wonLv, min, sec, perc);
			}
		}
		for (int i = 0; i < AI_LEVELS_MOD_1; i++) {
			std::getline(file, line);
			std::stringstream ss(line);
			ss >> wonLv >> min >> sec >> perc;
			// std::cout << "Read AI level " << 1 << " " << i << " " << wonLv << " " << min << " " << sec << " " << perc << std::endl;
			aiLevels[0][i] = LevelInfo(wonLv, min, sec, perc);
		}
		for (int i = 0; i < AI_LEVELS_MOD_2; i++) {
			std::getline(file, line);
			std::stringstream ss(line);
			ss >> wonLv >> min >> sec >> perc;
			// std::cout << "Read AI level " << 2 << " " << i << " " << wonLv << " " << min << " " << sec << " " << perc << std::endl;
			aiLevels[1][i] = LevelInfo(wonLv, min, sec, perc);
		}


		file.close();

	}

	void setDefaultLevelsInfo() {

		for (int i = 0; i < NUMBER_OF_MODS; i++) {
			won[i] = 0;
			for (int j = 0; j < LEVELS_PER_MOD; j++) {
				levels[i][j] = LevelInfo(false, 0, 0, 0);
			}
		}

		std::ofstream file("levelsInfo.txt");
		if (!file.is_open()) {
			std::cerr << "Error creating levels info file." << std::endl;
			return;
		}
		for (int i = 0; i < NUMBER_OF_MODS; i++)
				file << false << std::endl;
		for (int i = 0; i < NUMBER_OF_MODS * LEVELS_PER_MOD; i++)
				file << false << " " << 0 << " " << 0 << " " << 0 << std::endl;
		for (int i = 0; i < AI_LEVELS_MOD_1 + AI_LEVELS_MOD_2; i++)
				file << false << " " << 0 << " " << 0 << " " << 0 << std::endl;

		file.close();

	}

	void setLevelsInfo(uint8_t won[NUMBER_OF_MODS], LevelInfo levels[NUMBER_OF_MODS][LEVELS_PER_MOD]) {

		std::ofstream file("levelsInfo.txt");
		if (!file.is_open()) {
			std::cerr << "Error opening levels info file." << std::endl;
			return;
		}

		for (int i = 0; i < NUMBER_OF_MODS; i++)
				file << (int)won[i] << std::endl;
		for (int i = 0; i < NUMBER_OF_MODS; i++) {
			for (int j = 0; j < LEVELS_PER_MOD; j++) {
				file << levels[i][j].isWon() << " "
					 << (int)levels[i][j].getMin() << " "
					 << (int)levels[i][j].getSec() << " "
					 << (int)levels[i][j].getPerc() << std::endl;
			}
		}
		for (int i = 0; i < AI_LEVELS_MOD_1; i++) {
			file << aiLevels[0][i].isWon() << " "
				 << (int)aiLevels[0][i].getMin() << " "
				 << (int)aiLevels[0][i].getSec() << " "
				 << (int)aiLevels[0][i].getPerc() << std::endl;
		}
		for (int i = 0; i < AI_LEVELS_MOD_2; i++) {
			file << aiLevels[1][i].isWon() << " "
				 << (int)aiLevels[1][i].getMin() << " "
				 << (int)aiLevels[1][i].getSec() << " "
				 << (int)aiLevels[1][i].getPerc() << std::endl;
		}

		file.close();

	}

	void setNewLevelInfo(int mod, int level, LevelInfo newScore) {
		
		LevelInfo oldScore = levels[mod][level];
		bool changes = false;
		if (!oldScore.isWon()) {
			levels[mod][level] = newScore;
			changes = true;
		}
		else {
			if (newScore.getMin() < oldScore.getMin() ||
			   (newScore.getMin() == oldScore.getMin() && newScore.getSec() < oldScore.getSec())) {
				levels[mod][level].setMin(newScore.getMin());
				levels[mod][level].setSec(newScore.getSec());
				changes = true;
			}
			if (newScore.getPerc() > oldScore.getPerc()) {
				levels[mod][level].setPerc(newScore.getPerc());
				changes = true;
			}
		}
		if (changes) setLevelsInfo(won, levels);
	}

	void setNewAiLevelInfo(int mod, int level, LevelInfo newScore) {
		
		LevelInfo oldScore = aiLevels[mod][level];
		bool changes = false;
		if (!oldScore.isWon()) {
			aiLevels[mod][level] = newScore;
			changes = true;
		}
		else {
			if (newScore.getMin() < oldScore.getMin() ||
			   (newScore.getMin() == oldScore.getMin() && newScore.getSec() < oldScore.getSec())) {
				aiLevels[mod][level].setMin(newScore.getMin());
				aiLevels[mod][level].setSec(newScore.getSec());
				changes = true;
			}
			if (newScore.getPerc() > oldScore.getPerc()) {
				aiLevels[mod][level].setPerc(newScore.getPerc());
				changes = true;
			}
		}
		if (changes) setLevelsInfo(won, levels);
	}

	uint8_t getWonLevels(int mod) const { return won[mod]; }
	bool isLevelWon(int mod, int level) const { return levels[mod][level].isWon(); }
	void setWon(int mod, int level) { levels[mod][level].setWon(true); won[mod]++; }

	uint8_t getMin(int mod, int level) const { return levels[mod][level].getMin(); }
	void setMin(int mod, int level, uint8_t min) { levels[mod][level].setMin(min); }

	uint8_t getSec(int mod, int level) const { return levels[mod][level].getSec(); }
	void setSec(int mod, int level, uint8_t sec) { levels[mod][level].setSec(sec); }
	
	uint8_t getPerc(int mod, int level) const { return levels[mod][level].getPerc(); }
	void setPerc(int mod, int level, uint8_t perc) { levels[mod][level].setPerc(perc); }

	uint8_t getAiWonLevels(int mod) const { return aiWon[mod]; }
	bool isAiLevelWon(int mod, int level) const { return aiLevels[mod][level].isWon(); }
	void setWon_Ai(int mod, int level) { aiLevels[mod][level].setWon(true); aiWon[mod]++; }

	uint8_t getMin_Ai(int mod, int level) const { return aiLevels[mod][level].getMin(); }
	void setMin_Ai(int mod, int level, uint8_t min) { aiLevels[mod][level].setMin(min); }

	uint8_t getSec_Ai(int mod, int level) const { return aiLevels[mod][level].getSec(); }
	void setSec_Ai(int mod, int level, uint8_t sec) { aiLevels[mod][level].setSec(sec); }

	uint8_t getPerc_Ai(int mod, int level) const { return aiLevels[mod][level].getPerc(); }
	void setPerc_Ai(int mod, int level, uint8_t perc) { aiLevels[mod][level].setPerc(perc); }

};

#endif // LEMMINGS_LEVELINFO