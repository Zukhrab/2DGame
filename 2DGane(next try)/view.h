#pragma once

#include <SFML\Graphics.hpp>
using namespace sf;

View view;

View playerPosition(float x, float y)
{
	view.setCenter(x + 100, y);
	return view;
}

View viewMap(float time)
{
	if ((Keyboard::isKeyPressed(Keyboard::Left)))
	{
		view.move(-0.1 * time, 0);
	}
	if ((Keyboard::isKeyPressed(Keyboard::Right)))
	{
		view.move(0.1 * time, 0);
	}
	if ((Keyboard::isKeyPressed(Keyboard::Up)))
	{
		view.move(0, -0.1 * time);
	}
	if ((Keyboard::isKeyPressed(Keyboard::Down)))
	{
		view.move(0, 0.1 * time);
	}

	return view;
}

void changeview() {


	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view.zoom(1.0100f); //масштабируем, уменьшение
		//view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);//сразу же задает поворот камере
		view.rotate(1);//постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view.setSize(640, 480);//устанавливает размер камеры (наш исходный)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view.setSize(540, 380);//например другой размер
	}


	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));//таким образом делается раздельный экран для игры на двоих. нужно только создать ещё один объект View и привязывать к нему координаты игрока 2.
	}
}


void getplayercoordinateforview(float x, float y) { //функция для считывания координат игрока
	float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

	if (x < 320) tempX = 320;//убираем из вида левую сторону
	if (y < 240) tempY = 240;//верхнюю сторону
	if (y > 554) tempY = 554;//нижнюю сторону	

	view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты. 
}

