#pragma  once
#include "bits/stdc++.h"
#include "speaker.h"

using std::vector;
using std::string;
using std::map;

class SpeechManager {
private:
	int round;		// �����ִ�
	vector<int> v1; // ��¼����ѡ��
	vector<int> v2; // ��¼����ѡ��
	vector<int> v3; // ��¼ʤ��ѡ��
	
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