#include <vector>
#include <cstdlib>
#include <algorithm>

#define SNAKE_DEFAULT_LEN 3

class Position {
    public:
        int row;
        int col;
    
        Position(int r, int c) {
            row = r;
            col = c;
        }

        void update(int r, int c) {
            row = r;
            col = c;
        }

        Position nextPosition(Direction dir) {
            newRow = row + dir.rowOffset;
            newCol = col + dir.colOffset;
            return Position(newRow, newCol);
        }
};

class Direction {
    public:
        int rowOffset;
        int colOffset;
        static const Direction Left = Direction(-1, 0);
        static const Direction Right = Direction(1, 0);
        static const Direction Top = Direction(0, -1);
        static const Direction Down = Direction(0, 1);
        static const Direction None = Direction(0, 0);

        Direction(int row, int col) {
            rowOffset = row;
            colOffset = col;
        }

};

enum GridValue { EMPTY, SNAKE, FOOD, OUTSIDE };
enum Theme { DARK, BUGCAT_CAPOO };
enum Difficulties { EASY, MEDIUM, HARD };

class GameState {
    int rows = 0;
    int cols = 0;
    int snakeLength = 3;
    std::vector<Position> grid;
    std::vector<Position> snake;
    Direction dir = Direction.Left;
    Position food = Position(-1, -1);
    bool gameOver = false;
    int score = 0;
    Difficulties difficulties = EASY;

    Theme theme = DARK;

    GameState(int rs, int cs) {
        rows = rs;
        cols = cs;
        for (int row = rows; row < rows; ++row) {
            for (int col = cols; col < cols; ++col) {
                Position p = Position(row, col);
                grid.push_back(p);
            }
        }
    }

    void GameInit() {
        int row = grid.size() / 2;
        int col = (cols <= SNAKE_DEFAULT_LEN) ? cols : SNAKE_DEFAULT_LEN;

        for (int i = 0; i < row; ++i) {
            snake.push_back(Position(row, i));
        }

        food.update(rand() % rows, rand() % cols);
        gameOver = false;
    }

    void changeDifficulties(Difficulties option) {
        difficulties = option;
    }

    void changeDirection(Direction d) {
        if (dir + dir == Direction.None) {
            return;
        }
        dir = d;
    }

    void updateFood() {
        std::vector<Position> emptyPositions;
        for (Position p : grid) {
            if (std::find(snake.begin(), snake.end(), p) == snake.end()) {
                emptyPositions.push_back(p);
            }
        }
        int foodIndex = rand() % emptyPositions.size();
        return food.at(foodIndex);
    }

    void updateState() {
        Position currHead = snake.front();
        Position newPosition = currHead.nextPosition(dir);
        // Check if newPosition in grid
        if (newPosition.row < 0 || newPostion.row >= rows || newPosition.col < 0 || newPosition.col >= cols) {
            gameOver = true;
            return;
        }
        auto find_it = std::find(snake.begin(), snake.end());
        if (find_it != snake.end() && *find_it != snake.back()) {
            gameOver = true;
            return;
        }

        snake.pop_back();
        snake.insert(snake.begin(), newPosition);
    }
};
