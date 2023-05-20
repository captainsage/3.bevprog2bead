#include "widget.hpp"
#include "widgetcontrol.hpp"
#include "gamemanager.hpp"
#include "chesspiecewidget.hpp"

GameManager::GameManager(int field_size) :_game(field_size){}

void GameManager::start_game() {_game.run();}
