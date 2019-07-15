#pragma once
#include <windows.h>
#include "Element.h"
class Game
{
private:
	enum Colors { SELECTED = 80, CLOSED = 110, SPACE = 0 };
	static constexpr int ROW = 10, COL = 20;
	static constexpr int COUNTOFBOMBS = 15;
	COORD current = { 0 , 0 };
	Element field[ROW][COL];
	bool isOpened[ROW][COL];
	void ShowConsoleCursor(bool showFlag);
	void SetCursorPosition(int x, int y);
	void PrintElement(COORD c, int color);
	void FillingField();
	int AmountOfBombs(COORD coordinate);
	void GenerateBombs(COORD coordinate);
	void GenerateField();
	void PrintField();
	void MoveUp();
	void MoveRight();
	void MoveDown();
	void MoveLeft();
	void OpenMethod(int x, int y);
	bool CheckForVictory();

public:
	void Run();

	Game();
	~Game();
};

