#include <QWidget>
#include <QKeyEvent>
#include <iostream>

class Game : public QWdget {
public:
    Game(QWidget *parent = nullptr)
    void loadImages();
    void initGame();
    void update();
    void doDrawing();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    int width_;
    int height_;
    // int x_[300];
    // int y_[300];
    GameState game_;

    QImage head_;
    QImage body_;
    QImage food_;
    QImage background_;

    int points;
    std::string player;
    bool inGame;


}