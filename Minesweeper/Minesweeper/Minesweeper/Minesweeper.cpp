#include <iostream>
#include "Tile.h"
int main()
{
	srand(time(0));
	int randomPosX;
	int randomPosY;
	tile tileTable[8][9];
	int AmountOfBombs = 10;
	int rowNumber = 0;
	char colSymbol;
	char rowSymbol;
	int colNumber;
	bool FirstTurn = true;
	int notMinedTilesAmount = 64 - AmountOfBombs;
	int uncoveredTilesAmount;
	bool flagMode = false;
	bool continuieGame = true;
	int mode;
	string ModeCout;
	cout << "1 - Latwy:\t10 bomb" << endl << "2 - Sredni:\t15 bomb" << endl << "3 - Trudny:\t20 bomb" << endl << endl << "Wybierz poziom trudnosci:";
	cin >> mode;
	switch (mode)
	{
	default:
	case 1:
		AmountOfBombs = 10;
		ModeCout = "Latwy";
		break;

	case 2:
		AmountOfBombs = 15;
		ModeCout = "Sredni";
		break;

	case 3:
		AmountOfBombs = 20;
		ModeCout = "Trudny";
		break;
	}
	system("CLS");
	for (int i = 0; i < AmountOfBombs; i++) {
		do {
			randomPosX = rand() % 8;
			randomPosY = rand() % 8;
		} while (tileTable[randomPosY][randomPosX].isMined == true);
		
		tileTable[randomPosY][randomPosX].isMined = true;
	}

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (tileTable[row][col].isMined == true) {
				tileTable[row][col].area = 9;
			}
			else if (tileTable[row][col].isMined == false) {
				if (tileTable[row+1][col+1].isMined == true)
				{
					tileTable[row][col].area++;
				}
				if (tileTable[row - 1][col - 1].isMined == true)
				{
					tileTable[row][col].area++;
				}
				if (tileTable[row - 1][col + 1].isMined == true)
				{
					tileTable[row][col].area++;
				}
				if (tileTable[row + 1][col - 1].isMined == true)
				{
					tileTable[row][col].area++;
				}
				if (tileTable[row][col + 1].isMined == true)
				{
					tileTable[row][col].area++;
				}
				if (tileTable[row + 1][col].isMined == true)
				{
					tileTable[row][col].area++;
				}
				if (tileTable[row][col - 1].isMined == true)
				{
					tileTable[row][col].area++;
				}
				if (tileTable[row - 1][col].isMined == true)
				{
					tileTable[row][col].area++;
				}
			}
		}
	}
	do {
		cout << "Poziom trudnosci: "<< ModeCout << endl << endl;
		cout << "   a  b  c  d  e  f  g  h" << endl;
		for (int row = 0; row < 8; row++) {
			cout << row + 1 << "]";
			for (int col = 0; col < 8; col++) {
				if (tileTable[row][col].isCovered == true && tileTable[row][col].isFlagged == false) {
					cout << "|#|";
				}
				else if (tileTable[row][col].isCovered == true && tileTable[row][col].isFlagged == true) {
					cout << "|X|";
				}
				else {
					cout << " " << tileTable[row][col].area << " ";
				}
			}
			cout << endl;

		}


		if (flagMode == false) {
			cout << "Wpisz (-) w pole numeru wiersza zeby przejsc w tryb umieszczania flag." << endl << endl;
			do {
				cout << "Podaj numer wiersza: ";
				cin >> rowSymbol;
			} while ((int)rowSymbol > 56 || (int)rowSymbol < 49 && rowSymbol != '-');
			if (rowSymbol == '-' && flagMode == false) {
				flagMode = true;
				continuieGame = false;
			}
			if (flagMode == false) {
				do {
					cout << "Podaj litere kolumny: ";
					cin >> colSymbol;
				} while ((colSymbol > 'H' || colSymbol < 'A') && (colSymbol > 'h' || colSymbol < 'a'));
			}
		}


		else if (flagMode == true) {
			cout << "UWAGA! Tryb ustawiania flag jest wlaczony! Wpisz (-) zeby wyjsc" << endl << endl;
			do {
				cout << "Podaj numer wiersza: ";
				cin >> rowSymbol;
			} while ((int)rowSymbol > 56 || (int)rowSymbol < 49 && rowSymbol != '-');
			if (rowSymbol == '-' && flagMode == true) {
				flagMode = false;
			}
			if (flagMode == true) {
				do {
					cout << "Podaj litere kolumny: ";
					cin >> colSymbol;
				} while ((colSymbol > 'H' || colSymbol < 'A') && (colSymbol > 'h' || colSymbol < 'a'));

				rowNumber = (int)rowSymbol - 49;

				if (isupper(colSymbol)) {
					colNumber = (int)colSymbol - 65;
				}
				else {
					colNumber = (int)colSymbol - 97;
				}
				if (tileTable[rowNumber][colNumber].isFlagged == false) {
					tileTable[rowNumber][colNumber].isFlagged = true;
				}

				else if (tileTable[rowNumber][colNumber].isFlagged == true) {
					tileTable[rowNumber][colNumber].isFlagged = false;
				}
				

			}
		}
			
		

		
		
		if (continuieGame == true) {

			rowNumber = (int)rowSymbol - 49;

			if (isupper(colSymbol)) {
				colNumber = (int)colSymbol - 65;
			}
			else {
				colNumber = (int)colSymbol - 97;
			}

			if (tileTable[rowNumber][colNumber].isMined == true) {
				system("CLS");
				cout << endl << "Game Over!";
				return 0;
			}

			tileTable[rowNumber][colNumber].isCovered = false;
			uncoveredTilesAmount = 0;
			for (int row = 0; row < 8; row++) {
				for (int col = 0; col < 8; col++) {
					if (tileTable[row][col].isCovered == false) {
						uncoveredTilesAmount++;
					}
				}
			}

			if (uncoveredTilesAmount == notMinedTilesAmount) {
				system("CLS");
				cout << endl << "Wygrales!";
				return 0;
			}

			if (FirstTurn == true) {
				FirstTurn = false;

				for (int rowCheck = rowNumber; tileTable[rowCheck][colNumber].isMined == false; rowCheck++) {
					for (int colCheck = colNumber; tileTable[rowCheck][colCheck].isMined == false; colCheck++) {
						tileTable[rowCheck][colCheck].isCovered = false;
						if (colCheck > 7) {
							break;
						}
					}
					if (rowCheck > 7) {
						break;
					}
				}

				for (int rowCheck = rowNumber; tileTable[rowCheck][colNumber].isMined == false; rowCheck++) {
					for (int colCheck = colNumber; tileTable[rowCheck][colCheck].isMined == false; colCheck--) {
						tileTable[rowCheck][colCheck].isCovered = false;
						if (colCheck < 0) {
							break;
						}
					}
					if (rowCheck > 7) {
						break;
					}
				}

				for (int rowCheck = rowNumber; tileTable[rowCheck][colNumber].isMined == false; rowCheck--) {
					for (int colCheck = colNumber; tileTable[rowCheck][colCheck].isMined == false; colCheck++) {
						tileTable[rowCheck][colCheck].isCovered = false;
						if (colCheck > 7) {
							break;
						}
					}
					if (rowCheck < 0) {
						break;
					}
				}

				for (int rowCheck = rowNumber; tileTable[rowCheck][colNumber].isMined == false; rowCheck--) {
					for (int colCheck = colNumber; tileTable[rowCheck][colCheck].isMined == false; colCheck--) {
						tileTable[rowCheck][colCheck].isCovered = false;
						if (colCheck < 0) {
							break;
						}
					}
					if (rowCheck < 0) {
						break;
					}
				}
			}
		}
		if (flagMode == false) {
			continuieGame = true;
		}
		system("CLS");
	} while (1==1);
}
