#include <iostream>;
#include <Windows.h>;
using namespace std;

void SinglePlayer(),
	 MultiPlayer(),
	 Settings(),
	 Exit();

struct Options {
	//Пустое поле боя
	int size;
	int Map[10][10];
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

int ShowMenu() {
	// TODO: Menu
	do {
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
	} while (true);
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
				SetColor('#', 10);
				// cout << '#' << " ";
			}
			//Если... то игрок
			else if (options.Map[i][j] == 2) {
				cout << '*' << " ";
			}
			//Если... то ничего
			else if (options.Map[i][j] == 0) {
				cout << '~' << " ";
			}
			//Если... то мимо
			else if (options.Map[i][j] == 3) {
				cout << 'o' << " ";
			}
			//Если... то попадание
			else if (options.Map[i][j] == 4) {
				cout << 'x' << " ";
			}
			//Если... то уничтожен
			else if (options.Map[i][j] == 5) {
				cout << 'X' << " ";
			}
		}
		cout << endl;
	}
}


//Блок методов для главного меню
void SinglePlayer() {
	Options options;
	system("cls");
	cout << "\n\n\t\t\t\t\tВы выбрали режим одиночной игры\n\n";
	ShowMap(options);
	system("pause");
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




void PlayerMove() {

}

void BotMove() {

}

int main() {
	// TODO: Sea Fight
	setlocale(0, "");
	Options options;
	do {
		ShowMenu();
	} while (options.ShipCount != 0);
}
