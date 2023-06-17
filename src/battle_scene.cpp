#include "battle_scene.h"


BigButtonEvent* bigButtonEvent = new BigButtonEvent;
QFont font_temp2;
QString text;
QString path;
QImage img;
QIcon icon;
int text_list_index = 0;
QStringList text_list;
int click_time = 0;
int click_time_2 = 0;
int current_maxHP = 0;
int current_HP = 0;
int my_pokemon_num = 0;
int my_pokemon_HP[6] = {-1};
int my_pokemon_maxHP[6] = { -1 };
int op_pokemon_num = 0;
int op_pokemon_HP[6] = { -1 };
int op_pokemon_maxHP[6] = { -1 };
int move_num = 0;
int move_PP[4] = { 0 };
int move_maxPP[4] = { 0 };
int potion_number = 0;
int superPotion_number = 0;
int hyperPotion_number = 0;
int maxPotion_number = 0;
int random = 0;
int type_value = 0;
float effectiveness;
float op_effectiveness;
bool criticalHit;
bool op_criticalHit;
bool player;//1 is plyer, 0 is pc
bool whoGoFirst;//1 is plyer, 0 is pc
bool deadSwap;
std::set<Condition> pokemon_condition;
std::set<Condition> op_pokemon_condition;
PokemonType move_type[4];
std::string skill_element;
std::string current_pokemon_name;
std::string op_current_pokemon_name;
std::string current_pokemon_element;
std::string my_pokemon_name[6];
std::string op_pokemon_name[6];
std::string current_move[4];

std::string bag_use;
std::string move_use;
std::string op_move_use;
std::string swap_use;
std::string pokemon_use;
std::string op_pokemon_use;
//std::string temp_log;
//bool isLoad_game;
std::string status = "";
//status: choose, attack, heal, swap, run, show

//QMediaPlayer* music2;
//QMediaPlaylist* playlist2;

battle_scene::battle_scene(GameManager& GM, QWidget *parent)
	: QWidget(parent), my_GM(GM)
{
	ui.setupUi(this);

	//QPixmap variable
	QPixmap pokemon_pic;
	QPixmap scaledPixmap;
	QPixmap pic;

	//set window
	setFixedSize(1024, 768);

	//set music
	//music2 = new QMediaPlayer();
	//playlist2 = new QMediaPlaylist();

	//set background
	random = QRandomGenerator::global()->bounded(1, 9);
	switch (random) {
	case 1:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/beach.png)}");
		break;
	case 2:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/desert.png)}");
		break;
	case 3:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/forest1.png)}");
		break;
	case 4:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/forest2.png)}");
		break;
	case 5:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/land.png)}");
		break;
	case 6:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/purple.png)}");
		break;
	case 7:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/sand.png)}");
		break;
	case 8:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/sea.png)}");
		break;
	}
	ui.frame_dialog ->setStyleSheet("QFrame#frame_dialog{"
									"	border-top: 8px solid #292927;"
									"	background-image:url(./Resources/pic/background/dialog.png);"
									" }");
	//set main page
	//set player1 pokemon
	path = "./Resources/pic/pokemon/" + QString::fromStdString(current_pokemon_name) + ".png";
	pokemon_pic.load(path);
	scaledPixmap = pokemon_pic.scaledToWidth(430);
	ui.label_pokemon1->setPixmap(scaledPixmap);
	//set player1 pokemon name and HP
	ui.label_status1->setStyleSheet("background-color: #C9C8C9;"
									"border-top: 8px solid #292927;"
									"border-bottom: 8px solid #292927;"
									"border-left: 8px solid #292927;"
									"border-radius: 15px;"					
	);
	text = QString::fromStdString(current_pokemon_name) + "\n";
	text = text + "HP : " + QString::number(current_HP) + "/" + QString::number(current_maxHP) + "\n";
	ui.label_status1->setText(text);
	font_temp2.setPointSize(30);
	ui.label_status1->setFont(font_temp2);
	//set player1 pokemon condition
	ui.label_BRN1->setStyleSheet("background-color: red;"
								"color: white;"
								"border-radius: 10px;"

	);
	ui.label_BRN1->setAlignment(Qt::AlignCenter);
	ui.label_PSN1->setStyleSheet("background-color: green;"
								"color: white;"
								"border-radius: 10px;"

	);
	ui.label_PSN1->setAlignment(Qt::AlignCenter);
	ui.label_PAR1->setStyleSheet("background-color: purple;"
								"color: white;"
								"border-radius: 10px;"

	);
	ui.label_PAR1->setAlignment(Qt::AlignCenter);
	//set player1 remained pokemon
	pic.load("./Resources/pic/other/pokeball.png");
	scaledPixmap = pic.scaledToWidth(25);
	ui.label_p1->setPixmap(scaledPixmap);
	ui.label_p2->setPixmap(scaledPixmap);
	ui.label_p3->setPixmap(scaledPixmap);
	ui.label_p4->setPixmap(scaledPixmap);
	ui.label_p5->setPixmap(scaledPixmap);
	ui.label_p6->setPixmap(scaledPixmap);
	
	
	//set player2 pokemon
	path = "./Resources/pic/pokemon/" + QString::fromStdString(current_pokemon_name) + ".png";
	pokemon_pic.load(path);
	scaledPixmap = pokemon_pic.scaledToWidth(430);
	ui.label_pokemon2->setPixmap(scaledPixmap);
	//set player2 pokemon name and HP
	ui.label_status2->setStyleSheet("background-color: #C9C8C9;"
									"border-top: 8px solid #292927;"
									"border-bottom: 8px solid #292927;"
									"border-right: 8px solid #292927;"
									"border-radius: 15px;"
	);
	text = QString::fromStdString(current_pokemon_name) + "\n";
	text = text + "HP : " + QString::number(current_HP) + "/" + QString::number(current_maxHP) + "\n";
	ui.label_status2->setText(text);
	font_temp2.setPointSize(30);
	ui.label_status2->setFont(font_temp2);
	ui.label_status2->setContentsMargins(10, 0, 0, 0);
	//set player2 pokemon condition
	ui.label_BRN2->setStyleSheet("background-color: red;"
		"color: white;"
		"border-radius: 10px;"

	);
	ui.label_BRN2->setAlignment(Qt::AlignCenter);
	ui.label_PSN2->setStyleSheet("background-color: green;"
		"color: white;"
		"border-radius: 10px;"

	);
	ui.label_PSN2->setAlignment(Qt::AlignCenter);
	ui.label_PAR2->setStyleSheet("background-color: purple;"
		"color: white;"
		"border-radius: 10px;"

	);
	ui.label_PAR2->setAlignment(Qt::AlignCenter);
	//set player2 remained pokemon
	pic.load("./Resources/pic/other/pokeball.png");
	scaledPixmap = pic.scaledToWidth(25);
	ui.label_p1_2->setPixmap(scaledPixmap);
	ui.label_p2_2->setPixmap(scaledPixmap);
	ui.label_p3_2->setPixmap(scaledPixmap);
	ui.label_p4_2->setPixmap(scaledPixmap);
	ui.label_p5_2->setPixmap(scaledPixmap);
	ui.label_p6_2->setPixmap(scaledPixmap);

	
	
	
	
	//set option page
	//
	font_temp2 = ui.button_bag->font();
	font_temp2.setPointSize(35);
	//fight button
	ui.button_fight->setFont(font_temp2);
	ui.button_fight->setStyleSheet("background-color: #C7858D;"
									"border: 8px solid #292927;"
									"border-radius: 15px;"
									"color: white;"
									);
	ui.button_fight->installEventFilter(bigButtonEvent);
	//pokemon button
	ui.button_pokemon->setFont(font_temp2);
	ui.button_pokemon->setStyleSheet("background-color: #3B801B;"
									"border: 8px solid #292927;"
									"border-radius: 15px;"
									"color: white;"
								);
	ui.button_pokemon->installEventFilter(bigButtonEvent);
	//bag button
	ui.button_bag->setFont(font_temp2);
	ui.button_bag->setStyleSheet("background-color: #B47D20;"
									"border: 8px solid #292927;"
									"border-radius: 15px;"
									"color: white;"
								);
	ui.button_bag->installEventFilter(bigButtonEvent);
	//run button
	ui.button_run->setFont(font_temp2);
	ui.button_run->setStyleSheet("background-color: #1F6891;"
									"border: 8px solid #292927;"
									"border-radius: 15px;"
									"color: white;"
								);
	ui.button_run->installEventFilter(bigButtonEvent);
	//dialog label
	font_temp2.setPointSize(30);
	ui.label_dialog1->setFont(font_temp2);
	ui.label_dialog1->setAlignment(Qt::AlignCenter);
	ui.label_dialog1->setStyleSheet("background-color: #C9C8C9;" 
									"border: 8px solid #292927;"
									"border-radius: 15px;"
									);
	text = "What will\n" + QString::fromStdString(current_pokemon_name) + " do?";
	ui.label_dialog1->setText(text);

	//set move page
	//set move1
	font_temp2.setPointSize(35);
	ui.button_move1->setFont(font_temp2);
	ui.button_move1->setStyleSheet("background-color: white;"
									"border: 8px solid brown;"
									"border-radius: 15px;"
									"color: black;"
	);
	//set move2
	ui.button_move2->setFont(font_temp2);
	ui.button_move2->setStyleSheet("background-color: white;"
		"border: 8px solid brown;"
		"border-radius: 15px;"
		"color: black;"
	);
	//set move3
	ui.button_move3->setFont(font_temp2);
	ui.button_move3->setStyleSheet("background-color: white;"
		"border: 8px solid brown;"
		"border-radius: 15px;"
		"color: black;"
	);
	//set move4
	ui.button_move4->setFont(font_temp2);
	ui.button_move4->setStyleSheet("background-color: white;"
		"border: 8px solid brown;"
		"border-radius: 15px;"
		"color: black;"
	);
	//set use
	font_temp2.setPointSize(35);
	ui.button_use1->setFont(font_temp2);
	ui.button_use1->setStyleSheet("background-color: lightGray;"
									"border: 8px solid black;"
									"border-radius: 15px;"
									"color: black;"
	);
	ui.button_use1->setText("ACTION");
	ui.button_use1->setEnabled(false);
	//set cancel
	font_temp2.setPointSize(35);
	ui.button_cancel_1->setFont(font_temp2);
	ui.button_cancel_1->setStyleSheet("background-color: black;"
										"border: 8px solid #292927;"
										"border-radius: 15px;"
										"color: white;"
	);
	ui.button_cancel_1->installEventFilter(bigButtonEvent);

	//set dialog page
	font_temp2.setPointSize(30);
	ui.button_dialog->setFont(font_temp2);
	ui.button_dialog->setStyleSheet("background-color: #C9C8C9;"
									"border: 8px solid #292927;"
									"border-radius: 15px;"
	);
	ui.button_dialog->installEventFilter(bigButtonEvent);

	//set pokemon page
	ui.frame_pokemon_background->setStyleSheet("QFrame#frame_pokemon_background{border-image:url(./Resources/pic/background/bag.png)}");
	font_temp2.setPointSize(30);
	//set pokemon1
	ui.button_pokemon1->setFont(font_temp2);
	ui.button_pokemon1->setStyleSheet("background-color: black;"
									//"border: 4px solid white;"
									"border-top-left-radius: 30px;"
									"border-bottom-right-radius: 30px;"
									"color: white;"
									"text-align: left;"
									
	);
	ui.button_pokemon1->setText("");
	ui.button_pokemon1->setEnabled(false);
	//set pokemon2
	ui.button_pokemon2->setFont(font_temp2);
	ui.button_pokemon2->setStyleSheet("background-color: black;"
									//"border: 4px solid white;"
									"border-top-left-radius: 30px;"
									"border-bottom-right-radius: 30px;"
									"color: white;"
									"text-align: left;"

	);
	ui.button_pokemon2->setText("");
	ui.button_pokemon2->setEnabled(false);
	//set pokemon3
	ui.button_pokemon3->setFont(font_temp2);
	ui.button_pokemon3->setStyleSheet("background-color: black;"
									//"border: 4px solid white;"
									"border-top-left-radius: 30px;"
									"border-bottom-right-radius: 30px;"
									"color: white;"
									"text-align: left;"

	);
	ui.button_pokemon3->setText("");
	ui.button_pokemon3->setEnabled(false);
	//set pokemon4
	ui.button_pokemon4->setFont(font_temp2);
	ui.button_pokemon4->setStyleSheet("background-color: black;"
		//"border: 4px solid white;"
		"border-top-left-radius: 30px;"
		"border-bottom-right-radius: 30px;"
		"color: white;"
		"text-align: left;"

	);
	ui.button_pokemon4->setText("");
	ui.button_pokemon4->setEnabled(false);
	//set pokemon5
	ui.button_pokemon5->setFont(font_temp2);
	ui.button_pokemon5->setStyleSheet("background-color: black;"
		//"border: 4px solid white;"
		"border-top-left-radius: 30px;"
		"border-bottom-right-radius: 30px;"
		"color: white;"
		"text-align: left;"

	);
	ui.button_pokemon5->setText("");
	ui.button_pokemon5->setEnabled(false);
	//set pokemon6
	ui.button_pokemon6->setFont(font_temp2);
	ui.button_pokemon6->setStyleSheet("background-color: black;"
		//"border: 4px solid white;"
		"border-top-left-radius: 30px;"
		"border-bottom-right-radius: 30px;"
		"color: white;"
		"text-align: left;"

	);
	ui.button_pokemon6->setText("");
	ui.button_pokemon6->setEnabled(false);
	//set pokemon cancel
	ui.button_cancel_2->setFont(font_temp2);
	ui.button_cancel_2->setStyleSheet("background-color: black;"
									"border: 8px solid #292927;"
									"border-radius: 15px;"
									"color: white;"
	);
	ui.button_cancel_2->installEventFilter(bigButtonEvent);
	//set pokemon switch 
	ui.button_switch->setFont(font_temp2);
	ui.button_switch->setFont(font_temp2);
	ui.button_switch->setStyleSheet("background-color: lightGray;"
									"border: 8px solid #292927;"
									"border-radius: 15px;"
									"color: black;"
	);
	ui.button_switch->setEnabled(false);
	
	//set bag page
	//
	//potion
	ui.frame_bag_background->setStyleSheet("QFrame#frame_bag_background{border-image:url(./Resources/pic/background/bag.png)}");
	font_temp2.setPointSize(30);
	ui.button_potion->setFont(font_temp2);
	ui.button_potion->setStyleSheet("background-color: white;"
									"border: 4px solid purple;"
									"border-radius: 15px;"
									);
	pic.load("./Resources/pic/potion/potion.png");
	ui.button_potion->setIcon(pic);
	ui.button_potion->setIconSize(QSize(50, 50));
	ui.label_potion->setFont(font_temp2);
	ui.label_potion->setStyleSheet("background-color: white;"
									"border: 4px solid purple;"
									"border-radius: 15px;");
	//super potion
	ui.button_superPotion->setFont(font_temp2);
	ui.button_superPotion->setStyleSheet("background-color: white;"
		"border: 4px solid orange;"
		"border-radius: 15px;"
	);
	pic.load("./Resources/pic/potion/superPotion.png");
	ui.button_superPotion->setIcon(pic);
	ui.button_superPotion->setIconSize(QSize(50, 50));
	ui.label_superPotion->setFont(font_temp2);
	ui.label_superPotion->setStyleSheet("background-color: white;"
		"border: 4px solid orange;"
		"border-radius: 15px;");
	//hyper potion
	ui.button_hyperPotion->setFont(font_temp2);
	ui.button_hyperPotion->setStyleSheet("background-color: white;"
		"border: 4px solid pink;"
		"border-radius: 15px;"
	);
	pic.load("./Resources/pic/potion/hyperPotion.png");
	ui.button_hyperPotion->setIcon(pic);
	ui.button_hyperPotion->setIconSize(QSize(50, 50));
	ui.label_hyperPotion->setFont(font_temp2);
	ui.label_hyperPotion->setStyleSheet("background-color: white;"
		"border: 4px solid pink;"
		"border-radius: 15px;");
	//max potion
	ui.button_maxPotion->setFont(font_temp2);
	ui.button_maxPotion->setStyleSheet("background-color: white;"
		"border: 4px solid lightBlue;"
		"border-radius: 15px;"
	);
	pic.load("./Resources/pic/potion/maxPotion.png");
	ui.button_maxPotion->setIcon(pic);
	ui.button_maxPotion->setIconSize(QSize(50, 50));
	ui.label_maxPotion->setFont(font_temp2);
	ui.label_maxPotion->setStyleSheet("background-color: white;"
		"border: 4px solid lightBlue;"
		"border-radius: 15px;");
	//use potion
	ui.button_use2->setFont(font_temp2);
	ui.button_use2->setFont(font_temp2);
	ui.button_use2->setStyleSheet("background-color: lightGray;"
		"border: 8px solid #292927;"
		"border-radius: 15px;"
		"color: black;"
	);
	ui.button_use2->setEnabled(false);
	//cancel
	ui.button_cancel_3->setFont(font_temp2);
	ui.button_cancel_3->setStyleSheet("background-color: black;"
		"border: 8px solid #292927;"
		"border-radius: 15px;"
		"color: white;"
	);
	ui.button_cancel_3->installEventFilter(bigButtonEvent);
	//set pokemon to be healed
	ui.frame_heal_pokemon->setStyleSheet("background-color: darkBlue;"
		"border: 0px solid #292927;"
		"border-radius: 15px;"
	);
	ui.frame_heal_pokemon->hide();
	font_temp2.setPointSize(15);
	ui.button_heal_p1->setFont(font_temp2);
	ui.button_heal_p1->setStyleSheet("background-color: black;"
		"border: 0px solid #292927;"
		"border-radius: 15px;"
		"color: white;"
	);
	ui.button_heal_p1->setText("");

	ui.button_heal_p2->setFont(font_temp2);
	ui.button_heal_p2->setStyleSheet("background-color: black;"
		"border: 0px solid #292927;"
		"border-radius: 15px;"
		"color: white;"
	);
	ui.button_heal_p2->setText("");

	ui.button_heal_p3->setFont(font_temp2);
	ui.button_heal_p3->setStyleSheet("background-color: black;"
		"border: 0px solid #292927;"
		"border-radius: 15px;"
		"color: white;"
	);
	ui.button_heal_p3->setText("");

	ui.button_heal_p4->setFont(font_temp2);
	ui.button_heal_p4->setStyleSheet("background-color: black;"
		"border: 0px solid #292927;"
		"border-radius: 15px;"
		"color: white;"
	);
	ui.button_heal_p4->setText("");

	ui.button_heal_p5->setFont(font_temp2);
	ui.button_heal_p5->setStyleSheet("background-color: black;"
		"border: 0px solid #292927;"
		"border-radius: 15px;"
		"color: white;"
	);
	ui.button_heal_p5->setText("");

	ui.button_heal_p6->setFont(font_temp2);
	ui.button_heal_p6->setStyleSheet("background-color: black;"
		"border: 0px solid #292927;"
		"border-radius: 15px;"
		"color: white;"
	);
	ui.button_heal_p6->setText("");

	//set log
	font_temp2.setPointSize(15);
	ui.button_log->setFont(font_temp2);
	ui.button_log->setStyleSheet("background-color: lightGray;"
		"border: 8px solid #292927;"
		"border-radius: 15px;"
		"color: black;");
	ui.button_log->installEventFilter(bigButtonEvent);
	ui.scrollArea_log->hide();
	ui.scrollArea_log->setStyleSheet("QScrollArea#scrollArea_log{background-color: lightGray;"
		"border: 8px solid #292927;"
		"border-radius: 15px;"
		"color: black;}");
	ui.scrollArea_log->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	ui.scrollArea_log->setWidgetResizable(true);
	font_temp2.setPointSize(17);
	ui.label_log->setFont(font_temp2);
	ui.label_log->setStyleSheet("line-height: 20px;");


	//click event
	//
	//click fight
	connect(ui.button_fight, &QPushButton::clicked, [this]() {
		ui.stackedWidget_switch_small->setCurrentWidget(ui.page_move);
		});

	//click pokemon
	connect(ui.button_pokemon, &QPushButton::clicked, [this]() {
		ui.stackedWidget_switch_big->setCurrentWidget(ui.page_pokemon);
		});

	//click bag
	connect(ui.button_bag, &QPushButton::clicked, [this]() {
		ui.stackedWidget_switch_big->setCurrentWidget(ui.page_bag);
		});

	//click run
	connect(ui.button_run, &QPushButton::clicked, [this]() {
		status = "run";
		update_visual();
		});


	//click dialog
	connect(ui.button_dialog, &QPushButton::clicked, [this]() {
		if (status == "run") {
			QMessageBox quit;
			quit.setWindowTitle("startburst stream");
			quit.setText("Do you want to play again?");
			quit.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
			QPixmap ST("./Resources/pic/ST.png");
			QPixmap ST4("./Resources/pic/ST4.png");
			QPixmap scaledpic = ST4.scaled(QSize(100, 100));
			quit.setIconPixmap(scaledpic);
			quit.setWindowIcon(ST);
			int option = quit.exec();
			switch (option) {
			case QMessageBox::Yes:
				emit switchToStartSceneRequested();
				break;
			case QMessageBox::No:
				QCoreApplication::quit();
				break;
			}
		}
		if (status != "gameover") {
			status = "show";
		}
		update_visual();
		if (text_list_index < text_list.size()) {
			ui.button_dialog->setText(text_list[text_list_index]);
			if (text_list[text_list_index].contains("used")) {
				if (text_list[text_list_index].contains(QString::fromStdString(op_current_pokemon_name))) {
					hurtAnimation(ui.label_pokemon1);
				}
				else if (text_list[text_list_index].contains(QString::fromStdString(current_pokemon_name))) {
					hurtAnimation(ui.label_pokemon2);
				}
				
			}
			ui.label_log->setText(ui.label_log->text() + text_list[text_list_index] + "\n");
			text_list_index++;
		}
		else {
			if (status == "gameover") {
				QMessageBox quit1;
				quit1.setWindowTitle("startburst stream");
				quit1.setText("Do you want to play again?");
				quit1.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
				QPixmap ST("./Resources/pic/ST.png");
				QPixmap ST4("./Resources/pic/ST4.png");
				QPixmap scaledpic = ST4.scaled(QSize(100, 100));
				quit1.setIconPixmap(scaledpic);
				quit1.setWindowIcon(ST);
				int option1 = quit1.exec();
				switch (option1) {
				case QMessageBox::Yes:
					emit switchToStartSceneRequested();
					break;
				case QMessageBox::No:
					QCoreApplication::quit();
					break;
				}
			}
			if (deadSwap == 1) {
				ui.stackedWidget_switch_big->setCurrentWidget(ui.page_pokemon);
			}
			else if (deadSwap == 0) {
				text_list.clear();
				status = "choose";
				update_visual();
			}
			
		}

		});


	//click move1
	connect(ui.button_move1, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			QFont font;
			ui.button_move1->setStyleSheet("background-color: brown;"
											"border: 8px solid white;"
											"border-radius: 15px;"
											"color: white;"
			);
			font.setPointSize(23);
			ui.button_use1->setFont(font);
			ui.button_use1->setStyleSheet("background-color: darkGray;"
											"border: 8px solid black;"
											"border-radius: 15px;"
											"color: black;"
											"text-align: left;"
											"padding-left: 20;"
			);
			QString text = "       PP : " + QString::number(move_PP[0]) + "/" + QString::number(move_maxPP[0]) + "\n";
			text = text + "       Use";
			ui.button_use1->setText(text);
			type_value = static_cast<int>(move_type[0]);
			QString path = "./Resources/pic/element/" + QString::number(type_value) + ".png";
			QIcon icon(path);
			ui.button_use1->setIcon(icon);
			ui.button_use1->setIconSize(QSize(50, 50));
			ui.button_use1->installEventFilter(bigButtonEvent);
			ui.button_use1->setEnabled(true);
			ui.button_move2->setEnabled(false);
			ui.button_move3->setEnabled(false);
			ui.button_move4->setEnabled(false);
			move_use = current_move[0];
		}
		else if (click_time == 1) {
			click_time = 0;
			QFont font;
			ui.button_move1->setStyleSheet("background-color: white;"
				"border: 8px solid brown;"
				"border-radius: 15px;"
				"color: black;"
			);
			font.setPointSize(35);
			ui.button_use1->setFont(font);
			ui.button_use1->setStyleSheet("background-color: lightGray;"
				"border: 8px solid black;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use1->setText("ACTION");
			ui.button_use1->setIcon(QIcon());
			ui.button_use1->removeEventFilter(bigButtonEvent);
			ui.button_use1->setEnabled(false);
			if (move_PP[1] > 0) {
				ui.button_move2->setEnabled(true);
			}
			if (move_PP[2] > 0) {
				ui.button_move3->setEnabled(true);
			}
			if (move_PP[3] > 0) {
				ui.button_move4->setEnabled(true);
			}
			move_use = "";

		}


		});

	//click move2
	connect(ui.button_move2, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			QFont font;
			ui.button_move2->setStyleSheet("background-color: brown;"
				"border: 8px solid white;"
				"border-radius: 15px;"
				"color: white;"
			);
			font.setPointSize(23);
			ui.button_use1->setFont(font);
			ui.button_use1->setStyleSheet("background-color: darkGray;"
				"border: 8px solid black;"
				"border-radius: 15px;"
				"color: black;"
				"text-align: left;"
				"padding-left: 20;"
			);
			QString text = "       PP : " + QString::number(move_PP[1]) + "/" + QString::number(move_maxPP[1]) + "\n";
			text = text + "       Use";
			ui.button_use1->setText(text);
			type_value = static_cast<int>(move_type[1]);
			QString path = "./Resources/pic/element/" + QString::number(type_value) + ".png";
			QIcon icon(path);
			ui.button_use1->setIcon(icon);
			ui.button_use1->setIconSize(QSize(50, 50));
			ui.button_use1->installEventFilter(bigButtonEvent);
			ui.button_use1->setEnabled(true);
			ui.button_move1->setEnabled(false);
			ui.button_move3->setEnabled(false);
			ui.button_move4->setEnabled(false);
			move_use = current_move[1];
		}
		else if (click_time == 1) {
			click_time = 0;
			QFont font;
			ui.button_move2->setStyleSheet("background-color: white;"
				"border: 8px solid brown;"
				"border-radius: 15px;"
				"color: black;"
			);
			font.setPointSize(35);
			ui.button_use1->setFont(font);
			ui.button_use1->setStyleSheet("background-color: lightGray;"
				"border: 8px solid black;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use1->setText("ACTION");
			ui.button_use1->setIcon(QIcon());
			ui.button_use1->removeEventFilter(bigButtonEvent);
			ui.button_use1->setEnabled(false);
			if (move_PP[0] > 0) {
				ui.button_move1->setEnabled(true);
			}
			if (move_PP[2] > 0) {
				ui.button_move3->setEnabled(true);
			}
			if (move_PP[3] > 0) {
				ui.button_move4->setEnabled(true);
			}
			move_use = "";
		}


		});

	//click move3
	connect(ui.button_move3, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			QFont font;
			ui.button_move3->setStyleSheet("background-color: brown;"
				"border: 8px solid white;"
				"border-radius: 15px;"
				"color: white;"
			);
			font.setPointSize(23);
			ui.button_use1->setFont(font);
			ui.button_use1->setStyleSheet("background-color: darkGray;"
				"border: 8px solid black;"
				"border-radius: 15px;"
				"color: black;"
				"text-align: left;"
				"padding-left: 20;"
			);
			QString text = "       PP : " + QString::number(move_PP[2]) + "/" + QString::number(move_maxPP[2]) + "\n";
			text = text + "       Use";
			ui.button_use1->setText(text);
			type_value = static_cast<int>(move_type[2]);
			QString path = "./Resources/pic/element/" + QString::number(type_value) + ".png";
			QIcon icon(path);
			ui.button_use1->setIcon(icon);
			ui.button_use1->setIconSize(QSize(50, 50));
			ui.button_use1->installEventFilter(bigButtonEvent);
			ui.button_use1->setEnabled(true);
			ui.button_move1->setEnabled(false);
			ui.button_move2->setEnabled(false);
			ui.button_move4->setEnabled(false);
			move_use = current_move[2];
		}
		else if (click_time == 1) {
			click_time = 0;
			QFont font;
			ui.button_move3->setStyleSheet("background-color: white;"
				"border: 8px solid brown;"
				"border-radius: 15px;"
				"color: black;"
			);
			font.setPointSize(35);
			ui.button_use1->setFont(font);
			ui.button_use1->setStyleSheet("background-color: lightGray;"
				"border: 8px solid black;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use1->setText("ACTION");
			ui.button_use1->setIcon(QIcon());
			ui.button_use1->removeEventFilter(bigButtonEvent);
			ui.button_use1->setEnabled(false);
			if (move_PP[0] > 0) {
				ui.button_move1->setEnabled(true);
			}
			if (move_PP[1] > 0) {
				ui.button_move2->setEnabled(true);
			}
			if (move_PP[3] > 0) {
				ui.button_move4->setEnabled(true);
			}
			move_use = "";
		}


		});

	//click move4
	connect(ui.button_move4, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			QFont font;
			ui.button_move4->setStyleSheet("background-color: brown;"
				"border: 8px solid white;"
				"border-radius: 15px;"
				"color: white;"
			);
			font.setPointSize(23);
			ui.button_use1->setFont(font);
			ui.button_use1->setStyleSheet("background-color: darkGray;"
				"border: 8px solid black;"
				"border-radius: 15px;"
				"color: black;"
				"text-align: left;"
				"padding-left: 20;"
			);
			QString text = "       PP : " + QString::number(move_PP[3]) + "/" + QString::number(move_maxPP[3]) + "\n";
			text = text + "       Use";
			ui.button_use1->setText(text);
			type_value = static_cast<int>(move_type[3]);
			QString path = "./Resources/pic/element/" + QString::number(type_value) + ".png";
			QIcon icon(path);
			ui.button_use1->setIcon(icon);
			ui.button_use1->setIconSize(QSize(50, 50));
			ui.button_use1->installEventFilter(bigButtonEvent);
			ui.button_use1->setEnabled(true);
			ui.button_move1->setEnabled(false);
			ui.button_move2->setEnabled(false);
			ui.button_move3->setEnabled(false);
			move_use = current_move[3];
		}
		else if (click_time == 1) {
			click_time = 0;
			QFont font;
			ui.button_move4->setStyleSheet("background-color: white;"
				"border: 8px solid brown;"
				"border-radius: 15px;"
				"color: black;"
			);
			font.setPointSize(35);
			ui.button_use1->setFont(font);
			ui.button_use1->setStyleSheet("background-color: lightGray;"
				"border: 8px solid black;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use1->setText("ACTION");
			ui.button_use1->setIcon(QIcon());
			ui.button_use1->removeEventFilter(bigButtonEvent);
			ui.button_use1->setEnabled(false);
			if (move_PP[0] > 0) {
				ui.button_move1->setEnabled(true);
			}
			if (move_PP[1] > 0) {
				ui.button_move2->setEnabled(true);
			}
			if (move_PP[2] > 0) {
				ui.button_move3->setEnabled(true);
			}
			move_use = "";
		}


		});

	//click use move
	connect(ui.button_use1, &QPushButton::clicked, [this]() {
		click_time = 0;
		QFont font;
		font.setPointSize(35);
		ui.button_use1->setFont(font);
		ui.button_use1->setStyleSheet("background-color: lightGray;"
			"border: 8px solid black;"
			"border-radius: 15px;"
			"color: black;"
		);
		ui.button_use1->setText("ACTION");
		ui.button_use1->setIcon(QIcon());
		ui.button_use1->removeEventFilter(bigButtonEvent);
		ui.button_use1->setEnabled(false);
		if (move_PP[0] > 0) {
			ui.button_move1->setEnabled(true);
			ui.button_move1->setStyleSheet("background-color: white;"
				"border: 8px solid brown;"
				"border-radius: 15px;"
				"color: black;"
			);

		}
		if (move_PP[1] > 0) {
			ui.button_move2->setEnabled(true);
			ui.button_move2->setStyleSheet("background-color: white;"
				"border: 8px solid brown;"
				"border-radius: 15px;"
				"color: black;"
			);

		}
		if (move_PP[2] > 0) {
			ui.button_move3->setEnabled(true);
			ui.button_move3->setStyleSheet("background-color: white;"
				"border: 8px solid brown;"
				"border-radius: 15px;"
				"color: black;"
			);

		}
		if (move_PP[3] > 0) {
			ui.button_move4->setEnabled(true);
			ui.button_move4->setStyleSheet("background-color: white;"
				"border: 8px solid brown;"
				"border-radius: 15px;"
				"color: black;"
			);
		}
		op_move_use = my_GM.getPlayer2().getRandomValidSkill();
		my_GM.battle(move_use, op_move_use);
		status = "attack";
		update_visual();
		});

	//click fight cancel
	connect(ui.button_cancel_1, &QPushButton::clicked, [this]() {
		click_time = 0;
		QFont font;
		font.setPointSize(35);
		ui.button_use1->setFont(font);
		ui.button_use1->setStyleSheet("background-color: lightGray;"
			"border: 8px solid black;"
			"border-radius: 15px;"
			"color: black;"
		);
		ui.button_use1->setText("ACTION");
		ui.button_use1->setIcon(QIcon());
		ui.button_use1->removeEventFilter(bigButtonEvent);
		ui.button_use1->setEnabled(false);
		if (move_PP[0] > 0) {
			ui.button_move1->setEnabled(true);
			ui.button_move1->setStyleSheet("background-color: white;"
				"border: 8px solid brown;"
				"border-radius: 15px;"
				"color: black;"
			);
			
		}
		if (move_PP[1] > 0) {
			ui.button_move2->setEnabled(true);
			ui.button_move2->setStyleSheet("background-color: white;"
				"border: 8px solid brown;"
				"border-radius: 15px;"
				"color: black;"
			);
			
		}
		if (move_PP[2] > 0) {
			ui.button_move3->setEnabled(true);
			ui.button_move3->setStyleSheet("background-color: white;"
				"border: 8px solid brown;"
				"border-radius: 15px;"
				"color: black;"
			);
			
		}
		if (move_PP[3] > 0) {
			ui.button_move4->setEnabled(true);
			ui.button_move4->setStyleSheet("background-color: white;"
				"border: 8px solid brown;"
				"border-radius: 15px;"
				"color: black;"
			);
		}
		ui.stackedWidget_switch_small->setCurrentWidget(ui.page_option);
		});

	//click pokemon1
	connect(ui.button_pokemon1, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			ui.button_pokemon1->setStyleSheet("background-color: blue;"
									"border: 8px solid lightBlue;"
									"border-top-left-radius: 30px;"
									"border-bottom-right-radius: 30px;"
									"color: white;"
									"text-align: left;"
			);
			ui.button_switch->setStyleSheet("background-color: darkGray;"
											"border: 8px solid #292927;"
											"border-radius: 15px;"
											"color: black;"
			);
			ui.button_switch->installEventFilter(bigButtonEvent);
			ui.button_switch->setEnabled(true);
			ui.button_pokemon2->setEnabled(false);
			ui.button_pokemon3->setEnabled(false);
			ui.button_pokemon4->setEnabled(false);
			ui.button_pokemon5->setEnabled(false);
			ui.button_pokemon6->setEnabled(false);
			pokemon_use = my_pokemon_name[0];
		}
		else if (click_time == 1) {
			click_time = 0;
			ui.button_pokemon1->setStyleSheet("background-color: darkBlue;"
									"border: 4px solid white;"
									"border-top-left-radius: 30px;"
									"border-bottom-right-radius: 30px;"
									"color: white;"
									"text-align: left;"
			);
			ui.button_switch->setStyleSheet("background-color: lightGray;"
									"border: 8px solid #292927;"
									"border-radius: 15px;"
									"color: black;"
			);
			ui.button_switch->removeEventFilter(bigButtonEvent);
			ui.button_switch->setEnabled(false);
			if (my_pokemon_HP[1] != 0) {
				ui.button_pokemon2->setEnabled(true);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_pokemon3->setEnabled(true);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_pokemon4->setEnabled(true);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_pokemon5->setEnabled(true);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_pokemon6->setEnabled(true);
			}
			pokemon_use = "";
		}
		});

	//click pokemon2
	connect(ui.button_pokemon2, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			ui.button_pokemon2->setStyleSheet("background-color: blue;"
				"border: 8px solid lightBlue;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
			ui.button_switch->setStyleSheet("background-color: darkGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_switch->installEventFilter(bigButtonEvent);
			ui.button_switch->setEnabled(true);
			ui.button_pokemon1->setEnabled(false);
			ui.button_pokemon3->setEnabled(false);
			ui.button_pokemon4->setEnabled(false);
			ui.button_pokemon5->setEnabled(false);
			ui.button_pokemon6->setEnabled(false);
			pokemon_use = my_pokemon_name[1];
		}
		else if (click_time == 1) {
			click_time = 0;
			ui.button_pokemon2->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
			ui.button_switch->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_switch->removeEventFilter(bigButtonEvent);
			ui.button_switch->setEnabled(false);
			if (my_pokemon_HP[0] > 0) {
				ui.button_pokemon1->setEnabled(true);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_pokemon3->setEnabled(true);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_pokemon4->setEnabled(true);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_pokemon5->setEnabled(true);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_pokemon6->setEnabled(true);
			}
			pokemon_use = "";
		}
		});
	
	//click pokemon3
	connect(ui.button_pokemon3, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			ui.button_pokemon3->setStyleSheet("background-color: blue;"
				"border: 8px solid lightBlue;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
			ui.button_switch->setStyleSheet("background-color: darkGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_switch->installEventFilter(bigButtonEvent);
			ui.button_switch->setEnabled(true);
			ui.button_pokemon1->setEnabled(false);
			ui.button_pokemon2->setEnabled(false);
			ui.button_pokemon4->setEnabled(false);
			ui.button_pokemon5->setEnabled(false);
			ui.button_pokemon6->setEnabled(false);
			pokemon_use = my_pokemon_name[2];
		}
		else if (click_time == 1) {
			click_time = 0;
			ui.button_pokemon3->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
			ui.button_switch->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_switch->removeEventFilter(bigButtonEvent);
			ui.button_switch->setEnabled(false);
			if (my_pokemon_HP[0] > 0) {
				ui.button_pokemon1->setEnabled(true);
			}
			if (my_pokemon_HP[1] > 0) {
				ui.button_pokemon2->setEnabled(true);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_pokemon4->setEnabled(true);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_pokemon5->setEnabled(true);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_pokemon6->setEnabled(true);
			}
			pokemon_use = "";
		}
		});

	//click pokemon4
	connect(ui.button_pokemon4, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			ui.button_pokemon1->setStyleSheet("background-color: blue;"
				"border: 8px solid lightBlue;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
			ui.button_switch->setStyleSheet("background-color: darkGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_switch->installEventFilter(bigButtonEvent);
			ui.button_switch->setEnabled(true);
			ui.button_pokemon1->setEnabled(false);
			ui.button_pokemon2->setEnabled(false);
			ui.button_pokemon3->setEnabled(false);
			ui.button_pokemon5->setEnabled(false);
			ui.button_pokemon6->setEnabled(false);
			pokemon_use = my_pokemon_name[3];
		}
		else if (click_time == 1) {
			click_time = 0;
			ui.button_pokemon1->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
			ui.button_switch->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_switch->removeEventFilter(bigButtonEvent);
			ui.button_switch->setEnabled(false);
			if (my_pokemon_HP[0] > 0) {
				ui.button_pokemon1->setEnabled(true);
			}
			if (my_pokemon_HP[1] > 0) {
				ui.button_pokemon2->setEnabled(true);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_pokemon3->setEnabled(true);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_pokemon5->setEnabled(true);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_pokemon6->setEnabled(true);
			}
			pokemon_use = "";
		}
		});

	//click pokemon5
	connect(ui.button_pokemon5, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			ui.button_pokemon2->setStyleSheet("background-color: blue;"
				"border: 8px solid lightBlue;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
			ui.button_switch->setStyleSheet("background-color: darkGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_switch->installEventFilter(bigButtonEvent);
			ui.button_switch->setEnabled(true);
			ui.button_pokemon1->setEnabled(false);
			ui.button_pokemon2->setEnabled(false);
			ui.button_pokemon3->setEnabled(false);
			ui.button_pokemon4->setEnabled(false);
			ui.button_pokemon6->setEnabled(false);
			pokemon_use = my_pokemon_name[4];
		}
		else if (click_time == 1) {
			click_time = 0;
			ui.button_pokemon2->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
			ui.button_switch->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_switch->removeEventFilter(bigButtonEvent);
			ui.button_switch->setEnabled(false);
			if (my_pokemon_HP[0] > 0) {
				ui.button_pokemon1->setEnabled(true);
			}
			if (my_pokemon_HP[1] > 0) {
				ui.button_pokemon2->setEnabled(true);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_pokemon3->setEnabled(true);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_pokemon4->setEnabled(true);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_pokemon6->setEnabled(true);
			}
			pokemon_use = "";
		}
		});

	//click pokemon6
	connect(ui.button_pokemon6, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			ui.button_pokemon3->setStyleSheet("background-color: blue;"
				"border: 8px solid lightBlue;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
			ui.button_switch->setStyleSheet("background-color: darkGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_switch->installEventFilter(bigButtonEvent);
			ui.button_switch->setEnabled(true);
			ui.button_pokemon1->setEnabled(false);
			ui.button_pokemon2->setEnabled(false);
			ui.button_pokemon3->setEnabled(false);
			ui.button_pokemon4->setEnabled(false);
			ui.button_pokemon5->setEnabled(false);
			pokemon_use = my_pokemon_name[5];
		}
		else if (click_time == 1) {
			click_time = 0;
			ui.button_pokemon3->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
			ui.button_switch->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_switch->removeEventFilter(bigButtonEvent);
			ui.button_switch->setEnabled(false);
			if (my_pokemon_HP[0] != 0) {
				ui.button_pokemon1->setEnabled(true);
			}
			if (my_pokemon_HP[1] > 0) {
				ui.button_pokemon2->setEnabled(true);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_pokemon3->setEnabled(true);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_pokemon4->setEnabled(true);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_pokemon5->setEnabled(true);
			}
			pokemon_use = "";
		}
		});
	
	//click switch
	connect(ui.button_switch, &QPushButton::clicked, [this]() {
		click_time = 0;
		if (my_pokemon_HP[0] != -1) {
			ui.button_pokemon1->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
		}
		if (my_pokemon_HP[1] != -1) {
			ui.button_pokemon2->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
		}
		if (my_pokemon_HP[2] != -1) {
			ui.button_pokemon3->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
		}

		if (my_pokemon_HP[3] != -1) {
			ui.button_pokemon4->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
		}

		if (my_pokemon_HP[4] != -1) {
			ui.button_pokemon5->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
		}

		if (my_pokemon_HP[5] != -1) {
			ui.button_pokemon6->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
		}
		ui.button_switch->setStyleSheet("background-color: lightGray;"
			"border: 8px solid #292927;"
			"border-radius: 15px;"
			"color: black;"
		);
		ui.button_switch->removeEventFilter(bigButtonEvent);
		ui.button_switch->setEnabled(false);
		if (my_pokemon_HP[0] > 0) {
			ui.button_pokemon1->setEnabled(true);
		}
		if (my_pokemon_HP[1] > 0) {
			ui.button_pokemon2->setEnabled(true);
		}
		if (my_pokemon_HP[2] > 0) {
			ui.button_pokemon3->setEnabled(true);
		}
		if (my_pokemon_HP[3] > 0) {
			ui.button_pokemon4->setEnabled(true);
		}
		if (my_pokemon_HP[4] > 0) {
			ui.button_pokemon5->setEnabled(true);
		}
		if (my_pokemon_HP[5] > 0) {
			ui.button_pokemon6->setEnabled(true);
		}
		
		text_list_index = 0;
		text_list.clear();
		if (deadSwap == 1) {
			text_list << "Go! " + QString::fromStdString(pokemon_use);
			my_GM.swapPokemon(my_GM.getPlayer1(), pokemon_use);
			deadSwap = 0;
			text_list_index++;
			ui.button_dialog->setText(text_list[0]);
			ui.label_log->setText(ui.label_log->text() + text_list[0] + "\n");
			ui.stackedWidget_switch_big->setCurrentWidget(ui.page_main);
			ui.stackedWidget_switch_small->setCurrentWidget(ui.page_dialog);
		}
		else if (deadSwap == 0) {
			text_list << QString::fromStdString(current_pokemon_name) + ", come back!";
			my_GM.swapPokemon(my_GM.getPlayer1(), pokemon_use);
			op_move_use = my_GM.getPlayer2().getRandomValidSkill();
			my_GM.battle("no", op_move_use);
			status = "swap";
			update_visual();
		}
		
		});

	//click pokemon cancel
	connect(ui.button_cancel_2, &QPushButton::clicked, [this]() {
		click_time = 0;
		ui.stackedWidget_switch_big->setCurrentWidget(ui.page_main);
		ui.stackedWidget_switch_small->setCurrentWidget(ui.page_option);
		if (my_pokemon_HP[0] != -1) {
			ui.button_pokemon1->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
		}
		if (my_pokemon_HP[1] != -1) {
			ui.button_pokemon2->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
		}
		if (my_pokemon_HP[2] != -1) {
			ui.button_pokemon3->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
		}
		
		if (my_pokemon_HP[3] != -1) {
			ui.button_pokemon4->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
		}
		
		if (my_pokemon_HP[4] != -1) {
			ui.button_pokemon5->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
		}
		
		if (my_pokemon_HP[5] != -1) {
			ui.button_pokemon6->setStyleSheet("background-color: darkBlue;"
				"border: 4px solid white;"
				"border-top-left-radius: 30px;"
				"border-bottom-right-radius: 30px;"
				"color: white;"
				"text-align: left;"
			);
		}
		ui.button_switch->setStyleSheet("background-color: lightGray;"
			"border: 8px solid #292927;"
			"border-radius: 15px;"
			"color: black;"
		);
		ui.button_switch->removeEventFilter(bigButtonEvent);
		ui.button_switch->setEnabled(false);
		if (my_pokemon_HP[0] > 0) {
			ui.button_pokemon1->setEnabled(true);
		}
		if (my_pokemon_HP[1] > 0) {
			ui.button_pokemon2->setEnabled(true);
		}
		if (my_pokemon_HP[2] > 0) {
			ui.button_pokemon3->setEnabled(true);
		}
		if (my_pokemon_HP[3] > 0) {
			ui.button_pokemon4->setEnabled(true);
		}
		if (my_pokemon_HP[4] > 0) {
			ui.button_pokemon5->setEnabled(true);
		}
		if (my_pokemon_HP[5] > 0) {
			ui.button_pokemon6->setEnabled(true);
		}
		
		});

	//click potion
	connect(ui.button_potion, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			ui.button_potion->setStyleSheet("background-color: white;"
									"border: 8px solid darkBlue;"
									"border-radius: 15px;"
			);
			ui.label_potion->setStyleSheet("background-color: white;"
				"border: 8px solid darkBlue;"
				"border-radius: 15px;"
			);
			ui.button_superPotion->setEnabled(false);
			ui.button_hyperPotion->setEnabled(false);
			ui.button_maxPotion->setEnabled(false);
			ui.frame_heal_pokemon->show();
			bag_use = "potion";
		}
		else if (click_time == 1) {
			click_time = 0;
			click_time_2 = 0;
			ui.button_potion->setStyleSheet("background-color: white;"
									"border: 4px solid purple;"
									"border-radius: 15px;"
			);
			ui.label_potion->setStyleSheet("background-color: white;"
				"border: 4px solid purple;"
				"border-radius: 15px;"
			);
			if (superPotion_number != 0) {
				ui.button_superPotion->setEnabled(true);
			}
			if (hyperPotion_number != 0) {
				ui.button_hyperPotion->setEnabled(true);
			}
			if (maxPotion_number != 0) {
				ui.button_maxPotion->setEnabled(true);
			}
			ui.frame_heal_pokemon->hide();
				
			if (my_pokemon_HP[0] > 0) {
				ui.button_heal_p1->setEnabled(true);
				ui.button_heal_p1->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[1] > 0) {
				ui.button_heal_p2->setEnabled(true);
				ui.button_heal_p2->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_heal_p3->setEnabled(true);
				ui.button_heal_p3->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_heal_p4->setEnabled(true);
				ui.button_heal_p4->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_heal_p5->setEnabled(true);
				ui.button_heal_p5->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_heal_p6->setEnabled(true);
				ui.button_heal_p6->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			ui.button_use2->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->removeEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(false);
			bag_use = "";
		}
		});
	
	//click super potion
	connect(ui.button_superPotion, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			ui.button_superPotion->setStyleSheet("background-color: white;"
				"border: 8px solid red;"
				"border-radius: 15px;"
			);
			ui.label_superPotion->setStyleSheet("background-color: white;"
				"border: 8px solid red;"
				"border-radius: 15px;"
			);
			ui.button_potion->setEnabled(false);
			ui.button_hyperPotion->setEnabled(false);
			ui.button_maxPotion->setEnabled(false);
			ui.frame_heal_pokemon->show();
			bag_use = "superPotion";
		}
		else if (click_time == 1) {
			click_time = 0;
			click_time_2 = 0;
			ui.button_superPotion->setStyleSheet("background-color: white;"
				"border: 4px solid orange;"
				"border-radius: 15px;"
			);
			ui.label_superPotion->setStyleSheet("background-color: white;"
				"border: 4px solid orange;"
				"border-radius: 15px;"
			);
			if (potion_number != 0) {
				ui.button_potion->setEnabled(true);
			}
			if (hyperPotion_number != 0) {
				ui.button_hyperPotion->setEnabled(true);
			}
			if (maxPotion_number != 0) {
				ui.button_maxPotion->setEnabled(true);
			}
			ui.frame_heal_pokemon->hide();
			if (my_pokemon_HP[0] > 0) {
				ui.button_heal_p1->setEnabled(true);
				ui.button_heal_p1->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[1] > 0) {
				ui.button_heal_p2->setEnabled(true);
				ui.button_heal_p2->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_heal_p3->setEnabled(true);
				ui.button_heal_p3->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_heal_p4->setEnabled(true);
				ui.button_heal_p4->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_heal_p5->setEnabled(true);
				ui.button_heal_p5->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_heal_p6->setEnabled(true);
				ui.button_heal_p6->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			ui.button_use2->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->removeEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(false);
			bag_use = "";
		}
		});
	
	//click hyper potion
	connect(ui.button_hyperPotion, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			ui.button_hyperPotion->setStyleSheet("background-color: white;"
				"border: 8px solid magenta;"
				"border-radius: 15px;"
			);
			ui.label_hyperPotion->setStyleSheet("background-color: white;"
				"border: 8px solid magenta;"
				"border-radius: 15px;"
			);
			ui.button_potion->setEnabled(false);
			ui.button_superPotion->setEnabled(false);
			ui.button_maxPotion->setEnabled(false);
			ui.frame_heal_pokemon->show();
			bag_use = "hyperPotion";
		}
		else if (click_time == 1) {
			click_time = 0;
			click_time_2 = 0;
			ui.button_hyperPotion->setStyleSheet("background-color: white;"
				"border: 4px solid pink;"
				"border-radius: 15px;"
			);
			ui.label_hyperPotion->setStyleSheet("background-color: white;"
				"border: 4px solid pink;"
				"border-radius: 15px;"
			);
			if (potion_number != 0) {
				ui.button_potion->setEnabled(true);
			}
			if (superPotion_number != 0) {
				ui.button_superPotion->setEnabled(true);
			}
			if (maxPotion_number != 0) {
				ui.button_maxPotion->setEnabled(true);
			}
			ui.frame_heal_pokemon->hide();
			if (my_pokemon_HP[0] > 0) {
				ui.button_heal_p1->setEnabled(true);
				ui.button_heal_p1->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[1] > 0) {
				ui.button_heal_p2->setEnabled(true);
				ui.button_heal_p2->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_heal_p3->setEnabled(true);
				ui.button_heal_p3->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_heal_p4->setEnabled(true);
				ui.button_heal_p4->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_heal_p5->setEnabled(true);
				ui.button_heal_p5->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_heal_p6->setEnabled(true);
				ui.button_heal_p6->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			ui.button_use2->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->removeEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(false);
			bag_use = "";
		}
		});
	
	//click max potion
	connect(ui.button_maxPotion, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			ui.button_maxPotion->setStyleSheet("background-color: white;"
				"border: 8px solid blue;"
				"border-radius: 15px;"
			);
			ui.label_maxPotion->setStyleSheet("background-color: white;"
				"border: 8px solid blue;"
				"border-radius: 15px;"
			);
			ui.button_potion->setEnabled(false);
			ui.button_superPotion->setEnabled(false);
			ui.button_hyperPotion->setEnabled(false);
			ui.frame_heal_pokemon->show();
			bag_use = "maxPotion";
		}
		else if (click_time == 1) {
			click_time = 0;
			click_time_2 = 0;
			ui.button_maxPotion->setStyleSheet("background-color: white;"
				"border: 4px solid lightBlue;"
				"border-radius: 15px;"
			);
			ui.label_maxPotion->setStyleSheet("background-color: white;"
				"border: 4px solid lightBlue;"
				"border-radius: 15px;"
			);
			if (potion_number != 0) {
				ui.button_potion->setEnabled(true);
			}
			if (superPotion_number != 0) {
				ui.button_superPotion->setEnabled(true);
			}
			if (hyperPotion_number != 0) {
				ui.button_hyperPotion->setEnabled(true);
			}
			ui.frame_heal_pokemon->hide();
			if (my_pokemon_HP[0] > 0) {
				ui.button_heal_p1->setEnabled(true);
				ui.button_heal_p1->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[1] > 0) {
				ui.button_heal_p2->setEnabled(true);
				ui.button_heal_p2->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_heal_p3->setEnabled(true);
				ui.button_heal_p3->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_heal_p4->setEnabled(true);
				ui.button_heal_p4->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_heal_p5->setEnabled(true);
				ui.button_heal_p5->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_heal_p6->setEnabled(true);
				ui.button_heal_p6->setStyleSheet("background-color: blue;"
					"border: 3px solid #292927;"
					"border-radius: 15px;"
					"color: white;"
				);
			}
			ui.button_use2->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->removeEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(false);
			bag_use = "";
		}
		});

	//click use potion
	connect(ui.button_use2, &QPushButton::clicked, [this]() {
		click_time = 0;
		click_time_2 = 0;
		ui.button_potion->setStyleSheet("background-color: white;"
			"border: 4px solid purple;"
			"border-radius: 15px;"
		);
		ui.label_potion->setStyleSheet("background-color: white;"
			"border: 4px solid purple;"
			"border-radius: 15px;"
		);
		ui.button_superPotion->setStyleSheet("background-color: white;"
			"border: 4px solid orange;"
			"border-radius: 15px;"
		);
		ui.label_superPotion->setStyleSheet("background-color: white;"
			"border: 4px solid orange;"
			"border-radius: 15px;"
		);
		ui.button_hyperPotion->setStyleSheet("background-color: white;"
			"border: 4px solid pink;"
			"border-radius: 15px;"
		);
		ui.label_hyperPotion->setStyleSheet("background-color: white;"
			"border: 4px solid pink;"
			"border-radius: 15px;"
		);
		ui.button_maxPotion->setStyleSheet("background-color: white;"
			"border: 4px solid lightBlue;"
			"border-radius: 15px;"
		);
		ui.label_hyperPotion->setStyleSheet("background-color: white;"
			"border: 4px solid pink;"
			"border-radius: 15px;"
		);
		ui.button_use2->setStyleSheet("background-color: lightGray;"
			"border: 8px solid #292927;"
			"border-radius: 15px;"
			"color: black;"
		);
		ui.button_use2->removeEventFilter(bigButtonEvent);
		ui.button_use2->setEnabled(false);

		if (potion_number != 0) {
			ui.button_potion->setEnabled(true);
		}
		if (superPotion_number != 0) {
			ui.button_superPotion->setEnabled(true);
		}
		if (hyperPotion_number != 0) {
			ui.button_hyperPotion->setEnabled(true);
		}
		if (maxPotion_number != 0) {
			ui.button_maxPotion->setEnabled(true);
		}
		ui.frame_heal_pokemon->hide();
		if (my_pokemon_HP[0] > 0) {
			ui.button_heal_p1->setEnabled(true);
			ui.button_heal_p1->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
		}
		if (my_pokemon_HP[1] > 0) {
			ui.button_heal_p2->setEnabled(true);
			ui.button_heal_p2->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
		}
		if (my_pokemon_HP[2] > 0) {
			ui.button_heal_p3->setEnabled(true);
			ui.button_heal_p3->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
		}
		if (my_pokemon_HP[3] > 0) {
			ui.button_heal_p4->setEnabled(true);
			ui.button_heal_p4->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
		}
		if (my_pokemon_HP[4] > 0) {
			ui.button_heal_p5->setEnabled(true);
			ui.button_heal_p5->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
		}
		if (my_pokemon_HP[5] > 0) {
			ui.button_heal_p6->setEnabled(true);
			ui.button_heal_p6->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
		}
		my_GM.getPlayer1().usePotion(bag_use, pokemon_use);
		op_move_use = my_GM.getPlayer2().getRandomValidSkill();
		my_GM.battle("no", op_move_use);
		status = "heal";
		update_visual();
		});

	//click bag cancel
	connect(ui.button_cancel_3, &QPushButton::clicked, [this]() {
		ui.stackedWidget_switch_big->setCurrentWidget(ui.page_main);
		ui.stackedWidget_switch_small->setCurrentWidget(ui.page_option);
		click_time = 0;
		click_time_2 = 0;
		ui.button_potion->setStyleSheet("background-color: white;"
			"border: 4px solid purple;"
			"border-radius: 15px;"
		);
		ui.label_potion->setStyleSheet("background-color: white;"
			"border: 4px solid purple;"
			"border-radius: 15px;"
		);
		ui.button_superPotion->setStyleSheet("background-color: white;"
			"border: 4px solid orange;"
			"border-radius: 15px;"
		);
		ui.label_superPotion->setStyleSheet("background-color: white;"
			"border: 4px solid orange;"
			"border-radius: 15px;"
		);
		ui.button_hyperPotion->setStyleSheet("background-color: white;"
			"border: 4px solid pink;"
			"border-radius: 15px;"
		);
		ui.label_hyperPotion->setStyleSheet("background-color: white;"
			"border: 4px solid pink;"
			"border-radius: 15px;"
		);
		ui.button_maxPotion->setStyleSheet("background-color: white;"
			"border: 4px solid lightBlue;"
			"border-radius: 15px;"
		);
		ui.label_hyperPotion->setStyleSheet("background-color: white;"
			"border: 4px solid pink;"
			"border-radius: 15px;"
		);
		ui.button_use2->setStyleSheet("background-color: lightGray;"
			"border: 8px solid #292927;"
			"border-radius: 15px;"
			"color: black;"
		);
		ui.button_use2->removeEventFilter(bigButtonEvent);
		ui.button_use2->setEnabled(false);
		
		if (potion_number != 0) {
			ui.button_potion->setEnabled(true);
		}
		if (superPotion_number != 0) {
			ui.button_superPotion->setEnabled(true);
		}
		if (hyperPotion_number != 0) {
			ui.button_hyperPotion->setEnabled(true);
		}
		if (maxPotion_number != 0) {
			ui.button_maxPotion->setEnabled(true);
		}
		ui.frame_heal_pokemon->hide();
		if (my_pokemon_HP[0] > 0) {
			ui.button_heal_p1->setEnabled(true);
			ui.button_heal_p1->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
		}
		if (my_pokemon_HP[1] > 0) {
			ui.button_heal_p2->setEnabled(true);
			ui.button_heal_p2->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
		}
		if (my_pokemon_HP[2] > 0) {
			ui.button_heal_p3->setEnabled(true);
			ui.button_heal_p3->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
		}
		if (my_pokemon_HP[3] > 0) {
			ui.button_heal_p4->setEnabled(true);
			ui.button_heal_p4->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
		}
		if (my_pokemon_HP[4] > 0) {
			ui.button_heal_p5->setEnabled(true);
			ui.button_heal_p5->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
		}
		if (my_pokemon_HP[5] > 0) {
			ui.button_heal_p6->setEnabled(true);
			ui.button_heal_p6->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
		}
		
		
		
		
		});

	//click heal pokemon1
	connect(ui.button_heal_p1, &QPushButton::clicked, [this]() {
		if (click_time_2 == 0) {
			click_time_2 = 1;
			ui.button_heal_p1->setStyleSheet("background-color: blue;"
				"border: 3px solid lightBlue;"
				"border-radius: 15px;"
				"color: white;"
			);
			ui.button_use2->setStyleSheet("background-color: darkGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->installEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(true);
			ui.button_heal_p2->setEnabled(false);
			ui.button_heal_p3->setEnabled(false);
			ui.button_heal_p4->setEnabled(false);
			ui.button_heal_p5->setEnabled(false);
			ui.button_heal_p6->setEnabled(false);
			pokemon_use = my_GM.getPlayer1().getPokemons()[0].getName();
		}
		else if (click_time_2 == 1) {
			click_time_2 = 0;
			ui.button_heal_p1->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
			ui.button_use2->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->removeEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(false);
			if (my_pokemon_HP[1] > 0) {
				ui.button_heal_p2->setEnabled(true);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_heal_p3->setEnabled(true);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_heal_p4->setEnabled(true);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_heal_p5->setEnabled(true);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_heal_p6->setEnabled(true);
			}
			pokemon_use = "";
		}
		});

	//click heal pokemon2
	connect(ui.button_heal_p2, &QPushButton::clicked, [this]() {
		if (click_time_2 == 0) {
			click_time_2 = 1;
			ui.button_heal_p2->setStyleSheet("background-color: blue;"
				"border: 3px solid lightBlue;"
				"border-radius: 15px;"
				"color: white;"
			);
			ui.button_use2->setStyleSheet("background-color: darkGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->installEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(true);
			ui.button_heal_p1->setEnabled(false);
			ui.button_heal_p3->setEnabled(false);
			ui.button_heal_p4->setEnabled(false);
			ui.button_heal_p5->setEnabled(false);
			ui.button_heal_p6->setEnabled(false);
			pokemon_use = my_GM.getPlayer1().getPokemons()[1].getName();
		}
		else if (click_time_2 == 1) {
			click_time_2 = 0;
			ui.button_heal_p2->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
			ui.button_use2->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->removeEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(false);
			if (my_pokemon_HP[0] > 0) {
				ui.button_heal_p1->setEnabled(true);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_heal_p3->setEnabled(true);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_heal_p4->setEnabled(true);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_heal_p5->setEnabled(true);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_heal_p6->setEnabled(true);
			}
			pokemon_use = "";
		}
		});

	//click heal pokemon3
	connect(ui.button_heal_p3, &QPushButton::clicked, [this]() {
		if (click_time_2 == 0) {
			click_time_2 = 1;
			ui.button_heal_p3->setStyleSheet("background-color: blue;"
				"border: 3px solid lightBlue;"
				"border-radius: 15px;"
				"color: white;"
			);
			ui.button_use2->setStyleSheet("background-color: darkGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->installEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(true);
			ui.button_heal_p2->setEnabled(false);
			ui.button_heal_p1->setEnabled(false);
			ui.button_heal_p4->setEnabled(false);
			ui.button_heal_p5->setEnabled(false);
			ui.button_heal_p6->setEnabled(false);
			pokemon_use = my_GM.getPlayer1().getPokemons()[2].getName();
		}
		else if (click_time_2 == 1) {
			click_time_2 = 0;
			ui.button_heal_p3->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
			ui.button_use2->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->removeEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(false);
			if (my_pokemon_HP[1] > 0) {
				ui.button_heal_p2->setEnabled(true);
			}
			if (my_pokemon_HP[0] > 0) {
				ui.button_heal_p1->setEnabled(true);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_heal_p4->setEnabled(true);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_heal_p5->setEnabled(true);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_heal_p6->setEnabled(true);
			}
			pokemon_use = "";
		}
		});

	//click heal pokemon4
	connect(ui.button_heal_p4, &QPushButton::clicked, [this]() {
		if (click_time_2 == 0) {
			click_time_2 = 1;
			ui.button_heal_p4->setStyleSheet("background-color: blue;"
				"border: 3px solid lightBlue;"
				"border-radius: 15px;"
				"color: white;"
			);
			ui.button_use2->setStyleSheet("background-color: darkGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->installEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(true);
			ui.button_heal_p2->setEnabled(false);
			ui.button_heal_p3->setEnabled(false);
			ui.button_heal_p1->setEnabled(false);
			ui.button_heal_p5->setEnabled(false);
			ui.button_heal_p6->setEnabled(false);
			pokemon_use = my_GM.getPlayer1().getPokemons()[3].getName();
		}
		else if (click_time_2 == 1) {
			click_time_2 = 0;
			ui.button_heal_p4->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
			ui.button_use2->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->removeEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(false);
			if (my_pokemon_HP[1] > 0) {
				ui.button_heal_p2->setEnabled(true);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_heal_p3->setEnabled(true);
			}
			if (my_pokemon_HP[0] > 0) {
				ui.button_heal_p1->setEnabled(true);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_heal_p5->setEnabled(true);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_heal_p6->setEnabled(true);
			}
			pokemon_use = "";
		}
		});

	//click heal pokemon5
	connect(ui.button_heal_p5, &QPushButton::clicked, [this]() {
		if (click_time_2 == 0) {
			click_time_2 = 1;
			ui.button_heal_p5->setStyleSheet("background-color: blue;"
				"border: 3px solid lightBlue;"
				"border-radius: 15px;"
				"color: white;"
			);
			ui.button_use2->setStyleSheet("background-color: darkGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->installEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(true);
			ui.button_heal_p2->setEnabled(false);
			ui.button_heal_p3->setEnabled(false);
			ui.button_heal_p4->setEnabled(false);
			ui.button_heal_p1->setEnabled(false);
			ui.button_heal_p6->setEnabled(false);
			pokemon_use = my_GM.getPlayer1().getPokemons()[4].getName();
		}
		else if (click_time_2 == 1) {
			click_time_2 = 0;
			ui.button_heal_p1->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
			ui.button_use2->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->removeEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(false);
			if (my_pokemon_HP[1] > 0) {
				ui.button_heal_p2->setEnabled(true);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_heal_p3->setEnabled(true);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_heal_p4->setEnabled(true);
			}
			if (my_pokemon_HP[0] > 0) {
				ui.button_heal_p1->setEnabled(true);
			}
			if (my_pokemon_HP[5] > 0) {
				ui.button_heal_p6->setEnabled(true);
			}
			pokemon_use = "";
		}
		});

	//click heal pokemon6
	connect(ui.button_heal_p6, &QPushButton::clicked, [this]() {
		if (click_time_2 == 0) {
			click_time_2 = 1;
			ui.button_heal_p1->setStyleSheet("background-color: blue;"
				"border: 3px solid lightBlue;"
				"border-radius: 15px;"
				"color: white;"
			);
			ui.button_use2->setStyleSheet("background-color: darkGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->installEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(true);
			ui.button_heal_p2->setEnabled(false);
			ui.button_heal_p3->setEnabled(false);
			ui.button_heal_p4->setEnabled(false);
			ui.button_heal_p5->setEnabled(false);
			ui.button_heal_p1->setEnabled(false);
			pokemon_use = my_GM.getPlayer1().getPokemons()[5].getName();
		}
		else if (click_time_2 == 1) {
			click_time_2 = 0;
			ui.button_heal_p6->setStyleSheet("background-color: blue;"
				"border: 3px solid #292927;"
				"border-radius: 15px;"
				"color: white;"
			);
			ui.button_use2->setStyleSheet("background-color: lightGray;"
				"border: 8px solid #292927;"
				"border-radius: 15px;"
				"color: black;"
			);
			ui.button_use2->removeEventFilter(bigButtonEvent);
			ui.button_use2->setEnabled(false);
			if (my_pokemon_HP[1] > 0) {
				ui.button_heal_p2->setEnabled(true);
			}
			if (my_pokemon_HP[2] > 0) {
				ui.button_heal_p3->setEnabled(true);
			}
			if (my_pokemon_HP[3] > 0) {
				ui.button_heal_p4->setEnabled(true);
			}
			if (my_pokemon_HP[4] > 0) {
				ui.button_heal_p5->setEnabled(true);
			}
			if (my_pokemon_HP[0] > 0) {
				ui.button_heal_p1->setEnabled(true);
			}
			pokemon_use = "";
		}
		});

	//click log
	connect(ui.button_log, &QPushButton::clicked, [this]() {
		if (click_time == 0) {
			click_time = 1;
			ui.scrollArea_log->show();
		}
		else if (click_time == 1) {
			click_time = 0;
			ui.scrollArea_log->hide();
		}
		
		});
}

battle_scene::~battle_scene()
{
}

void battle_scene::initiation() {
	//initiaiton
	status = "choose";
	ui.stackedWidget_switch_big->setCurrentWidget(ui.page_main);
	ui.stackedWidget_switch_small->setCurrentWidget(ui.page_option);
	ui.scrollArea_log->hide();
	ui.label_log->setText("");


	//set background
	random = QRandomGenerator::global()->bounded(1, 9);
	switch (random) {
	case 1:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/beach.png)}");
		break;
	case 2:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/desert.png)}");
		break;
	case 3:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/forest1.png)}");
		break;
	case 4:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/forest2.png)}");
		break;
	case 5:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/land.png)}");
		break;
	case 6:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/purple.png)}");
		break;
	case 7:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/sand.png)}");
		break;
	case 8:
		ui.frame_main_background->setStyleSheet("QFrame#frame_main_background{border-image:url(./Resources/pic/background/sea.png)}");
		break;
	}
	ui.frame_dialog->setStyleSheet("QFrame#frame_dialog{"
		"	border-top: 8px solid #292927;"
		"	background-image:url(./Resources/pic/background/dialog.png);"
		" }");

	//set exist pokemon
	for (int i = 0; i < 6; i++) {
		my_pokemon_HP[i] = -1;
		op_pokemon_HP[i] = -1;
	}
	ui.label_p1->hide();
	ui.label_p2->hide();
	ui.label_p3->hide();
	ui.label_p4->hide();
	ui.label_p5->hide();
	ui.label_p6->hide();
	ui.label_p1_2->hide();
	ui.label_p2_2->hide();
	ui.label_p3_2->hide();
	ui.label_p4_2->hide();
	ui.label_p5_2->hide();
	ui.label_p6_2->hide();
	my_pokemon_num = my_GM.getPlayer1().getPokemons().size();
	op_pokemon_num = my_GM.getPlayer2().getPokemons().size();
	for (int i = 0; i < my_pokemon_num; i++) {
		my_pokemon_HP[i] = 0;
	}
	for (int i = 0; i < op_pokemon_num; i++) {
		op_pokemon_HP[i] = 0;
	}
	if (my_pokemon_HP[0] == 0) {
		ui.button_pokemon1->setStyleSheet("background-color: darkBlue;"
			"border: 4px solid white;"
			"border-top-left-radius: 30px;"
			"border-bottom-right-radius: 30px;"
			"color: white;"
			"text-align: left;"
		);
		ui.button_pokemon1->setEnabled(true);
		ui.label_p1->show();
		ui.button_heal_p1->setStyleSheet("background-color: blue;"
			"border: 3px solid #292927;"
			"border-radius: 15px;"
			"color: white;"
		);
	}
	if (my_pokemon_HP[1] == 0) {
		ui.button_pokemon2->setStyleSheet("background-color: darkBlue;"
			"border: 4px solid white;"
			"border-top-left-radius: 30px;"
			"border-bottom-right-radius: 30px;"
			"color: white;"
			"text-align: left;"
		);
		ui.button_pokemon2->setEnabled(true);
		ui.label_p2->show();
		ui.button_heal_p2->setStyleSheet("background-color: blue;"
			"border: 3px solid #292927;"
			"border-radius: 15px;"
			"color: white;"
		);
	}
	if (my_pokemon_HP[2] == 0) {
		ui.button_pokemon3->setStyleSheet("background-color: darkBlue;"
			"border: 4px solid white;"
			"border-top-left-radius: 30px;"
			"border-bottom-right-radius: 30px;"
			"color: white;"
			"text-align: left;"
		);
		ui.button_pokemon3->setEnabled(true);
		ui.label_p3->show();
		ui.button_heal_p3->setStyleSheet("background-color: blue;"
			"border: 3px solid #292927;"
			"border-radius: 15px;"
			"color: white;"
		);
	}
	if (my_pokemon_HP[3] == 0) {
		ui.button_pokemon4->setStyleSheet("background-color: darkBlue;"
			"border: 4px solid white;"
			"border-top-left-radius: 30px;"
			"border-bottom-right-radius: 30px;"
			"color: white;"
			"text-align: left;"
		);
		ui.button_pokemon4->setEnabled(true);
		ui.label_p4->show();
		ui.button_heal_p4->setStyleSheet("background-color: blue;"
			"border: 3px solid #292927;"
			"border-radius: 15px;"
			"color: white;"
		);
	}
	if (my_pokemon_HP[4] == 0) {
		ui.button_pokemon5->setStyleSheet("background-color: darkBlue;"
			"border: 4px solid white;"
			"border-top-left-radius: 30px;"
			"border-bottom-right-radius: 30px;"
			"color: white;"
			"text-align: left;"
		);
		ui.button_pokemon5->setEnabled(true);
		ui.label_p5->show();
		ui.button_heal_p5->setStyleSheet("background-color: blue;"
			"border: 3px solid #292927;"
			"border-radius: 15px;"
			"color: white;"
		);
	}
	if (my_pokemon_HP[5] == 0) {
		ui.button_pokemon6->setStyleSheet("background-color: darkBlue;"
			"border: 4px solid white;"
			"border-top-left-radius: 30px;"
			"border-bottom-right-radius: 30px;"
			"color: white;"
			"text-align: left;"
		);
		ui.button_pokemon6->setEnabled(true);
		ui.label_p6->show();
		ui.button_heal_p6->setStyleSheet("background-color: blue;"
			"border: 3px solid #292927;"
			"border-radius: 15px;"
			"color: white;"
		);
	}
	if (op_pokemon_HP[0] == 0) {
		ui.label_p1_2->show();
	}
	if (op_pokemon_HP[1] == 0) {
		ui.label_p2_2->show();
	}
	if (op_pokemon_HP[2] == 0) {
		ui.label_p3_2->show();
	}
	if (op_pokemon_HP[3] == 0) {
		ui.label_p4_2->show();
	}
	if (op_pokemon_HP[4] == 0) {
		ui.label_p5_2->show();
	}
	if (op_pokemon_HP[5] == 0) {
		ui.label_p6_2->show();
	}

	if (isLoad_game == true) {
		loadData(temp_log);
		isLoad_game = false;
		testMode = false;
		text_list.clear();
		status = "choose";
	}
	//testMode = true;
	//play music
	//playlist2->addMedia(QUrl::fromLocalFile("./Resources/music/battle.wav"));
	//playlist2->setPlaybackMode(QMediaPlaylist::Loop);
	//music2->setPlaylist(playlist2);
	//music2->setVolume(10);
	//music2->play();

	//update
	update_visual();
	
}

void battle_scene::update_visual() {
	QPixmap pokemon_pic;
	QPixmap scaledPixmap;
	QPixmap scaledPixmap2;
	QPixmap pic;
	QPixmap grayPixmap;
	
	//set who go first
	

	//player1
	// 
	// 
	//load data
	//
	for (int i = 0; i < my_pokemon_num; i++) {
		my_pokemon_name[i] = my_GM.getPlayer1().getPokemons()[i].getName();
		my_pokemon_HP[i] = my_GM.getPlayer1().getPokemons()[i].getHP();
		my_pokemon_maxHP[i] = my_GM.getPlayer1().getPokemons()[i].getMaximumHP();
	}
	for (int i = 0; i < 4; i++) {
		move_PP[i] = -1;
	}
	move_num = my_GM.getPlayer1().getCurrentPokemon().getSkills().size();
	for (int i = 0; i < move_num; i++) {
		current_move[i] = my_GM.getPlayer1().getCurrentPokemon().getSkills()[i].getName();
		move_PP[i] = my_GM.getPlayer1().getCurrentPokemon().getSkills()[i].getPP();
		move_maxPP[i] = my_GM.getPlayer1().getCurrentPokemon().getSkills()[i].getMaximumPP();
		move_type[i] = my_GM.getPlayer1().getCurrentPokemon().getSkills()[i].getPokemonType();
	}

	current_pokemon_name = my_GM.getPlayer1().getCurrentPokemon().getName();
	current_HP = my_GM.getPlayer1().getCurrentPokemon().getHP();
	current_maxHP = my_GM.getPlayer1().getCurrentPokemon().getMaximumHP();
	pokemon_condition.clear();
	pokemon_condition = my_GM.getPlayer1().getCurrentPokemon().getConditions();
	potion_number = my_GM.getPlayer1().getPotion();
	superPotion_number = my_GM.getPlayer1().getSuperPotion();
	hyperPotion_number = my_GM.getPlayer1().getHyperPotion();
	maxPotion_number = my_GM.getPlayer1().getMaxPotion();
	
	//change pokemon pic and status  and remained pokemon on background
	// 
	//set player1 pokemon pic
	path = "./Resources/pic/pokemon/" + QString::fromStdString(current_pokemon_name) + ".png";
	pokemon_pic.load(path);
	scaledPixmap = pokemon_pic.scaledToHeight(350);
	ui.label_pokemon1->setPixmap(scaledPixmap);
	//set player1 pokemon name and HP
	text = QString::fromStdString(current_pokemon_name) + "\n";
	text = text + "HP : " + QString::number(current_HP) + "/" + QString::number(current_maxHP) + "\n";
	ui.label_status1->setText(text);
	font_temp2.setPointSize(30);
	ui.label_status1->setFont(font_temp2);
	//set player1 pokemon condition
	if (pokemon_condition.find(Condition::BRN) != pokemon_condition.end()) {
		ui.label_BRN1->setVisible(true);
	}
	else {
		ui.label_BRN1->setVisible(false);
	}
	if (pokemon_condition.find(Condition::PSN) != pokemon_condition.end()) {
		ui.label_PSN1->setVisible(true);
	}
	else {
		ui.label_PSN1->setVisible(false);
	}
	if (pokemon_condition.find(Condition::PAR) != pokemon_condition.end()) {
		ui.label_PAR1->setVisible(true);
	}
	else {
		ui.label_PAR1->setVisible(false);
	}
	//set remained pokemon
	pic.load("./Resources/pic/other/pokeball.png");
	pic = pic.scaledToWidth(25);
	grayPixmap.load("./Resources/pic/other/gray_pokeball.png");
	grayPixmap = grayPixmap.scaledToWidth(25);
	if (my_pokemon_HP[0] == 0) {
		ui.label_p1->setPixmap(grayPixmap);
	}
	else {
		ui.label_p1->setPixmap(pic);
	}
	if (my_pokemon_HP[1] == 0) {
		ui.label_p2->setPixmap(grayPixmap);
	}
	else {
		ui.label_p2->setPixmap(pic);
	}
	if (my_pokemon_HP[2] == 0) {
		ui.label_p3->setPixmap(grayPixmap);
	}
	else {
		ui.label_p3->setPixmap(pic);
	}
	if (my_pokemon_HP[3] == 0) {
		ui.label_p4->setPixmap(grayPixmap);
	}
	else {
		ui.label_p4->setPixmap(pic);
	}
	if (my_pokemon_HP[4] == 0) {
		ui.label_p5->setPixmap(grayPixmap);
	}
	else {
		ui.label_p5->setPixmap(pic);
	}
	if (my_pokemon_HP[5] == 0) {
		ui.label_p6->setPixmap(grayPixmap);
	}
	else {
		ui.label_p6->setPixmap(pic);
	}
	
	//change option's dialog
	//
	text = "What will\n" + QString::fromStdString(current_pokemon_name) + " do?";
	ui.label_dialog1->setText(text);
	
	//change move 1~4
	// 
	//set 0 move
	ui.button_move1->setStyleSheet("background-color: Black;"
			"border: 8px solid black;"
			"border-radius: 15px;"
		"color: black;");
	ui.button_move1->setEnabled(false);
	ui.button_move2->setStyleSheet("background-color: Black;"
		"border: 8px solid black;"
		"border-radius: 15px;"
		"color: black;");
	ui.button_move2->setEnabled(false);
	ui.button_move3->setStyleSheet("background-color: Black;"
		"border: 8px solid black;"
		"border-radius: 15px;"
		"color: black;");
	ui.button_move3->setEnabled(false);
	ui.button_move4->setStyleSheet("background-color: Black;"
		"border: 8px solid black;"
		"border-radius: 15px;"
		"color: black;");
	ui.button_move4->setEnabled(false);
	//add move
	if (move_PP[0] >= 0) {
		ui.button_move1->setText(QString::fromStdString(current_move[0]));
		ui.button_move1->setStyleSheet("background-color: white;"
			"border: 8px solid brown;"
			"border-radius: 15px;"
			"color: black;"
		);
		ui.button_move1->setEnabled(true);
	}
	if (move_PP[1] >= 0) {
		ui.button_move2->setText(QString::fromStdString(current_move[1]));
		ui.button_move2->setStyleSheet("background-color: white;"
			"border: 8px solid brown;"
			"border-radius: 15px;"
			"color: black;"
		);
		ui.button_move2->setEnabled(true);
	}
	if (move_PP[2] >= 0) {
		ui.button_move3->setText(QString::fromStdString(current_move[2]));
		ui.button_move3->setStyleSheet("background-color: white;"
			"border: 8px solid brown;"
			"border-radius: 15px;"
			"color: black;"
		);
		ui.button_move3->setEnabled(true);
	}
	if (move_PP[3] >= 0) {
		ui.button_move4->setText(QString::fromStdString(current_move[3]));
		ui.button_move4->setStyleSheet("background-color: white;"
			"border: 8px solid brown;"
			"border-radius: 15px;"
			"color: black;"
		);
		ui.button_move4->setEnabled(true);
	}
	//set exhausted move
	if (move_PP[0] == 0) {
		ui.button_move1->setStyleSheet("background-color: gray;"
			"border: 8px solid brown;"
			"border-radius: 15px;"
			"color: black;");
		ui.button_move1->setEnabled(false);
	}
	if (move_PP[1] == 0) {
		ui.button_move2->setStyleSheet("background-color: gray;"
			"border: 8px solid gray;"
			"border-radius: 15px;"
			"color: black;");
		ui.button_move2->setEnabled(false);
	}
	if (move_PP[2] == 0) {
		ui.button_move3->setStyleSheet("background-color: gray;"
			"border: 8px solid gray;"
			"border-radius: 15px;"
			"color: black;");
		ui.button_move3->setEnabled(false);
	}
	
	if (move_PP[3] == 0) {
		ui.button_move4->setStyleSheet("background-color: gray;"
			"border: 8px solid gray;"
			"border-radius: 15px;"
			"color: black;");
		ui.button_move4->setEnabled(false);
	}
	
	//change bag's item
	// 
	ui.label_potion->setText(QString::number(potion_number));
	ui.button_potion->setEnabled(true);
	ui.button_superPotion->setEnabled(true);
	ui.button_hyperPotion->setEnabled(true);
	ui.button_maxPotion->setEnabled(true);
	if (potion_number == 0) {
		ui.button_potion->setEnabled(false);
	}
	ui.label_superPotion->setText(QString::number(superPotion_number));
	if (superPotion_number == 0) {
		ui.button_superPotion->setEnabled(false);
	}
	ui.label_hyperPotion->setText(QString::number(hyperPotion_number));
	if (hyperPotion_number == 0) {
		ui.button_hyperPotion->setEnabled(false);
	}
	ui.label_maxPotion->setText(QString::number(maxPotion_number));
	if (maxPotion_number == 0) {
		ui.button_maxPotion->setEnabled(false);
	}
	//change pokemon to be healed
	if (my_pokemon_HP[0] >= 0) {
		path = "./Resources/pic/pokemon/" + QString::fromStdString(my_pokemon_name[0]) + ".png";
		pic.load(path);
		icon.addPixmap(pic);
		ui.button_heal_p1->setIcon(icon);
		ui.button_heal_p1->setIconSize(QSize(50, 50));
		text = "   " + QString::fromStdString(my_pokemon_name[0]) + "\n";
		text = text + "   HP : " + QString::number(my_pokemon_HP[0]) + "/" + QString::number(my_pokemon_maxHP[0]);
		ui.button_heal_p1->setText(text);
		if (my_pokemon_HP[0] == 0) {
			ui.button_heal_p1->setEnabled(false);
		}
	}
	if (my_pokemon_HP[1] >= 0) {
		path = "./Resources/pic/pokemon/" + QString::fromStdString(my_pokemon_name[1]) + ".png";
		pic.load(path);
		icon.addPixmap(pic);
		ui.button_heal_p2->setIcon(icon);
		ui.button_heal_p2->setIconSize(QSize(50, 50));
		text = "   " + QString::fromStdString(my_pokemon_name[1]) + "\n";
		text = text + "   HP : " + QString::number(my_pokemon_HP[1]) + "/" + QString::number(my_pokemon_maxHP[1]);
		ui.button_heal_p2->setText(text);
		if (my_pokemon_HP[1] == 0) {
			ui.button_heal_p2->setEnabled(false);
		}
	}
	if (my_pokemon_HP[2] >= 0) {
		path = "./Resources/pic/pokemon/" + QString::fromStdString(my_pokemon_name[2]) + ".png";
		pic.load(path);
		icon.addPixmap(pic);
		ui.button_heal_p3->setIcon(icon);
		ui.button_heal_p3->setIconSize(QSize(50, 50));
		text = "   " + QString::fromStdString(my_pokemon_name[2]) + "\n";
		text = text + "   HP : " + QString::number(my_pokemon_HP[2]) + "/" + QString::number(my_pokemon_maxHP[2]);
		ui.button_heal_p3->setText(text);
		if (my_pokemon_HP[2] == 0) {
			ui.button_heal_p3->setEnabled(false);
		}
	}
	if (my_pokemon_HP[3] >= 0) {
		path = "./Resources/pic/pokemon/" + QString::fromStdString(my_pokemon_name[3]) + ".png";
		pic.load(path);
		icon.addPixmap(pic);
		ui.button_heal_p4->setIcon(icon);
		ui.button_heal_p4->setIconSize(QSize(50, 50));
		text = "   " + QString::fromStdString(my_pokemon_name[3]) + "\n";
		text = text + "   HP : " + QString::number(my_pokemon_HP[3]) + "/" + QString::number(my_pokemon_maxHP[3]);
		ui.button_heal_p4->setText(text);
		if (my_pokemon_HP[3] == 0) {
			ui.button_heal_p4->setEnabled(false);
		}
	}
	if (my_pokemon_HP[4] >= 0) {
		path = "./Resources/pic/pokemon/" + QString::fromStdString(my_pokemon_name[4]) + ".png";
		pic.load(path);
		icon.addPixmap(pic);
		ui.button_heal_p5->setIcon(icon);
		ui.button_heal_p5->setIconSize(QSize(50, 50));
		text = "   " + QString::fromStdString(my_pokemon_name[4]) + "\n";
		text = text + "   HP : " + QString::number(my_pokemon_HP[4]) + "/" + QString::number(my_pokemon_maxHP[4]);
		ui.button_heal_p5->setText(text);
		if (my_pokemon_HP[4] == 0) {
			ui.button_heal_p5->setEnabled(false);
		}
	}
	if (my_pokemon_HP[5] >= 0) {
		path = "./Resources/pic/pokemon/" + QString::fromStdString(my_pokemon_name[5]) + ".png";
		pic.load(path);
		icon.addPixmap(pic);
		ui.button_heal_p6->setIcon(icon);
		ui.button_heal_p6->setIconSize(QSize(50, 50));
		text = "   " + QString::fromStdString(my_pokemon_name[5]) + "\n";
		text = text + "   HP : " + QString::number(my_pokemon_HP[5]) + "/" + QString::number(my_pokemon_maxHP[5]);
		ui.button_heal_p6->setText(text);
		if (my_pokemon_HP[5] == 0) {
			ui.button_heal_p6->setEnabled(false);
		}
	}
	if (my_pokemon_HP[0] >= 0) {
		path = "./Resources/pic/pokemon/" + QString::fromStdString(my_pokemon_name[0]) + ".png";
		pic.load(path);
		icon.addPixmap(pic);
		ui.button_heal_p1->setIcon(icon);
		ui.button_heal_p1->setIconSize(QSize(50, 50));
		text = "   " + QString::fromStdString(my_pokemon_name[0]) + "\n";
		text = text + "   HP : " + QString::number(my_pokemon_HP[0]) + "/" + QString::number(my_pokemon_maxHP[0]);
		ui.button_heal_p1->setText(text);
		if (my_pokemon_HP[0] == 0) {
			ui.button_heal_p1->setEnabled(false);
		}
	}
	
	//change pokemon in bag
	//
	//pokemon1
	if (my_pokemon_HP[0] >= 0) {
		path = "./Resources/pic/pokemon/" + QString::fromStdString(my_GM.getPlayer1().getPokemons()[0].getName()) + ".png";
		pic.load(path);
		icon.addPixmap(pic);
		ui.button_pokemon1->setIcon(icon);
		ui.button_pokemon1->setIconSize(QSize(100, 100));
		text = "   " + QString::fromStdString(my_pokemon_name[0]) + "\n";
		text = text + "   HP : " + QString::number(my_pokemon_HP[0]) + "/" + QString::number(my_pokemon_maxHP[0]);
		ui.button_pokemon1->setText(text);
		if (my_pokemon_HP[0] == 0) {
			ui.button_pokemon1->setEnabled(false);
		}
	}
	
	//pokemon2
	if (my_pokemon_HP[1] >= 0) {
		path = "./Resources/pic/pokemon/" + QString::fromStdString(my_GM.getPlayer1().getPokemons()[1].getName()) + ".png";
		pic.load(path);
		icon.addPixmap(pic);
		ui.button_pokemon2->setIcon(icon);
		ui.button_pokemon2->setIconSize(QSize(100, 100));
		text = "   " + QString::fromStdString(my_pokemon_name[1]) + "\n";
		text = text + "   HP : " + QString::number(my_pokemon_HP[1]) + "/" + QString::number(my_pokemon_maxHP[1]);
		ui.button_pokemon2->setText(text);
		if (my_pokemon_HP[1] == 0) {
			ui.button_pokemon2->setEnabled(false);
		}
	}
	
	//pokemon3
	if (my_pokemon_HP[2] >= 0) {
		path = "./Resources/pic/pokemon/" + QString::fromStdString(my_GM.getPlayer1().getPokemons()[2].getName()) + ".png";
		pic.load(path);
		icon.addPixmap(pic);
		ui.button_pokemon3->setIcon(icon);
		ui.button_pokemon3->setIconSize(QSize(100, 100));
		text = "   " + QString::fromStdString(my_pokemon_name[2]) + "\n";
		text = text + "   HP : " + QString::number(my_pokemon_HP[2]) + "/" + QString::number(my_pokemon_maxHP[2]);
		ui.button_pokemon3->setText(text);
		if (my_pokemon_HP[2] == 0) {
			ui.button_pokemon3->setEnabled(false);
		}
	}
	
	//pokemon4
	if (my_pokemon_HP[3] >= 0) {
		path = "./Resources/pic/pokemon/" + QString::fromStdString(my_GM.getPlayer1().getPokemons()[3].getName()) + ".png";
		pic.load(path);
		icon.addPixmap(pic);
		ui.button_pokemon4->setIcon(icon);
		ui.button_pokemon4->setIconSize(QSize(100, 100));
		text = "   " + QString::fromStdString(my_pokemon_name[3]) + "\n";
		text = text + "   HP : " + QString::number(my_pokemon_HP[3]) + "/" + QString::number(my_pokemon_maxHP[3]);
		ui.button_pokemon4->setText(text);
		if (my_pokemon_HP[3] == 0) {
			ui.button_pokemon4->setEnabled(false);
		}
	}
	
	//pokemon5
	if (my_pokemon_HP[4] >= 0) {
		path = "./Resources/pic/pokemon/" + QString::fromStdString(my_GM.getPlayer1().getPokemons()[4].getName()) + ".png";
		pic.load(path);
		icon.addPixmap(pic);
		ui.button_pokemon5->setIcon(icon);
		ui.button_pokemon5->setIconSize(QSize(100, 100));
		text = "   " + QString::fromStdString(my_pokemon_name[4]) + "\n";
		text = text + "   HP : " + QString::number(my_pokemon_HP[4]) + "/" + QString::number(my_pokemon_maxHP[4]);
		ui.button_pokemon5->setText(text);
		if (my_pokemon_HP[4] == 0) {
			ui.button_pokemon5->setEnabled(false);
		}
	}
	
	//pokemon6
	if (my_pokemon_HP[5] >= 0) {
		path = "./Resources/pic/pokemon/" + QString::fromStdString(my_GM.getPlayer1().getPokemons()[5].getName()) + ".png";
		pic.load(path);
		icon.addPixmap(pic);
		ui.button_pokemon6->setIcon(icon);
		ui.button_pokemon6->setIconSize(QSize(100, 100));
		text = "   " + QString::fromStdString(my_pokemon_name[5]) + "\n";
		text = text + "   HP : " + QString::number(my_pokemon_HP[5]) + "/" + QString::number(my_pokemon_maxHP[5]);
		ui.button_pokemon6->setText(text);
		if (my_pokemon_HP[5] == 0) {
			ui.button_pokemon6->setEnabled(false);
		}
	}
	
	
	//change big dialog
	
	//player2
	// 
	// 
	//load data
	// 
	for (int i = 0; i < op_pokemon_num; i++) {
		op_pokemon_name[i] = my_GM.getPlayer2().getPokemons()[i].getName();
		op_pokemon_HP[i] = my_GM.getPlayer2().getPokemons()[i].getHP();
		op_pokemon_maxHP[i] = my_GM.getPlayer2().getPokemons()[i].getMaximumHP();
	}
	
	op_current_pokemon_name = my_GM.getPlayer2().getCurrentPokemon().getName();
	current_HP = my_GM.getPlayer2().getCurrentPokemon().getHP();
	current_maxHP = my_GM.getPlayer2().getCurrentPokemon().getMaximumHP();
	op_pokemon_condition.clear();
	op_pokemon_condition = my_GM.getPlayer2().getCurrentPokemon().getConditions();
	//change pokemon pic and status  and remained pokemon on background
	// 
	//set player2 pokemon
	path = "./Resources/pic/pokemon/" + QString::fromStdString(op_current_pokemon_name) + ".png";
	pokemon_pic.load(path);
	scaledPixmap = pokemon_pic.scaledToHeight(300);
	ui.label_pokemon2->setPixmap(scaledPixmap);
	//set player2 pokemon name and HP
	text = QString::fromStdString(op_current_pokemon_name) + "\n";
	text = text + "HP : " + QString::number(current_HP) + "/" + QString::number(current_maxHP) + "\n";
	ui.label_status2->setText(text);
	font_temp2.setPointSize(30);
	ui.label_status2->setFont(font_temp2);
	//set player2 pokemon condition
	if (op_pokemon_condition.find(Condition::BRN) != op_pokemon_condition.end()) {
		ui.label_BRN2->setVisible(true);
	}
	else {
		ui.label_BRN2->setVisible(false);
	}
	if (op_pokemon_condition.find(Condition::PSN) != op_pokemon_condition.end()) {
		ui.label_PSN2->setVisible(true);
	}
	else {
		ui.label_PSN2->setVisible(false);
	}
	if (op_pokemon_condition.find(Condition::PAR) != op_pokemon_condition.end()) {
		ui.label_PAR2->setVisible(true);
	}
	else {
		ui.label_PAR2->setVisible(false);
	}
	//set remained pokemon
	pic.load("./Resources/pic/other/pokeball.png");
	pic = pic.scaledToWidth(25);
	grayPixmap.load("./Resources/pic/other/gray_pokeball.png");
	grayPixmap = grayPixmap.scaledToWidth(25);
	if (op_pokemon_HP[0] == 0) {
		ui.label_p1_2->setPixmap(grayPixmap);
	}
	else {
		ui.label_p1_2->setPixmap(pic);
	}
	if (op_pokemon_HP[1] == 0) {
		ui.label_p2_2->setPixmap(grayPixmap);
	}
	else {
		ui.label_p2_2->setPixmap(pic);
	}
	if (op_pokemon_HP[2] == 0) {
		ui.label_p3_2->setPixmap(grayPixmap);
	}
	else {
		ui.label_p3_2->setPixmap(pic);
	}
	if (op_pokemon_HP[3] == 0) {
		ui.label_p4_2->setPixmap(grayPixmap);
	}
	else {
		ui.label_p4_2->setPixmap(pic);
	}
	if (op_pokemon_HP[4] == 0) {
		ui.label_p5_2->setPixmap(grayPixmap);
	}
	else {
		ui.label_p5_2->setPixmap(pic);
	}
	if (op_pokemon_HP[5] == 0) {
		ui.label_p6_2->setPixmap(grayPixmap);
	}
	else {
		ui.label_p6_2->setPixmap(pic);
	}

	//update status
	if (status == "choose") {
		ui.stackedWidget_switch_big->setCurrentWidget(ui.page_main);
		ui.stackedWidget_switch_small->setCurrentWidget(ui.page_option);
		if (my_GM.getPlayer1().isAllFaint()) {
			text_list.clear();
			text_list << "You lose!";
			status = "gameover";
			ui.button_dialog->setText(text_list[0]);
			ui.stackedWidget_switch_big->setCurrentWidget(ui.page_main);
			ui.stackedWidget_switch_small->setCurrentWidget(ui.page_dialog);
		}
		if (my_GM.getPlayer2().isAllFaint()) {
			text_list.clear();
			text_list << "You win!";
			status = "gameover";
			ui.button_dialog->setText(text_list[0]);
			ui.stackedWidget_switch_big->setCurrentWidget(ui.page_main);
			ui.stackedWidget_switch_small->setCurrentWidget(ui.page_dialog);
		}
	}
	else if (status == "attack") {
		whoGoFirst = my_GM.getWhoIsFirst();
		pokemon_use = current_pokemon_name;
		op_pokemon_use = op_current_pokemon_name;
		text_list_index = 0;
		text_list.clear();
		for (int i = 0; i < 2; i++) {
			if (whoGoFirst == 0) {//pc go first
				text_list << getBattleList(0);
				if (i == 0) {
					hurtAnimation(ui.label_pokemon1);
				}
				whoGoFirst = 1;
			}
			else if (whoGoFirst == 1) {//player go first
				text_list << getBattleList(1);
				if (i == 0) {
					hurtAnimation(ui.label_pokemon2);
				}
				
				whoGoFirst = 0;
			}
		}
		text_list << getFinalList();
		text_list_index++;
		ui.button_dialog->setText(text_list[0]);
		ui.label_log->setText(ui.label_log->text() + text_list[0] + "\n");

		ui.stackedWidget_switch_big->setCurrentWidget(ui.page_main);
		ui.stackedWidget_switch_small->setCurrentWidget(ui.page_dialog);
	}
	else if (status == "heal") {
		op_pokemon_use = op_current_pokemon_name;
		text_list_index = 0;
		text_list.clear();
		text_list << "You use a " + QString::fromStdString(bag_use) + "!";
		text_list << QString::fromStdString(pokemon_use) + " had its HP restored.";
		text_list << getBattleList(0);//pc move
		text_list << getFinalList();
		text_list_index++;
		ui.button_dialog->setText(text_list[0]);
		ui.label_log->setText(ui.label_log->text() + text_list[0] + "\n");
		
		ui.stackedWidget_switch_big->setCurrentWidget(ui.page_main);
		ui.stackedWidget_switch_small->setCurrentWidget(ui.page_dialog);

	}
	else if (status == "swap") {
		op_pokemon_use = op_current_pokemon_name;
		text_list << "Go! " + QString::fromStdString(pokemon_use) + "!";
		text_list << getBattleList(0);//pc move
		text_list << getFinalList();
		text_list_index++;
		ui.button_dialog->setText(text_list[0]);
		ui.label_log->setText(ui.label_log->text() + text_list[0] + "\n");

		ui.stackedWidget_switch_big->setCurrentWidget(ui.page_main);
		ui.stackedWidget_switch_small->setCurrentWidget(ui.page_dialog);
	}
	else if (status == "run") {
		text_list_index = 0;
		text_list.clear();
		text_list << "Go away safety!";
		text_list_index++;
		ui.button_dialog->setText(text_list[0]);
		ui.label_log->setText(ui.label_log->text() + text_list[0] + "\n");
		
		ui.stackedWidget_switch_big->setCurrentWidget(ui.page_main);
		ui.stackedWidget_switch_small->setCurrentWidget(ui.page_dialog);
	}
	else if (status == "show") {

	}

}

QStringList battle_scene::getBattleList(bool p) {
	QStringList t;
	if (p == 1) {//player
		if (!my_GM.getWhoIsFirst() && my_GM.getPlayer1().getCurrentPokemon().isFaint()) {
			return t;
		}
		//get criticalHit
		//get effectiveness
		criticalHit = my_GM.getCrit1();
		effectiveness = my_GM.getEffective1();
		//move
		t << QString::fromStdString(pokemon_use) + " used " + QString::fromStdString(move_use) + "!";
		//paralyze
		if (my_GM.getIsParalysis1()) {
			t << QString::fromStdString(pokemon_use) + " is paralyzed! It can't move!";
			return t;
		}
		//miss
		if (my_GM.getMiss1()) {
			t << QString::fromStdString(op_pokemon_use) + " avoided the attack!";
			return t;
		}
		//critical hit
		if (criticalHit == true) {
			t << "A critical hit!";
		}
		//effectiveness
		if (effectiveness >= 2.0) {
			t << "It's super effective!";
		}
		else if (effectiveness == 0.0) {
			t << "It's not effective!";
		}
		else if (effectiveness <= 0.5) {
			t << "It's not very effective...";
		}
		
		//condition
		if (my_GM.getPlayer1().getCurrentPokemon().getSkill(move_use).getCondition() == Condition::BRN) {
			t << QString::fromStdString(op_pokemon_use) + " is burned.";
		}
		if (my_GM.getPlayer1().getCurrentPokemon().getSkill(move_use).getCondition() == Condition::PSN) {
			t << QString::fromStdString(op_pokemon_use) + " is poisoned.";
		}
		if (my_GM.getPlayer1().getCurrentPokemon().getSkill(move_use).getCondition() == Condition::PAR) {
			t << QString::fromStdString(op_pokemon_use) + " is paralyzed, so it may be unable to move!";
		}

		//swap
	}
	else if (p == 0) {//pc
		if (my_GM.getWhoIsFirst() && my_GM.getPlayer2().getCurrentPokemon().isFaint()) {
			return t;
		}
		//get op_criticalHit
		//get op_effectiveness
		op_criticalHit = my_GM.getCrit2();
		op_effectiveness = my_GM.getEffective2();
		t << "The opposing " + QString::fromStdString(op_pokemon_use) + " used " + QString::fromStdString(op_move_use) + "!";
		//paralyze
		if (my_GM.getIsParalysis2()) {
			t << QString::fromStdString(op_pokemon_use) + " is paralyzed! It can't move!";
			return t;
		}
		//miss
		if (my_GM.getMiss2()) {
			t << QString::fromStdString(pokemon_use) + " avoided the attack!";
			return t;
		}
		if (op_criticalHit == true) {
			t << "A critical hit!";
		}
		if (op_effectiveness >= 2.0) {
			t << "It's super effective!";
		}
		else if (op_effectiveness == 0.0) {
			t << "It's not effective!";
		}
		else if (op_effectiveness <= 0.5) {
			t << "It's not very effective...";
		}
		
		//condition
		if (my_GM.getPlayer2().getCurrentPokemon().getSkill(move_use).getCondition() == Condition::BRN) {
			t << QString::fromStdString(pokemon_use) + " is burned.";
		}
		if (my_GM.getPlayer2().getCurrentPokemon().getSkill(move_use).getCondition() == Condition::PSN) {
			t << QString::fromStdString(pokemon_use) + " is poisoned.";
		}
		if (my_GM.getPlayer2().getCurrentPokemon().getSkill(move_use).getCondition() == Condition::PAR) {
			t << QString::fromStdString(pokemon_use) + " is paralyzed, so it may be unable to move!";
		}
	}
	

	return t;
}

QStringList battle_scene::getFinalList() {
	QStringList t;
	deadSwap = 0;
	//check condition
	if (!my_GM.getPlayer1().getCurrentPokemon().isFaint()) {
		if (my_GM.getPlayer1().getCurrentPokemon().getConditions().count(Condition::BRN)) {
			t << QString::fromStdString(current_pokemon_name) + " is hurt by its burn!";
		}
		if (my_GM.getPlayer1().getCurrentPokemon().getConditions().count(Condition::PSN)) {
			t << QString::fromStdString(current_pokemon_name) + " is hurt by its poisoning!";
		}
	}
	if (!my_GM.getPlayer2().getCurrentPokemon().isFaint()) {
		if (my_GM.getPlayer2().getCurrentPokemon().getConditions().count(Condition::BRN)) {
			t << QString::fromStdString(op_current_pokemon_name) + " is hurt by its burn!";
		}
		if (my_GM.getPlayer2().getCurrentPokemon().getConditions().count(Condition::PSN)) {
			t << QString::fromStdString(op_current_pokemon_name) + " is hurt by its poisoning!";
		}
	}
	my_GM.burnAndPoison();
	if (my_GM.getPlayer2().getCurrentPokemon().isFaint()) {
		t << QString::fromStdString(op_current_pokemon_name) + " is faint!";
		//check if PC lost or change pokemon
		if (my_GM.getPlayer2().isAllFaint()) {
			t << "You win!";
			status = "gameover";
			return t;
		}
		else {
			my_GM.getPlayer2().swapToNext();
			op_current_pokemon_name = my_GM.getPlayer2().getCurrentPokemon().getName();
			t << "Go! " + QString::fromStdString(op_current_pokemon_name);
		}
	}
	if (my_GM.getPlayer1().getCurrentPokemon().isFaint()) {
		t << QString::fromStdString(current_pokemon_name) + " is faint!";
		if (my_GM.getPlayer1().isAllFaint()) {
			t << "You lose!";
			status = "gameover";
			return t;
		}
		else {
			deadSwap = 1;
		}
	}

	return t;
}

void battle_scene::hurtAnimation(QLabel* pokemon) {
	int duration = 500;  //0.5s
	int blinkCount = 3;  //3 times
	int blinkInterval = duration / (blinkCount * 2); 

	QTimer* timer = new QTimer();
	timer->setInterval(blinkInterval);

	QObject::connect(timer, &QTimer::timeout, [=]() {
		bool isVisible = pokemon->isVisible();
		pokemon->setVisible(!isVisible);
		});

	QTimer::singleShot(duration, [=]() {
		pokemon->setVisible(true);
		timer->stop();
		timer->deleteLater();
		});

	timer->start();
}

void battle_scene::loadData(string temp_log) {
	std::string line;
	std::istringstream iss(temp_log);
	while (getline(iss, line)) {
		if (status == "gameover") {
			break;
		}
		if (line == "Test") {
			testMode = true;
		}
		else if (line == "Battle") {
			getline(iss, line);
			move_use = line;
			getline(iss, line);
			op_move_use = line;
			my_GM.battle(move_use, op_move_use);
			status = "attack";
			update_visual();
			for (int i = 1; i < text_list.size(); i++) {
				ui.label_log->setText(ui.label_log->text() + text_list[i] + '\n');
			}
			text_list.clear();
		}
		else if (line == "Bag") {
			getline(iss, line);
			bag_use = line;
			getline(iss, line);
			pokemon_use = line;
			getline(iss, line);
			op_move_use = line;
			my_GM.getPlayer1().usePotion(bag_use, pokemon_use);
			my_GM.battle("no", op_move_use);
			status = "heal";
			update_visual();
			for (int i = 1; i < text_list.size(); i++) {
				ui.label_log->setText(ui.label_log->text() + text_list[i] + '\n');
			}
			text_list.clear();
		}
		else if (line == "Pokemon") {
			getline(iss, line);
			pokemon_use = line;
			getline(iss, line);
			op_move_use = line;
			ui.label_log->setText(ui.label_log->text() + QString::fromStdString(my_GM.getPlayer1().getCurrentPokemon().getName()) + ", come back!" + '\n');
			my_GM.swapPokemon(my_GM.getPlayer1(), pokemon_use);
			my_GM.battle("no", op_move_use);
			status = "swap";
			update_visual();
			for (int i = 1; i < text_list.size(); i++) {
				ui.label_log->setText(ui.label_log->text() + text_list[i] + '\n');
			}
			text_list.clear();
		}
		else if (line == "Status") {
			current_pokemon_name = my_GM.getPlayer1().getCurrentPokemon().getName();
			ui.label_log->setText(ui.label_log->text() +QString::fromStdString(current_pokemon_name) + " ");
			current_HP = my_GM.getPlayer1().getCurrentPokemon().getHP();
			ui.label_log->setText(ui.label_log->text() + QString::number(current_HP) + " ");
			pokemon_condition = my_GM.getPlayer1().getCurrentPokemon().getConditions();
			if (pokemon_condition.find(Condition::PAR) != pokemon_condition.end()) {
				ui.label_log->setText(ui.label_log->text() + "PAR" + " ");
			}
			if (pokemon_condition.find(Condition::BRN) != pokemon_condition.end()) {
				ui.label_log->setText(ui.label_log->text() + "BRN" + " ");
			}
			if (pokemon_condition.find(Condition::PSN) != pokemon_condition.end()) {
				ui.label_log->setText(ui.label_log->text() + "PSN" + " ");
			}

			current_pokemon_name = my_GM.getPlayer2().getCurrentPokemon().getName();
			ui.label_log->setText(ui.label_log->text() + QString::fromStdString(current_pokemon_name) + " ");
			current_HP = my_GM.getPlayer2().getCurrentPokemon().getHP();
			ui.label_log->setText(ui.label_log->text() + QString::number(current_HP) + " ");
			op_pokemon_condition = my_GM.getPlayer2().getCurrentPokemon().getConditions();
			if (op_pokemon_condition.find(Condition::PAR) != op_pokemon_condition.end()) {
				ui.label_log->setText(ui.label_log->text() + "PAR" + " ");
			}
			if (op_pokemon_condition.find(Condition::BRN) != op_pokemon_condition.end()) {
				ui.label_log->setText(ui.label_log->text() + "BRN" + " ");
			}
			if (op_pokemon_condition.find(Condition::PSN) != op_pokemon_condition.end()) {
				ui.label_log->setText(ui.label_log->text() + "PSN" + " ");
			}
			
			ui.label_log->setText(ui.label_log->text() + "\n");
		}
		else if (line == "Check") {
			for (int i = 0; i < 4; i++) {
				current_move[i] = my_GM.getPlayer1().getCurrentPokemon().getSkills()[i].getName();
				move_PP[i] = my_GM.getPlayer1().getCurrentPokemon().getSkills()[i].getPP();
			}
			for (int i = 0; i < 4; i++) {
				ui.label_log->setText(ui.label_log->text() + QString::fromStdString(current_move[i]) + " ");
				ui.label_log->setText(ui.label_log->text() + QString::number(move_PP[i]) + " ");
			}
			ui.label_log->setText(ui.label_log->text() + "\n");
		}
		else if (line == "Run") {

		}
	}
	
}



