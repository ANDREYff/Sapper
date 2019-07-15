#include "Game.h"
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include "Element.h"

Game::Game()
{
	system("mode 20, 10");
	ShowConsoleCursor(false);
	FillingField();
	GenerateField();
}

void Game::ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void Game::SetCursorPosition(int x, int y) {
	COORD coord = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Game::PrintElement(COORD c, int color) {
	static HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	static DWORD written;

	//COORD c;
	//c.X = x;
	//c.Y = y;
	//FillConsoleOutputAttribute(hout, FOREGROUND_GREEN | BACKGROUND_RED, 1, c, &written);
	FillConsoleOutputAttribute(hout, color, 1, c, &written);
}
void Game::FillingField() {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			field[i][j].SetValue(0);
			field[i][j].SetOpened(false);
			field[i][j].SetColour(CLOSED);
		}
	}
}
int Game::AmountOfBombs(COORD coordinate) {
	int amount = 0;
	if (field[coordinate.Y - 1][coordinate.X - 1].GetValue() == 9) {
		if (coordinate.Y != 0 && coordinate.X != 0) {
			++amount;
		}
	}
	if (field[coordinate.Y - 1][coordinate.X].GetValue() == 9) {
		if (coordinate.Y != 0) {
			++amount;
		}
	}
	if (field[coordinate.Y - 1][coordinate.X + 1].GetValue() == 9) {
		if (coordinate.Y != 0 && coordinate.X != (COL - 1)) {
			++amount;
		}
	}
	if (field[coordinate.Y][coordinate.X + 1].GetValue() == 9) {
		if (coordinate.X != (COL - 1)) {
			++amount;
		}
	}
	if (field[coordinate.Y + 1][coordinate.X + 1].GetValue() == 9) {
		if (coordinate.Y != (ROW - 1) && coordinate.X != (COL - 1)) {
			++amount;
		}
	}
	if (field[coordinate.Y + 1][coordinate.X].GetValue() == 9) {
		if (coordinate.Y != (ROW - 1)) {
			++amount;
		}
	}
	if (field[coordinate.Y + 1][coordinate.X - 1].GetValue() == 9) {
		if (coordinate.Y != (ROW - 1) && coordinate.X != 0) {
			++amount;
		}
	}
	if (field[coordinate.Y][coordinate.X - 1].GetValue() == 9) {
		if (coordinate.X != 0) {
			++amount;
		}
	}
	return amount;
}
void Game::GenerateBombs(COORD coordinate) {
	srand(time(NULL));
	int r, c, count = 0;
	do {
		r = rand() % ROW;
		c = rand() % COL;
		if (field[r][c].GetValue() != 9 && (r != current.Y || c != current.X)) {
			++count;
			field[r][c].SetValue(9);
		}
	} while (count < COUNTOFBOMBS);
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			coordinate.X = j;
			coordinate.Y = i;
			if (field[i][j].GetValue() != 9) {
				field[i][j].SetValue(AmountOfBombs(coordinate));
			}
		}
	}
}
void Game::GenerateField() {
	current.X = 0;
	current.Y = 0;
	SetCursorPosition(current.X, current.Y);
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			current.X = j;
			current.Y = i;
			PrintElement(current, field[i][j].GetColour());
		}
	}
	current.X = (COL / 2);
	current.Y = (ROW / 2);
	field[current.Y][current.X].SetColour(SELECTED);
	PrintElement(current, field[current.Y][current.X].GetColour());
}
void Game::PrintField() {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			current.X = j;
			current.Y = i;
			SetCursorPosition(current.X, current.Y);
			if (field[i][j].GetValue() == 0) {
				printf(" ");
			}
			else {
				printf("%i", field[i][j].GetValue());
			}
		}
	}
}
void Game::MoveUp() {
	if (current.Y != 0) {
		if (field[current.Y][current.X].GetOpened()) {
			field[current.Y][current.X].SetColour(SPACE);
			PrintElement(current, field[current.Y][current.X].GetColour());
			SetCursorPosition(current.X, current.Y);
			if (field[current.Y][current.X].GetValue()) {
				printf("%i", field[current.Y][current.X].GetValue());
			}
		}
		else {
			field[current.Y][current.X].SetColour(CLOSED);
			PrintElement(current, field[current.Y][current.X].GetColour());
		}
		--current.Y;
		field[current.Y][current.X].SetColour(SELECTED);
		PrintElement(current, field[current.Y][current.X].GetColour());
	}

}
void Game::MoveRight() {
	if (current.X != COL - 1) {
		if (field[current.Y][current.X].GetOpened()) {
			field[current.Y][current.X].SetColour(SPACE);
			PrintElement(current, field[current.Y][current.X].GetColour());
			SetCursorPosition(current.X, current.Y);
			if (field[current.Y][current.X].GetValue()) {
				printf("%i", field[current.Y][current.X].GetValue());
			}
		}
		else {
			field[current.Y][current.X].SetColour(CLOSED);
			PrintElement(current, field[current.Y][current.X].GetColour());
		}
		++current.X;
		field[current.Y][current.X].SetColour(SELECTED);
		PrintElement(current, SELECTED);
	}
}
void Game::MoveDown() {
	if (current.Y != ROW - 1) {
		if (field[current.Y][current.X].GetOpened()) {
			field[current.Y][current.X].SetColour(SPACE);
			PrintElement(current, SPACE);
			SetCursorPosition(current.X, current.Y);
			if (field[current.Y][current.X].GetValue()) {
				printf("%i", field[current.Y][current.X].GetValue());
			}
		}
		else {
			field[current.Y][current.X].SetColour(CLOSED);
			PrintElement(current, CLOSED);
		}
		++current.Y;
		field[current.Y][current.X].SetColour(SELECTED);
		PrintElement(current, SELECTED);
	}
}
void Game::MoveLeft() {
	if (current.X != 0) {
		if (field[current.Y][current.X].GetOpened()) {
			field[current.Y][current.X].SetColour(SPACE);
			PrintElement(current, SPACE);
			SetCursorPosition(current.X, current.Y);
			if (field[current.Y][current.X].GetValue()) {
				printf("%i", field[current.Y][current.X].GetValue());
			}
		}
		else {
			field[current.Y][current.X].SetColour(CLOSED);
			PrintElement(current, CLOSED);
		}
		--current.X;
		field[current.Y][current.X].SetColour(SELECTED);
		PrintElement(current, SELECTED);
	}
}
void Game::OpenMethod(int x, int y) {
	COORD coordinate = { x, y };

	if (field[y][x].GetValue() == 9) {
		PrintField();
	}
	field[y][x].SetOpened(true);

	if (field[y][x].GetValue() > 0 && field[y][x].GetValue() < 9) {
		SetCursorPosition(x, y);
		printf("%i", field[y][x].GetValue());
		return;
	}

	if (field[y][x].GetValue() == 0) {
		field[y][x].SetColour(SPACE);
		PrintElement(coordinate, field[y][x].GetColour());

		if (coordinate.Y != 0 && coordinate.X != 0) {
			if (!field[coordinate.Y - 1][coordinate.X - 1].GetOpened()) {
				OpenMethod(coordinate.X - 1, coordinate.Y - 1);
			}
		}

		if (coordinate.Y != 0) {
			if (!field[coordinate.Y - 1][coordinate.X].GetOpened()) {
				OpenMethod(coordinate.X, coordinate.Y - 1);
			}
		}

		if (coordinate.Y != 0 && coordinate.X != (COL - 1)) {
			if (!field[coordinate.Y - 1][coordinate.X + 1].GetOpened()) {
				OpenMethod(coordinate.X + 1, coordinate.Y - 1);
			}
		}

		if (coordinate.X != (COL - 1)) {
			if (!field[coordinate.Y][coordinate.X - 1].GetOpened()) {
				OpenMethod(coordinate.X + 1, coordinate.Y);
			}
		}

		if (coordinate.Y != (ROW - 1) && coordinate.X != (COL - 1)) {
			if (!field[coordinate.Y + 1][coordinate.X + 1].GetOpened()) {
				OpenMethod(coordinate.X + 1, coordinate.Y + 1);
			}
		}

		if (coordinate.Y != (ROW - 1)) {
			if (!field[coordinate.Y + 1][coordinate.X].GetOpened()) {
				OpenMethod(coordinate.X, coordinate.Y + 1);
			}
		}

		if (coordinate.Y != (ROW - 1) && coordinate.X != 0) {
			if (!field[coordinate.Y + 1][coordinate.X - 1].GetOpened()) {
				OpenMethod(coordinate.X - 1, coordinate.Y + 1);
			}
		}

		if (coordinate.X != 0) {
			if (!field[coordinate.Y][coordinate.X - 1].GetOpened()) {
				OpenMethod(coordinate.X - 1, coordinate.Y);
			}
		}
	}
}
bool Game::CheckForVictory() {
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			if (field[i][j].GetValue() != 9 && !field[i][j].GetOpened()) {
				return false;
			}
		}
	}
	return true;
}


void Game::Run() {
	bool firstPush = true;
	enum Keys { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ENTER = 10, ESCAPE = 27 };
	unsigned char a;
	while (1)
	{
		//system("cls");
		a = _getch();
		//for detect the function\arrow keys 
		//we must call the getch() again
		//testing if a is '0' or '0xE0'
		if (a == 0 || a == 0xE0) {
			a = _getch();
		}
		if (a == ESCAPE) {//ESC for exit the 'while'
			break;
		}
		else if (a == UP) {//up
			MoveUp();
		}
		else if (a == DOWN) {//down
			MoveDown();
		}
		else if (a == LEFT) {//left
			MoveLeft();
		}
		else if (a == RIGHT) {//right
			MoveRight();
		}
		else if (a = ENTER) {//enter
			if (!field[current.Y][current.X].GetOpened()) {
				if (firstPush) {
					GenerateBombs(current);
					OpenMethod(current.X, current.Y);
					field[current.Y][current.X].SetColour(SELECTED);
					PrintElement(current, field[current.Y][current.X].GetColour());
					firstPush = false;
				}
				else {
					OpenMethod(current.X, current.Y);
					field[current.Y][current.X].SetColour(SELECTED);
					PrintElement(current, field[current.Y][current.X].GetColour());
				}
			}
		}
		if (CheckForVictory()) {
			system("cls");
			SetCursorPosition((ROW / 2), (COL / 2));
			printf("Win");
		}
	}
}

Game::~Game()
{
}
