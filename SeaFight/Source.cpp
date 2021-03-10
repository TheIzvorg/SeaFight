#include <iostream>;
#include <Windows.h>;
using namespace std;

void SinglePlayer(),
	 MultiPlayer(),
	 Settings(),
	 Exit();

struct Options {
	//������ ���� ���
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
		//������� ����
		system("cls");
		cout << "\n\n\t\t\t\t\t����� ���������� � '������� ���!'\n\n"
			"\t\t\t[1]. ��������� ����\n"
			"\t\t\t[2]. ��������������������� ����\n"
			"\t\t\t[3]. ���������\n"
			"\t\t\t[4]. �����\n";
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
	//��������� ����� � ����������� �� �������� � �������
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			//����... �� �����
			if (options.Map[i][j] == 1) {
				SetColor('#', 10);
				// cout << '#' << " ";
			}
			//����... �� �����
			else if (options.Map[i][j] == 2) {
				cout << '*' << " ";
			}
			//����... �� ������
			else if (options.Map[i][j] == 0) {
				cout << '~' << " ";
			}
			//����... �� ����
			else if (options.Map[i][j] == 3) {
				cout << 'o' << " ";
			}
			//����... �� ���������
			else if (options.Map[i][j] == 4) {
				cout << 'x' << " ";
			}
			//����... �� ���������
			else if (options.Map[i][j] == 5) {
				cout << 'X' << " ";
			}
		}
		cout << endl;
	}
}


//���� ������� ��� �������� ����
void SinglePlayer() {
	Options options;
	system("cls");
	cout << "\n\n\t\t\t\t\t�� ������� ����� ��������� ����\n\n";
	ShowMap(options);
	system("pause");
}
void MultiPlayer() {
	cout << "�� ������� ����� ��������������������� ����";
}
void Settings() {
	cout << "�� ����� � ���������";
}
void Exit() {
	system("cls");
	cout << "����� �� ����...\n";
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
