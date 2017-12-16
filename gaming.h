#include "board.h"
#include "player.h"
#include "printer.h"

#include <cctype>
#include <string>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

#define cls() cout << string(100, '\n');

class Game {
 private:
  Board *board;
  Player *p[2];
  Printer *printer;
  bool ReadCommand(int &x, int &y) {
    char ope[10];
    cout << "Type you command:" << endl;
    cin >> ope;
    if (ope[0] == 'e')
      return 0;
    if (isupper(ope[0])) {
      x = ope[0] - 'A';
    } else if (islower(ope[0])) {
      x = ope[0] - 'a';
    } else {
      cout << "Undefine command" << endl;
      return ReadCommand(x, y);
    }
    if (!isdigit(ope[1])) {
      cout << "Undefine command" << endl;
      return ReadCommand(x, y);
    }
    y = ope[1] & 0xf;
    if (isdigit(ope[2]))
      y = y * 10 + (ope[2] & 0xf);
    if (x >= 8) x--;
    return 1;
  }

 public:
  Game() {
    const int n = 19;
    board = new Board(n);
    p[0] = new Player(),
    p[1] = new Player();
    printer = new Printer();
  }
  void Play() {
    int x, y;
    bool now_player = 1;
    while (true) {
      cls();
      printer->printBoard(*board, p[now_player]);

      now_player ^= 1;

      if (!ReadCommand(x, y))
        break;
      board->playAt(y, x, p[now_player]);
    }

    delete p[0], p[1];
  }
};

#undef cls()