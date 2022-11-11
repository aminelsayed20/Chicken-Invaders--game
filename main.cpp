#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <vector>
#include <deque>
#include <cmath>
#include <ctime>
#include <SFML/Audio.hpp>


using namespace sf;
using namespace std;

struct chicken{
  // dimensions
  int x, y;

  bool life = true;
  Sprite ch;
  int frame=0;
  int cnt=1;
};


/// data structures

chicken army[5][15];                    // create array army to storage chicken

deque<Sprite> guns;                    // create DeQue to storage guns

vector<Sprite> eggs;                   // create vector to storage eggs

vector<pair<Sprite, long long>> beggs; //create vector of pair to storage broken eggs and time

vector<Sprite> hearts(50);             // create vector to storage hearts




Texture  chickenImage, ship, gunImage,     /// Textures
         bomch, bomship, eggImage,
         heartImage, loseImage, background,
         eggb, greench;

Sprite   ch, shp,                         ///Sprites
         gun, bch, bshp,
         egg, heart,
         lose, bg,
         egb, gch;


void loadAnimations ()
{
    chickenImage.loadFromFile("image/chickenRed-removebg-preview.png");
    ship.loadFromFile("image/ship1.png");
    gunImage.loadFromFile("image/b1.png");
    bomch.loadFromFile("image/cartoon-explosion-fire-effect-effect-boom-vector-28473340-removebg-preview.png");
    bomship.loadFromFile("image/boomship.png");
    eggImage.loadFromFile("image/egg.png");
    heartImage.loadFromFile("image/heart.png");
    loseImage.loadFromFile("image/lose.png");
    background.loadFromFile("image/night-starry-sky-beautiful-space-with-nebula-abstract-background-with-stars-space_105386-140.jpg");
    eggb.loadFromFile("image/eggBreak1.png");
    greench.loadFromFile("image/chickenGreen.png");
    ///path for dynamic background
    //ezgif.com-gif-maker (5).png

    ch.setTexture(chickenImage);
     shp.setTexture(ship);
     gun.setTexture(gunImage), bch.setTexture(bomch), bshp.setTexture(bomship),
    egg.setTexture(eggImage), heart.setTexture(heartImage),
    lose.setTexture(loseImage), bg.setTexture(background),
    egb.setTexture(eggb), gch.setTexture(greench);


    shp.setScale(3,3);
    ch.setScale(1.2,1.2);
    gun.setScale(2.5, 2.5);
    egg.setScale(2,2);
    shp.setOrigin(25, 25);
    lose.setPosition(600, 300);
    bg.setPosition(0,0);
    bg.setScale(3,3);
}



void initArmyOfChicken ()
{
         for (int i=0,ych=70 ; i<5 ; ++i, ych+=70)
         for (int j=0, xch=250 ; j<15 ; ++j, xch+=80)
         {
            army[i][j].x = xch;
            army[i][j].y= ych;
            army[i][j].life = true;
            army[i][j].ch.setTexture(chickenImage);
            army[i][j].frame = rand()%10;
         }
}

void initPositionHearts(int countHearts)
{
          for (int i=0, j= 100, k=30 ; i<countHearts ; ++i, j+=50)
        hearts[i].setTexture(heartImage), hearts[i].setPosition(j, k);
}

int main()
{
    srand(time(0));
    // Create the main window
    RenderWindow app(VideoMode(1700, 950), "SFML window");

         // Frames Control
        app.setFramerateLimit(60);

    // variables
        // for animation
     int dx = 3;
    int  b1=0, b2=0, a1=0, a2=0; // controlling ->frames
     long long cnt = 0; // for controlling-> speed and time
     int countHearts =3; // count -> hearts
    long long tim ;
    bool gameOver=false, win =false, level2 = false, damage_ship = false;
    /////////////////////////////////////////////////////////////////

    // Load a sprite to display
       loadAnimations ();


    // initialization army of chicken
     initArmyOfChicken ();

    // initialization positions of hearts
    initPositionHearts(countHearts);


	// Start the game loop
    while (app.isOpen())
    {
                // Process events
        Event ev;
        if (gameOver)
        {
                    while (app.pollEvent(ev))
        {
            // Close window : exit
            if (ev.type == sf::Event::Closed)
                app.close();

                    if (ev.type == Event::MouseButtonPressed)
         if (ev.mouseButton.button == Mouse::Left)
            gameOver = false;
        }
        countHearts = 3;
       initArmyOfChicken();
        eggs.clear(), guns.clear(), beggs.clear();

           app.clear();
           app.draw(bg);
           app.draw(lose);
           app.display();

        }
       if (!gameOver)
        {

       cnt++;
        while (app.pollEvent(ev))
        {
            // Close window : exit
            if (ev.type == sf::Event::Closed)
                app.close();

                    // to hide Mouse
        if (Mouse::getPosition().x>0 and Mouse::getPosition().x < 1700
            and Mouse::getPosition().y >0 and Mouse::getPosition().y <950)
            app.setMouseCursorVisible(false);

                // for Shooting
        if (ev.type == Event::MouseButtonPressed)
         if (ev.mouseButton.button == Mouse::Left)
         {
             Sprite gun(gunImage);
             gun.setPosition(Mouse::getPosition().x-140, 800);
             gun.setScale(2.5, 2.5);
            guns.push_back(gun);
         }
                   // for moving
         if (ev.type == sf::Event::MouseMoved)
             {
                  shp.setPosition (ev.mouseMove.x,800);
             }


        }
        if (cnt%100 == 0) // random eggs
        {
            int randx = rand()%5;
            int randy =rand()%15;
            if (army[randx][randy].life)
           egg.setPosition(army[randx][randy].x, army[randx][randy].y),
           eggs.push_back(egg);
        }


             if (cnt%10 ==0)// for control speed of ship
             {
                 b1+=42;
                 if (damage_ship and b1>168)b1=0;
                 if(!damage_ship and b1 >83) b1=0;

                         a1+=636;
               if (a1>14620) a1=0;
             }

             if (cnt%4 ==0) // for control speed of chicken
         for (int i=0 ;i<5 ; ++i) for (int j=0 ; j<15 ; ++j)
         {
             army[i][j].frame++;
             if (army[i][j].frame==10) army[i][j].frame=0;
         }


          if (army[0][0].x<2 or army[0][14].x>=1660 ) dx*=-1;// move the chicken
        for (int i=0 ;i<5 ; ++i) for (int j=0 ; j<15 ; ++j) army[i][j].x+=dx;

        for (int i=0 ; i<guns.size() ; ++i)// move gun
        {
            guns[i].move(0,-3);
        }
        for (int i=0 ; i<eggs.size() ; ++i) // move eggs
            eggs[i].move(0,3);

         /////////////////////////////////////////////////////////////////////////////


                 // for Shoot the chicken
        for (int i=0 ; i<5 ; ++i) for (int j=0; j<15 ; ++j)
        {
            if (army[i][j].life)
            for (int k=0 ; k<guns.size() ; ++k)
              if (army[i][j].ch.getGlobalBounds().intersects(guns[k].getGlobalBounds()))
              {
                   guns[k].setPosition(3000,3000);
                  if(level2)
                  {
                      army[i][j].cnt--;
                      if (army[i][j].cnt<=0)
                        army[i][j].life = false;
                  }
                  else
                army[i][j].life = false, guns[k].setPosition(3000,3000);
              }
        }


        // for delete gun
        for (int i=0 ; i<guns.size() ; ++i)
            if (guns[i].getPosition().y<0)
            guns.pop_front();

      for (int i=0 ; i<eggs.size() ; ++i)
      {
          if (eggs[i].getPosition().y >850)
          {
              egb.setPosition(eggs[i].getPosition().x,eggs[i].getPosition().y );

              eggs[i].setPosition(3000, 3000);
              beggs.push_back({egb, time(0)});

          }


      }


      //bg.setTextureRect(IntRect(a1,0,636,356));   --->turn on this for dynamic background
      shp.setTextureRect(IntRect(b1,b2,42,52));


             long long t = time(0);

               if (t>tim)
                 for (int i=0 ; i<eggs.size() ; ++i)
                if (shp.getGlobalBounds().intersects (eggs[i].getGlobalBounds()))
                     {  tim = t +1; countHearts--, damage_ship = true ;break;}



                /// if win
                 bool wn = true;
                for (int i=0 ; i<5 ; ++i) for (int j=0 ; j<15 ; ++j) if (army[i][j].life)wn=false;
                if (wn) win = true;
                if (win)
                {
                    for (int i=0 ; i<5 ; ++i) for (int j=0 ; j<15 ; ++j) army[i][j].ch.setTexture(greench),
                        army[i][j].life = true,army[i][j].cnt=2;
                    win = false;
                    level2 = true;
                }

        long long tt= time(0);

       if (damage_ship)
        shp.setTexture(bomship), tim = tt+2, damage_ship = false;

        if (tt>=tim)
        {
            damage_ship= false;
            shp.setTexture(ship);
        }

        if (!countHearts)
        {
           gameOver = true;
        }


        // Clear screen
        app.clear();

        /// draws
         app.draw(bg);

          // draw the army of chicken
         for (int i=0 ; i<5 ; ++i)
         {
             for (int j=0; j<15 ; ++j)
             {
                 army[i][j].ch.setTextureRect(IntRect(army[i][j].frame *57,a2,57,50));
                 army[i][j].ch.setPosition(army[i][j].x,army[i][j].y);
                 if (army[i][j].life)
                 app.draw(army[i][j].ch);
             }
         }

                for (int i=0 ; i<beggs.size() ; ++i)
            if (beggs[i].second+5>(time(0)))
                app.draw(beggs[i].first);


        for (int i=0 ; i<guns.size() ; ++i)
            app.draw(guns[i]);

        for (int i=0 ; i<eggs.size() ; ++i)
                app.draw(eggs[i]);


        for (int i=0 ; i<countHearts;++i)
       {
           app.draw(hearts[i]);
       }

       app.draw(shp);

        // Update the window
        app.display();
        }
    }


    return EXIT_SUCCESS;
}
