#include <iostream>
#include <conio.h>
#include <dos.h>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;


class Bullet
{
public:
    Bullet() : row(7),isalive(false) {}
    bool isalive;
    void move();
    int row,col;
};


class Gun
{
public:
    Gun() : col(4) {}
    void fire();
    Bullet b;
    void move(char);
    int col;
};

class Enemy
{
public:
    Enemy() : row(0),col(1) {}
    void move();
    int row,col;
};

class Board
{
public:
    void output(int &);
    void move_bullet();
    void move_enemy();
    void move_player(char);
    bool win(){
        return (g.b.row == e.row && g.col == e.col || e.row == g.b.row-1 && e.col == g.col);
    }
     bool lose(){
        return (e.row == 6 );
    }
    int text;
    Enemy e;
    Gun g;
    char data[8][8];
    int i,j;
};

int main()
{
    Board b;
    time_t s,s1;
    int start = 0;
    s = time(NULL);
    char x;
    b.output(start);
    while(start == 0)
    {
        s1 = time(NULL);
        if(s1-s > 1)
        {
            system("cls");
            b.output(start);
            b.move_enemy();
            b.move_bullet();
            s = s1;
        }
        if(kbhit())
        {
            system("cls");
            b.output(start);
            x = getch();
            if(x == ' '){
                b.g.fire();
            }
            else {
                 b.move_player(x);
            }


        }

    }
    system("cls");
    if(b.text==1){
        cout << "YOU WIN!!!";
    }
    else if(b.text==0){
        cout << "YOU LOSE!!!";
    }
    return 0;
}

void Enemy::move()
{
    if((col == 7 && row%2 == 0) && (col == 1 && row%2 == 1))
    {
        ++row;
    }
    else if( row%2 == 0)
    {
        ++col;
    }
    else
    {
        --col;
    }
}

void Gun::move(char x)
{
    switch(x)
    {
    case 'a':
    {
        if(col != 1)
            --col;
        break;
    }
    case 'd':
    {
        if(col != 7)
            ++col;
        break;
    }
    /*case ' ':{
        Bullet::move();
        break;

    }
    */
    }
}

void Bullet::move()
{
    if(isalive){ //true
    if(row != 0)
      --row;
    else{
       isalive = false;
    }
}
}
void Board::move_bullet()
{
    g.b.move();
}


void Board::output(int &s)
{

    for(i = 0; i < 8; ++i)
    {
        for(j = 0; j < 8; ++j)
        {
            if(i == e.row && j == e.col)
            {
                data[i][j] = 'E';
            }
            else if(i == 7 && j == g.col )
            {
                data[i][j] = 'G';
            }
            else if(i == g.b.row && j == g.b.col && g.b.isalive)//true
            {
                data[i][j] = '^';
            }
            else if(win()){
                    s=1;
                    text=1;
                break;
            }
            else if(lose()){
                    s=1;
                    text=0;
                break;
            }
            else
            {
                data[i][j] = ' ';
            }

        }
    }
    for (i = 0; i < 8; ++i)
    {
        for(j = 0; j < 8; ++j)
        {
            if (j != 0)
            {
                cout << data[i][j] << "_";
            }
        }
        cout << endl;
    }
}

void Board::move_enemy()
{
    e.move();
}
void Board::move_player(char x)
{
    g.move(x);
}
void Gun::fire()
{
    b.row = 6;
    b.col=col;
    b.isalive = true;
}
