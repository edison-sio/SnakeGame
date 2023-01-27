#include <QWidget>
#include <QKeyEvent>
#include <iostream>
#include "Game.hpp"
#include "Gameobject.hpp"

#define LEFT Direction(-1, 0)
#define RIGHT Direction(1, 0)
#define UP Direction(0, -1)
#define DOWN Direction(0, 1)

Game::Game(QWidge *parent) : QWidget(parent) {
    width_ = 300;
    height_ = 300;
    game = GameState(height_, width_)
    inGame_ = true;
    points_ = 0;
}

void Game::loadImages() {

}

void Game::initGame() {
    game.gameStart();
}

void Game::doDrawing() {

    QPainter qp(this);

    if (inGame) {
        std::vector<Position> g = game.grid();
        std::vector<Position> s = game.snake();
        for (Position p : g) {
            int x = p.col();
            int y = p.row();
            qp.drawImage(x, y, background_);
        }
        int i = 0;
        for (Position p: s) {
            int x = s.col();
            int y = p.row();
            if (i == 0) {
                qp.drawImage(x, y, head_);
                i++;
            } else {
                qp.drawImage(x, y, body_);
            }
        }
        qp.drawImage(f.col(), f.row(), food_);
    }
}

void Game::timeEvent(QTimerEvent *e) {
    Q_UNUSED(e);

    if (inGame) {
        game.updateState();
    }

    repaint();
}

void Game::keyPressEvent(QKeyEvent *e) {
    int key = e->key();
    
    if (key == Qt::Key_Left) {
        game.changeDirection(LEFT)
    }
    if (key == Qt::Key_Right) {
        game.changeDirection(RIGHT)
    }
    if (key == Qt::Key_Up) {
        game.changeDirection(UP)
    }
    if (key == Qt::Key_Down) {
        game.changeDirection(DOWN)
    }

    QWidget::keyPressEvent(e);
}
