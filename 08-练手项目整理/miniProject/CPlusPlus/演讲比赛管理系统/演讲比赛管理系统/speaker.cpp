#define _CRT_SECURE_NO_WARNINGS 1

#include "speaker.h"
#include "bits/stdc++.h"


// ���������ղι��캯��,
// ʹ�� map<int,Speaker> speakers��ȡSpeaker���󽫻ᱨ��
Speaker::Speaker() {
	this->name = string();
	for (int i = 0; i < 2; i++) {
		this->score[i] = 0.0f;
	}
}

// ���ڱ���ֻ������,�������ֻ��Ҫ��¼���μ���
Speaker::Speaker(string name):name(name) {
	for (int i = 0; i < 2; i++) {
		this->score[i] = 0.0f;
	}
}