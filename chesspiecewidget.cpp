#include "widget.hpp"
#include "graphics.hpp"
#include "chesspiecewidget.hpp"

using namespace genv;

ChessPiece::ChessPiece(int x, int y, int size_x, int size_y, bool white, canvas starting_piece) :Widget(x,y,size_x,size_y,0), _white(white), _piece(starting_piece){
    field_refresh(_piece);
}

void ChessPiece::field_refresh(canvas new_piece) {
    _piece = new_piece;
    _display << move_to(0,0)
             << color(255*_white,255*_white,255*_white)
             << box(_size_x, _size_y)
             << move_to(0,0)
             << stamp(_piece, 0, 0);
}

void ChessPiece::display_update(){}

void ChessPiece::action(event &ev){}

void ChessPiece::btn_action_int(int arg){}
