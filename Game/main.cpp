#include <SFML/Graphics.hpp>
#include<windows.h>
#include <time.h>
#include<iostream>
#include <tchar.h>


using namespace sf;
using namespace std;
struct point {
    int x, y;
};
int score = 0;
int main(){
    
    srand(time(0));
    
    RenderWindow app(VideoMode(400, 710), "Doodle Game!");
    app.setFramerateLimit(60);
    Text text;
    Font font;
    Texture t1, t2, t3,t4;
    RectangleShape heart, countHeart;
    int count=3;
    float totalTime = 0;
    t1.loadFromFile("images/background.jpg");
    t2.loadFromFile("images/ice-bar.png");
    t3.loadFromFile("images/penguin.png");
    t4.loadFromFile("images/heart.png");
    font.loadFromFile("arial.ttf");

    heart.setTexture(&t4);
    heart.setSize((Vector2f)t4.getSize());
    heart.setOrigin((Vector2f)t4.getSize() * 0.5f);
    heart.setPosition(-50, -50);
    countHeart = heart;

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(Color::Blue);
    text.setPosition(0,0);
    text.setStyle(Text::Bold);//in dam

    Sprite sBackground(t1), sPlat(t2), sPers(t3); 
    point plat[20]; 

    for (int i = 0; i < 10; i++  ) {
        plat[i].x = rand() % 400;
        plat[i].y = rand() % 700;
    }

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;

    while ( app.isOpen() ){

        Event e;
        while ( app.pollEvent(e) ){
            if ( e.type == Event::Closed ) app.close();
        }
        
            if ( Keyboard::isKeyPressed ( Keyboard::Right) ) x += 3;
            if ( Keyboard::isKeyPressed ( Keyboard::Left ) ) x -= 3;

        if ( heart.getPosition().x==-50 ) totalTime += 0.5f;
        if ( totalTime > 70.f ){
            totalTime = 0;
            int x = rand() % 350;
            heart.setPosition(x, 0);
        }
        
        if ( heart.getPosition().y > 700 ) heart.setPosition( -50, -50 );
        if ( sPers.getGlobalBounds().intersects(heart.getGlobalBounds()) ){
            if ( count < 4 ) count++;
            heart.setPosition ( -50, -50 );
        }
        dy += 0.2;
        y += dy;
        if ( y > 700 ){
            if ( count == 0 ) {
                string Information = "Score: " + to_string(score);
                wstring stemp = wstring(Information.begin(), Information.end());
                LPCWSTR sw = stemp.c_str();
                if (MessageBox(NULL, sw, L"Game over", MB_OK) == IDOK) app.close();
            }
            else {
                count--;
                //sPers.setPosition(100, 100);
                y = 100; x = 100;
                dy = 0; dx = 0;
            }
        }
        if ( y < h ){
            for (int i = 0; i < 10; i++ ){
                y = h;
                plat[i].y = plat[i].y - dy;
                if ( plat[i].y > 700 ){
                    plat[i].y = 0; 
                    plat[i].x = rand() % 400;
                }
            }
            score += 1;
        }
       
        for ( int i = 0;i < 10;i++ )
            if ( (x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
                && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0) ){
                dy = -10;
            }
        heart.move( 0, 1.f ); // toc do di cua tym
        sPers.setPosition( x, y );
        app.clear();
        app.draw( sBackground );
        app.draw( sPers ); // bird
        for (int i = 0;i < 10;i++){
            sPlat.setPosition ( plat[i].x, plat[i].y );
            app.draw ( sPlat );
        }
        text.setString ( "Score: " + to_string ( score ) );
        app.draw ( text );
        app.draw ( heart );
        for ( int i = 0;i < count; i++ ) {
            countHeart.setPosition ( Vector2f ( 375 - i * 50, 25 ) );
            app.draw ( countHeart );
        }
        app.display();
    }
    
    return 0;
}
