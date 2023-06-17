#include "mainwindow.h"

QMediaPlayer* music1;
QMediaPlaylist* playlist1;

mainwindow::mainwindow(GameManager& GM, QWidget *parent)
	: QWidget(parent), my_GM(GM)
{
	ui.setupUi(this);

	//set window
	setFixedSize(1024, 768);
	//set window title
	setWindowTitle("Startburst stream");
	//set window icon
	QIcon icon("./Resources/pic/title_icon.png");
	setWindowIcon(icon);
	

	//set stacked layout
	screen_ = new QStackedLayout(ui.frame_screen);
	start_scene_ = std::make_unique<start_scene>(my_GM);
	screen_->addWidget(start_scene_.get());
	battle_scene_ = std::make_unique<battle_scene>(my_GM);
	screen_->addWidget(battle_scene_.get());


	//set music
	music1 = new QMediaPlayer();
	playlist1 = new QMediaPlaylist();
	playlist1->addMedia(QUrl::fromLocalFile("./Resources/music/menu.wav"));
	playlist1->addMedia(QUrl::fromLocalFile("./Resources/music/battle.wav"));
	playlist1->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
	music1->setPlaylist(playlist1);
	music1->setVolume(10);

	//
	connect(start_scene_.get(), &start_scene::switchToBattleSceneRequested, [this] {
		battle_scene_->initiation();
		screen_->setCurrentWidget(battle_scene_.get());
		//play music
		music1->pause();
		playlist1->setCurrentIndex(1);
		music1->play();
		});

	connect(battle_scene_.get(), &battle_scene::switchToStartSceneRequested, [this] {
		start_scene_->initiation();
		screen_->setCurrentWidget(start_scene_.get());
		//play music
		playlist1->setCurrentIndex(0);
		music1->play();
		});



	//initiation
	screen_->setCurrentWidget(start_scene_.get());
	start_scene_->initiation();
	battle_scene_->initiation();
	//play music
	//playlist1->setCurrentIndex(0);
	music1->setPlaylist(playlist1);
	music1->play();
}


mainwindow::~mainwindow()
{
	
}
