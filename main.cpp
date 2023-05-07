#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include "headers/Class_ObjetoMovil.h" 
#include "headers/Class_Personaje.h"
#include "headers/Class_Barril.h"
#include "headers/Class_Mapa.h"
using namespace std;
using namespace sf;
int lectura();
void escritura(int p);
int main()
{	
	SoundBuffer buffer;
	Sound musica;
	buffer.loadFromFile("snd/musiquita.ogg");
	musica.setBuffer(buffer);
	Font fuente;
	Text puntaje;
	Text puntajeAltoTexto;
	Time barrilRoto;
	Clock relojJuego;
	Time delay = seconds(3);
	Time empezarJugar = seconds(4);
	Time reset = seconds(5);
	Time arranque;
	Clock relojBarril;
	Texture tex1;
	Texture tex2;
	Texture tex3;
	Texture tex4;
	Texture tex5;
    tex1.loadFromFile("img/mapa.png");
    tex2.loadFromFile("img/kong.png");
    tex3.loadFromFile("img/menu.png");
    tex4.loadFromFile("img/win.png");
    tex5.loadFromFile("img/gameover.png");
    Sprite sprite(tex1);
   	Sprite monito(tex2);
   	Sprite menu(tex3);
   	Sprite win(tex4);
   	Sprite gameOver(tex5);
   	monito.setTextureRect(IntRect(42,6,26,24)); 
   	monito.setScale(2,2); 
   	monito.setPosition(85,170);
  	RenderWindow ventana(sf::VideoMode(505, 570), "Donkey Kong" ,  Style::Titlebar | Style::Close );
	ventana.setFramerateLimit(30);
	ventana.setKeyRepeatEnabled(false);
	Personaje *mario = new Personaje("mario");
	Personaje *princesa = new Personaje("princesa");
    Barril** arrayBarriles = new Barril*[10];
	Mapa** escaleras = new Mapa*[9]; 
	int cantBarriles=0;
	int puntajeJugando=0;	
	int puntajeAlto=lectura();
	fuente.loadFromFile("font/Commodore Angled v1.2.ttf");
	puntaje.setFont(fuente);
	puntaje.setPosition(92,73);
	puntaje.setCharacterSize(20);
	puntajeAltoTexto.setFont(fuente);
	puntajeAltoTexto.setCharacterSize(20);
	stringstream conversionPuntajeAlto;
	conversionPuntajeAlto<<puntajeAlto;
	string puntajeAltoConvertido = conversionPuntajeAlto.str();
	puntajeAltoTexto.setString(puntajeAltoConvertido);
	musica.setVolume(50.f);
	musica.setLoop(true);
	musica.play();
	int estadoJuego=0;
	for(int i = 0; i<9; i++)
	{
		escaleras[i] = new Mapa(i);
	}
	puntajeJugando=0;
	while (ventana.isOpen())
    {
        Event evento;
        while (ventana.pollEvent(evento))
        {
   
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }
        
      	stringstream conversionPuntajeJugando;
		conversionPuntajeJugando<<puntajeJugando;
		string puntajeConvertido = conversionPuntajeJugando.str();
		puntaje.setString(puntajeConvertido);
         if(estadoJuego==0)
         {
         	arranque = relojJuego.getElapsedTime();
         	if( arranque > empezarJugar )
         	{
         		estadoJuego=1;
         		relojJuego.restart();
         		arranque = seconds(0);
			}
         	puntajeAltoTexto.setPosition(210,15);
         	ventana.clear();
         	ventana.draw(menu);
         	ventana.draw(puntajeAltoTexto);
         	ventana.display();
		 }
       if(estadoJuego==1)
       {
       	puntajeAltoTexto.setPosition(210,73);
	    ventana.clear();
        ventana.draw(sprite); 
        for(int i = 0; i<9; i++)
		{	
			mario->escalar(escaleras[i]->returnColisionador());	
		}
		mario->actualizar();
		mario->salto();
        mario->mostrar(ventana);
    
        princesa->mostrar(ventana);
        
        ventana.draw(monito);
    	barrilRoto = relojBarril.getElapsedTime();
    	for(int i=0; i<cantBarriles; i++)
		{
			arrayBarriles[i]->actualizar();	
		}
    	if(barrilRoto > delay )
    	{
    		if(cantBarriles < 5)
			{
			relojBarril.restart();
    		monito.setTextureRect(IntRect(0,6,26,24)); 
			arrayBarriles[cantBarriles] = new Barril();
			cantBarriles++;
    		cout<<cantBarriles<<endl;
    		}
		}
		else
		{
			monito.setTextureRect(IntRect(42,6,26,24)); 
		}
		
		for(int i=0; i<cantBarriles; i++)
		{	
			arrayBarriles[i]->mostrar(ventana);
			for(int j = 0; j<9; j++)
			{	
				arrayBarriles[i]->escalar(escaleras[j]->returnColisionador());
			}	
			if(arrayBarriles[i]->salioMapa())
			{
				delete arrayBarriles[i];
				arrayBarriles[i] = new Barril();
			}
			if(arrayBarriles[i]->colision(mario->returnColisionador()))
			{
				arranque = seconds(0);
				relojJuego.restart();
				estadoJuego=3;
				if(puntajeJugando>puntajeAlto)
    			{
    				escritura(puntajeJugando);
				}
			}
			if(arrayBarriles[i]->puntaje(mario->returnColisionador()))
			{
				puntajeJugando=puntajeJugando+10;
				cout<<puntajeJugando<<endl;
			}
		}
		if(mario->colisionPrincesa(*princesa))
		{
			arranque = seconds(0);
			relojJuego.restart();	
		
			estadoJuego=4;
		}
	    ventana.draw(puntaje);
	    ventana.draw(puntajeAltoTexto);
		ventana.display();
		}
		 if(estadoJuego==3)
         {	
         	mario->reset();
        	ventana.clear();
        	ventana.draw(gameOver);
			ventana.display();
         	arranque = relojJuego.getElapsedTime();
         	if( arranque > reset )
         	{
         		puntajeJugando=0;
         		cantBarriles=0;
         		relojJuego.restart();
         		estadoJuego=1;
			}
         	
		 }
		 if(estadoJuego==4)
         {	
         	mario->reset();
        	ventana.clear();
        	ventana.draw(win);
			ventana.display();
         	arranque = relojJuego.getElapsedTime();
         	if( arranque > reset )
         	{
         		puntajeJugando=0;
         		cantBarriles=0;
         		relojJuego.restart();
         		estadoJuego=1;
			}
         	
		 }
    }
}

int lectura()
{
	ifstream archivoLectura;
	string texto;
	string nombreArchivo="res/puntaje.txt";
	archivoLectura.open(nombreArchivo.c_str(),ios::in); //Abrimos el archivo en modo lectura
	if(archivoLectura.fail()){
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	while(!archivoLectura.eof()){ 
		getline(archivoLectura,texto);
	}
	archivoLectura.close(); 
	stringstream conversion(texto);
    int p = atoi(texto.c_str());
    return p;
}

void escritura(int p)
{
	
	ofstream archivo;
	string nombreArchivo="res/puntaje.txt";
	archivo.open(nombreArchivo.c_str(),ios::out); 
	if(archivo.fail()){  
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}
	archivo<<p;
	archivo.close(); 
}
