#pragma  once
#include "bits/stdc++.h"
#include "speaker.h"

using std::vector;
using std::string;
using std::map;

class SpeechManager {
private:
	int round;		// 比赛轮次
	vector<int> v1; // 记录比赛选手
	vector<int> v2; // 记录晋级选手
	vector<int> v3; // 记录胜利选手
	
	bool fileIsEmpty;

	map<int, Speaker> speakers;
	map<int, vector<string>> records;
	

public:
	SpeechManager();

private:
	void creatSpeaker();
	void printSpeaker();
	void speechDraw();
	void speechContest();
	void saveResult();
	void resetCompetition();
	void loadRecord();

public:
	void menu();
	void startCompetition();
	void checkRecord();
	void clearRecord();
	void exitCompetition();

public:
	~SpeechManager() {};

};