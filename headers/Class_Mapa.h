#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Mapa{
	private:
		RectangleShape *colisionador = new RectangleShape();
	public:
		Mapa(int elemento)
		{
				if(elemento==0)
				{
					colisionador->setPosition(Vector2f(387,421));
					colisionador->setSize(Vector2f(1,61));
				}
				else if(elemento==1)
				{
					colisionador->setPosition(Vector2f(238,359));
					colisionador->setSize(Vector2f(1,73));
				}
				else if(elemento==2)
				{
					colisionador->setPosition(Vector2f(126,365));
					colisionador->setSize(Vector2f(1,60));
				}
				else if(elemento==3)
				{
					colisionador->setPosition(Vector2f(266,300));
					colisionador->setSize(Vector2f(1,75));
				}
				else if(elemento==4)
				{
					colisionador->setPosition(Vector2f(387,308));
					colisionador->setSize(Vector2f(1,60));
				}
				else if(elemento==5)
				{
					colisionador->setPosition(Vector2f(195,248));
					colisionador->setSize(Vector2f(1,67));	
				}
				else if(elemento==6)
				{
					colisionador->setPosition(Vector2f(128,251));
					colisionador->setSize(Vector2f(1,59));
				}
				else if(elemento==7)
				{
					colisionador->setPosition(Vector2f(387,195));
					colisionador->setSize(Vector2f(1,59));
				}
				else if(elemento==8)
				{
					colisionador->setPosition(Vector2f(292,143));
					colisionador->setSize(Vector2f(1,65));
				}
			
		
		}
	void mostrar(RenderWindow &v)
	{
		v.draw(*colisionador);
	}
	RectangleShape returnColisionador()
		{
			return *colisionador;
		}
	~Mapa()
	{
	}
};


