#include "start_scene.h"


BigButtonEvent2 *bigButtonEvent = new BigButtonEvent2;
QSize imageSize;
QFont font_temp;
QString filePath;
int buttonWidth;
int buttonHeight;
std::string pokemon_lib_path;
std::string move_lib_path;
std::string game_data_path;
std::string load_game_path;
bool isLoad_game;
std::string temp_log;
//QMediaPlayer* music1;
//QMediaPlaylist* playlist1;

start_scene::start_scene(GameManager& GM, QWidget *parent)
	: QWidget(parent), my_GM(GM)
{
	ui.setupUi(this);

	isLoad_game = false;

	//Pixmap varible
	QPixmap title;
	QPixmap scaledImage;
	QPixmap pokemon_1;
	QPixmap pokemon_2;

	//set window
	setFixedSize(1024, 768);

	//set background
	ui.frame_background->setStyleSheet("QFrame#frame_background{border-image:url(./Resources/pic/background/menu.png)}");
	
	//set scene size
	ui.frame_title->setFixedSize(1024, 256);
	ui.stackedWidget_menu->setFixedSize(1024, 512);
	
	
	
	//set title
	title.load("./Resources/pic/logo.png");
	imageSize.setWidth(550);
	imageSize.setHeight(550);
	scaledImage = title.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui.label_title->setPixmap(scaledImage);
	ui.label_title->setAlignment(Qt::AlignCenter);

	//set menu
	buttonWidth = 250;
	buttonHeight = 50;
	font_temp = ui.button_newGame->font();
	font_temp.setPointSize(16);
	
	ui.button_loadGame->setFixedSize(buttonWidth, buttonHeight);
	ui.button_loadGame->setFont(font_temp);
	ui.button_loadGame->setStyleSheet("background-color: lightBlue; "
										"border: 4px solid #292927;"
										"border-radius: 15px;");
	ui.button_loadGame->installEventFilter(bigButtonEvent);
	ui.button_newGame->setFixedSize(buttonWidth, buttonHeight);
	ui.button_newGame->setFont(font_temp);
	ui.button_newGame->setStyleSheet("background-color: lightBlue; "
										"border: 4px solid #292927;"
										"border-radius: 15px;");
	ui.button_newGame->installEventFilter(bigButtonEvent);
	ui.button_quitGame->setFixedSize(buttonWidth, buttonHeight);
	ui.button_quitGame->setFont(font_temp);
	ui.button_quitGame->setStyleSheet("background-color: lightBlue; "
										"border: 4px solid #292927;"
										"border-radius: 15px;");
	ui.button_quitGame->installEventFilter(bigButtonEvent);
	ui.vLayout_menu->setSpacing(20);
	ui.vLayout_menu->setAlignment(Qt::AlignCenter);

	//set picture
	pokemon_1.load("./Resources/pic/pokemon/Charizard.png");
	ui.label_pokemon1->setPixmap(pokemon_1);
	ui.label_pokemon1->setScaledContents(true);
	pokemon_2.load("./Resources/pic/pokemon/Blastoise.png");
	ui.label_pokemon2->setPixmap(pokemon_2);
	ui.label_pokemon2->setScaledContents(true);

	//set new game
	ui.button_newGame_back->setFixedSize(230, buttonHeight);
	ui.button_newGame_back->setFont(font_temp);
	ui.button_newGame_back->setStyleSheet("background-color: lightBlue; "
									"border: 4px solid #292927;"
									"border-radius: 15px;");
	ui.button_newGame_back->installEventFilter(bigButtonEvent);
	ui.button_newGame_start->setFont(font_temp);
	ui.button_newGame_start->setStyleSheet("background-color: lightBlue; "
									"border: 4px solid #292927;"
									"border-radius: 15px;");
	ui.button_newGame_start->installEventFilter(bigButtonEvent);
	ui.button_choosePokemon->setFixedSize(buttonWidth, buttonHeight);
	ui.button_choosePokemon->setFont(font_temp);
	ui.button_choosePokemon->setStyleSheet("background-color: lightBlue; "
										"border: 4px solid #292927;"
										"border-radius: 15px;");
	ui.button_choosePokemon->installEventFilter(bigButtonEvent);
	ui.button_chooseMove->setFixedSize(buttonWidth, buttonHeight);
	ui.button_chooseMove->setFont(font_temp);
	ui.button_chooseMove->setStyleSheet("background-color: lightBlue; "
										"border: 4px solid #292927;"
										"border-radius: 15px;");
	ui.button_chooseMove->installEventFilter(bigButtonEvent);
	ui.button_chooseTeam->setFixedSize(buttonWidth, buttonHeight);
	ui.button_chooseTeam->setFont(font_temp);
	ui.button_chooseTeam->setStyleSheet("background-color: lightBlue; "
										"border: 4px solid #292927;"
										"border-radius: 15px;");
	ui.button_chooseTeam->installEventFilter(bigButtonEvent);

	//set load game
	ui.button_loadGame_back->setFixedSize(230, buttonHeight);
	ui.button_loadGame_back->setFont(font_temp);
	ui.button_loadGame_back->setStyleSheet("background-color: lightBlue; "
									"border: 4px solid #292927;"
									"border-radius: 15px;");
	ui.button_loadGame_back->installEventFilter(bigButtonEvent);
	ui.button_loadGame_start->setFont(font_temp);
	ui.button_loadGame_start->setStyleSheet("background-color: lightBlue; "
									"border: 4px solid #292927;"
									"border-radius: 15px;");
	ui.button_loadGame_start->installEventFilter(bigButtonEvent);
	ui.button_chooseGame->setFixedSize(buttonWidth, buttonHeight);
	ui.button_chooseGame->setFont(font_temp);
	ui.button_chooseGame->setStyleSheet("background-color: lightBlue; "
									"border: 4px solid #292927;"
									"border-radius: 15px;");
	ui.button_chooseGame->installEventFilter(bigButtonEvent);

	
	
	//click event
	// 
	// 
	//click new game
	connect(ui.button_newGame, &QPushButton::clicked, [this]() {
		ui.stackedWidget_menu->setCurrentWidget(ui.page_newGame);
		});

	//click load game
	connect(ui.button_loadGame, &QPushButton::clicked, [this](){
		ui.stackedWidget_menu->setCurrentWidget(ui.page_loadGame);
	});
	
	//click quit game
	connect(ui.button_quitGame, &QPushButton::clicked, [this]() {
		QMessageBox messagebox;
		messagebox.setWindowTitle("startburst stream");
		messagebox.setText("Do you want to leave the game?");
		messagebox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		QPixmap ST3("./Resources/pic/ST3.png");
		QPixmap ST5("./Resources/pic/ST5.png");
		QPixmap scaledpic = ST5.scaled(QSize(100, 100));
		messagebox.setIconPixmap(scaledpic);
		messagebox.setWindowIcon(ST3);
		int option = messagebox.exec();
		switch (option) {
		case QMessageBox::Yes:
			QCoreApplication::quit();
			break;
		case QMessageBox::No:
			break;
		}
		});
	
	//click choose pokemon
	connect(ui.button_choosePokemon, &QPushButton::clicked, [this] {
		QFileDialog dialog(this);
		dialog.setWindowTitle("kirito");
		dialog.setFileMode(QFileDialog::ExistingFile);
		filePath = dialog.getOpenFileName();
		ui.lineEdit_pokemon->setText(filePath);
		QString temp = ui.lineEdit_pokemon->text();
		pokemon_lib_path = temp.toStdString();
		});

	//click choose move
	connect(ui.button_chooseMove, &QPushButton::clicked, [this] {
		QFileDialog dialog(this);
		dialog.setWindowTitle("kirito");
		dialog.setFileMode(QFileDialog::ExistingFile);
		filePath = dialog.getOpenFileName();
		ui.lineEdit_move->setText(filePath);
		QString temp = ui.lineEdit_move->text();
		move_lib_path = temp.toStdString();
		});

	//click choose team
	connect(ui.button_chooseTeam, &QPushButton::clicked, [this] {
		QFileDialog dialog(this);
		dialog.setWindowTitle("kirito");
		dialog.setFileMode(QFileDialog::ExistingFile);
		filePath = dialog.getOpenFileName();
		ui.lineEdit_team->setText(filePath);
		QString temp = ui.lineEdit_team->text();
		game_data_path = temp.toStdString();
		});

	//click choose game
	connect(ui.button_chooseGame, &QPushButton::clicked, [this] {
		QFileDialog dialog(this);
		dialog.setWindowTitle("kirito");
		dialog.setFileMode(QFileDialog::ExistingFile);
		filePath = dialog.getOpenFileName();
		ui.lineEdit_game->setText(filePath);
		//Àò¨úÀÉ®×³~®|
		QString temp = ui.lineEdit_game->text();
		load_game_path = temp.toStdString();
		});

	//click new game back
	connect(ui.button_newGame_back, &QPushButton::clicked, [this] {
		ui.stackedWidget_menu->setCurrentWidget(ui.page_menu);
		});

	//click load game back
	connect(ui.button_loadGame_back, &QPushButton::clicked, [this] {
		ui.stackedWidget_menu->setCurrentWidget(ui.page_menu);
		});

	//click new game start
	connect(ui.button_newGame_start, &QPushButton::clicked, [this] {
		if (my_GM.startSeperateFile(pokemon_lib_path, move_lib_path, game_data_path)) {
			emit switchToBattleSceneRequested();
		}
		else {
			QMessageBox warn;
			warn.setText("Fail to load file.");
			QPixmap ST("./Resources/pic/ST.png");
			QPixmap ST2("./Resources/pic/ST2.png");
			QPixmap scaledpic = ST2.scaled(QSize(100, 100));
			warn.setIconPixmap(scaledpic);
			warn.setWindowIcon(ST);
			warn.exec();
		}
		
		});

	//click load game start
	connect(ui.button_loadGame_start, &QPushButton::clicked, [this] {
		//ÅªÀÉ
		//
		ifstream file1(load_game_path);
		std::string line;
		file1.seekg(0);
		temp_log.clear();
		//read pokemon lib, move lib, game data
		getline(file1, line);
		pokemon_lib_path = "./Resources/list/Game/" + line;
		getline(file1, line);
		move_lib_path = "./Resources/list/Game/" + line;
		getline(file1, line);
		game_data_path = "./Resources/list/Game/" + line;
		if (my_GM.startSeperateFile(pokemon_lib_path, move_lib_path, game_data_path)) {
			while (getline(file1, line)) {
				temp_log += line + '\n';
			}
			isLoad_game = true;
			file1.close();
			emit switchToBattleSceneRequested();
		}
		else {
			QMessageBox warn;
			warn.setText("Fail to load file.");
			QPixmap ST("./Resources/pic/ST.png");
			QPixmap ST2("./Resources/pic/ST2.png");
			QPixmap scaledpic = ST2.scaled(QSize(100, 100));
			warn.setIconPixmap(scaledpic);
			warn.setWindowIcon(ST);
			warn.exec();
		}
		
		

		});

	
	


}

void start_scene::initiation() {
	//initiation when switch screen
	ui.stackedWidget_menu->setCurrentWidget(ui.page_menu);
	//play music
	//playlist1->addMedia(QUrl::fromLocalFile("./Resources/music/menu.wav"));
	//playlist1->setPlaybackMode(QMediaPlaylist::Loop);
	//music1->setPlaylist(playlist1);
	//music1->setVolume(10);
	//music1->play();
	//ui.lineEdit_game->setText("");
	//ui.lineEdit_move->setText("");
	//ui.lineEdit_pokemon->setText("");
	//ui.lineEdit_team->setText("");

}








