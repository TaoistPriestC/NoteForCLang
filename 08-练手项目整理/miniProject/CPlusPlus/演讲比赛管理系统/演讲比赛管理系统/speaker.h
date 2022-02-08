#pragma  once
#include "bits/stdc++.h"

using std::string;

class Speaker {
public:
	string name;
	double score[2];
public:
	Speaker();
	Speaker(string name);
public:
	~Speaker() {};
};