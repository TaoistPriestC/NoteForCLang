#define _CRT_SECURE_NO_WARNINGS 1

#include "bits/stdc++.h"
#include "speechManager.h"

using std::cin;
using std::cout;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::fixed;
using std::setw;
using std::setprecision;
using std::endl;

using std::deque;
using std::multimap;
using std::greater;
using std::sort;
using std::make_pair;
using std::random_shuffle;
using std::accumulate;




// ���캯��ʵ��:
SpeechManager::SpeechManager() {
	v1.clear();
	v2.clear();
	v3.clear();
	speakers.clear();
	records.clear();
	round = 1;
	creatSpeaker();
}










// ˽�з���ʵ��:
void SpeechManager::creatSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++){
		// ���������ѡ�ֲ�������
		Speaker sp(string("ѡ��") + nameSeed[i]);
		v1.push_back(i + 10000 + 1);
		speakers.insert(make_pair(i + 10000 + 1, sp));
	}
}

void SpeechManager::printSpeaker(){
	for (auto it = speakers.begin(); it != speakers.end(); it++) {
		cout <<"���: "<< (*it).first << " ����:"<<(*it).second.name << endl;
	}
}

void SpeechManager::speechDraw() {
	random_shuffle(v1.begin(), v1.end());
}

void SpeechManager::speechContest() {
	cout << "��" << round << "��" << " - " << "������ʽ��ʼ" << endl;
	multimap <double, int, greater<double>>groupScore;
	vector<int> vsrc = (round == 1 ? v1 : v2);
	deque<double> d;
	int cnt = 0;
	for (auto it = vsrc.begin(); it != vsrc.end(); it++) {
		cnt++;
		for (int i = 0; i < 10; i++) {
			srand(time(0));
			double s = (rand() % (1000 - 600 + 1) + 600) / 10.0f;
			d.push_back(s);
		}
		sort(d.begin(), d.end(), greater<double>());

		// ȥ����ߺ����Ȼ����ƽ��ֵ
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		// roundȡֵ1/2, תΪ�±�
		speakers[*it].score[round - 1] = avg;
		groupScore.insert(make_pair(avg, *it));
		if (cnt % 6 == 0) {
			int count = 0;
			cout << "��" << (cnt / 6) << "��" << " - " << "��������" << endl;
			for (auto it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "���:" << (*it).second
					<< "\t����:" << speakers[(*it).second].name
					<< "\t�ɼ�:" << fixed << setw(5) << setprecision(2) << (*it).first
					<< endl;

				// ÿ������һ��, ÿ��ǰ��������
				if (count < 3) {
					(round == 1) ? 
						v2.push_back((*it).second): 
						v3.push_back((*it).second);
					count++;
				}
			}
			groupScore.clear();
		}
	}
	round++;
	cout << endl << endl;
}

void SpeechManager::saveResult() {
	ofstream ofs("speech.csv", ios::out | ios::app);
	for (auto it = v3.begin(); it != v3.end(); it++) {
		ofs << *it << ","
			<< speakers[*it].name << ","
			<< fixed << setprecision(2)
			<< speakers[*it].score[0] << ","
			<< speakers[*it].score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "������¼�Ѿ�����" << endl;
}

void SpeechManager::resetCompetition() {
	v1.clear();
	v2.clear();
	v3.clear();
	speakers.clear();
	records.clear();
	round = 1;
	creatSpeaker();
}

void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open()) {
		fileIsEmpty = true;
		cout << "�ļ�������!" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		fileIsEmpty = true;
		cout << "�ļ���¼Ϊ��!" << endl;
		ifs.close();
		return;
	}

	// ��ȡһ���ַ��ж��ļ��Ƿ�Ϊ��, ����Ϊ���ٰѶ������ַ��Ż�
	fileIsEmpty = false;
	ifs.putback(ch);

	string data;
	int session = 1;
	while (ifs >> data) {
		vector<string> v;
		int pos = -1;
		int start = 0;
		while (1) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			string t = data.substr(start, pos - start);
			v.push_back(t);
			start = pos + 1;
		}
		records.insert(make_pair(session, v));
		session++;
	}
	ifs.close();
}







// ���з���ʵ��:
void SpeechManager::menu() {
	cout << "==========================" << endl;
	cout << "===== 1.��ʼ�ݽ����� =====" << endl;
	cout << "===== 2.�鿴�����¼ =====" << endl;
	cout << "===== 3.��ձ�����¼ =====" << endl;
	cout << "===== 0.�˳��������� =====" << endl;
	cout << "==========================" << endl;
}

void SpeechManager::startCompetition() {
	speechDraw();
	system("cls");
	speechContest();// ��һ�ֱ���
	system("pause");
	system("cls");


	speechContest();// �ڶ��ֱ���
	system("pause");
	system("cls");

	cout << "��������ѽ���" << endl;
	system("pause");
	system("cls");

	// ���ñ�����Ϣ
	saveResult();
	resetCompetition();
}

void SpeechManager::checkRecord() {
	loadRecord();
	for (auto it = records.begin(); it != records.end(); it++) {
		cout << "��" << (*it).first << "��" << " - " << "������¼:" << endl;

		for (size_t i = 0; i < (*it).second.size(); i++) {
			if (i != 0 && i % 4 == 0) {
				cout << "\t";
			}
			cout << (*it).second[i] << " ";
		}
		cout << endl << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	int opts;
	cout << "��ȷ��Ҫ����������������?" << endl;
	cout << "--->1.ȷ��" << endl;
	cout << "--->2.ȡ��" << endl;
	cin >> opts;
	if (opts == 1) {
		// ʹ��truncģʽ��,����Ѿ������ļ�����ɾ���ٴ���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		resetCompetition();
		cout << "��ճɹ�!" << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::exitCompetition() {
	exit(EXIT_SUCCESS);
}