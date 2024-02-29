#include <cstdio>
#include <cstdlib> // for std::system
#include <iomanip> // std::setw
#include <iostream>
#include <string>
#include <vector>

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
  bool draw = false;
};

string InputName(string message) {
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
    cout << "Number must be between 1 and 10, Try again ";
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
  printf("Round: %d of %d | %s [%d] V %s [%d]\n",
         thisRoundNum,
         info.rounds,
         name.player1Name.c_str(),
         info.player1WinningRound,
         name.player2Name.c_str(),
         info.player2WinningRound);
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
  if (!playerTurn.player1StartFirst) {
    cout << name.player1Name << " Is Your Turn => | X |\n";
  } else {
    cout << name.player2Name << " Is Your Turn => | O |\n";
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
    return true;
  } else if (CheckDigitsIfEqual(arr, PLAYER2)) {
    info.player2WinningRound++;
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

void ResetBox(char arr[3][3], vector<char> &existingNumbers) {
  existingNumbers.clear();
  arr[0][0] = '1', arr[0][1] = '2', arr[0][2] = '3', arr[1][0] = '4',
  arr[1][1] = '5', arr[1][2] = '6', arr[2][0] = '7', arr[2][1] = '8',
  arr[2][2] = '9';
}

string FinalWinner(stPlayersName name, stInfo info) {
  if (info.player1WinningRound > info.player2WinningRound) {
    return name.player1Name + " The Final Winner\n";
  } else if (info.player2WinningRound > info.player1WinningRound) {
    return name.player2Name + " The Final Winner\n";
  } else {
    return "NO Winner It\'s Draw\n";
  }
}

void DisplayFinalResult(stPlayersName name, stInfo info) {
  cout << "*********************************************\n";
  cout << "Total Rounds: " << info.rounds << "\n";
  cout << "Draw: " << info.draw << "\n";
  cout << name.player1Name << " Win " << info.player1WinningRound << "\n";
  cout << name.player2Name << " Win " << info.player2WinningRound << "\n";
  cout << "*********************************************\n";
  cout << FinalWinner(name, info);
  cout << "*********************************************\n";
}

short InputNumberPosition(string message) {
  short inputNum = 0;
  cout << message << " ";
  cin >> inputNum;
  while (inputNum > 9 || inputNum < 1) {
    cout << "Number must be between 1 and 9, Try again ";
    cin >> inputNum;
  }
  return inputNum;
}

string AskForNumber(stInfo info, stPlayersName name) {
  const string player1 = name.player1Name + " please enter number:";
  const string player2 = name.player2Name + " please enter number:";
  if (!info.player1StartFirst) {
    return player1;
  }
  return player2;
}

short ConvertInputNumberToChar(short number) {
  if (number == 1) {
    return 49;
  } else if (number == 2) {
    return 50;
  } else if (number == 3) {
    return 51;
  } else if (number == 4) {
    return 52;
  } else if (number == 5) {
    return 53;
  } else if (number == 6) {
    return 54;
  } else if (number == 7) {
    return 55;
  } else if (number == 8) {
    return 56;
  } else if (number == 9) {
    return 57;
  }
  return 0;
}

bool CheckArrayIfDubricated(vector<char> &existingNumbers, char &newNumber,
                            stInfo info, stPlayersName name) {
  newNumber = char(
      ConvertInputNumberToChar(InputNumberPosition(AskForNumber(info, name))));

  for (char &num : existingNumbers) {
    if (num == newNumber) {
      return true;
    }
  }
  existingNumbers.push_back(newNumber);
  return false;
}

void RenderGame(char arr[3][3], vector<char> &existingNumbers, stInfo info,
                stPlayersName name, char playerTurn) {
  char newNumber;

  DisplayBox(arr);
  playerTurnNotification(info, name);
  while (CheckArrayIfDubricated(existingNumbers, newNumber, info, name)) {
    cout << "Location is taken, Choose another number \n";
  }
  char userPosition = newNumber;
  SwitchPlayerTurn(info);
  UpdateNumBox(arr, userPosition, playerTurn);
  system(CLEAR_COMMAND);
}

void PlayGame(stPlayersName name) {
  char arr[3][3]{{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
  vector<char> existingNumbers; // for checking if the user
                                // entered number already exist
  char newNumber;
  stInfo info;
  short round = 1;
  short totalRounds =
      HowManyRound("Please enter how many round do you want to play 1 to 10");
  info.rounds = totalRounds;

  system(CLEAR_COMMAND);
  while (round <= totalRounds) {
    do {
      HeaderInfo(name, info, round);
      RenderGame(arr, existingNumbers, info, name, SwitchPlayerTurn(info));
    } while (GameOver(arr, info));
    round++;
    ResetBox(arr, existingNumbers);
  }
  system(CLEAR_COMMAND);
  DisplayFinalResult(name, info);
}

bool PlayAgain() {
  char answer;
  cout << "Do you want to play again? Y/N ";
  cin >> answer;
  while (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n') {
    cout << "Y/y for |YES| OR N/n for |NO| ! ";
    cin >> answer;
  }
  if (answer == 'y' || answer == 'Y') {
    system(CLEAR_COMMAND);
    return true;
  } else {
    return false;
  }
}

int main() {
  stPlayersName name;
  AskNames(name);
  do {
    PlayGame(name);
    cout << endl;
  } while (PlayAgain());
  return 0;
}
