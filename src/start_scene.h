#pragma once

#include "ui_start_scene.h"
#include "GameManager.h"
#include "variable.h"
#include <fstream>

#include <QWidget>
#include <QString>
#include <QPalette>
#include <QPixmap>
#include<QMessagebox>
#include<QCoreApplication>
#include<QString>
#include<QFileDialog>
#include<QStackedLayout>
#include<memory>
#include<QRandomGenerator>
#include<QTextDocument>
#include<QEvent>
#include<QObject>
#include<QtMultimedia/QMediaPlayer>


class start_scene : public QWidget
{
	Q_OBJECT

public:
	start_scene(GameManager& GM, QWidget *parent = Q_NULLPTR);
	void initiation();
signals:
	void switchToBattleSceneRequested();
private:
	Ui::start_sceneClass ui;
	GameManager& my_GM;
};

class BigButtonEvent2 : public QObject
{
	Q_OBJECT

protected:
	bool eventFilter(QObject* watched, QEvent* event) override {
		if (event->type() == QEvent::Enter) {
			QPushButton* button = qobject_cast<QPushButton*>(watched);
			if (button) {
				QString originalStyle = button->styleSheet();
				originalStyle.remove("border: 8px solid #292927;");
				button->setStyleSheet(originalStyle + "border: 4px solid blue;");
			}
		}
		else if (event->type() == QEvent::Leave) {
			QPushButton* button = qobject_cast<QPushButton*>(watched);
			if (button) {
				QString originalStyle = button->styleSheet();
				originalStyle.remove("border: 8px solid blue;");
				button->setStyleSheet(originalStyle + "border: 4px solid #292927;");
			}
		}
		return QObject::eventFilter(watched, event);
	}
};
