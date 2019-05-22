#include"database.h"

user::user(string newName, string newPassword)
{
	name = newName;
	password = newPassword;
};
user::~user()
{
};
string user::get_name()
{
	return name;
}
string user::get_password()
{
	return password;
}

player::player(string newName, string newPassword,int newExp,int newLevel,int newbestRound) : user(newName,newPassword)
{
	exp = newExp;
	level = newLevel;
	best_round = newbestRound;
};
player::~player()
{
}
int player::get_exp() { return exp; }
int player::get_level() { return level; }
int player::get_best_round() { return best_round; }
void player::rewards(int bestRound)
{
	exp += 5*bestRound*bestRound;//获得经验为(5*本次游戏关数^2)
	if (this->best_round < bestRound)//若本次回合数大于历史最佳回合数则更新
		best_round = bestRound;
	while (exp / (10 * (level + 1)) > 0)//每升一级，需要10倍（等级+1）的经验再升级
	{
		exp -= 10 * (level + 1); 
		level++;
	}
}

tester::tester(string newName, string newPassword,int newProblemNum, int newLevel) :user(newName, newPassword)
{
	level = newProblemNum;
	problemNum = newProblemNum;
}
tester::~tester()
{
}
short tester::get_level() { return level; }
int tester::get_problem_num() { return problemNum; }
void tester::rewards(int wordAdd)
{
	problemNum += wordAdd;
	while (problemNum >= ((level + 1)*(level + 2) / 2))
		level++;//每升1级，升级需要单词数变为级数+1。0级1个单词，1级2个单词，以此类推。单词总数不像Exp一样会自减，因此递推得到等级与单词总数的关系。
};



