#include "map.h" 
#include <iostream> 
#include <sstream>
#include "view.h"


using namespace sf;

class Character
{
private:
	float x, y;
public:
	float  w, h, dx, dy, speed;					//���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int dir, playScore, health;											//����������� (direction) �������� ������
	bool life;
	std::string File;										//name of file with extension
	Image image;										//���� �����������
	Texture texture;									//���� ��������
	Sprite sprite;										//���� ������


	Character(std::string F, float X, float Y, float W, float H)
	{														//����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
		dir = 0; playScore = 0;
		dx = 0; dy = 0; speed = 0; health = 100;
		life = true;
		File = F;											//��� �����+����������
		w = W; h = H;										//������ � ������
		image.loadFromFile("Images/" + File);				//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� image.loadFromFile("images/hero/png");
		//image.createMaskFromColor(Color(41, 33, 59));		//������� �������� �����-����� ����, ��� ���� ��� ���������� �� ��������.
		texture.loadFromImage(image);						//���������� ���� ����������� � ��������
		sprite.setTexture(texture);							//�������� ������ ���������
		x = X; y = Y;										//���������� ��������� �������
		sprite.setTextureRect(IntRect(0, 0, w, h));			//������ ������� ���� ������������� ��� ������ ������ ����, � �� ���� ����� �����. IntRect - ���������� �����
	}

	void update(float time) //������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	{
		switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
		{
		case 0: dx = speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
		case 1: dx = -speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
		case 2: dx = 0; dy = speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
		case 3: dx = 0; dy = -speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
		};

		x += dx * time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
		y += dy * time;//���������� �� ������

		speed = 0;//�������� ��������, ����� �������� �����������.
		sprite.setPosition(x, y);
		interactionWithMap();//������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
		
		if (health <= 0) life = false;
	}

	float getPlayerPositionX()
	{
		return x;
	}

	float getPlayerPositionY()
	{
		return y;
	}

	void interactionWithMap()//�-��� �������������� � ������
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
			for (int j = x / 32; j < (x + w) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
			{
				if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
				{
					if (dy > 0)//���� �� ��� ����,
					{
						y = i * 32 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
					}
					if (dy < 0)
					{
						y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
					}
					if (dx > 0)
					{
						x = j * 32 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
					}
					if (dx < 0)
					{
						x = j * 32 + 32;//���������� ���� �����
					}
				}


				if (TileMap[i][j] == '1')
				{ //���� ������ ����� 's' (������)
					playScore++;//����� �� ��������... �������� ������������ �����
					TileMap[i][j] = ' ';//������� ������, ���� ����� �����. ����� � �� �������, ������.
				}



				if (TileMap[i][j] == 'm') 
				{ //���� ������ ����� 's' (������)
					health = health - 40;//����� �� ��������... �������� ������������ �����
					TileMap[i][j] = ' ';//������� ������, ���� ����� �����. ����� � �� �������, ������.
				}


				if (TileMap[i][j] == 'h')
				{ //���� ������ ����� 's' (������)
					health = health + 40;//����� �� ��������... �������� ������������ �����
					TileMap[i][j] = ' ';//������� ������, ���� ����� �����. ����� � �� �������, ������.
				}
			}
	}
};


void music()
{
	Music music;//������� ������ ������
	music.openFromFile("Audio/gambit.wav");//��������� ����
	music.play();//������������� ������
}


int main()
{


	RenderWindow window(VideoMode(640, 480), "2D Game");
	view.reset(FloatRect(0, 0, 640, 480));
	// Create Character 

	Font font; font.loadFromFile("CenturyGothic.ttf");

	Text text("", font, 20);
	text.setFillColor(Color::Black);							//???????????????????????????????????????????????????
	text.setStyle(Text::Bold);

	Image mapImage; mapImage.loadFromFile("Images/tiles.png");

	Texture map; map.loadFromImage(mapImage);
	
	Sprite mapSprite; mapSprite.setTexture(map);


	Character Hero("Birds.png", 250, 250, 48, 48);
	//Character Bird("bird.png", 250, 250, 48, 48);

	// First Character position

	float HeroCurrentFrame = 0;
	Clock clock;




	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		// For Character moving


			///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
		if (Hero.life)
		{

			if ((Keyboard::isKeyPressed(Keyboard::A)))
			{
				Hero.dir = 1; Hero.speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������. �������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
				HeroCurrentFrame += 0.0085 * time;
				if (HeroCurrentFrame > 3) HeroCurrentFrame -= 3;
				Hero.sprite.setTextureRect(IntRect(48 * int(HeroCurrentFrame), 48, 48, 48)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
			}

			if ((Keyboard::isKeyPressed(Keyboard::D))) {
				Hero.dir = 0; Hero.speed = 0.1;//����������� ������, �� ����
				HeroCurrentFrame += 0.0085 * time;
				if (HeroCurrentFrame > 3) HeroCurrentFrame -= 3;
				Hero.sprite.setTextureRect(IntRect(48 * int(HeroCurrentFrame), 96, 48, 48)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)

			}

			if ((Keyboard::isKeyPressed(Keyboard::W))) {
				Hero.dir = 3; Hero.speed = 0.1;//����������� ����, �� ����
				HeroCurrentFrame += 0.0085 * time;
				if (HeroCurrentFrame > 3) HeroCurrentFrame -= 3;
				Hero.sprite.setTextureRect(IntRect(48 * int(HeroCurrentFrame), 144, 48, 48)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)

			}

			if ((Keyboard::isKeyPressed(Keyboard::S)))
			{ //���� ������ ������� ������� ����� ��� ���� ����� �
				Hero.dir = 2; Hero.speed = 0.1;//����������� �����, �� ����
				HeroCurrentFrame += 0.0085 * time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
				if (HeroCurrentFrame > 3) HeroCurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
				Hero.sprite.setTextureRect(IntRect(48 * int(HeroCurrentFrame), 0, 48, 48)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96

			}
		}
		playerPosition(Hero.getPlayerPositionX(), Hero.getPlayerPositionY());
		Hero.update(time);

		//changeview();
		viewMap(time);
		window.setView(view);
		window.clear(Color(87, 113, 156));

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ') mapSprite.setTextureRect(IntRect(681, 104, 32, 32));
				if (TileMap[i][j] == '0') mapSprite.setTextureRect(IntRect(23, 135, 32, 32));
				if (TileMap[i][j] == '1') mapSprite.setTextureRect(IntRect(310, 80, 32, 32));
				if (TileMap[i][j] == 'm') mapSprite.setTextureRect(IntRect(360, 80, 32, 32));
				if (TileMap[i][j] == 'h') mapSprite.setTextureRect(IntRect(335, 160, 32, 32));

				mapSprite.setPosition(j * 32, i * 32);
				window.draw(mapSprite);
			}

		std::ostringstream playerHealthString;    // �������� ����������
		playerHealthString << Hero.health;		//������� � ��� ����� �����, �� ���� ��������� ������
		text.setString("Health: " + playerHealthString.str());//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 
		text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);//������ ������� ������, �������� �� ������ ������
		window.draw(text);//����� ���� �����


		window.draw(Hero.sprite);
		window.display();

	}

	return 0;
}