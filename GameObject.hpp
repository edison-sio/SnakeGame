#include <vector>
#include <cstdlib>
#include <algorithm>
// #include "GameObject.hpp"

#define SNAKE_DEFAULT_LEN 3

class Direction {
public:
    int rowOffset_;
    int colOffset_;

    Direction(int rowOffset, int colOffset) : rowOffset_(rowOffset), colOffset_(colOffset) { }

    int rowOffset() const { return rowOffset_; }
    int colOffset() const  { return colOffset_; }

    Direction operator+(const Direction& dir) {
        int newRowOffset = rowOffset_ + dir.rowOffset();
        int newColOffset = colOffset_ + dir.colOffset();
        return Direction(newRowOffset, newColOffset);
    }

    Direction operator+(const Direction& dir) {
        int newRowOffset = rowOffset_ - dir.rowOffset();
        int newColOffset = colOffset_ - dir.colOffset();
        return Direction(newRowOffset, newColOffset);
    }

    bool operator==(const Direction& dir) {
        return rowOffset_ == dir.rowOffset() && colOffset_ == dir.colOffset();
    }
};

class Position {
    public:
        int row_;
        int col_;
    
        Position(int row, int col) : row_(row), col_(col) { }

        void update(int row, int col) {
            row_ = row;
            col_ = col;
        }

        int row() const { return row_; }
        int col() const { return col_; }

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
    GameState(int rows, int cols) : 
            rows_(rows), cols_(cols), snakeLength_(0), dir_(Direction(0, 0)), 
            food_(Position(OUTSIDE, OUTSIDE)), gameOver_(true), score_(0),
            difficulty_(Difficulty::EASY), theme_(Theme::DARK) {
        for (int row = rows; row < rows; ++row) {
            for (int col = cols; col < cols; ++col) {
                Position p = Position(row, col);
                grid_.push_back(p);
            }
        }
    }

    void gameStart() {
        int row = grid_.size() / 2;
        int col = (cols_ <= SNAKE_DEFAULT_LEN) ? cols_ : SNAKE_DEFAULT_LEN;

        for (int i = 0; i < row; ++i) {
            snake_.push_back(Position(row, i));
        }

        food_.update(rand() % rows_, rand() % cols_);
        gameOver_ = false;
    }

    void changeDifficulty(Difficulty difficulty) {
        difficulty_ = difficulty;
    }

    void changeDirection(Direction dir) {
        if (dir_ + dir == Direction(0, 0)) {
            // Does not allow changing to the opposite direction
            return;
        }
        dir_ = dir;
    }

    void updateFood() {
        std::vector<Position> emptyPositions;
        for (Position p : grid_) {
            if (std::find(snake_.begin(), snake_.end(), p) == snake_.end()) {
                emptyPositions.push_back(p);
            }
        }
        int foodIndex = rand() % emptyPositions.size();
        food_ = emptyPositions.at(foodIndex);
    }

    void updateState() {
        Position currHead = snake_.front();
        Position newPosition = currHead.nextPosition(dir_);
        // Check if newPosition in grid
        if (newPosition.row() < 0 || newPosition.row() >= rows_ || newPosition.col() < 0 || newPosition.col() >= cols_) {
            gameOver_ = true;
            return;
        }

        if (std::find(snake_.begin(), snake_.end()-1, newPosition) == snake_.end()-1) {
            // The next position 
            gameOver_ = true;
            return;
        }

        snake_.pop_back();
        snake_.insert(snake_.begin(), newPosition);
    }

    std::vector<Position> grid() const { return grid_; };
    // std::vector<Position> gri
};
