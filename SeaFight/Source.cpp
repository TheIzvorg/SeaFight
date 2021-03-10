#include <iostream>;
#include <Windows.h>;
#include <conio.h>;
#include <ctime>;
using namespace std;

void SinglePlayer(),
MultiPlayer(),
Settings(),
Exit();
struct Options {
	//Пустое поле боя
	int Map[12][12] = { {1,1,1,1,1,1,1,1,1,1,1,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,2,2,2,2,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,0,0,0,0,0,0,0,0,0,0,1, },
						{1,1,1,1,1,1,1,1,1,1,1,1, } };

	int shipS = 4, 
		shipM = 3,
		shipL = 2,
		shipXL = 1;

	int PlayerX = 6, PlayerY = 4;



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
		cout << "\n\n\t\t\t\t\tДобро пожаловать в 'Морской бой!'\n\n"
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
			else if (options.Map[i][j] == 2) {
				SetColor('=', 7);
			}
			//Если... то ничего
			else if (options.Map[i][j] == 0) {
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
		}
		cout << endl;
	}
}


void PlaceShip(Options& options) {
	bool isStop = false;
	while (!isStop) {
		switch (_getch())
		{
		case 'A':
		case 'a':
		case 75:
			if (options.Map[options.PlayerX - 1][options.PlayerY] != 1) {
				options.PlayerX--;
				isStop = true;
				for (int i = 0; i <= 4; i++) {
					if (options.Map[options.PlayerX][options.PlayerY + i] != 2) {
						options.Map[options.PlayerX][options.PlayerY + i] = 0;
						
					}
				}
			}
			break;
		}
		options.Map[options.PlayerY][options.PlayerX] = 2;
	}
}

void PlayerMove() {

}

void BotMove() {

}
//Блок методов для главного меню
void SinglePlayer() {
	Options options;
	cout << "\n\n\t\t\t\t\tВы выбрали режим одиночной игры\n\n";
	for (int i = 0; i < 10 ; i++) {
		system("cls");
		ShowMap(options);
		cout << "\nОсталось кораблей"
			<< "\nXL - " << options.shipXL
			<< "\nL  - " << options.shipL
			<< "\nM  - " << options.shipM
			<< "\nS  - " << options.shipS;
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





int main() {
	// TODO: Sea Fight
	setlocale(0, "");
	Options options;
	do {
		ShowMenu();
	} while (options.ShipCount != 0);
}
