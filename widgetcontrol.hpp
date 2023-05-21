#ifndef WIDGETCONTROL_HPP_INCLUDED
#define WIDGETCONTROL_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include "chesspiecewidget.hpp"
#include "gamemanager.hpp"
#include <vector>

class WidgetControl{
protected:
    std::vector<std::vector<ChessPiece*>> _game_display;
    std::vector<std::vector<genv::canvas>> _piece_storage;
    int _field_size;
    GameManager _rules;
public:
    WidgetControl(int field_size);
    void field_draw();
    void field_refresh();
    void start_game();
    void run();
    void reset_pieces();
    void setup_storage(int field_size);
    void display_target(std::vector<std::vector<int>> targets);
};


#endif // WIDGETCONTROL_HPP_INCLUDED
