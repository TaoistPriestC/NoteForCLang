#define _CRT_SECURE_NO_WARNINGS 1

#include "speaker.h"
#include "bits/stdc++.h"


// 如果不定义空参构造函数,
// 使用 map<int,Speaker> speakers获取Speaker对象将会报错
Speaker::Speaker() {
	this->name = string();
	for (int i = 0; i < 2; i++) {
		this->score[i] = 0.0f;
	}
}

// 由于比赛只有两轮,因而分数只需要记录两次即可
Speaker::Speaker(string name):name(name) {
	for (int i = 0; i < 2; i++) {
		this->score[i] = 0.0f;
	}
}