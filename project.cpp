#include <iostream>
#include <string>
using namespace std;

enum enGameChoices { Stone = 1, Paper = 2, Scissors = 3 };

void startGame();

struct stGameInfo {
	short rounds, playerWins, botWins, draw;
};

int RandomNumber(int From, int To) {
	int number = rand() % (To - From + 1) + From;

	return number;
}

enGameChoices Choice(short choice) {
	switch (choice) {
	case 1:
		return enGameChoices::Stone;
	case 2:
		return enGameChoices::Paper;
	default:
		return enGameChoices::Scissors;
	}
}

string ChoiceName(enGameChoices Choice) {
	if (Choice == enGameChoices::Stone)
		return "Stone";
	else if (Choice == enGameChoices::Paper)
		return "Paper";
	else
		return "Scissors";
}

stGameInfo ReadHowManyRounds() {
	stGameInfo gameInfo;
	do {
		cout << "How Many Rounds 1 to 10 ?" << endl;
		cin >> gameInfo.rounds;
	} while (gameInfo.rounds > 10 || gameInfo.rounds <= 0);

	gameInfo.draw = 0;
	gameInfo.playerWins = 0;
	gameInfo.botWins = 0;

	return gameInfo;
}

short ReadChoice() {
	short choice = 0;

	do {
		cout << "Your Choice: [1]: Stone, [2]: Paper, [3] Scissors ?:  ";
		cin >> choice;
	} while (choice <= 0 || choice > 3);

	return choice;
}

void ResetCMD() {
	system("cls");
	system("color 0F");
}

bool IsPlayAgain() {
	char isPlay;
	do {
		cout << "\t\tDo you want to play agina ? Y/N ?:  ";
		cin >> isPlay;
	} while (isPlay != 'N' && isPlay != 'Y');

	if (isPlay == 'Y') return true;

	return false;
}

string getWinner(enGameChoices playerChoice, enGameChoices botChoice, stGameInfo &gameInfo) {
	if (playerChoice == botChoice) {
		system("color 6E");
		gameInfo.draw = gameInfo.draw + 1;
		return "[No Winner]";
	} else if (
		(enGameChoices::Paper == playerChoice && enGameChoices::Stone == botChoice) ||
		(enGameChoices::Stone == playerChoice && enGameChoices::Scissors == botChoice) ||
		(enGameChoices::Scissors == playerChoice && enGameChoices::Paper == botChoice)
	) {
		system("color 2E");
		gameInfo.playerWins = gameInfo.playerWins + 1;
		return "[Player1]";
	}
	else {
		system("color 4E");
		cout << "\a";
		gameInfo.botWins = gameInfo.botWins + 1;
		return "[Computer]";
	}
}

void endGame(stGameInfo& gameInfo) {
	cout << "\n\n\t\t---------------------------------------------------------------------------\n";
	cout << "\t\t\t\t\t+++ G a m e  O v e r +++\n";
	cout << "\t\t---------------------------------------------------------------------------\n";
	cout << "\t\t----------------------------- [ Game Result ] -----------------------------\n";
	cout << "\t\tGame Rounds        : " << gameInfo.rounds << endl;
	cout << "\t\tPlayer1 won times  : " << gameInfo.playerWins << endl;
	cout << "\t\tComputer won times : " << gameInfo.botWins << endl;
	cout << "\t\tDraw times         : " << gameInfo.draw << endl;

	string FinalWinner = "No Winner";
	if (gameInfo.playerWins > gameInfo.botWins)
		FinalWinner = "Player1";
	else if (gameInfo.playerWins < gameInfo.botWins)
		FinalWinner = "Computer";
	else
		FinalWinner = "Draw";

	cout << "\t\tFinal Winner       : " << FinalWinner << endl;
	cout << "\t\t---------------------------------------------------------------------------\n";

	if (IsPlayAgain()) {
		ResetCMD();
		startGame();
	}
}

void startRounds(stGameInfo& gameInfo) {
	for (int i = 1; i <= gameInfo.rounds; i++) {
		cout << "\n\nRound [" << i << "] begins:" << endl;

		enGameChoices playerChoice = Choice(ReadChoice());
		enGameChoices botChoice = Choice(RandomNumber(1, 3));
		cout << "\n------------------ Round [" << i << "] ------------------\n";
		cout << "Player1 Choice  : " << ChoiceName(playerChoice) << endl;
		cout << "Computer Choice : " << ChoiceName(botChoice) << endl;
		cout << "Round Winner    : " << getWinner(playerChoice, botChoice, gameInfo) << endl;
		cout << "----------------------------------------------";
	}

	endGame(gameInfo);
}

void startGame() {
	stGameInfo info = ReadHowManyRounds();
	startRounds(info);
}

int main() {
	srand((unsigned)time(NULL));

	startGame();

	return 0;
}
