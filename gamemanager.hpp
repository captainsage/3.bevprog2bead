#ifndef GAMEMANAGER_HPP_INCLUDED
#define GAMEMANAGER_HPP_INCLUDED

#include "widget.hpp"
#include "widgetcontrol.hpp"
#include "chesspiecewidget.hpp"

class GameManager {
protected:
    GameField _game;
public:
    GameManager(int field_size);
    void start_game();
};


#endif // GAMEMANAGER_HPP_INCLUDED
