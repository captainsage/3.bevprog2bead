#ifndef CHESSPIECEWIDGET_HPP_INCLUDED
#define CHESSPIECEWIDGET_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include <string>

class ChessPiece : public Widget {
protected:
    bool _white;
    genv::canvas _piece;
public:
    ChessPiece(int x, int y, int size_x, int size_y, bool white, genv::canvas starting_piece);
    void field_refresh(genv::canvas piece);
    virtual void display_update() override;
    virtual void action(genv::event &ev) override;
    virtual void btn_action_int(int arg) override;
};

#endif // CHESSPIECEWIDGET_HPP_INCLUDED
