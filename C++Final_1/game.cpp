#include"mainfunc.h"
int state_game(vector<string>& wordList)//����ֵΪ������
{
	int rewards = 0;
	int round = 0;//�ڼ���
	int wordCount =5;
	int size = wordList.size();
	int round_time = 3000;

	string targetWord;
	string myWord="\0";
	cout << "Game Start ! Type \":q\" to Quit !" << endl;
	while(myWord!=":q")
	{
		if (wordCount == 0)
		{
			round++;//ÿ��5�����ʡ����ֵ�����ɺ����ò�������һ�֡�
			wordCount = 5;
			cout << "Next Round " << round << " ! " << wordCount << "word(s) left !" << endl;
		}
		targetWord = wordList[rand()%wordList.size()];
		cout << targetWord;
		Sleep(round_time);
		cout << "\r                   \r";//���һ�У����ѹ���Ƶ���ʼ��
		cin >> myWord;
		if (targetWord == myWord)
		{
			wordCount--;
			cout << "Correct !" << endl;
		}
		else if(myWord !=":q")
		{
			cout << "Wrong !" << endl;
		}
	}
	cout << "Your Best Round��" << round << endl;
	return round;
}
void flush_player(int nowUserPos, int bestRound, vector<player>& playerList)
{
	player nowPlayer = playerList[nowUserPos];
	nowPlayer.rewards(bestRound);	//���´��˵ľ��顢�ȼ����������

	for (vector<player>::iterator playerIter=playerList.begin(); playerIter!=playerList.end();)//����playerList
	{
		if (playerIter->get_name() == nowPlayer.get_name())
		{
			playerList.erase(playerIter);
			playerList.push_back(nowPlayer);
			break;
		}
		else
			playerIter++;
	}

	string tmpPlayerInfo;//����playerFile
	vector<string> tmpInfoList;
	fstream playerFile;
	if(DEV_MODE)
		playerFile.open("D:\\coding\\C++Final\\C++Final_1\\Debug\\playerList.csv", ios::in | ios::out);
	else 
		playerFile.open("playerList.csv", ios::in | ios::out);

	if (!playerFile)
	{
		cout << "playerList.csv open failed! " << endl;
		abort();
	}
	playerFile.seekp(0);
	getline(playerFile, tmpPlayerInfo);
	streamoff tmpFptr = playerFile.tellg();//��ÿ��ͷ����һ�е�ĩβ����һ����ַ�����������һ������Ϣ��Ҫ�޸ĵģ��ص����ͷ�����޸���Ϣ��
	while (playerFile && !(playerFile.peek()==EOF))
	{
		getline(playerFile, tmpPlayerInfo);
		string_split(tmpPlayerInfo, tmpInfoList, ",");
		if (tmpInfoList[0] == nowPlayer.get_name())
		{
			playerFile.seekp(tmpFptr);
			playerFile << "\n" << nowPlayer.get_name() << "," << nowPlayer.get_password() << "," << nowPlayer.get_level() << "," << nowPlayer.get_exp() << "," << nowPlayer.get_best_round();
			break;
		}
		tmpInfoList.clear();
		tmpFptr = playerFile.tellg();
	}
	playerFile.close();
	return;
}
