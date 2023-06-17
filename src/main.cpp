#include"enum.h"
#include"GameManager.h"
#include"Player.h"
#include"Pokemon.h"
#include"Skill.h"
#include"Variable.h"
#include<iostream>
#include<stdlib.h>
#include"mainwindow.h"
#include<QApplication>

bool testMode = false;
int criticalChance = 24;
GameManager GM;

int main(int argc, char* argv[])
{
	srand(time(NULL));
	QApplication app(argc, argv);
	mainwindow window(GM);
	window.show();
	return app.exec();

}
