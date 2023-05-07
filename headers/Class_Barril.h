#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Barril:public objetoMovil
{
	private:
	Texture textura;
	Sprite barril;
	RectangleShape *sumadorPuntaje = new RectangleShape();
	int camino;
	public:
	Barril()
	{	
		camino = rand() % 3 + 1;
	
		textura.loadFromFile("img/barriles.png"); 
		textura.setSmooth(true);
		barril.setTexture(textura);
    	barril.setTextureRect(IntRect(42,8,23,19)); 
  		barril.setPosition(74,193);
		colisionador->setSize(Vector2f(10,5));
		colisionador->setPosition(Vector2f(83,205)); 
		sumadorPuntaje->setSize(Vector2f(10,10));
		sumadorPuntaje->setPosition(Vector2f(83,185)); 
		
	}
	void escalar(RectangleShape m)
	{
			if(camino==1)
			{
			
			if(colisionador->getGlobalBounds().intersects(m.getGlobalBounds()))
			{
				barril.setTextureRect(IntRect(10,8,27,21)); 
				barril.move(0,3);
				colisionador->move(0,3);
				sumadorPuntaje->move(0,3);
				if(colisionador->getPosition().y>(m.getPosition().y+m.getSize().y-(colisionador->getSize().y))||colisionador->getPosition().y<(m.getPosition().y+(colisionador->getSize().y-8)))
				{
					puedeEscalar=false;
					
				}
				else
				{
					puedeEscalar=true;
				}
			}	
				if(!puedeEscalar)
				{
					mover();
					barril.setTextureRect(IntRect(42,8,23,19)); 
				}
			
			}
			if(camino==2)
			{
				if(colisionador->getPosition().x<372&&colisionador->getPosition().y<361)
				{
				sumadorPuntaje->move(.3,.01);
				barril.move(.3,.01);
				colisionador->move(.3,.01);
				barril.setTextureRect(IntRect(42,8,23,19)); 
				}
				if(colisionador->getPosition().x>372)
				{
					barril.move(0,.3);
					colisionador->move(0,.3);
					sumadorPuntaje->move(0,.3);
					barril.setTextureRect(IntRect(10,8,27,21)); 
				}
				if(colisionador->getPosition().y>364)
				{
					sumadorPuntaje->move(-.3,.01);
					barril.move(-.3,.01);
					colisionador->move(-.3,.01);
					barril.setTextureRect(IntRect(42,8,23,19)); 
				}
				if(colisionador->getPosition().y>364&&colisionador->getPosition().x<160)
				{
					camino=1;
				}
			}
			if(camino==3)
			{
				if(colisionador->getPosition().x<95)
				{
				sumadorPuntaje->move(.3,.01);
				barril.move(.3,.01);
				colisionador->move(.3,.01);
				barril.setTextureRect(IntRect(42,8,23,19)); 
				}
				else if(colisionador->getPosition().y<310)
				{
					barril.move(0,.3);
					colisionador->move(0,.3);
					sumadorPuntaje->move(0,.3);
					barril.setTextureRect(IntRect(10,8,27,21)); 
				}
				else
				{
					sumadorPuntaje->move(.3,.01);
					barril.move(.3,.01);
					colisionador->move(.3,.01);
					barril.setTextureRect(IntRect(42,8,23,19)); 
				}
				if(colisionador->getPosition().y>310&&colisionador->getPosition().x>320)
				{
					camino=1;
				}
			}
			
	}
	void actualizar()
		{
			if(colisionador->getPosition().y<=485)
			{
				piso=0;
				minPiso=489;
			}
		
			if(colisionador->getPosition().y<=440)
			{
				piso=1;
				minPiso=435;
			}
			if(colisionador->getPosition().y<=383)
			{
				piso=2;
				minPiso=385;
			}
			
			if(colisionador->getPosition().y<=327)
			{
				piso=3;
				minPiso=325;
			}
			
			if(colisionador->getPosition().y<=285)
			{
				piso=4;
				minPiso=280;
			}
			if(colisionador->getPosition().y<=219)
			{
				piso=5;
				minPiso=210;
			}
			
			if(colisionador->getPosition().y<=159)
			{
				piso=6;
				minPiso=150;
			}
	
			
		}
	void mostrar(RenderWindow &v)
	{
		v.draw(barril);
	//	v.draw(*colisionador);
	//	v.draw(*sumadorPuntaje);
		
	}
	
	void mover()
	{
		if(piso==5||piso==3||piso==1)
		{
			sumadorPuntaje->move(.3,.01);
			barril.move(.3,.01);
			colisionador->move(.3,.01);
		}
		if(piso==4||piso==2||piso==0)
		{
			sumadorPuntaje->move(-.3,.01);
			barril.move(-.3,.01);
			colisionador->move(-.3,.01);
		}
		
	}
	bool colision(RectangleShape target)
	{
		if(colisionador->getGlobalBounds().intersects(target.getGlobalBounds()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool puntaje(RectangleShape target)
	{
		if(sumadorPuntaje->getGlobalBounds().intersects(target.getGlobalBounds()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool salioMapa()
	{
			if(piso==0)
			{
				if(colisionador->getPosition().x<=68)
				{
					return true;
				}
			}
			else
			{
				return false;
			}
	}
	~Barril()
	{
		
	}

};

