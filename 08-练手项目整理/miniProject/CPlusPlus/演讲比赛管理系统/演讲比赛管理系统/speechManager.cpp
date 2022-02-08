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




// 构造函数实现:
SpeechManager::SpeechManager() {
	v1.clear();
	v2.clear();
	v3.clear();
	speakers.clear();
	records.clear();
	round = 1;
	creatSpeaker();
}










// 私有方法实现:
void SpeechManager::creatSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++){
		// 创建具体的选手并分配编号
		Speaker sp(string("选手") + nameSeed[i]);
		v1.push_back(i + 10000 + 1);
		speakers.insert(make_pair(i + 10000 + 1, sp));
	}
}

void SpeechManager::printSpeaker(){
	for (auto it = speakers.begin(); it != speakers.end(); it++) {
		cout <<"编号: "<< (*it).first << " 姓名:"<<(*it).second.name << endl;
	}
}

void SpeechManager::speechDraw() {
	random_shuffle(v1.begin(), v1.end());
}

void SpeechManager::speechContest() {
	cout << "第" << round << "轮" << " - " << "比赛正式开始" << endl;
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

		// 去掉最高和最低然后求平均值
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		// round取值1/2, 转为下标
		speakers[*it].score[round - 1] = avg;
		groupScore.insert(make_pair(avg, *it));
		if (cnt % 6 == 0) {
			int count = 0;
			cout << "第" << (cnt / 6) << "组" << " - " << "比赛名次" << endl;
			for (auto it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "编号:" << (*it).second
					<< "\t姓名:" << speakers[(*it).second].name
					<< "\t成绩:" << fixed << setw(5) << setprecision(2) << (*it).first
					<< endl;

				// 每六个人一组, 每个前三名晋级
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
	cout << "比赛记录已经保存" << endl;
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
		cout << "文件不存在!" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		fileIsEmpty = true;
		cout << "文件记录为空!" << endl;
		ifs.close();
		return;
	}

	// 读取一个字符判断文件是否为空, 若不为空再把读出的字符放回
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







// 公有方法实现:
void SpeechManager::menu() {
	cout << "==========================" << endl;
	cout << "===== 1.开始演讲比赛 =====" << endl;
	cout << "===== 2.查看往届记录 =====" << endl;
	cout << "===== 3.清空比赛记录 =====" << endl;
	cout << "===== 0.退出比赛程序 =====" << endl;
	cout << "==========================" << endl;
}

void SpeechManager::startCompetition() {
	speechDraw();
	system("cls");
	speechContest();// 第一轮比赛
	system("pause");
	system("cls");


	speechContest();// 第二轮比赛
	system("pause");
	system("cls");

	cout << "本届比赛已结束" << endl;
	system("pause");
	system("cls");

	// 重置比赛信息
	saveResult();
	resetCompetition();
}

void SpeechManager::checkRecord() {
	loadRecord();
	for (auto it = records.begin(); it != records.end(); it++) {
		cout << "第" << (*it).first << "届" << " - " << "比赛记录:" << endl;

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
	cout << "您确认要清空往届比赛数据吗?" << endl;
	cout << "--->1.确认" << endl;
	cout << "--->2.取消" << endl;
	cin >> opts;
	if (opts == 1) {
		// 使用trunc模式打开,如果已经存在文件会先删掉再创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		resetCompetition();
		cout << "清空成功!" << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::exitCompetition() {
	exit(EXIT_SUCCESS);
}