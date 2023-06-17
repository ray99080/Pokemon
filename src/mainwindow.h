#pragma once

#include "ui_mainwindow.h"
#include "start_scene.h"
#include "battle_scene.h"

#include <QStackedLayout>
#include <QWidget>
#include<QtMultimedia/QMediaPlayer>
#include<QtMultimedia/QMediaPlaylist>

class mainwindow : public QWidget
{
	Q_OBJECT

public:
	mainwindow(GameManager& GM, QWidget *parent = Q_NULLPTR);
	~mainwindow();
signals:

private:
	Ui::mainwindow ui;
	std::unique_ptr<battle_scene> battle_scene_;
	std::unique_ptr<start_scene> start_scene_;
	GameManager& my_GM;
	QStackedLayout* screen_;
};
