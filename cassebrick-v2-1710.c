#include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 920
#define FPS 60
#define nombreColonne 3
#define nombreLigne 3


// Lancement du jeu
int start;

//position du carre dessiné dans drawGame()
int x;
int y;

//Variables du cercle
int xRond;
int yRond;
int r;
int vitessex;
int vitessey;

//Variables du Pad
int longPad;
int largPad;
int xPad;
int yPad;
int compteurPad;

// Les briques
int ecartx;
int ecarty;
int xBrick;
int yBrick;
int longBrick;
int largBrick;
int espaceBrick;
int i;
int j;
int nombreBrick;

int tabX[nombreLigne][nombreColonne];
int tabY[nombreLigne][nombreColonne];

int tabVieBr[nombreLigne][nombreColonne];
int tabCartesX[nombreLigne][nombreColonne];
int tabCartesY[nombreLigne][nombreColonne];
int cartesMax;
int vieBrickMax;

// Vie du joueur
int coeur;
int xVie;
int yVie;
int longVie;
int largVie;
int k;


/*---------------- Ecran de démarrage Gnomes-------------------*/
void startGame()
{	

	if(start==0)
	{
        sprite(0,0,"Assets/start-play.bmp");
        actualize();
        }
}


/*---------------Fond d'écran du jeu--------------------------*/ 
void drawWallpaper()
{	
		
	sprite(0,0,"Assets/wallpaper-wow.bmp");
}


/*----------------Déplacement de la balle---------------------*/ 
void drawBall()
{   
    
    sprite(xRond-r,yRond-r,"Assets/fireball.bmp");
    
    if(start==1)
        {
    	xRond+=vitessex;
    	yRond+=vitessey; //le + fait office de compteur pour dire que le x du rond doit prendre la valeur de vitessey en boucle, comme un i++.
    	}
       
   
}


/*--------------Déplacement du Pad---------------------*/
void drawPad()
{
	changeColor(255,255,255);
	drawLine(xPad, yPad,xPad+longPad,yPad);
} 

/*-----------------Mes cartes et collisions-----------*/
void tabBrick()
{
    
    for(int i=0;i<nombreColonne;i++) //nombre de colonnes = nombre de briques par ligne
    {
   
	    for(int j=0;j<nombreLigne;j++) //nombre de lignes 
	    	
	    	{
	    	
	    	if (tabVieBr[j][i]>0)
	    	{
	    		sprite(tabX[j][i],tabY[j][i],"Assets/card-wow.bmp");
	    	}
	    	else if(tabCartesX[j][i]==1 && tabCartesY[j][i]==1)
	    	{
	    	sprite(tabX[j][i],tabY[j][i],"Assets/carte1.bmp");
	    	}
	    	else if(tabCartesX[j][i]==2 && tabCartesY[j][i]==1)
	    	{
	    	sprite(tabX[j][i],tabY[j][i],"Assets/carte2.bmp");
	    	}
	    	else if(tabCartesX[j][i]==3 && tabCartesY[j][i]==1)
	    	{
	    	sprite(tabX[j][i],tabY[j][i],"Assets/carte3.bmp");
	    	}
	    	else if(tabCartesX[j][i]==1 && tabCartesY[j][i]==2)
	    	{
	    	sprite(tabX[j][i],tabY[j][i],"Assets/carte4.bmp");
	    	}
	    	else if(tabCartesX[j][i]==2 && tabCartesY[j][i]==2)
	    	{
	    	sprite(tabX[j][i],tabY[j][i],"Assets/carte5.bmp");
	    	}
	    	else if(tabCartesX[j][i]==3 && tabCartesY[j][i]==2)
	    	{
	    		sprite(tabX[j][i],tabY[j][i],"Assets/carte6.bmp");
	    	}
	    	else if(tabCartesX[j][i]==1 && tabCartesY[j][i]==3)
	    	{
	    		sprite(tabX[j][i],tabY[j][i],"Assets/carte7.bmp");
	    	}
	    	else if(tabCartesX[j][i]==2 && tabCartesY[j][i]==3)
	    	{
	    		sprite(tabX[j][i],tabY[j][i],"Assets/carte8.bmp");
	    	}
	    	else 
	    	{
	    		sprite(tabX[j][i],tabY[j][i],"Assets/returned-card.bmp");
	    	}
	    	
	    	
	    	
	    	
	    	if(tabVieBr[j][i]>0 && 
	    	   yRond+r>=tabY[j][i] && yRond<=tabY[j][i]  && 
	    	   xRond-r>=tabX[j][i] && xRond+r<=tabX[j][i]+longBrick 
	    	   && vitessey>0)
	    	
	    	//Haut de la brique. Les deux conditions contradictoires de collision avec le côté de la brique doivent avoir un signe égal en plus de inférieur ou supérieur pour fonctionner. 
	    	//Pas de rayon pour la condition qui correspond à l'espace devant la collision
			  
			  { 
		  	    tabVieBr[j][i]--;
		  	    nombreBrick--;
			    vitessey=-vitessey;
			  } 
			  
		else if(tabVieBr[j][i]>0 && 
			yRond>=tabY[j][i]+largBrick && yRond-r<=tabY[j][i]+largBrick && 
			xRond-r>=tabX[j][i] && xRond+r<=tabX[j][i]+longBrick 
			&& vitessey<0) // Bas de la brique
			  { 
		  	    tabVieBr[j][i]--;
		  	    nombreBrick--;
			    vitessey=-vitessey;
			  } 
			  
		else if(tabVieBr[j][i]>0 && 
			xRond<=tabX[j][i] && xRond+r>=tabX[j][i] && 
			yRond-r>=tabY[j][i] && yRond+r<=tabY[j][i]+largBrick && 
			vitessex>0) // Côté gauche
			  { 
		  	    tabVieBr[j][i]--;
		  	    nombreBrick--;
			    vitessex=-vitessex;
			  } 
			  
		else if(tabVieBr[j][i]>0 && 
			xRond>=tabX[j][i]+longBrick && xRond-r<=tabX[j][i]+longBrick && 
			yRond>=tabY[j][i] && yRond+r<=tabY[j][i]+largBrick && 
			vitessex<0) // Côté droit
			  { 
		  	    tabVieBr[j][i]--;
		  	    nombreBrick--;
			    vitessex=-vitessex;
			  }
		
        	else if(tabVieBr[j][i]>0 && 
        		yRond<=tabY[j][i] && yRond+r>=tabY[j][i] && 
        		xRond>=tabX[j][i]+longBrick && xRond-r<=tabX[j][i]+longBrick && 
        		vitessex<0 && vitessey>0) //haut droit
             		  { 
                	    printf("%d\n",tabX[j][i]);
		  	    tabVieBr[j][i]--;
		  	    nombreBrick--;
			    vitessex=-vitessex;
			  } 
			  
		else if(tabVieBr[j][i]>0 && 
			yRond-r<=tabY[j][i]+largBrick && yRond>=tabY[j][i]+largBrick && 
			xRond>=tabX[j][i]+longBrick && xRond-r<=tabX[j][i]+longBrick && 
			vitessex<0 && vitessey<0) //bas droit
             		  { 
                	printf("%d\n",tabX[j][i]);
		  	    tabVieBr[j][i]--;
		  	    nombreBrick--;
			    vitessex=-vitessex;
			  } 
		else if(tabVieBr[j][i]>0 && 
			yRond<=tabY[j][i] && yRond+r>=tabY[j][i] && 
			xRond+r>=tabX[j][i] && xRond<=tabX[j][i] && 
			vitessex>0 && vitessey>0) //haut gauche
             		  { 
                	printf("%d\n",tabX[j][i]);
		  	    tabVieBr[j][i]--;
		  	    nombreBrick--;
			    vitessex=-vitessex;
			  } 
		else if(tabVieBr[j][i]>0 && 
			yRond-r<=tabY[j][i]+largBrick && yRond>=tabY[j][i]+largBrick && 
			xRond+r>=tabX[j][i] && xRond<=tabX[j][i] && 
			vitessex>0 && vitessey<0) //bas gauche
             		  { 
                	printf("%d\n",tabX[j][i]);
		  	    tabVieBr[j][i]--;
		  	    nombreBrick--;
			    vitessex=-vitessex;
			  } 
			  
			  
	
			    
			  }
	
	    	}
	    	
    }
    
    

/*-------------------------------Rebonds---------------------------------------*/
void Rebonds()
{

    // Rebonds sur les côtés du casse-brique

    if ((xRond>=WINDOW_WIDTH-r)||(xRond<=r))
    	{
    	vitessex=-vitessex; 
    	}
    	
    if((yRond>=WINDOW_HEIGHT-r)||(yRond<=r))
    	{
    	vitessey=-vitessey; // L'inverse de l'autre, si il est égal à -1, il fera l'inverse et inversement. 
    	}
    	
    //Rebond de la balle sur le Pad
    
    
    if(yRond+r>=yPad && yRond<=yPad  && xRond-r>=xPad && xRond<=xPad+longPad && vitessey>0)
    {
    	vitessey=-vitessey;
    		
    }
    
    
    //Les rebonds du Pad
    
    if(xPad<=0)
    	{
    	compteurPad=0;
    	xPad=1;
    	}
    
    if(xPad>=WINDOW_WIDTH-longPad)
    	{
    	compteurPad=0;
    	xPad=(WINDOW_WIDTH-longPad)-1;
    	}
    	
}

/*--------------------Vies du joueur-----------------------------*/
void vieJoueur()
{
    
    for(i=0;i<coeur;i++)
 	
    {
    
    xVie=87+i*longVie;
    changeColor(107,210,102);
    drawRect(xVie,yVie,longVie,largVie);

    }
    
    if(yRond>=WINDOW_HEIGHT-r)
    	{
    	coeur--;
    	}
   
}

/*--------------------Game Over-----------------------------*/
void gameOver()
{
    if(coeur==0)
    {
    start=0;
    sprite(0,0,"Assets/game-over.bmp");
    }
}

/*--------------------Game win-----------------------------*/
void gameWin ()
{
	if(nombreBrick==0)
	{
	sprite(0,0,"Assets/winner.bmp");
	start=0;
	}
}


void init_game(){
    

    /*---------Lancement du jeu---------*/

    start=0;
    startGame();
    
   
    /*----------Vie du joueur----------*/
    
    
   coeur=3; //Nombre de vies
   
   xVie; 
   yVie=862;
   longVie=35;
   largVie=12;
   
    
    
    /*------Création de la balle------*/
    r=20;
    xRond=WINDOW_WIDTH/2;
    yRond=WINDOW_HEIGHT-120;
    
    vitessex=5; 
    vitessey=-5;
    
    
    
    /*--------Création du Pad--------*/
    
    longPad=150;
    largPad=10;
    xPad=(WINDOW_WIDTH/2)-(longPad/2); 
    yPad=WINDOW_HEIGHT-100;
    
    compteurPad=10;
    
    /*----Définition d'une brique et de sa vie----*/
    
   longBrick=91;
   largBrick=135;
 
   xBrick; 
   yBrick;
   espaceBrick=60;

   vieBrickMax=1;
   
   
   ecartx=(WINDOW_WIDTH-(nombreColonne*longBrick+(nombreColonne-1)*espaceBrick))/2; 
   
   ecarty=150; 
  
   
   /*---------Tableau de briques----------------*/
  
  for(int i=0;i<nombreColonne;i++)
    {
    	for(int j=0;j<nombreLigne;j++)
    	 //nombre de lignes 
    	{
        xBrick=ecartx+i*(longBrick+espaceBrick);
        yBrick=ecarty+j*(largBrick+espaceBrick);
        
        tabX[j][i]=xBrick;
        tabY[j][i]=yBrick;
        
        tabVieBr[j][i]=vieBrickMax;
        
        tabCartesX[j][i]=i+1;
        tabCartesY[j][i]=j+1;
        
        nombreBrick++; //compteur pour la destruction des briques pour gagner
        
        }
    }

  
   
  
}



void drawGame(){
 
clear();


drawWallpaper();

vieJoueur();
 
drawPad();

Rebonds();

tabBrick();

drawBall();

gameWin();

gameOver();  



    	
actualize();

   
usleep(1000000 / FPS); // 60 images par seconde | 1000000 = 1 seconde 

}




void KeyPressed(SDL_Keycode touche){
    /** @brief event.key.keysym.sym renvoi la touche appuyé
     *
     */
    switch (touche) {
        
        case SDLK_q:
            //touche q appuyé
            
            printf("Q\n");
            
           compteurPad=-5;
           xPad+=compteurPad;
             
             //le x du Pad (valeur - pour dire qu'on va en arrière)
           
            break;
        case SDLK_d:
            //touche d appuyé
            printf("D\n");
            
            compteurPad=5;
            xPad+=compteurPad;
       
            break;
            
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;

        case SDLK_SPACE:
            start=1;
            
            break;

        default:
            break;
    }
}
void joyButtonPressed(){
}

void gameLoop() {
    int programLaunched = 1;
    while (programLaunched == 1) {
       
            
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // boucle pour la gestion d'évenement
            switch (event.type) {
                
                case SDL_QUIT:
                    // quand on clique sur fermer la fénêtre en haut à droite
                    programLaunched = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    /* clique de la souris
                     * event.motion.y | event.motion.x pour les positions de la souris
                     */
                    printf("position de la souris x : %d , y : %d\n", event.motion.x, event.motion.y);
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
                case SDL_JOYBUTTONDOWN:
                    break;
                default:
                    break;
            }
        }
        
         
        if(start==1)
        {
       
        drawGame();

        }
        
        
        
    }
}

int main(){
	
    /** @description 3 fonctions dans le main qui permettent de créer l'application et la maintenir ouverte :
     *  init(...) : initialiser la SDL/ fenêtre
     *  gameLoop() : boucle de jeu dans laquelle l'application reste ouverte
     *  freeAndTerminate() : quitte le programme proprement
     */
    init(WINDOW_WIDTH, WINDOW_HEIGHT);

    init_game();

    gameLoop();
    printf("Fin du programme\n");
    freeAndTerminate();
}

