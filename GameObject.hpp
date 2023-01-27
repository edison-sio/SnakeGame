#include <vector>
#include <cstdlib>
#include <algorithm>
// #include "GameObject.hpp"

#define SNAKE_DEFAULT_LEN 3

class Direction {
private:
    int rowOffset_;
    int colOffset_;

public:
    Direction(int rowOffset, int colOffset);
    int rowOffset() const;
    int colOffset() const;

    Direction operator+(const Direction& dir);
    Direction operator+(const Direction& dir);
    bool operator==(const Direction& dir);
};

class Position {
private:
    int row_;
    int col_;

public:
    Position(int row, int col);

    void update(int row, int col);

    int row() const;
    int col() const;

    Position nextPosition(Direction dir) {
        int newRow = row_ + dir.rowOffset();
        int newCol = col_ + dir.colOffset();
        return Position(newRow, newCol);
    }
};


enum GridValue { EMPTY=0, SNAKE, FOOD, OUTSIDE };
enum Theme { DARK, BUGCAT_CAPOO };
enum Difficulty { EASY, MEDIUM, HARD };

class GameState {
private:
    int rows_;
    int cols_;
    int snakeLength_;
    // GridValue **gridVals;
    std::vector<Position> grid_;
    std::vector<Position> snake_;
    Direction dir_;
    Position food_;
    bool gameOver_;
    int score_;
    Difficulty difficulty_;
    Theme theme_;

public:
    GameState(int rows, int cols);
    void gameStart();
    void changeDifficulty(Difficulty difficulty);
    void changeDirection(Direction dir);
    void updateFood();
    void updateState();
    
    std::vector<Position> grid() const;
};
