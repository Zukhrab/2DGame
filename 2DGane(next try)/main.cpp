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
	float  w, h, dx, dy, speed;					//координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir, playScore, health;											//направление (direction) движения игрока
	bool life;
	std::string File;										//name of file with extension
	Image image;										//сфмл изображение
	Texture texture;									//сфмл текстура
	Sprite sprite;										//сфмл спрайт


	Character(std::string F, float X, float Y, float W, float H)
	{														//Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		dir = 0; playScore = 0;
		dx = 0; dy = 0; speed = 0; health = 100;
		life = true;
		File = F;											//имя файла+расширение
		w = W; h = H;										//высота и ширина
		image.loadFromFile("Images/" + File);				//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
		//image.createMaskFromColor(Color(41, 33, 59));		//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
		texture.loadFromImage(image);						//закидываем наше изображение в текстуру
		sprite.setTexture(texture);							//заливаем спрайт текстурой
		x = X; y = Y;										//координата появления спрайта
		sprite.setTextureRect(IntRect(0, 0, w, h));			//Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
	}

	void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
		case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
		case 2: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
		case 3: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
		};

		x += dx * time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
		y += dy * time;//аналогично по игреку

		speed = 0;//зануляем скорость, чтобы персонаж остановился.
		sprite.setPosition(x, y);
		interactionWithMap();//выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
		
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

	void interactionWithMap()//ф-ция взаимодействия с картой
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
			for (int j = x / 32; j < (x + w) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
			{
				if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
				{
					if (dy > 0)//если мы шли вниз,
					{
						y = i * 32 - h;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
					}
					if (dy < 0)
					{
						y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
					}
					if (dx > 0)
					{
						x = j * 32 - w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
					}
					if (dx < 0)
					{
						x = j * 32 + 32;//аналогично идем влево
					}
				}


				if (TileMap[i][j] == '1')
				{ //если символ равен 's' (камень)
					playScore++;//какое то действие... например телепортация героя
					TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
				}



				if (TileMap[i][j] == 'm') 
				{ //если символ равен 's' (камень)
					health = health - 40;//какое то действие... например телепортация героя
					TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
				}


				if (TileMap[i][j] == 'h')
				{ //если символ равен 's' (камень)
					health = health + 40;//какое то действие... например телепортация героя
					TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
				}
			}
	}
};


void music()
{
	Music music;//создаем объект музыки
	music.openFromFile("Audio/gambit.wav");//загружаем файл
	music.play();//воспроизводим музыку
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


			///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if (Hero.life)
		{

			if ((Keyboard::isKeyPressed(Keyboard::A)))
			{
				Hero.dir = 1; Hero.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
				HeroCurrentFrame += 0.0085 * time;
				if (HeroCurrentFrame > 3) HeroCurrentFrame -= 3;
				Hero.sprite.setTextureRect(IntRect(48 * int(HeroCurrentFrame), 48, 48, 48)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
			}

			if ((Keyboard::isKeyPressed(Keyboard::D))) {
				Hero.dir = 0; Hero.speed = 0.1;//направление вправо, см выше
				HeroCurrentFrame += 0.0085 * time;
				if (HeroCurrentFrame > 3) HeroCurrentFrame -= 3;
				Hero.sprite.setTextureRect(IntRect(48 * int(HeroCurrentFrame), 96, 48, 48)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

			}

			if ((Keyboard::isKeyPressed(Keyboard::W))) {
				Hero.dir = 3; Hero.speed = 0.1;//направление вниз, см выше
				HeroCurrentFrame += 0.0085 * time;
				if (HeroCurrentFrame > 3) HeroCurrentFrame -= 3;
				Hero.sprite.setTextureRect(IntRect(48 * int(HeroCurrentFrame), 144, 48, 48)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)

			}

			if ((Keyboard::isKeyPressed(Keyboard::S)))
			{ //если нажата клавиша стрелка влево или англ буква А
				Hero.dir = 2; Hero.speed = 0.1;//направление вверх, см выше
				HeroCurrentFrame += 0.0085 * time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
				if (HeroCurrentFrame > 3) HeroCurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
				Hero.sprite.setTextureRect(IntRect(48 * int(HeroCurrentFrame), 0, 48, 48)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96

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

		std::ostringstream playerHealthString;    // объявили переменную
		playerHealthString << Hero.health;		//занесли в нее число очков, то есть формируем строку
		text.setString("Health: " + playerHealthString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);//задаем позицию текста, отступая от центра камеры
		window.draw(text);//рисую этот текст


		window.draw(Hero.sprite);
		window.display();

	}

	return 0;
}