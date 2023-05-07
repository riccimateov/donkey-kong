#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class objetoMovil
{
	protected:
		RectangleShape *colisionador = new RectangleShape();
		float gravity;	
		float  jumpSpeed;
		bool saltar= true;
		Vector2f velocity;
		int posX;
		int posY;
		int minPiso;
		bool puedeEscalar;
		int piso;
		string tipo;
		bool control=NULL;
	public:
		objetoMovil()
		{
		}

		~objetoMovil()
		{
		}
};
	
