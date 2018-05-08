// main.cpp : Defines the entry point for the windows application.
// SFML Game: Breakout
// Gameplay features: Level Design, Collision Detection, Vector Math, Score Calcualation
// Author: Shweta Patil
// Copyright: Shweta Patil © 2018
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

void update_state(float dt);
void render_frame();

sf::RenderWindow window(sf::VideoMode(800, 600), "Breakout");
sf::Vector2f velocity(100, 300);

sf::Texture tex;
sf::Texture brstr;
sf::Texture brwk;

sf::SoundBuffer buf;
sf::Sound sound;

sf::SoundBuffer wallbuf;
sf::Sound wallsound;

sf::SoundBuffer paddlebuf;
sf::Sound paddlesound;

sf::SoundBuffer damagebuf;
sf::Sound damagesound;

sf::SoundBuffer destroybuf;
sf::Sound destroysound;

sf::SoundBuffer scorebuf;
sf::Sound scoresound;

sf::SoundBuffer lifebuf;
sf::Sound lifesound;

sf::SoundBuffer winbuf;
sf::Sound winsound;

sf::SoundBuffer losebuf;
sf::Sound losesound;

sf::Font font;

sf::RectangleShape background;

int playerscore = 0;
int computerscore = 0;
int life = 3;
bool pause = false;
bool start = true;
int level = 1;

sf::Texture damaged;

class Ball;
class Brick;

class Paddle
{
	private:
		sf::Vector2f position;
		sf::Vector2f origin;
		sf::Vector2f size;
		sf::RectangleShape paddle;
		bool lose;
		bool win;
	public:
		void track(Ball ball, float dt);
		void update(float dt);
		sf::Vector2f getposition();
		void setposition(sf::Vector2f position);
		sf::Vector2f getorigin();
		void setorigin(sf::Vector2f origin);
		sf::Vector2f getsize();
		void setsize(sf::Vector2f size);
		void setfillcolor(sf::Color color);
		sf::RectangleShape getshape();
		void setlose();
		void setwin();
		void resetlose();
		void resetwin();
		bool getlose();
		bool getwin();
};

class Ball
{
	private:
		sf::Vector2f position;
		sf::Vector2f origin;
		sf::Vector2f radius;
		sf::CircleShape ball;

	public:
		void track(Paddle paddle, Paddle computer);
		void trace(Paddle computer, float dt);
		void update(Paddle player, float dt);
		sf::Vector2f getposition();
		void setposition(sf::Vector2f position);
		sf::Vector2f getorigin();
		void setorigin(sf::Vector2f origin);
		float getradius();
		void setradius(float radius);
		void setfillcolor(sf::Color color);
		sf::CircleShape getshape();
};

class Brick
{
	private:
		sf::Vector2f position;
		sf::Vector2f origin;
		sf::Vector2f size;
		sf::RectangleShape brick;
		bool weak;
		bool strong;
		bool broken;
		bool destroyed;
	public:
		void track(Ball ball, float dt);
		void update(float dt);
		sf::Vector2f getposition();
		void setposition(sf::Vector2f position);
		sf::Vector2f getorigin();
		void setorigin(sf::Vector2f origin);
		sf::Vector2f getsize();
		void setsize(sf::Vector2f size);
		void setfillcolor(sf::Color color);
		void settexture(sf::Texture *tex);
		sf::RectangleShape getshape();
		void setbroken();
		void setdestroyed();
		void resetbroken();
		void resetdestroyed();
		bool getlbroken();
		bool getdestroyed();
};

void Paddle::track(Ball ball, float dt)
{
	sf::Vector2f paddlepos = paddle.getPosition();
	sf::Vector2f ballpos = ball.getposition();
	if (ballpos.x > 400)
	{
		if (ballpos.y < 300)
		{
			ball.setfillcolor(sf::Color::Green);
			
			paddlepos.y -= paddlepos.y*dt;

			if (paddlepos.y <= 100)
			{
				paddle.setFillColor(sf::Color::Red);
				paddlepos.y = 100;
			}
			else
			{
				paddle.setFillColor(sf::Color::Cyan);
			}

			paddle.setPosition(paddlepos);
		}

		if (ballpos.y > 300)
		{
			{
				ball.setfillcolor(sf::Color::Blue);
				
				paddlepos.y += paddlepos.y*dt;

				if (paddlepos.y >= 500)
				{
					paddle.setFillColor(sf::Color::Yellow);
					paddlepos.y = 500;
				}
				else
				{
					paddle.setFillColor(sf::Color::Cyan);
				}

				paddle.setPosition(paddlepos);
			}
		}
	}
}

void Paddle::update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		sf::Vector2f paddlepos = paddle.getPosition();

		paddlepos.x -= paddlepos.x*dt * 5;
		if (paddlepos.x <= 100)
		{
			paddle.setFillColor(sf::Color::Red);
			paddlepos.x = 100;
		}
		else
		{
			paddle.setFillColor(sf::Color::Cyan);
		}

		paddle.setPosition(paddlepos);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sf::Vector2f paddlepos = paddle.getPosition();

		paddlepos.x += paddlepos.x*dt * 5;
		if (paddlepos.x >= 700)
		{
			paddle.setFillColor(sf::Color::Yellow);
			paddlepos.x = 700;
		}
		else
		{
			paddle.setFillColor(sf::Color::Cyan);
		}

		paddle.setPosition(paddlepos);
	}
}

sf::Vector2f Paddle::getposition()
{
	return paddle.getPosition();
}

void Paddle::setposition(sf::Vector2f position)
{
	paddle.setPosition(position);
	this->position = position;
}

sf::Vector2f Paddle::getorigin()
{
	return paddle.getOrigin();
}

void Paddle::setorigin(sf::Vector2f origin)
{
	paddle.setOrigin(origin);
}

sf::Vector2f Paddle::getsize()
{
	return paddle.getSize();
}

void Paddle::setsize(sf::Vector2f size)
{
	paddle.setSize(size);
}

void Paddle::setfillcolor(sf::Color color)
{
	paddle.setFillColor(color);
}

sf::RectangleShape Paddle::getshape()
{
	return paddle;
}

void Paddle::setlose()
{
	lose = true;
}

void Paddle::setwin()
{
	win = true;
}

void Paddle::resetlose()
{
	lose = false;
}

void Paddle::resetwin()
{
	win = false;
}

bool Paddle::getlose()
{
	return lose;
}

bool Paddle::getwin()
{
	return win;
}

void Ball::track(Paddle player, Paddle computer)
{
	if (position.x < 0)
	{
		player.setlose();
		computer.setwin();
		++computerscore;
		setposition(sf::Vector2f(450, 300));
		velocity.x = 100;
		velocity.y = 300;
	}

	if (position.x > 800)
	{
		player.setwin();
		computer.setlose();
		++playerscore;
		setposition(sf::Vector2f(400, 300));
		velocity.x = 100;
		velocity.y = 300;
	}
}

void Ball::update(Paddle player, float dt)
{
	position += velocity * dt;

	if (position.y > window.getSize().y && velocity.y > 0)
	{
		ball.setFillColor(sf::Color::White);
		
		setposition(sf::Vector2f(400, 525));

		lifesound.play();
		--life;
		start = true;
	}

	if (position.y < 0 && velocity.y < 0)
	{
		ball.setFillColor(sf::Color::White);
		velocity.y = -velocity.y;
		wallsound.play();
	}

	if (position.x > 800 && velocity.x > 0)
	{
		ball.setFillColor(sf::Color::White);
		velocity.x = -velocity.x;
		paddlesound.play();
	}

	if (position.x < 0 && velocity.x < 0)
	{
		ball.setFillColor(sf::Color::White);
		velocity.x = -velocity.x;
		wallsound.play();
	}

	if ((100 + 20) >= abs(player.getposition().x - position.x) && (15 + 20) >= abs(player.getposition().y - position.y) && velocity.y > 0)
	{
		int l = sqrt((position.x - player.getposition().x)*(position.x - player.getposition().x) + (position.y - player.getposition().y + 100)*(position.y - player.getposition().y + 100));
		sf::Vector2f dir(((position.x - player.getposition().x) / l), ((position.y - player.getposition().y + 100) / l));
		ball.setFillColor(sf::Color::Red);

		int velenght = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
		velocity.x = -velenght*dir.x*1.f;
		velocity.y = -velenght*dir.y*1.f;

		paddlesound.play();
	}

	velocity.y += 5 * dt;

	ball.setPosition(position);
}

sf::Vector2f Ball::getposition()
{
	return ball.getPosition();
}

void Ball::setposition(sf::Vector2f position)
{
	ball.setPosition(position);
	this->position = position;
}

sf::Vector2f Ball::getorigin()
{
	return ball.getOrigin();
}

void Ball::setorigin(sf::Vector2f origin)
{
	ball.setOrigin(origin);
}

float Ball::getradius()
{
	return ball.getRadius();
}

void Ball::setradius(float radius)
{
	ball.setRadius(radius);
}

void Ball::setfillcolor(sf::Color color)
{
	ball.setFillColor(color);
}

sf::CircleShape Ball::getshape()
{
	return ball;
}

void Brick::track(Ball ball, float dt)
{
	if (destroyed == 0 && (50 + 20) >= abs(ball.getposition().x - position.x) && (15 + 20) >= abs(ball.getposition().y - position.y))
	{
		int l = sqrt((position.x - ball.getposition().x)*(position.x - ball.getposition().x) + (position.y - ball.getposition().y + 0)*(position.y - ball.getposition().y + 0));
		sf::Vector2f dir(((position.x - ball.getposition().x) / l), ((position.y - ball.getposition().y + 0) / l));
		ball.setfillcolor(sf::Color::Green);

		int velenght = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
		velocity.x = -velenght*dir.x*1.f;
		velocity.y = -velenght*dir.y*1.f;

		{
			if (broken == 0) //strong brick
			{
				damaged.loadFromFile("broken.png"); //brick broken
												
				brick.setTexture(&damaged);
				broken = 1;
				++playerscore;
				++playerscore;
				damagesound.play();
			}
			else
			if (broken == 1) // weak brick
			{
				destroyed = 1;
				++playerscore;
				destroysound.play();
			}
		}

		scoresound.play();
	}
}

sf::Vector2f Brick::getposition()
{
	return brick.getPosition();
}

void Brick::setposition(sf::Vector2f position)
{
	brick.setPosition(position);
	this->position = position;
}

sf::Vector2f Brick::getorigin()
{
	return brick.getOrigin();
}

void Brick::setorigin(sf::Vector2f origin)
{
	brick.setOrigin(origin);
}

sf::Vector2f Brick::getsize()
{
	return brick.getSize();
}

void Brick::setsize(sf::Vector2f size)
{
	brick.setSize(size);
}

void Brick::setfillcolor(sf::Color color)
{
	brick.setFillColor(color);
}

void Brick::settexture(sf::Texture *tex)
{
	brick.setTexture(tex);
}

sf::RectangleShape Brick::getshape()
{
	return brick;
}

void Brick::setbroken()
{
	weak = 1;
	broken = 1;
}

void Brick::setdestroyed()
{
	destroyed = 1;
}

void Brick::resetbroken()
{
	strong = 1;
	broken = 0;
}

void Brick::resetdestroyed()
{
	destroyed = 0;
}

bool Brick::getlbroken()
{
	return broken;
}

bool Brick::getdestroyed()
{
	return destroyed;
}

Paddle player;
Ball ball;
Brick brick[2];
Brick brickstructure[23];
int winner = 0;
sf::Text text;
sf::Text playerscoretext;
sf::Text lifetext;
sf::Text leveltext;
bool end = false;
bool win = false;

void arrangebricks(int level)
{
	switch (level)
	{
		case 1:
			for (int i = 0; i < 23; i++)
			{
				brickstructure[i].setsize(sf::Vector2f(100, 30));
				brickstructure[i].setorigin(sf::Vector2f(50, 15));
				brickstructure[i].resetdestroyed();
			}

			brickstructure[0].setposition(sf::Vector2f(200, 110));
			brickstructure[0].setbroken(); //weak brick
			brickstructure[0].settexture(&brwk);

			for (int i = 1; i < 5; i++)
			{
				brickstructure[i].setposition(sf::Vector2f(brickstructure[i - 1].getposition().x + 110, brickstructure[i - 1].getposition().y));
				brickstructure[i].setbroken(); //weak brick
				brickstructure[i].settexture(&brwk);
			}

			brickstructure[5].setposition(sf::Vector2f(250, 150));
			brickstructure[5].resetbroken(); //strong brick
			brickstructure[5].settexture(&brstr);

			for (int i = 6; i < 9; i++)
			{
				brickstructure[i].setposition(sf::Vector2f(brickstructure[i - 1].getposition().x + 110, brickstructure[i - 1].getposition().y));
				brickstructure[i].resetbroken(); //strong brick
				brickstructure[i].settexture(&brstr);
			}

			brickstructure[9].setposition(sf::Vector2f(200, 190));
			brickstructure[9].setbroken(); //weak brick
			brickstructure[9].settexture(&brwk);

			for (int i = 10; i < 14; i++)
			{
				brickstructure[i].setposition(sf::Vector2f(brickstructure[i - 1].getposition().x + 110, brickstructure[i - 1].getposition().y));
				brickstructure[i].setbroken(); //weak brick
				brickstructure[i].settexture(&brwk);
			}

			brickstructure[14].setposition(sf::Vector2f(250, 230));
			brickstructure[14].resetbroken(); //strong brick
			brickstructure[14].settexture(&brstr);

			for (int i = 15; i < 18; i++)
			{
				brickstructure[i].setposition(sf::Vector2f(brickstructure[i - 1].getposition().x + 110, brickstructure[i - 1].getposition().y));
				brickstructure[i].resetbroken(); //weak brick
				brickstructure[i].settexture(&brstr);
			}

			brickstructure[18].setposition(sf::Vector2f(300, 270));
			brickstructure[18].resetbroken(); //strong brick
			brickstructure[18].settexture(&brstr);

			for (int i = 19; i < 21; i++)
			{
				brickstructure[i].setposition(sf::Vector2f(brickstructure[i - 1].getposition().x + 110, brickstructure[i - 1].getposition().y));
				brickstructure[i].resetbroken(); //strong brick
				brickstructure[i].settexture(&brstr);
			}

			brickstructure[21].setposition(sf::Vector2f(350, 310));
			brickstructure[21].setbroken(); //weak brick
			brickstructure[21].settexture(&brwk);

			for (int i = 22; i < 23; i++)
			{
				brickstructure[i].setposition(sf::Vector2f(brickstructure[i - 1].getposition().x + 110, brickstructure[i - 1].getposition().y));
				brickstructure[i].setbroken(); //weak brick
				brickstructure[i].settexture(&brwk);
			}
			break;

		case 2:
			for (int i = 0; i < 23; i++)
			{
				brickstructure[i].setsize(sf::Vector2f(100, 30));
				brickstructure[i].setorigin(sf::Vector2f(50, 15));
				brickstructure[i].resetdestroyed();
			}

			brickstructure[0].setposition(sf::Vector2f(100, 110));
			brickstructure[0].resetbroken(); //strong brick
			brickstructure[0].settexture(&brstr);

			for (int i = 1; i < 5; i++)
			{
				brickstructure[i].setposition(sf::Vector2f(brickstructure[i - 1].getposition().x + 150, brickstructure[i - 1].getposition().y));
				brickstructure[i].resetbroken(); //strong brick
				brickstructure[i].settexture(&brstr);
			}

			brickstructure[5].setposition(sf::Vector2f(150, 150));
			brickstructure[5].resetbroken(); //strong brick
			brickstructure[5].settexture(&brstr);

			for (int i = 6; i < 9; i++)
			{
				brickstructure[i].setposition(sf::Vector2f(brickstructure[i - 1].getposition().x + 150, brickstructure[i - 1].getposition().y));
				brickstructure[i].resetbroken(); //strong brick
				brickstructure[i].settexture(&brstr);
			}

			brickstructure[9].setposition(sf::Vector2f(200, 190));
			brickstructure[9].setbroken(); //weak brick
			brickstructure[9].settexture(&brwk);

			for (int i = 10; i < 14; i++)
			{
				brickstructure[i].setposition(sf::Vector2f(brickstructure[i - 1].getposition().x + 110, brickstructure[i - 1].getposition().y));
				brickstructure[i].setbroken(); //weak brick
				brickstructure[i].settexture(&brwk);
			}

			brickstructure[14].setposition(sf::Vector2f(250, 230));
			brickstructure[14].setbroken(); //weak brick
			brickstructure[14].settexture(&brwk);

			for (int i = 15; i < 18; i++)
			{
				brickstructure[i].setposition(sf::Vector2f(brickstructure[i - 1].getposition().x + 110, brickstructure[i - 1].getposition().y));
				brickstructure[i].setbroken(); //weak brick
				brickstructure[i].settexture(&brwk);
			}

			brickstructure[18].setposition(sf::Vector2f(200, 270));
			brickstructure[18].resetbroken(); //strong brick
			brickstructure[18].settexture(&brstr);

			for (int i = 19; i < 21; i++)
			{
				brickstructure[i].setposition(sf::Vector2f(brickstructure[i - 1].getposition().x + 200, brickstructure[i - 1].getposition().y));
				brickstructure[i].resetbroken(); //strong brick
				brickstructure[i].settexture(&brstr);
			}

			brickstructure[21].setposition(sf::Vector2f(300, 320));
			brickstructure[21].resetbroken(); //strong brick
			brickstructure[21].settexture(&brstr);

			for (int i = 22; i < 23; i++)
			{
				brickstructure[i].setposition(sf::Vector2f(brickstructure[i - 1].getposition().x + 200, brickstructure[i - 1].getposition().y));
				brickstructure[i].resetbroken(); //strong brick
				brickstructure[i].settexture(&brstr);
			}
			break;
	}
}

int main()
{
	std::string score;
	sf::Clock clock;
	tex.loadFromFile("pongback.png"); //background 
	brstr.loadFromFile("tough.png"); //brick strong
	brwk.loadFromFile("basic.png"); //brick weak

	wallbuf.loadFromFile("wall.wav");
	wallsound.setBuffer(wallbuf);

	paddlebuf.loadFromFile("paddle.wav");
	paddlesound.setBuffer(paddlebuf);

	damagebuf.loadFromFile("damage.wav");
	damagesound.setBuffer(damagebuf);

	destroybuf.loadFromFile("destroy.wav");
	destroysound.setBuffer(destroybuf);

	scorebuf.loadFromFile("score.mp3");
	scoresound.setBuffer(scorebuf);

	lifebuf.loadFromFile("life.wav");
	lifesound.setBuffer(lifebuf);

	winbuf.loadFromFile("win.flac");
	winsound.setBuffer(winbuf);

	losebuf.loadFromFile("lose.wav");
	losesound.setBuffer(losebuf);

	font.loadFromFile("arial.TTF");

	background.setSize(sf::Vector2f(800, 600));
	background.setPosition(0, 0);
	background.setTexture(&tex);

	ball.setradius(20.f);
	ball.setorigin(sf::Vector2f(20, 20));
	ball.setposition(sf::Vector2f(450, 525));
	ball.setfillcolor(sf::Color::White);

	player.setsize(sf::Vector2f(200, 30));
	player.setorigin(sf::Vector2f(100, 15));
	player.setposition(sf::Vector2f(400, 560));
	player.setfillcolor(sf::Color::Cyan);

	brick[0].resetdestroyed();
	brick[0].resetbroken(); //strong
	brick[0].setsize(sf::Vector2f(100, 30));
	brick[0].setorigin(sf::Vector2f(50, 15));
	brick[0].setposition(sf::Vector2f(400, 450));
	brick[0].settexture(&brstr);

	brick[1].resetdestroyed();
	brick[1].setbroken(); //weak
	brick[1].setsize(sf::Vector2f(100, 30));
	brick[1].setorigin(sf::Vector2f(50, 15));
	brick[1].setposition(sf::Vector2f(400, 400));
	brick[1].settexture(&brwk);

	//Structure of bricks
	arrangebricks(level);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		text.setFont(font);
		text.setCharacterSize(50);
		score = "Breakout";
		text.setString(score);
		text.setColor(sf::Color::Green);
		text.setPosition(300, 20);//player 

		float dt = clock.restart().asSeconds();

		if (!pause)
		{
			update_state(dt);
			render_frame();
			window.display();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && pause == true)
		{
			pause = false;

			start = false;

			if (win == true)
			{
				if (level == 1)
					level = 2;
				else
					level = 1;
				win = false;
			}

			if (end == true)
			{
				life = 3;
				playerscore = 0;

				//Reset destroy and damage values for bricks
				brick[0].resetdestroyed();
				brick[0].resetbroken(); //strong
				brick[1].resetdestroyed();
				brick[1].setbroken(); //weak

				arrangebricks(level);
			}

			end = false;
		}
	}
	return 0;
}

void update_state(float dt)
{
	if (!start)
		ball.update(player, dt);
	brick[0].track(ball, dt);
	brick[1].track(ball, dt);
	for (int i = 0; i < 23; i++)
		brickstructure[i].track(ball, dt);

	player.update(dt);

	playerscoretext.setFont(font);
	playerscoretext.setCharacterSize(30);
	std::string s = "SCORE: ";
	s += std::to_string(playerscore);
	playerscoretext.setString(s);
	playerscoretext.setColor(sf::Color::Yellow);
	playerscoretext.setPosition(50, 500);

	lifetext.setFont(font);
	lifetext.setCharacterSize(30);
	std::string li = "LIFE: ";
	li += std::to_string(life);
	lifetext.setString(li);
	lifetext.setColor(sf::Color::Red);
	lifetext.setPosition(650, 500);

	leveltext.setFont(font);
	leveltext.setCharacterSize(40);
	std::string le = "LEVEL: ";
	le += std::to_string(level);
	leveltext.setString(le);
	leveltext.setColor(sf::Color::Magenta);
	leveltext.setPosition(30, 20);

	if (end)
	{
		pause = true;
	}

	if (start)
	{
		player.setfillcolor(sf::Color::Cyan);

		player.setposition(sf::Vector2f(400, 560));
		pause = true;
	}
}

void render_frame()
{
	{
		window.clear();
		window.draw(background);
	
		if (!(brick[0].getdestroyed()))
			window.draw(brick[0].getshape());
		if (!(brick[1].getdestroyed()))
			window.draw(brick[1].getshape());
		for (int i = 0; i < 23; i++)
			if (!(brickstructure[i].getdestroyed()))
				window.draw(brickstructure[i].getshape());
		window.draw(ball.getshape());
		window.draw(player.getshape());

		switch (life)
		{
		case 0: text.setString("Game Over");
			end = true;
			player.setfillcolor(sf::Color::Cyan);
			ball.setposition(sf::Vector2f(450, 525));
			player.setposition(sf::Vector2f(400, 560));
			win = false;
			velocity.x = 100;
			velocity.y = 300;
			losesound.play();
			break;
		}
		if (playerscore > 48 && level == 1)
		{
			text.setString("Congratulations!!!");
			end = true;
			win = true;
			player.setfillcolor(sf::Color::Cyan);
			ball.setposition(sf::Vector2f(450, 525));
			player.setposition(sf::Vector2f(400, 560));
			velocity.x = 150;
			velocity.y = 350;
			winsound.play();
		}
		else
		if (playerscore > 54 && level == 2)
		{

			text.setString("Congratulations!!!");
			end = true;
			win = true;
			player.setfillcolor(sf::Color::Cyan);
			ball.setposition(sf::Vector2f(450, 525));
			player.setposition(sf::Vector2f(400, 560));
			velocity.x = 100;
			velocity.y = 300;
			winsound.play();
		}
		window.draw(playerscoretext);
		window.draw(lifetext);
		window.draw(leveltext);
		window.draw(text);
	}
}