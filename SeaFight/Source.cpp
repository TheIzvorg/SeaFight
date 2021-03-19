#include <iostream>;
#include <Windows.h>;
#include <conio.h>;
#include <ctime>;
#include <string>;

using namespace std;

struct Options {
	int FirstMap[12][12] = { {1,1,1,1,1,1,1,1,1,1,1,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,1,1,1,1,1,1,1,1,1,1,1, } };
	int SecondMap[12][12] = { {1,1,1,1,1,1,1,1,1,1,1,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,1,1,1,1,1,1,1,1,1,1,1, } };

	int shipS = 0, 
		shipM = 0,
		shipL = 0,
		shipXL = 0;

	int size = 12;
	bool isRandomPlace = true;
	int ShipColor = 7;
	int ShipCount1 = 20, ShipCount2 = 20;
};

void ShowMenu(Options& options);

void SetColor(char symbol, int color) {
	HANDLE _color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(_color, color);
	cout << symbol << " ";
	SetConsoleTextAttribute(_color, 7);
}

void ShowMap(Options options, bool move, bool isFirstPlayer = false) {
	//int** Map = new int *[12];
	//for (int i = 0; i < 12; i++) Map[i] = new int[12];
	int Map[12][12];
	if (isFirstPlayer) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				Map[i][j] = options.FirstMap[i][j];
			}
		}
		cout << "Первый:\n";
	}
	else {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				Map[i][j] = options.SecondMap[i][j];
			}
		}
		cout << "Второй:\n";
	}
	cout << "     a b c d e f g h i j" << endl;
	for (int i = 0; i < 12; i++) {
		if (i>= 1 && i <= 9)
			cout << i << "  ";
		else if (i == 10)
			cout << i << " ";
		else 
			cout << "   ";
		for (int j = 0; j < 12; j++) {
			if (Map[i][j] == 1) {
				SetColor('#', 14);
			}
			else if ((Map[i][j] == 2 || Map[i][j] == 9) && move) {
				SetColor('=', options.ShipColor);
			}
			else if (Map[i][j] == 3) {
				SetColor('o', 11);
			}
			else if (Map[i][j] == 4) {
				SetColor('x', 6);
			}
			else if (Map[i][j] == 5) {
				SetColor('X', 4);
			}
			else if ((Map[i][j] == 0 || Map[i][j] == 8) || !move) {
				SetColor('~', 9);
			}
		}
		cout << endl;
	}
}

void RandomShip(Options& options, bool isFirstMap = true) {
	srand(time(0) % (rand() / 2 - 5 / 3 * 2));
	int Map[12][12];
	if (isFirstMap) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				Map[i][j] = options.FirstMap[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				Map[i][j] = options.SecondMap[i][j];
				options.shipXL = 0;
				options.shipL = 0;
				options.shipM = 0;
				options.shipS = 0;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		if (options.shipXL != 1) {
			bool isStop = false;
			for (; !isStop;) {
				int X = rand() % 10 + 1;
				int Y = rand() % 10 + 1;
				switch (rand() % 4 + 1) {
				case 1:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2 &&
						Map[X+1][Y] != 1 && Map[X+1][Y] != 8 && Map[X+1][Y] != 2 &&
						Map[X+2][Y] != 1 && Map[X+2][Y] != 8 && Map[X+2][Y] != 2 &&
						Map[X+3][Y] != 1 && Map[X+3][Y] != 8 && Map[X+3][Y] != 2) {
						for (int o = 0; o < 4; o++) {
							Map[X + o][Y] = 2;
							Map[X + o][Y - 1] = 8;
							Map[X + o][Y + 1] = 8;
							if (o == 3) {
								Map[X + o + 1][Y] = 8;
								Map[X + o + 1][Y - 1] = 8;
								Map[X + o + 1][Y + 1] = 8;
								Map[X - 1][Y] = 8;
								Map[X - 1][Y - 1] = 8;
								Map[X - 1][Y + 1] = 8;
							}
						}
						isStop = true;
						break;
					}
				case 2:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2 &&
						Map[X - 1][Y] != 1 && Map[X - 1][Y] != 8 && Map[X-1][Y] != 2 &&
						Map[X - 2][Y] != 1 && Map[X - 2][Y] != 8 && Map[X-2][Y] != 2 &&
						Map[X - 3][Y] != 1 && Map[X - 3][Y] != 8 && Map[X-3][Y] != 2) {
						for (int o = 0; o < 4; o++) {
							Map[X - o][Y] = 2;
							Map[X - o][Y - 1] = 8;
							Map[X - o][Y + 1] = 8;
							if (o == 3) {
								Map[X - o - 1][Y] = 8;
								Map[X - o - 1][Y - 1] = 8;
								Map[X - o - 1][Y + 1] = 8;
								Map[X + 1][Y] = 8;
								Map[X + 1][Y - 1] = 8;
								Map[X + 1][Y + 1] = 8;
							}
						}
						isStop = true;
						break;
					}
				case 3:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2 &&
						Map[X][Y+1] != 1 && Map[X][Y+1] != 8 && Map[X][Y+1] != 2 &&
						Map[X][Y+2] != 1 && Map[X][Y+2] != 8 && Map[X][Y+2] != 2 &&
						Map[X][Y+3] != 1 && Map[X][Y+3] != 8 && Map[X][Y+3] != 2) {
						for (int o = 0; o < 4; o++) {
							Map[X][Y + o] = 2;
							Map[X - 1][Y + o] = 8;
							Map[X + 1][Y + o] = 8;
							if (o == 3) {
								Map[X][Y + o + 1] = 8;
								Map[X - 1][Y + o + 1] = 8;
								Map[X + 1][Y + o + 1] = 8;
								Map[X][Y - 1] = 8;
								Map[X - 1][Y - 1] = 8;
								Map[X + 1][Y - 1] = 8;
							}
						}
						isStop = true;
						break;
					}
				case 4:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2 &&
						Map[X][Y - 1] != 1 && Map[X][Y - 1] != 8 && Map[X][Y-1] != 2 &&
						Map[X][Y - 2] != 1 && Map[X][Y - 2] != 8 && Map[X][Y-2] != 2 &&
						Map[X][Y - 3] != 1 && Map[X][Y - 3] != 8 && Map[X][Y-3] != 2) {
						for (int o = 0; o < 4; o++) {
							Map[X][Y - o] = 2;
							Map[X - 1][Y - o] = 8;
							Map[X + 1][Y - o] = 8;
							if (o == 3) {
								Map[X][Y - o - 1] = 8;
								Map[X - 1][Y - o - 1] = 8;
								Map[X + 1][Y - o - 1] = 8;
								Map[X][Y + 1] = 8;
								Map[X - 1][Y + 1] = 8;
								Map[X + 1][Y + 1] = 8;
							}
						}
						isStop = true;
					}
					break;
				}
			}
			options.shipXL++;
		}
		if (options.shipL != 2) {
			bool isStop = false;
			for (; !isStop;) {
				int X = rand() % 10 + 1;
				int Y = rand() % 10 + 1;
				switch (rand() % 4 + 1) {
				case 1:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2 &&
						Map[X + 1][Y] != 1 && Map[X + 1][Y] != 8 && Map[X+1][Y] != 2 &&
						Map[X + 2][Y] != 1 && Map[X + 2][Y] != 8 && Map[X+2][Y] != 2) {
						for (int o = 0; o < 3; o++) {
							if (Map[X + o][Y] != 2 && Map[X + o][Y] != 8) {
								Map[X + o][Y] = 2;
								Map[X + o][Y - 1] = 8;
								Map[X + o][Y + 1] = 8;
								if (o == 2) {
									Map[X + o + 1][Y] = 8;
									Map[X + o + 1][Y - 1] = 8;
									Map[X + o + 1][Y + 1] = 8;
									Map[X - 1][Y] = 8;
									Map[X - 1][Y - 1] = 8;
									Map[X - 1][Y + 1] = 8;
								}
							}
						}
						isStop = true;
						break;
					}
				case 2:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2 &&
						Map[X - 1][Y] != 1 && Map[X - 1][Y] != 8 && Map[X-1][Y] != 2 &&
						Map[X - 2][Y] != 1 && Map[X - 2][Y] != 8 && Map[X-2][Y] != 2) {
						for (int o = 0; o < 3; o++) {
							if (Map[X - o][Y] != 2 && Map[X - o][Y] != 8) {
								Map[X - o][Y] = 2;
								Map[X - o][Y - 1] = 8;
								Map[X - o][Y + 1] = 8;
								if (o == 2) {
									Map[X - o - 1][Y] = 8;
									Map[X - o - 1][Y - 1] = 8;
									Map[X - o - 1][Y + 1] = 8;
									Map[X + 1][Y] = 8;
									Map[X + 1][Y - 1] = 8;
									Map[X + 1][Y + 1] = 8;
								}
							}
						}
						isStop = true;
						break;
					}
				case 3:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2 &&
						Map[X][Y + 1] != 1 && Map[X][Y + 1] != 8 && Map[X][Y+1] != 2 &&
						Map[X][Y + 2] != 1 && Map[X][Y + 2] != 8 && Map[X][Y+2] != 2) {
						for (int o = 0; o < 3; o++) {
							if (Map[X][Y + o] != 2 && Map[X][Y + o] != 8)
							{
								Map[X][Y + o] = 2;
								Map[X - 1][Y + o] = 8;
								Map[X + 1][Y + o] = 8;
								if (o == 2) {
									Map[X][Y + o + 1] = 8;
									Map[X - 1][Y + o + 1] = 8;
									Map[X + 1][Y + o + 1] = 8;
									Map[X][Y - 1] = 8;
									Map[X - 1][Y - 1] = 8;
									Map[X + 1][Y - 1] = 8;
								}
							}
						}
						isStop = true;
						break;
					}
				case 4:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2 &&
						Map[X][Y - 1] != 1 && Map[X][Y - 1] != 8 && Map[X][Y-1] != 2 &&
						Map[X][Y - 2] != 1 && Map[X][Y - 2] != 8 && Map[X][Y-2] != 2) {
						for (int o = 0; o < 3; o++) {
							if (Map[X][Y - o] != 2 && Map[X][Y - o] != 8) {
								Map[X][Y - o] = 2;
								Map[X - 1][Y - o] = 8;
								Map[X + 1][Y - o] = 8;
								if (o == 2) {
									Map[X][Y - o - 1] = 8;
									Map[X - 1][Y - o - 1] = 8;
									Map[X + 1][Y - o - 1] = 8;
									Map[X][Y + 1] = 8;
									Map[X - 1][Y + 1] = 8;
									Map[X + 1][Y + 1] = 8;
								}
							}
						}
						isStop = true;
					}
					break;
				}
			}
			options.shipL++;
		}
		if (options.shipM != 3) {
			bool isStop = false;
			for (; !isStop;) {
				int X = rand() % 10 + 1;
				int Y = rand() % 10 + 1;
				switch (rand() % 4 + 1) {
				case 1:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2 &&
						Map[X + 1][Y] != 1 && Map[X + 1][Y] != 8 && Map[X+1][Y] != 2) {
						for (int o = 0; o < 2; o++) {
							if (Map[X + o][Y] != 2 && Map[X + o][Y] != 8) {
								Map[X + o][Y] = 2;
								Map[X + o][Y - 1] = 8;
								Map[X + o][Y + 1] = 8;
								if (o == 1) {
									Map[X + o + 1][Y] = 8;
									Map[X + o + 1][Y - 1] = 8;
									Map[X + o + 1][Y + 1] = 8;
									Map[X - 1][Y] = 8;
									Map[X - 1][Y - 1] = 8;
									Map[X - 1][Y + 1] = 8;
								}
							}
						}
						isStop = true;
						break;
					}
				case 2:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2 &&
						Map[X - 1][Y] != 1 && Map[X - 1][Y] != 8 && Map[X-1][Y] != 2) {
						for (int o = 0; o < 2; o++) {
							if (Map[X - o][Y] != 2 && Map[X - o][Y] != 8) {
								Map[X - o][Y] = 2;
								Map[X - o][Y - 1] = 8;
								Map[X - o][Y + 1] = 8;
								if (o == 1) {
									Map[X - o - 1][Y] = 8;
									Map[X - o - 1][Y - 1] = 8;
									Map[X - o - 1][Y + 1] = 8;
									Map[X + 1][Y] = 8;
									Map[X + 1][Y - 1] = 8;
									Map[X + 1][Y + 1] = 8;
								}
							}
						}
						isStop = true;
						break;
					}
				case 3:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2 &&
						Map[X][Y + 1] != 1 && Map[X][Y + 1] != 8 && Map[X][Y+1] != 2) {
						for (int o = 0; o < 2; o++) {
							if (Map[X][Y + o] != 2 && Map[X][Y + o] != 8)
							{
								Map[X][Y + o] = 2;
								Map[X - 1][Y + o] = 8;
								Map[X + 1][Y + o] = 8;
								if (o == 1) {
									Map[X][Y + o + 1] = 8;
									Map[X - 1][Y + o + 1] = 8;
									Map[X + 1][Y + o + 1] = 8;
									Map[X][Y - 1] = 8;
									Map[X - 1][Y - 1] = 8;
									Map[X + 1][Y - 1] = 8;
								}
							}
						}
						isStop = true;
						break;
					}
				case 4:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2 &&
						Map[X][Y - 1] != 1 && Map[X][Y - 1] != 8 && Map[X][Y-1] != 2) {
						for (int o = 0; o < 2; o++) {
							if (Map[X][Y - o] != 2 && Map[X][Y - o] != 8) {
								Map[X][Y - o] = 2;
								Map[X - 1][Y - o] = 8;
								Map[X + 1][Y - o] = 8;
								if (o == 1) {
									Map[X][Y - o - 1] = 8;
									Map[X - 1][Y - o - 1] = 8;
									Map[X + 1][Y - o - 1] = 8;
									Map[X][Y + 1] = 8;
									Map[X - 1][Y + 1] = 8;
									Map[X + 1][Y + 1] = 8;
								}
							}
						}
						isStop = true;
					}
					break;
				}
			}
			options.shipM++;
		}
		if (options.shipS != 4) {
			bool isStop = false;
			for (; !isStop;) {
				int X = rand() % 10 + 1;
				int Y = rand() % 10 + 1;
				switch (rand() % 4 + 1) {
				case 1:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2) {
						for (int o = 0; o < 1; o++) {
							if (Map[X + o][Y] != 2 && Map[X + o][Y] != 8) {
								Map[X + o][Y] = 2;
								Map[X + o][Y - 1] = 8;
								Map[X + o][Y + 1] = 8;
									Map[X + o + 1][Y] = 8;
									Map[X + o + 1][Y - 1] = 8;
									Map[X + o + 1][Y + 1] = 8;
									Map[X - 1][Y] = 8;
									Map[X - 1][Y - 1] = 8;
									Map[X - 1][Y + 1] = 8;
							}
						}
						isStop = true;
						break;
					}
				case 2:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2) {
						for (int o = 0; o < 1; o++) {
							if (Map[X - o][Y] != 2 && Map[X - o][Y] != 8) {
								Map[X - o][Y] = 2;
								Map[X - o][Y - 1] = 8;
								Map[X - o][Y + 1] = 8;
									Map[X - o - 1][Y] = 8;
									Map[X - o - 1][Y - 1] = 8;
									Map[X - o - 1][Y + 1] = 8;
									Map[X + 1][Y] = 8;
									Map[X + 1][Y - 1] = 8;
									Map[X + 1][Y + 1] = 8;
							}
						}
						isStop = true;
						break;
					}
				case 3:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2) {
						for (int o = 0; o < 1; o++) {
							if (Map[X][Y + o] != 2 && Map[X][Y + o] != 8)
							{
								Map[X][Y + o] = 2;
								Map[X - 1][Y + o] = 8;
								Map[X + 1][Y + o] = 8;
									Map[X][Y + o + 1] = 8;
									Map[X - 1][Y + o + 1] = 8;
									Map[X + 1][Y + o + 1] = 8;
									Map[X][Y - 1] = 8;
									Map[X - 1][Y - 1] = 8;
									Map[X + 1][Y - 1] = 8;
							}
						}
						isStop = true;
						break;
					}
				case 4:
					if (Map[X][Y] != 1 && Map[X][Y] != 8 && Map[X][Y] != 2) {
						for (int o = 0; o < 1; o++) {
							if (Map[X][Y - o] != 2 && Map[X][Y - o] != 8) {
								Map[X][Y - o] = 2;
								Map[X - 1][Y - o] = 8;
								Map[X + 1][Y - o] = 8;
									Map[X][Y - o - 1] = 8;
									Map[X - 1][Y - o - 1] = 8;
									Map[X + 1][Y - o - 1] = 8;
									Map[X][Y + 1] = 8;
									Map[X - 1][Y + 1] = 8;
									Map[X + 1][Y + 1] = 8;
							}
						}
						isStop = true;
					}
					break;
				}
			}
			options.shipS++;
		}
	}
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if (i == 0 || i == 11 || j == 0 || j == 11) {
				Map[i][j] = 1;
			}
		}
	}
	if (isFirstMap) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				options.FirstMap[i][j] = Map[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				options.SecondMap[i][j] = Map[i][j];
			}
		}
	}
}

bool PlaceShip(Options& options, int D = 1, bool isFirstMap = true) {
	bool isStop = false;
	int Map[12][12];
	if (isFirstMap) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				Map[i][j] = options.FirstMap[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				Map[i][j] = options.SecondMap[i][j];
			}
		}
	}
	const int C = 4;
	int cord[C][2];
	for (int x = 0, count = 0; x < 12; x++) {
		for (int y = 0; y < 12; y++) {
			if (Map[y][x] == 9) {
				cord[count][0] = x;
				cord[count][1] = y;
				count++;
				if (count == C-1) {
					break;
				}
			}
			else {
			}
		}
		if (count == C-1) {
			break;
		}
	}
	while (!isStop) {
		switch (_getch())
		{
			case 'A':
			case 'a':
			case 75:
				if (Map[cord[C-1][1]][cord[C-1][0] - 1] != 1 && Map[cord[0][1]][cord[0][0] - 1] != 1) {
					for (int i = 0; i < C; i++) {
						Map[cord[i][1]][cord[i][0]] = 0;
						cord[i][0]--;
						Map[cord[i][1]][cord[i][0]] = 9;
					}
				}
				isStop = true;
				break;
			case 'D':
			case 'd':
			case 77:
				if (Map[cord[C-1][1]][cord[C-1][0] + 1] != 1 && Map[cord[0][1]][cord[0][0] + 1] != 1) {
					for (int i = C-1; i >= 0; i--) {
						Map[cord[i][1]][cord[i][0]] = 0;
						cord[i][0]++;
						Map[cord[i][1]][cord[i][0]] = 9;
					}
				}
				isStop = true;
				break;
			case 'S':
			case 's':
			case 80:
				if (Map[cord[C-1][1]+1][cord[C-1][0]] != 1 && Map[cord[0][1]+1][cord[0][0]] != 1) {
					for (int i = C-1; i >= 0; i--) {
						Map[cord[i][1]][cord[i][0]] = 0;
						cord[i][1]++;
						Map[cord[i][1]][cord[i][0]] = 9;
					}
				}
				isStop = true;
				break;
			case 'W':
			case 'w':
			case 72:
				if (Map[cord[C-1][1] - 1][cord[C-1][0]] != 1 && Map[cord[0][1] - 1][cord[0][0]] != 1) {
					for (int i = 0; i < C; i++) {
						Map[cord[i][1]][cord[i][0]] = 0;
						cord[i][1]--;
						Map[cord[i][1]][cord[i][0]] = 9;
					}
				}
				isStop = true;
				break;
			case 'E':
			case 'e':
			case 'Q':
			case 'q':
				if (true) {
					int	bufferArray[4][4];
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
 							bufferArray[i][j] = Map[cord[i][0]][cord[j][1] + j / 2];
						}
					}
					int buf[4][4];
					for (int i = 0; i < 4; i++){
						Map[cord[i][1]][cord[i][0]] = 0;
						for (int j = 0; j < 4; j++) {
							buf[j][i] = bufferArray[i][j];
						}
					}
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
							if (buf[i][j] == 9) {
								Map[cord[i][1]+i][cord[j][0]+j] = buf[i][j];
							}
						}
					}
				}
				isStop = true;
				break;
			case 13: // ENTER
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						if (Map[i][j] == 9) {
							Map[i][j] = 2;
						}
					}
				}
				return true;
				isStop = true;
				break;
		}
	}
	if (isFirstMap) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				options.FirstMap[i][j] = Map[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				options.SecondMap[i][j] = Map[i][j];
			}
		}
	}
	return false;
}

int CharToInt(char symbol) {
	int result = 0;
	// a b c d e f g h i j
	switch (symbol) {
	case 'a':
	case 'A':
	case '1':
		result = 1;
		break;
	case 'b':
	case 'B':
	case '2':
		result = 2;
		break;
	case 'c':
	case 'C':
	case '3':
		result = 3;
		break;
	case 'd':
	case 'D':
	case '4':
		result = 4;
		break; 
	case 'e':
	case 'E':
	case '5':
		result = 5;
		break; 
	case 'f':
	case 'F':
	case '6':
		result = 6;
		break; 
	case 'g':
	case 'G':
	case '7':
		result = 7;
		break; 
	case 'h':
	case 'H':
	case '8':
		result = 8;
		break; 
	case 'i':
	case 'I':
	case '9':
		result = 9;
		break; 
	case 'j':
	case 'J':
	case '10':
		result = 10;
		break;
	}
	return result;
}

void Surrender(Options& options, bool isFirstPlayer) {
	// TODO: Surrender
}

void PlayerMove(Options& options, bool isFirstPlayer = true) {
	int Map[12][12];
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if (isFirstPlayer) {
				Map[i][j] = options.FirstMap[i][j];
			}
			else {
				Map[i][j] = options.SecondMap[i][j];
			}
		}
	}
	system("cls");
	//сюда вставить cout карты врага через ShowMap();
	cout << "Ваша ход!\n\n";
	ShowMap(options, true, !isFirstPlayer);
	ShowMap(options, false, isFirstPlayer);
	char hitX; int hitY;
	cout << "Куда вы хотите ударить?\n[?] - "; 
	cin >> hitX; 
	hitX = CharToInt(hitX);
	cin >> hitY;
	if (hitX < 1 || hitX > 11 || hitY < 1 || hitY > 11 || options.SecondMap[hitY][hitX] == 3 || options.SecondMap[hitY][hitX] == 4) {
		hitX = rand() % 9 + 1;
		hitY = rand() % 9 + 1;
	}
	if (Map[hitY][hitX] == 0 || Map[hitY][hitX] == 8) {
		Map[hitY][hitX] = 3;
	}
	else if (Map[hitY][hitX] == 2) {
		Map[hitY][hitX] = 4;
		if (isFirstPlayer) {
			options.ShipCount2--;
		}
		else {
			options.ShipCount1--;
		}

	}
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if (isFirstPlayer) {
				options.FirstMap[i][j] = Map[i][j];
			}
			else {
				options.SecondMap[i][j] = Map[i][j];
			}
		}
	}
	//здесь мы обновим массив врага в выводе консоли чтобы увидеть результат
}

void BotMove(Options& options) {
	srand(time(0));
	int i1 = rand() % 10 + 1,
		i2 = rand() % 10 + 1;
	bool isRerun = options.FirstMap[i1][i2] == 3 || options.FirstMap[i1][i2] == 4;
	for (int i = 0; isRerun; i++) {
		i1 = rand() % 10 + 1;
		i2 = rand() % 10 + 1;
		isRerun = options.FirstMap[i1][i2] == 3 || options.FirstMap[i1][i2] == 4;
	}
	if (options.FirstMap[i1][i2] == 0 || options.FirstMap[i1][i2] == 8) {
		options.FirstMap[i1][i2] = 3;
	}
	else if (options.FirstMap[i1][i2] == 2) {
		options.FirstMap[i1][i2] = 4;
		options.ShipCount1--;
	}
	cout << endl << "Противник ударил по координатам: " << endl << "[X]: " << i1 << endl << "[Y]: " << i2;
}

void End(Options& options, bool isFirstPlWin) {
	Sleep(1000);
	system("CLS");
	cout << "Игра окончена!\nПобеда за:" << endl;
	if (isFirstPlWin) {
		cout << "Игроком №1";
	}
	else
	{
		cout << "Игроком №2";
	}
	Sleep(5000);
	ShowMenu(options);
}
//Блок методов для главного меню
void SinglePlayer(Options& options) {
	cout << "\n\n\t\t\t\t\tВы выбрали режим одиночной игры\n\n";
	if (options.isRandomPlace) {
		RandomShip(options, true);
		RandomShip(options, false);
	}
	else {
		PlaceShip(options, true);
		RandomShip(options, false);
	}
	for (;;) {
		system("cls");
		PlayerMove(options,true);
		if (options.ShipCount1 <= 0) {
			End(options,false);
		}
		BotMove(options);
		if (options.ShipCount2 <= 0) {
			End(options,true);
		}
		Sleep(500);
	}
}

void MultiPlayer(Options& options) {
	
	cout << "Вы выбрали режим многопользовательской игры";
	if (options.isRandomPlace) {
		RandomShip(options, true);
		RandomShip(options, false);
	}
	else {
		PlaceShip(options, true);
		PlaceShip(options, false);
	}
	for (;;) {
		system("cls");
		PlayerMove(options, true);
		if (options.ShipCount2 <= 0) {
			End(options,true);
		}
		PlayerMove(options, false);
		if (options.ShipCount1 <= 0) {
			End(options,false);
		}
	}
}

void Settings(Options& options) {
	cout << "Вы зашли в настройки";
	do {
		system("CLS");
		cout << "Цвет корабля: ";
		SetColor('Ц', options.ShipColor);
		SetColor('В', options.ShipColor);
		SetColor('Е', options.ShipColor);
		SetColor('Т', options.ShipColor);
		cout << "(" << options.ShipColor << ")\n";
		string randomPla = options.isRandomPlace ? "Вкл.\n" : "Выкл.\n";
		cout << "Случайное расположение кораблей: " << randomPla;
		cout << "\n[1] Выбрать новый цвет\n[2] Случайное\\Мануальное расположение кораблей\n[3] Вернуться в меню\n\n[?] ";
		int newColor = 0;
		switch (_getch()) {
		case '1':
			cout << "Введите любое число, что станет новым цветом: ";
			cin >> newColor;
			options.ShipColor = newColor;
			break;
		case '2':
			options.isRandomPlace = !options.isRandomPlace;
			break;
		default:
			ShowMenu(options);
			break;
		}
	} while (true);
}

void Exit() {
	system("cls");
	cout << "Выход из игры...\n";
	exit(0);
}

void ShowMenu(Options& options) {
	system("cls");
	cout << "\n\n\t\t\t\t\tДобро пожаловать в 'Морской бой'!\n\n"
		"\t\t\t[1]. Одиночная игра\n"
		"\t\t\t[2]. Многопользовательская игра\n"
		"\t\t\t[3]. Настройки\n"
		"\t\t\t[4]. Выход\n";
	int MainMenuOption;
	cout << "\n\t\t\t[?] - "; cin >> MainMenuOption;
	switch (MainMenuOption)
	{
	case 1:
		SinglePlayer(options);
		break;
	case 2:
		MultiPlayer(options);
		break;
	case 3:
		Settings(options);
		break;
	case 4:
		Exit();
		break;
	default:
		break;
	}
}

int main() {
	setlocale(0, "");
	Options options;
	do {
		ShowMenu(options);
	} while (options.ShipCount1 != 0 && options.ShipCount2 != 0);
}
