#include "map.h" 
#include <iostream> 


using namespace sf;

class Character
{
private:
	float X, Y;
public:
	float x, y, w, h, dx, dy, speed;					//���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	int dir;											//����������� (direction) �������� ������
	std::string File;										//name of file with extension
	Image image;										//���� �����������
	Texture texture;									//���� ��������
	Sprite sprite;										//���� ������


	Character(std::string F, float X, float Y, float W, float H)
	{														//����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
		dx = 0; dy = 0; speed = 0; dir = 0;
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
		sprite.setPosition(x, y); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
	}

	float getPlayerPositionX()
	{
		return X;
	}

	float getPlayerPositionY()
	{
		return Y;
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


	RenderWindow window(VideoMode(600, 600), "2D Game");

	// Create Character 


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

		Hero.update(time);


		window.clear();

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ') mapSprite.setTextureRect(IntRect(681, 104, 32, 32));
				if (TileMap[i][j] == '0') mapSprite.setTextureRect(IntRect(23, 135, 32, 32));
				if (TileMap[i][j] == '1') mapSprite.setTextureRect(IntRect(21, 135, 32, 32));

				mapSprite.setPosition(j * 32, i * 32);
				window.draw(mapSprite);
			}


		window.draw(Hero.sprite);
		window.display();

	}

	return 0;
}