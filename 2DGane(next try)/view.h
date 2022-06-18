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
		view.zoom(1.0100f); //������������, ����������
		//view.zoom(1.0006f); //���� ����� ����������� ��������������
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);//����� �� ������ ������� ������
		view.rotate(1);//���������� ������������ ������ (������������� �������� - � �������� �������)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view.setSize(640, 480);//������������� ������ ������ (��� ��������)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view.setSize(540, 380);//�������� ������ ������
	}


	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));//����� ������� �������� ���������� ����� ��� ���� �� �����. ����� ������ ������� ��� ���� ������ View � ����������� � ���� ���������� ������ 2.
	}
}


void getplayercoordinateforview(float x, float y) { //������� ��� ���������� ��������� ������
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (x < 320) tempX = 320;//������� �� ���� ����� �������
	if (y < 240) tempY = 240;//������� �������
	if (y > 554) tempY = 554;//������ �������	

	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������. 
}

