#include <iostream>

class Board {
public:
  Board() {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        data_[3 * i + j] = ' ';
  }

  char get(int i, int j) const {
    return data_[3 * i + j];
  }

  void set(int i, int j, char c) {
    data_[3 * i + j] = c;
  }

  bool free(int i, int j) {
    return data_[3 * i + j] == ' ';
  }

  bool won(char c) {
    if (get(0, 0) == c && get(0, 1) == c && get(0, 2) == c)
      return true;
    if (get(1, 0) == c && get(1, 1) == c && get(1, 2) == c)
      return true;
    if (get(2, 0) == c && get(2, 1) == c && get(2, 2) == c)
      return true;
    if (get(0, 0) == c && get(1, 0) == c && get(2, 0) == c)
      return true;
    if (get(0, 1) == c && get(1, 1) == c && get(2, 1) == c)
      return true;
    if (get(0, 2) == c && get(1, 2) == c && get(2, 2) == c)
      return true;
    if (get(0, 0) == c && get(1, 1) == c && get(2, 2) == c)
      return true;
    if (get(0, 2) == c && get(1, 1) == c && get(2, 0) == c)
      return true;
    return false;
  }

private:
  char data_[9];
};

std::ostream& operator<<(std::ostream& out, const Board& board) {
  for (int i = 0; i < 3; i++) {
    out << "------" << std::endl;
    for (int j = 0; j < 3; j++) {
      out << board.get(i, j) << "|";
    }
    out << std::endl;
  }
  return out << "------";
}

class Player {
public:
  virtual ~Player() = default;
  virtual void play(Board& board) = 0;
  virtual char symbol() const = 0;
};

class HumanPlayer : public Player {
public:
  HumanPlayer(char c) {
    c_ = c;
  }

  void play(Board& board) override {
    int i, j;
    do {
      std::cout << "Unesite lokaciju: ";
      std::cin >> i >> j;
    } while (!board.free(i, j) && std::cout << "Unesite ponovo" << std::endl);
    board.set(i, j, c_);
  }

  char symbol() const override {
    return c_;
  }

private:
  char c_;
};

class MachinePlayer : public Player {
public:
  MachinePlayer(char c) : c_{c} {
  }

  void play(Board& board) override {
    int i;
    int j;
    do {
      i = rand() % 3;
      j = rand() % 3;
    } while (!board.free(i, j));
    board.set(i, j, c_);
  }

  char symbol() const override {
    return c_;
  }

private:
  char c_;
};

int main() {
  Board board;
  Player* p1;
  Player* p2;

  int izbor;
  std::cout << "Odaberite nacin igre" << std::endl
            << "1. H vs H" << std::endl
            << "2. H vs M" << std::endl
            << "3. M vs M" << std::endl;
  std::cin >> izbor;
  if (izbor == 1) {
    p1 = new HumanPlayer{'x'};
    p2 = new HumanPlayer{'o'};
  } else {
    p1 = new HumanPlayer{'x'};
    p2 = new MachinePlayer{'o'};
  }

  while (1) {
    std::cout << board << std::endl;
    p1->play(board);
    if (board.won('x'))
      break;
    std::cout << board << std::endl;
    p2->play(board);
    if (board.won('o'))
      break;
  }
  std::cout << "Congrats" << std::endl;
  std::cout << board << std::endl;
  std::cout << "Congrats" << std::endl;

  delete p1;
  delete p2;

  return 0;
}
