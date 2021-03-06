#include<iostream>
#include<iomanip>
#include<conio.h>

using namespace std;
#define Up 72
#define Down 80
#define Left 75
#define Right 77
int mx = 30, my = 20;
int tx, ty;
int dir = Right;
int length = 3;
clock_t now, last;
int speed = 1;
bool lose = false;
int body_x[100] = { 5,4,3 };
int body_y[100] = { 5,5,5 };
void rand_t() {
	tx = rand() % mx + 1;
	ty = rand() % my + 1;
}
void insert(int x, int y) {
	for (int i = 1; i < length; i++)
	{
		body_x[length - i] = body_x[length - i - 1];
		body_y[length - i] = body_y[length - i - 1];
	}
	body_x[0] = x;
	body_y[0] = y;
}
char get_item(int x, int y) {
	char item = ' ';
	//border
	//content
	for (int a = 0; a < length; a++)
	{
		if (y == body_y[a] && x == body_x[a]) { item = 'O'; }
	}
	if (y == ty && x == tx) { item = 'X'; }
	if (lose)
	{
		item = '#';
	}
	return item;
}
void update_map() {
	system("cls");
	cout << "你的分数是：" << length << endl;
	for (int i = 0; i <= my + 1; i++)
	{
		for (int j = 0; j <= mx + 1; j++)
		{
			if (i == 0 || i == my + 1 || j == 0 || j == mx + 1)
			{
				cout << setw(2) << '#';
				if (j == mx + 1)cout << endl;
			}
			else
			{
				cout << setw(2) << get_item(j, i);
			}
		}
	}
	if (lose)
	{
		cout << "你输了！" << endl;
		system("pause");
		exit(0);
	}
}
void update_data() {
	//bool state = 0;
	speed = 1 + length / 5;
	int tar_x, tar_y;//目标坐标
	switch (dir)
	{
	case Up:
		tar_x = body_x[0]; tar_y = body_y[0] - 1;
		break;
	case Down:
		tar_x = body_x[0]; tar_y = body_y[0] + 1;
		break;
	case Left:
		tar_x = body_x[0] - 1; tar_y = body_y[0];
		break;
	case Right:
		tar_x = body_x[0] + 1; tar_y = body_y[0];
		break;
	}
	if (body_x[0] == 0 || body_x[0] == mx + 1 || body_y[0] == 0 || body_y[0] == my + 1)lose = true;//撞到墙
	for (int i = 1; i < length; i++)//撞到自己
	{
		if (tar_x == body_x[i] && tar_y == body_y[i])lose = true;
	}
	if (tx == tar_x && ty == tar_y)//如果吃到
	{
		rand_t();
		body_x[length] = tx;
		body_y[length] = ty;
		length += 1;
	}
	insert(tar_x, tar_y);//移动
}
void update_key() {
	if (_kbhit()) {
		char key = _getch();
		switch (key)
		{
		case Up:if (dir == Right || dir == Left) { dir = Up; }break;
		case Down:if (dir == Right || dir == Left) { dir = Down; }break;
		case Left:if (dir == Up || dir == Down) { dir = Left; }break;
		case Right:if (dir == Up || dir == Down) { dir = Right; }break;
		}
	}
}
void update() {
	update_key();
	if ((now - last) / (CLOCKS_PER_SEC / speed) != 0) {
		last = now;
		update_map();
		update_data();
	}
}
void main() {
	rand_t();
	last = clock();
	while (true)
	{
		now = clock();
		update();
	}
}