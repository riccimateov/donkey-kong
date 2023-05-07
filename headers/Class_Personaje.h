#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Personaje:public objetoMovil
{
	
	private:
		Texture textura;
		Sprite personaje;
		int lado=1;
  	 	string tipo; 
	public:
		Personaje(string t)
		{
			textura.loadFromFile("img/marioPrincesa.png"); 
			textura.setSmooth(true);
			tipo=t;
		
			if(tipo=="princesa")
			{
			
				personaje.setTexture(textura);
				personaje.setScale(1.5,1.5); 
    			personaje.setTextureRect(IntRect(0,56,20,20)); 
  				personaje.setPosition(235,137);
				colisionador->setSize(Vector2f(14,16));
				colisionador->setPosition(Vector2f(244,143));
			}
			if(tipo=="mario")
			{
				gravity=2;	
				jumpSpeed=11;
				saltar= true;
				posX=100;
				posY=471;
				puedeEscalar=NULL;
				velocity.x=0;
				velocity.y=0;
				minPiso=484;
				personaje.setTexture(textura);
				personaje.setScale(1.5,1.5); 
    			personaje.setTextureRect(IntRect(85,0,20,20)); 
  				personaje.setPosition(posX-10,posY-5);
				colisionador->setSize(Vector2f(16,18));
				colisionador->setPosition(Vector2f(posX,posY));
			 }
		}
		void mostrar(RenderWindow &v)
		{
			if(tipo=="mario")
			{	
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					if(saltar)
					{
					personaje.setTextureRect(IntRect(85,0,20,20));
					}
					lado=1;
				}
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					lado=2;
					if(saltar)
					{
					personaje.setTextureRect(IntRect(24,0,20,20));
					}
				}
			}
			v.draw(personaje);
		}
		void caminar()
		{
			if(piso!=6)
			{
			
					if (Keyboard::isKeyPressed(Keyboard	::Right)&&colisionador->getPosition().x<415)
					{
						colisionador->move(.2,0);
						personaje.move(.2,0);
					}
					if (Keyboard::isKeyPressed(Keyboard::Left)&&colisionador->getPosition().x>92)
					{
						colisionador->move(-.2,0);
						personaje.move(-.2,0);
					}
			}
			else
			{
				if (Keyboard::isKeyPressed(Keyboard::Right)&&colisionador->getPosition().x<290)
					{
						colisionador->move(.2,0);
						personaje.move(.2,0);
					}
					if (Keyboard::isKeyPressed(Keyboard::Left)&&colisionador->getPosition().x>217)
					{
						colisionador->move(-.2,0);
						personaje.move(-.2,0);
					}
			}
		}
		
		void salto()
		{	
			if (control&&(Keyboard::isKeyPressed(Keyboard::Space) && saltar))
			
			velocity.y = -jumpSpeed;
			saltar = false;
			

				if ((control&&((colisionador->getPosition().y + colisionador->getSize().y) < minPiso  )||control&& (velocity.y<0) && (!saltar))){
					velocity.y = velocity.y + gravity;
					if(lado==1)
					{
						personaje.setTextureRect(IntRect(0,30,20,20));
					}
					if(lado==2)
					{
						personaje.setTextureRect(IntRect(25,59,20,20));
					}
				}
				else  
				{
				
					velocity.y=0;
					saltar=true;
					control=true;
					
				}
			
					colisionador->move(0,velocity.y);
					personaje.move(0,velocity.y);
				
		
		}
		
		void escalar(RectangleShape m)
		{
			
			if(colisionador->getGlobalBounds().intersects(m.getGlobalBounds())&&saltar)
			{
				
					
				if(Keyboard::isKeyPressed(Keyboard::Up)&&colisionador->getPosition().y>m.getPosition().y)
				{
					personaje.setTextureRect(IntRect(60,0,20,20));
					colisionador->move(0,-2);
					personaje.move(0,-2);
					control=false;
			
				}
				
				if(Keyboard::isKeyPressed(Keyboard::Down)&&colisionador->getPosition().y<(m.getPosition().y+m.getSize().y)-colisionador->getSize().y)
				{
					
					personaje.setTextureRect(IntRect(60,0,20,20));
					colisionador->move(0,2);
					personaje.move(0,2);
					control=false;
				}
			
			
				if(colisionador->getPosition().y>(m.getPosition().y+m.getSize().y-(colisionador->getSize().y)-4)||colisionador->getPosition().y<(m.getPosition().y+(colisionador->getSize().y-8)))
				{
					puedeEscalar=false;
					
				}
				else
				{
					control=false;
					puedeEscalar=true;
				}
			}
			
			
			if(!puedeEscalar)
			{
				caminar();	
			}
					
		}
		
		void actualizar()
		{
			if(colisionador->getPosition().y<=485)
			{
				piso=0;
				minPiso=485;
			}
		
			if(colisionador->getPosition().y<=440)
			{
				piso=1;
				minPiso=435;
			}
			if(colisionador->getPosition().y<=383)
			{
				piso=2;
				minPiso=380;
			}
			
			if(colisionador->getPosition().y<=327)
			{
				piso=3;
				minPiso=320;
			}
			
			if(colisionador->getPosition().y<=275)
			{
				piso=4;
				minPiso=260;
			}
			if(colisionador->getPosition().y<=219)
			{
				piso=5;
				minPiso=212;
			}
			if(colisionador->getPosition().y<=159)
			{
				piso=6;
				minPiso=153;
			}
		}
		
		bool colisionPrincesa(Personaje &target)
		{
			if(colisionador->getGlobalBounds().intersects(target.colisionador->getGlobalBounds()))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		RectangleShape returnColisionador()
		{
			return *colisionador;
		} 
		
		void reset()
		{
			piso=0;
			gravity=2;	
			jumpSpeed=11;
			saltar= true;
			posX=100;
			posY=471;
			puedeEscalar=NULL;
			velocity.x=0;
			velocity.y=0;
			minPiso=484;
			personaje.setTexture(textura);
			personaje.setScale(1.5,1.5); 
    		personaje.setTextureRect(IntRect(85,0,20,20)); 
  			personaje.setPosition(posX-10,posY-5);
			colisionador->setSize(Vector2f(16,18));
			colisionador->setPosition(Vector2f(posX,posY));
		}
		~Personaje()
		{
		}
};


