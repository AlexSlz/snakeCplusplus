#include "Header.h"

using namespace std;

int height = 500, width = 500, score, gameSpeed, enemyDelay, snakeDir = 1;
vector< myObject > snakeBody = {
    myObject(30, 30, COLOR(0, 255 ,0))
};
myObject apple = {
    myObject(height / 2, width / 2, COLOR(255, 255 ,0))
};
vector< myObject > enemy = {
};
void loadSnakeGame() {
    snakeBody.clear();
    snakeBody.push_back(myObject(30, 30, COLOR(0, 255, 0)));
    apple = myObject(height / 2, width / 2, COLOR(255, 255, 0));
    enemy.clear();
    enemyDelay = 0;
    score = 0;
    gameSpeed = 100;
    snakeDir = 1;
}
void SpawnEnemy() {
    enemy.push_back(myObject(-30, -30, COLOR(255, 0, 0)));
    enemy[enemy.size() - 1].getRandCords();
}
void inputSnake() {
    if (GetAsyncKeyState(VK_LEFT) && snakeDir != 1) {
        //snakeBody[0].x -= 15;
        snakeDir = 0;
    }
    if (GetAsyncKeyState(VK_RIGHT) && snakeDir != 0) {
        //snakeBody[0].x += 15;
        snakeDir = 1;
    }
    if (GetAsyncKeyState(VK_UP) && snakeDir != 3) {
        //snakeBody[0].y -= 15;
        snakeDir = 2;
    }
    if (GetAsyncKeyState(VK_DOWN) && snakeDir != 2) {
        //snakeBody[0].y += 15;
        snakeDir = 3;
    }

    if (snakeDir == 0) snakeBody[0].x -= 15;
    else if (snakeDir == 1) snakeBody[0].x += 15;
    else if (snakeDir == 2) snakeBody[0].y -= 15;
    else if (snakeDir == 3) snakeBody[0].y += 15;
}
void moveSnakeBody() {
    for (size_t i = snakeBody.size() - 1; i > 0; i--)
    {
        snakeBody[i].x = snakeBody[i - 1].x;
        snakeBody[i].y = snakeBody[i - 1].y;
    }
}
void snakeLimits() {
    if (snakeBody[0].x >= height - 10) {
        snakeBody[0].x = 1;
    }
    if (snakeBody[0].x <= 0) {
        snakeBody[0].x = height - 10;
    }
    if (snakeBody[0].y >= width - 10) {
        snakeBody[0].y = 1;
    }
    if (snakeBody[0].y <= 0) {
        snakeBody[0].y = width - 10;
    }
    /*
    for (size_t i = 1; i < snakeBody.size(); i++)
    {
        if (snakeBody[i].collide(snakeBody[0])) {
            snakeBody.clear();
        }
    }
    */
}
int main()
{
    initwindow(width, height, "snake...");
    loadSnakeGame();
    while (1) {
        cleardevice();
        char dataText[1024];
        sprintf(dataText, "Score > %d\n", score);
        setcolor(COLOR(255, 255, 0));
        outtextxy(10, 10, dataText);
        if (snakeBody.size() != 0) {
            moveSnakeBody();
            inputSnake();
            snakeLimits();
            if (snakeBody.size() != 0 && snakeBody[0].collide(apple)) {
                snakeBody.push_back(myObject(-30, -30, COLOR(0, 100, 0)));
                apple.getRandCords();
                score++;
                if (gameSpeed >= 50)
                    gameSpeed--;
            }
            for (size_t i = 0; i < enemy.size(); i++)
            {
                if (enemy[i].collide(snakeBody[0])) {
                    if (snakeBody.size() <= 3) {
                        snakeBody.clear();
                    }
                    for (size_t i = 0; i < snakeBody.size() / 1.5f; i++)
                    {
                        snakeBody.pop_back();
                    }
                    enemy.erase(enemy.begin() + i);
                }
            }
            if (score >= enemyDelay) {
                SpawnEnemy();
                enemyDelay += 3;
            }
            //Print
            for (size_t i = 0; i < snakeBody.size(); i++)
            {
                snakeBody[i].print();
            }
            apple.print();
            for (size_t i = 0; i < enemy.size(); i++)
            {
                enemy[i].print();
            }
        }
        else {
            string text = "you die :(\n your score > %d";
            sprintf(dataText, "You Die :( Your Score > %d", score);
            setcolor(COLOR(255, 255, 0));
            outtextxy(10, 10, dataText);
        }
        delay(gameSpeed);
        if (GetAsyncKeyState(0x52)) {
            loadSnakeGame();
        }
    }
}
