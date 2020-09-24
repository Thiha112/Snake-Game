#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
using namespace sf;
class Food{
public:
    int x,y; };
class Snake{
public:
    int x,y; };
int main() {
    srand(time(0));
    Food f;
    Snake s[50];
    int dir,s_num = 0;
    int X = 20, Y = 20;
    int Size = 20;
    int Height = X*Size, Width = Y*Size;
    int score, program = 0;
    Clock clock;
    float timer,speed = 0.15;
    RenderWindow game(VideoMode(Height,Width),"Snake Game");
    Texture t1,t2,t3;
    t1.loadFromFile("grass.png");
    t3.loadFromFile("food.png");
    t2.loadFromFile("snake.png");
    Sprite field(t1);  Sprite player(t2);  Sprite target(t3);
    f.x = 10;   f.y = 10;
    Music music;
    music.openFromFile("Electro-session.wav");
    music.play();
    // game loop
    while(game.isOpen()){
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer+=time;
        Event event;
        while(game.pollEvent(event)){
            if(event.type == Event::Closed){ game.close(); } }
        //updates
        if(Keyboard::isKeyPressed(Keyboard::Up)) { dir = 1; }
        if(Keyboard::isKeyPressed(Keyboard::Down)) { dir = 2; }
        if(Keyboard::isKeyPressed(Keyboard::Left)) { dir = 3; }
        if(Keyboard::isKeyPressed(Keyboard::Right)) { dir = 4; }

        if(timer>speed) {
                timer = 0;
            for(int i = s_num;i>0;i--){
                s[i].x = s[i-1].x;
                s[i].y = s[i-1].y; }

                if(dir == 1) { s[0].y = s[0].y-1; }
                if(dir == 2) { s[0].y = s[0].y+1; }
                if(dir == 3) { s[0].x = s[0].x-1; }
                if(dir == 4) { s[0].x = s[0].x+1; }

            if(s[0].x > X) { s[0].x = 0;}   if(s[0].x<0) { s[0].x = X;}
            if(s[0].y > Y) { s[0].y = 0;}   if(s[0].y<0) { s[0].y = Y;}

            if(s[0].x == f.x && s[0].y == f.y) {
                s_num = s_num+30;
                score = s_num;
                f.x = rand()%X;
                f.y = rand()%Y; }

            for(int i =1; i<s_num;i++){
                if(s[0].x == s[i].x && s[0].y == s[i].y) { program = 1; s_num = i; } }
        }

        //rendering
        game.clear(Color::Yellow);
        for(int i=0;i<X;i++){
            for(int j=0;j<Y;j++){
                field.setPosition(i*Size,j*Size);
                game.draw(field);} }

        for (int i=0;i<=s_num; i++){
            player.setPosition(s[i].x*Size,  s[i].y*Size);
            game.draw(player); }
        target.setPosition(f.x*Size,f.y*Size);
        game.draw(target);
            if(program) {
                if(score == 40) {std::cout<<"You won\nYour Score is : "<<score;}
                if(score < 40) {std::cout<<"*****Game Over******\nYour score is : "<<score<<std::endl; }
                game.close(); }
        game.display();
    }
}
