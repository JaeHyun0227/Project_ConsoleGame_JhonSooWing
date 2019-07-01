#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include "Color.h"

using namespace std;


int map[7][7] = {
	{ 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 2, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1 }
};




class Map{
public:

	void Print();
	void MoveCntPrint(int num);


	void textcolor(int color_number)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
	}

	void PlayerMove(int p, char ch, int cnt) {	


		switch (ch){
		case 'A':
		case 'a':
			if (p > cnt){
				map[5][p] -= 2;
				map[5][p - cnt] += 2;
			}break;
		case 'D':
		case 'd':
			if (p < 6-cnt){
				map[5][p] -= 2;
				map[5][p + cnt] += 2;
			}break;
		case 'q':
		case 'Q':
			{
				Map map;
				
				map.textcolor(LIGHTBLUE);
				for (int i = 0; i < 10; i++)
					cout << " |일시 정지|" << endl;;
				getch();
			}break;
		default: break;
		}
	}
	int PlayerFind(){
		int i;

		for (i = 0; i < 5; i++)	
			if (map[5][i] == 2 || map[5][i]== 5) break;

		return i;
	}




};


void Map::Print(){

	Color color;

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			switch (map[i][j]) {
			case 0: textcolor(WHITE); cout << "□"; break;
			case 1: textcolor(YELLOW); cout << "■"; break;
			case 2: textcolor(LIGHTWHITE); cout << "▲"; break;
			case 3: textcolor(BLUE); cout << "◆"; break;
			case 4: textcolor(PURPLE); cout << "！"; break;
			case 5: textcolor(LIGHTRED); cout << "△"; break;
			case 6: textcolor(RED); cout << "▒"; break;
			case 8: textcolor(LIGHTPURPLE); cout << "▒"; break;
			}
		}
		cout << endl;
	}
}

void Map::MoveCntPrint(int num) {
	Color color;

	for (int i = 1; i <= 4; i++) {
		
		textcolor(OK);
		if(num == i)
			textcolor(LIGHTOK);
		
		cout << "  " << i;
	}
	cout << endl;


}

class Player {
private:
	int position;
public:
	Player() { position = 3; }

	int getPosition() { return position; }
	void setPosition(int position) { this->position = position; }


	bool PlayerDie(){
		switch (map[5][position]) {
		case 5:
		case 8: return true; break;
		default: return false; break;
		}
	}

};

class Wall {
private:
public:

	void WallCreate() {

		int Wallcnt = 0;

		for (int i = 1; i <= 5 && Wallcnt < 2; i++) {
			if (map[0][i] == 6) continue;

			map[0][i] = rand() % 2;


			switch (map[0][i]) {
			case 0: map[0][i] = 0; break;
			case 1: map[0][i] = 3; Wallcnt++;  break;
			default: break;
			}

		}
	}
	void WallDown() {
		for (int i = 1; i <= 5; i++)
			if(map[5][i] == 3)
				map[5][i] -= 3;

		for (int i = 4; i >= 0; i--) {
			for (int j = 5; j >= 1; j--) {
				if (map[i][j] == 3 || map[i][j] == 5) {
					map[i][j] -= 3;
					map[i + 1][j] += 3;

					if (map[i + 1][j] == 5) {
						//Life -1
					}
				}
			}
		}
	}
};

class JhonSoo {
public:
	int DangerLineFind() {
		for (int i = 1; i <= 5; i++)
			if (map[6][i] == 4) return i;
	}

	void Danger() {
		int DangerLine = rand() % 5 + 1;

		map[6][DangerLine] = 4;
	}
	void Attack() {
		int Line = DangerLineFind();

		for (int i = 0; i < 6; i++){
			if (map[i][Line] == 5 || map[i][Line] == 2) {
				//죽음처리
			}
			else {
				map[i][Line] = 6;
			}
		}
	}
	void AttackCancle() {
		int Line = DangerLineFind();

		for (int i = 0; i < 7; i++) {
			map[i][Line] = 0;
		}
	}
};

class Score {
private:
	int Point[5] = { 0,0,0,0,0 };
public:
	void ShowPoint() {
		Map map;

		map.textcolor(LIGHTYELLO); cout << " |ＳＣＯＲＥ|" << endl;
		
		map.textcolor(YELLOW);
		cout << " |";
		for (int i = 0; i < 5; i++)
			switch (Point[i]) {
			case 0: cout << "０"; break;
			case 1: cout << "１"; break;
			case 2: cout << "２"; break;
			case 3: cout << "３"; break;
			case 4: cout << "４"; break;
			case 5: cout << "５"; break;
			case 6: cout << "６"; break;
			case 7: cout << "７"; break;
			case 8: cout << "８"; break;
			case 9: cout << "９"; break;
			default: break;
			}
		cout << "|";
		cout << endl;

	}
	void AddPoint() {
		Point[4]++;

		for (int i = 4; i > 0; i--) {
			if (Point[i] >= 10) {
				Point[i] -= 10;
				Point[i - 1]++;
			}
		}
	}


};

int main(){
	int MoveCnt = 1;
	int JhonCnt = 0;

	int LOOPTIME = 1000;

	char Move;
	Map Field;
	Player PLAYER;
	Wall wall;
	JhonSoo Jhon;
	Score score;

	srand(time(NULL));

	system("mode con:cols=15 lines=11");

	score.ShowPoint();
	Field.Print();
	Field.MoveCntPrint(MoveCnt);

	double Time = GetTickCount();

	while (true) {


		if (GetTickCount() - Time >= LOOPTIME) {
			score.AddPoint();

			JhonCnt++;
			if (JhonCnt == 5) {
				Jhon.Danger();
			}else if (JhonCnt == 8) {
				Jhon.Attack();
			}else if (JhonCnt == 9) {
				Jhon.AttackCancle();
			}else if (JhonCnt == 10) {
				LOOPTIME -= 50;
				JhonCnt = 0;
			}

			system("cls");
			wall.WallDown();
			wall.WallCreate();
			score.ShowPoint();
			Field.Print();
			Field.MoveCntPrint(MoveCnt);

			Time = GetTickCount();

		}

		if (_kbhit()) {

			Move = getch();


			if ('1' <= Move && Move <= '4')
				MoveCnt = Move - '0';
			else {

				Field.PlayerMove(PLAYER.getPosition(), Move, MoveCnt);
				PLAYER.setPosition(Field.PlayerFind());
			}
			system("cls");
			score.ShowPoint();
			Field.Print();
			Field.MoveCntPrint(MoveCnt);
		}

		if (PLAYER.PlayerDie() == true) break;
	}

	system("cls");
	cout << " 당신은 명치를 뚫렸습니다. " << endl;
	getch();
	getch();


	system("cls");
	cout << " |종료포인트|" << endl;
	score.ShowPoint();

	getch();
	return 0;
}