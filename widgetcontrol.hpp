#ifndef WIDGETCONTROL_HPP_INCLUDED
#define WIDGETCONTROL_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include "chesspiecewidget.hpp"
#include <vector>

class GameField{
protected:
    std::vector<std::vector<ChessPiece*>> _game_display;
    std::vector<std::vector<genv::canvas>> _piece_storage;
public:
    GameField(int field_size);
    void field_draw();
    void run();
    void reset_pieces();
    void setup_storage(int field_size);
};


#endif // WIDGETCONTROL_HPP_INCLUDED
