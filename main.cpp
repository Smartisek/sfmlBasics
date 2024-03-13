#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

struct tile
{
    CircleShape shape;

    bool isSelected( int x, int y){
        int posX = shape.getPosition().x;
        int posY = shape.getPosition().y;

        return (x >= posX && x <= posX+46 && y >= posY && y <= posY+46);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(100, 0);
    int dirY = 10;
    int dirX = 3;
    vector<RectangleShape> background;
    vector<tile> tiles;
    int st =0;
    for(int r = 7; r>=0; r--){
        if(r >=5 || r<=2){
            for(int c = st; c <= 7; c+=2){
                tile t;
                t.shape = CircleShape(25.0f);
                t.shape.setFillColor(r<=2?Color::Red:Color::Magenta);
                t.shape.setOutlineColor(Color::Black);
                t.shape.setPosition(c*50+2, r*50+2);
                tiles.push_back(t);
            }
        }
        if(r%2==1){
            st++;
        } else {
            st--;
        }
    }

    for(int r =0; r <8; r++){
       for(int c = 0; c < 8; c++){
           RectangleShape shape(Vector2f(50,50));
           shape.setFillColor((r+c) %2==0?Color::Black:Color::White);
           shape.setPosition(c*50, r*50);
           background.push_back(shape);
       }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseButtonReleased){
                if(shape.getFillColor() == Color::Green){
                    shape.setFillColor(Color::Red);
                } else {
                    shape.setFillColor(Color::Green);
                }
            }
            else if(event.type == Event::KeyReleased){
                if(shape.getFillColor() == Color::Green){
                    shape.setFillColor(Color::Red);
                } else {
                    shape.setFillColor(Color::Green);
                }
            }
        }
        window.setFramerateLimit(60);
        shape.setPosition(shape.getPosition().x+dirX, shape.getPosition().y+dirY);
        if(shape.getPosition().y >= 300 || shape.getPosition().y <= 0){
            dirY *=-1;
        }
        if(shape.getPosition().x >= 300 || shape.getPosition().x <= 0){
            dirX*=-1;
        }

        window.clear();
        for(RectangleShape &s : background){
            window.draw(s);
        }
        for(tile &s : tiles){
            window.draw(s.shape);
        }

        window.draw(shape);
        window.display();
    }

    return 0;
}
