#include <iostream>;
#include <Windows.h>;
#include <conio.h>;
#include <ctime>;
using namespace std;

void SinglePlayer(),
MultiPlayer(),
Settings(),
Exit(),
BotMove();
struct Options {
	//Пустое поле боя
	int Map[12][12] = { {1,1,1,1,1,1,1,1,1,1,1,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,9,9,9,9,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,1,1,1,1,1,1,1,1,1,1,1, } };

	int enemyMap[12][12] = { {1,1,1,1,1,1,1,1,1,1,1,1, },
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

	int shipS = 4, 
		shipM = 3,
		shipL = 2,
		shipXL = 1;

	int PlayerX = 4, PlayerY = 6;

	// Тест


	int size;
	//int Map[10][10];
	bool isRandomPlace = false;
	int ShipColor = 7;
	int ShipCount = 0;

};

void SetColor(char symbol, int color) {
	HANDLE _color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(_color, color);
	cout << symbol << " ";
	SetConsoleTextAttribute(_color, 7);
}

void ShowMenu() {
	// TODO: Menu

		//Главное меню
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
			SinglePlayer();
			break;
		case 2:
			MultiPlayer();
			break;
		case 3:
			Settings();
			break;
		case 4:
			Exit();
			break;
		default:
			break;
		}

	// SinglePlayer
	// Player vs Player
	// Settings (Map size, ships color, manual or randomed placement)
	// Exit
}

void ShowMap(Options& options) {
	//Отрисовка карта в зависимости от значения в массиве
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			//Если... то стена
			if (options.Map[i][j] == 1) {
				SetColor('#', 14);
			}
			//Если... то игрок
			else if (options.Map[i][j] == 2 || options.Map[i][j] == 9) {
				SetColor('=', 7);
			}
			//Если... то ничего
			else if (options.Map[i][j] == 0 || options.Map[i][j] == 8) {
				SetColor('~', 9);
			}
			//Если... то мимо
			else if (options.Map[i][j] == 3) {
				SetColor('o', 11);
			}
			//Если... то попадание
			else if (options.Map[i][j] == 4) {
				SetColor('x', 6);
			}
			//Если... то уничтожен
			else if (options.Map[i][j] == 5) {
				SetColor('X', 4);
			}
			else if (options.enemyMap[i][j] != 999) {
				SetColor('~', 9);
			}
		}
		cout << endl;
	}
}


void PlaceShip(Options& options) {
	bool isStop = false;
	// Массив координат, в котором можно будет увидеть координаты корабля
	int cord[4][2];
	for (int x = 0, count = 0; x < 12; x++) {
		for (int y = 0; y < 12; y++) {
			// Число 9 на карте означает корабль, с которым прямо сейчас происходит взаимодействие
			// После того как будет выбрано место и нажата определённая кнопка
			// Все 9-ки на поле превратятся в 2, чтобы случайно не задеть их
			if (options.Map[y][x] == 9) {
				// Заполняю массив координатами
				// Count - это номер палубы, когда 0 отвечает за координату X, а 1 за Y
				cord[count][0] = x;
				cord[count][1] = y;
				count++;
				if (count == 4) {
					break;
				}
			}
			else {
			}
		}
		if (count == 4) {
			break;
		}
	}
	while (!isStop) {
		switch (_getch())
		{
			case 'A':
			case 'a':
			case 75:
				// Как проверку я использую координаты крайных палуб корабля
				// Пока такая проверка настроенна только на 4-х палубники, но после это исправлю
				if (options.Map[cord[3][1]][cord[3][0] - 1] != 1 && options.Map[cord[0][1]][cord[0][0] - 1] != 1) {
					for (int i = 0; i < 4; i++) {
						// Абсолютно всё перемещение по карте производится по следующей схеме:
						// Сначала убираю все 9-ки с карты
						options.Map[cord[i][1]][cord[i][0]] = 0;
						// Изменяю координаты всех палуб (в данном случае палубы перемещаются влево по X)
						cord[i][0]--;
						// А потом возвращаю 9-ки на карту используя изменившиеся координаты палуб
						options.Map[cord[i][1]][cord[i][0]] = 9;
					}
				}
				/*
					// Я отказался от этого метода т.к. он оказался не эффективным.
				if (options.Map[options.PlayerY][options.PlayerX-1] != 1) {
					options.PlayerX--;
					for (int i = 1; i <= 4; i++) {
						if (options.Map[options.PlayerY][options.PlayerX + i + 1] != 2) {
							options.Map[options.PlayerY][options.PlayerX + i] = 0;
							break;
						}
					}
				}*/
				isStop = true;
				break;
			case 'D':
			case 'd':
			case 77:
				if (options.Map[cord[3][1]][cord[3][0] + 1] != 1 && options.Map[cord[0][1]][cord[0][0] + 1] != 1) {
					for (int i = 3; i >= 0; i--) {
						options.Map[cord[i][1]][cord[i][0]] = 0;
						cord[i][0]++;
						options.Map[cord[i][1]][cord[i][0]] = 9;
					}
				}
				isStop = true;
				break;
			case 'S':
			case 's':
			case 80:
				if (options.Map[cord[3][1]+1][cord[3][0]] != 1 && options.Map[cord[0][1]+1][cord[0][0]] != 1) {
					for (int i = 3; i >= 0; i--) {
						options.Map[cord[i][1]][cord[i][0]] = 0;
						cord[i][1]++;
						options.Map[cord[i][1]][cord[i][0]] = 9;
					}
				}
				isStop = true;
				break;
			case 'W':
			case 'w':
			case 72:
				if (options.Map[cord[3][1] - 1][cord[3][0]] != 1 && options.Map[cord[0][1] - 1][cord[0][0]] != 1) {
					for (int i = 0; i < 4; i++) {
						options.Map[cord[i][1]][cord[i][0]] = 0;
						cord[i][1]--;
						options.Map[cord[i][1]][cord[i][0]] = 9;
					}
				}
				isStop = true;
				break;
			case 'E':
			case 'e':
			case 'Q':
			case 'q':
				// Отсюда начинается костыльно-адский код для разворота фигуры
				if (true /*Проверка пока не сделана*/) {
					// Массив-буфер созданный с целью облегчить разворот фигуры
					int	bufferArray[4][4];
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
							// Заполняю этот массив следующим образом:
							// Используя координаты палуб я забираю с карты кусок 4 на 4, где находится корабль
							bufferArray[i][j] = options.Map[cord[i][0]][cord[j][1] + j / 2];
						}
						
					}
					int buf[4][4];
					for (int i = 0; i < 4; i++){
						// И убираю все палубы с карты
						options.Map[cord[i][1]][cord[i][0]] = 0;
						for (int j = 0; j < 4; j++) {
							// Дальше просто разворачиваю массив просто меняя местами Y с X
							buf[j][i] = bufferArray[i][j];
						}
					}
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 4; j++) {
							// И вывожу изменённые координаты палуб на карту
							// К сожалению этот этап пока работает не верно.
							if (buf[i][j] == 9) {
								options.Map[cord[i][1]+i][cord[j][0]+j] = buf[i][j];
							}
						}
					}
				}
				isStop = true;
				break;
		}
	}
}

void PlayerMove(Options& options) {
	cout << "Ваша ход!";
	ShowMap(options);
	char hitX; int hitY;
	cout << "Куда вы хотите ударить?"; cin >> hitX; cin >> hitY;





}

void BotMove(Options& options) {
	srand(time(0));
	int i1 = rand() % 10 + 1,
		i2 = rand() % 10 + 1;
	if (options.Map[i1][i2] == 0) {
		options.Map[i1][i2] = 3;
	}
	else if (options.Map[i1][i2] == 2) {
		options.Map[i1][i2] = 4;
	}

	cout << endl << "Противник ударил по координатам: " << endl << "[X]: " << i1 << endl << "[Y]: " << i2;


}
//Блок методов для главного меню
void SinglePlayer() {
	Options options;
	cout << "\n\n\t\t\t\t\tВы выбрали режим одиночной игры\n\n";
	for (int i = 0; i < 100 ; i++) {
		system("cls");
		ShowMap(options);
		cout << "\nОсталось кораблей"
			<< "\nXL - " << options.shipXL
			<< "\nL  - " << options.shipL
			<< "\nM  - " << options.shipM
			<< "\nS  - " << options.shipS;
		BotMove(options);
		PlaceShip(options);

	}

}
void MultiPlayer() {
	cout << "Вы выбрали режим многопользовательской игры";
}
void Settings() {
	cout << "Вы зашли в настройки";
}
void Exit() {
	system("cls");
	cout << "Выход из игры...\n";
	exit(0);
}

int KoStIlnAxOd() {
	int Choise;
	switch (Choise)
	{
	case 'A':
		Choise = 1;
	case 'B':
		Choise = 2;
	case 'C':
		Choise = 3;
	case 'D':
		Choise = 4;
	case 'E':
		Choise == 5;
	case 'F':
		Choise == 6;
	case 'G':
		Choise == 7;
	case 'H':
		Choise == 8;
	case 'I':
		Choise == 9;
	case 'J':
		Choise == 10;
	default:
		break;
	}
	return Choise;
}

int main() {
	// TODO: Sea Fight
	setlocale(0, "");
	Options options;
	do {
		ShowMenu();
	} while (options.ShipCount != 0);
}
