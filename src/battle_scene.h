#pragma once

#include "ui_battle_scene.h"
#include "GameManager.h"
#include "variable.h"

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
#include<QTimer>
#include<set>
#include<sstream>


class battle_scene : public QWidget
{
	Q_OBJECT

public:
	//battle_scene(QStackedLayout* screen, QWidget* parent = Q_NULLPTR);
	battle_scene(GameManager& GM, QWidget *parent = Q_NULLPTR);
	~battle_scene();
	void initiation();
	void update_visual();
	QStringList getBattleList(bool p);
	QStringList getFinalList();
	void hurtAnimation(QLabel* pokemon);
	void loadData(std::string temp_log);
signals:
	void switchToStartSceneRequested();

private:
	Ui::battle_scene ui;
	GameManager& my_GM;
};

class BigButtonEvent : public QObject
{
    Q_OBJECT

protected:
	bool eventFilter(QObject* watched, QEvent* event) override {
		if (event->type() == QEvent::Enter) {
			QPushButton* button = qobject_cast<QPushButton*>(watched);
			if (button) {
				QString originalStyle = button->styleSheet();
				originalStyle.remove("border: 8px solid #292927;");
				button->setStyleSheet(originalStyle + "border: 8px solid white;");
			}
		}
		else if (event->type() == QEvent::Leave) {
			QPushButton* button = qobject_cast<QPushButton*>(watched);
			if (button) {
				QString originalStyle = button->styleSheet();
				originalStyle.remove("border: 8px solid white;");
				button->setStyleSheet(originalStyle + "border: 8px solid #292927;");
			}
		}
		return QObject::eventFilter(watched, event);
	}
};


