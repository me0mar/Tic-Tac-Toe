#include <cstdio>
#include <cstdlib> // for std::system
#include <iomanip> // std::setw
#include <iostream>
#include <string>

#ifdef _WIN32 // Check if compiling for Windows
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

using namespace std;

struct stPlayersName {
  string player1Name;
  string player2Name;
};

struct stInfo {
  bool player1StartFirst = true;
  short rounds;
  short player1WinningRound = 0;
  short player2WinningRound = 0;
  string roundWinner;
  bool draw = false;
  string gameWinner;
};

string InputName(string message) { // VALIDATION !
  string name;
  cout << message;
  cin >> name;
  return name;
}

short HowManyRound(string message) {
  short inputNum = 0;

  cout << message << " ";
  cin >> inputNum;
  while (inputNum > 10 || inputNum < 1) {
    cout << "Number must be between 1 and 10 ";
    cin >> inputNum;
  }
  return inputNum;
}

void AskNames(stPlayersName &name) {
  name.player1Name = InputName("Player 1 Enter Your Name: ");
  name.player2Name = InputName("Player 2 Enter Your Name: ");
}

void HeaderInfo(stPlayersName name, stInfo info, short thisRoundNum) {
  cout << "================================================\n";
  printf("Round: %d of %d | %s [%d] V %s [%d]\n", thisRoundNum, info.rounds,
         name.player1Name.c_str(), info.player1WinningRound,
         name.player2Name.c_str(), info.player2WinningRound);
  cout << "================================================\n";
}

void DisplayBox(char arr[3][3]) {
  cout << "\n\n";
  for (short i = 0; i < 3; i++) {
    if (i != 0) {
      cout << "   _____________________________\n\n";
    }

    for (short j = 0; j < 3; j++) {
      cout << setw(6) << arr[i][j];
      if (j != 2) {
        cout << setw(6) << "|";
      }
    }
    cout << "\n";
  }
  cout << "\n\n";
}

char InputLocation(char userInputNumList[9], string message) {
  char inputNum = '0';
  cout << message << " ";
  cin >> inputNum;
  for (short i = 0; i < 9; i++) {
    while (inputNum == userInputNumList[i]) {
      cout << "Location is reserved, chose different number ";
      cin >> inputNum;
      while (inputNum > '9' || inputNum < '1') {
        cout << "Number must be between 1 and 9 ";
        cin >> inputNum;
      }
    }
    userInputNumList[i] = inputNum;
    break;
  }
  return inputNum;
}

bool CheckIfExistInLocation(char userInputNumList[9], char inputLocation) {
  for (short i = 0; i < 10; i++) {
    if (userInputNumList[i] == inputLocation) {
      return true;
    }
  }
  return false;
}

char SwitchPlayerTurn(stInfo &playerTurn) {
  const char player1 = 'X';
  const char player2 = 'O';

  if (playerTurn.player1StartFirst == true) {
    playerTurn.player1StartFirst = false;
    return player1;
  }
  playerTurn.player1StartFirst = true;
  return player2;
}

void playerTurnNotification(stInfo playerTurn, stPlayersName name) {
  if (playerTurn.player1StartFirst) {
    cout << name.player1Name << " Is Your Turn\n";
  } else {
    cout << name.player2Name << " Is Your Turn\n";
  }
}

void UpdateNumBox(char arr[3][3], char userPosition, char playerTurn) {
  for (short i = 0; i < 3; i++) {
    for (short j = 0; j < 3; j++) {
      if (arr[i][j] == userPosition) {
        arr[i][j] = playerTurn;
      }
    }
  }
}

void PlayGame(char arr[3][3], char userInputNumList[9], stInfo info,
              char playerTurn, short counter) {
  DisplayBox(arr);
  char userPosition = InputLocation(userInputNumList, "Please Enter Number");
  SwitchPlayerTurn(info);
  UpdateNumBox(arr, userPosition, playerTurn);
  system(CLEAR_COMMAND);
}

bool CheckDigitsIfEqual(char arr[3][3], char XO) {
  for (short i = 0; i < 3; i++) {
    for (short j = 0; j < 3; j++) {

      if (arr[0][0] == XO && arr[0][1] == XO && arr[0][2] == XO) {
        return true;
      } else if (arr[1][0] == XO && arr[1][1] == XO && arr[1][2] == XO) {
        return true;
      } else if (arr[2][0] == XO && arr[2][1] == XO && arr[2][2] == XO) {
        return true;

      } else if (arr[0][0] == XO && arr[1][0] == XO && arr[2][0] == XO) {
        return true;
      } else if (arr[0][1] == XO && arr[1][1] == XO && arr[2][1] == XO) {
        return true;
      } else if (arr[0][2] == XO && arr[1][2] == XO && arr[2][2] == XO) {
        return true;

      } else if (arr[0][0] == XO && arr[1][1] == XO && arr[2][2] == XO) {
        return true;
      } else if (arr[0][2] == XO && arr[1][1] == XO && arr[2][0] == XO) {
        return true;
      }
    }
  }
  return false;
}

bool PlayerWinner(char arr[3][3], stInfo &info) {
  const char PLAYER1 = 'X';
  const char PLAYER2 = 'O';
  if (CheckDigitsIfEqual(arr, PLAYER1)) {
    info.player1WinningRound++;
    cout << info.player1WinningRound;
    return true;
  } else if (CheckDigitsIfEqual(arr, PLAYER2)) {
    info.player2WinningRound++;
    cout << info.player2WinningRound;
    return true;
  }
  return false;
}

bool CheckIfDraw(char arr[3][3]) {
  for (short i = 0; i < 3; i++) {
    for (short j = 0; j < 3; j++) {
      if (arr[0][0] != '1' && arr[0][1] != '2' && arr[0][2] != '3' &&
          arr[1][0] != '4' && arr[1][1] != '5' && arr[1][2] != '6' &&
          arr[2][0] != '7' && arr[2][1] != '8' && arr[2][2] != '9') {
        return true;
      }
    }
  }
  return false;
}

bool GameOver(char arr[3][3], stInfo &info) {
  if (PlayerWinner(arr, info)) {
    return false;
  } else if (CheckIfDraw(arr)) {
    info.draw = true;
    return false;
  }
  return true;
}

void ResetBox(char arr[3][3], char userInputNumList[9]) {
  arr[0][0] = '1', arr[0][1] = '2', arr[0][2] = '3', arr[1][0] = '4',
  arr[1][1] = '5', arr[1][2] = '6', arr[2][0] = '7', arr[2][1] = '8',
  arr[2][2] = '9';
}

void DisplayFinalResult(stPlayersName name, stInfo info) {
  cout << "*********************************************\n";
  cout << "Total Rounds: " << info.rounds << "\n";
  cout << name.player1Name << " Won " << info.player1WinningRound << "\n";
  cout << name.player2Name << " Won " << info.player2WinningRound << "\n";
  cout << "*********************************************\n";
}

int main() {
  char arr[3][3]{{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
  char userInputNumList[9]; // for checking if the user entered number already
                            // exist
  stPlayersName name;
  stInfo info;
  short counter = 0;
  short round = 1;
  short totalRounds =
      HowManyRound("Please enter how many round do you want to play 1 to 10");
  info.rounds = totalRounds;

  AskNames(name);
  system(CLEAR_COMMAND);
  while (round <= totalRounds) {

    do {
      HeaderInfo(name, info, round);
      playerTurnNotification(info, name);
      PlayGame(arr, userInputNumList, info, SwitchPlayerTurn(info), counter);
      counter++;
    } while (GameOver(arr, info));
    round++;
    ResetBox(arr, userInputNumList);
  }
  system(CLEAR_COMMAND);
  DisplayFinalResult(name, info);
  return 0;
}
