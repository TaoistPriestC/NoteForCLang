#define _CRT_SECURE_NO_WARNINGS 1

#include "bits/stdc++.h"
#include "speaker.h"
#include "speechManager.h"


using std::cin;
using std::cout;
using std::endl;


int opts;
int main(){
	SpeechManager sp;
	while (1) {
		sp.menu();
		cin >> opts;
		switch (opts) {
			case 0:
				sp.exitCompetition();
				break;
			case 1:
				sp.startCompetition();
				break;
			case 2:
				sp.checkRecord();
				break;
			case 3:
				sp.clearRecord();
				break;
			default:
				break;
		}
	}
	return 0;
}