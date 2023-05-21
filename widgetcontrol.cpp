#include "graphics.hpp"
#include "widget.hpp"
#include "chesspiecewidget.hpp"
#include "widgetcontrol.hpp"
#include "gamemanager.hpp"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace genv;

WidgetControl::WidgetControl(int field_size) :_field_size(field_size){
    gout.open(field_size*8,field_size*8);
    canvas basic;
    basic.open(field_size,field_size);
    basic.transparent(true);
    basic << move_to(0,0)
          << color(0,0,0)
          << box(field_size, field_size);
    canvas b1 = basic;
    for(int y = 0; y < 8; y++) {
        vector<ChessPiece*> game_display_row;
        for(int x = 0; x < 8; x++) {
            ChessPiece* p1 =  new ChessPiece(x*field_size, y*field_size, field_size, field_size, (y+x)%2 == 0, b1);
            game_display_row.push_back(p1);
        }
        _game_display.push_back(game_display_row);
    }
    setup_storage(field_size);
    reset_pieces();
    field_draw();
    gout << refresh;
}

void WidgetControl::start_game() {
    run();
}

void WidgetControl::field_draw() {
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            _game_display[y][x]->draw_widget(&gout);
        }
    }
}

void WidgetControl::field_refresh() {
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            _game_display[y][x]->display_update();
        }
    }
}

void WidgetControl::run() {
    event ev;
    bool selected = false;
    int sel_x, sel_y;
    while(gin >> ev && ev.keycode != key_escape && _rules.get_winner() == "None") {
        if(ev.button == btn_left) {
            for(int y = 0; y < 8; y++) {
                for(int x = 0; x < 8; x++) {

                    if(!selected && _game_display[y][x]->is_selected(ev.pos_x, ev.pos_y) && _rules.selectable(x,y)) {
                        display_target(_rules.select_target(x,y));
                        sel_x = x;
                        sel_y = y;
                        selected = true;
                    }
                    else if(selected && _game_display[y][x]->is_selected(ev.pos_x, ev.pos_y) ) {
                        selected = false;
                        if(_rules.piece_move(sel_x,sel_y,x,y)) {
                            _game_display[y][x]->field_change(_game_display[sel_y][sel_x]->get_piece());
                            _game_display[sel_y][sel_x]->field_change(_piece_storage[0][0]);
                        }
                        field_refresh();
                        field_draw();
                        gout << refresh;
                    }
                }
            }
        }
    }
    while(gin >> ev &&  ev.keycode != key_backspace) {
        gout << move_to(_field_size*1.5,_field_size*1.5)
             << color(0,0,0)
             << box(_field_size*5,_field_size*5)
             <<color(255,255,255)
             << move_to(_field_size*2.5, _field_size*4);
        if(_rules.get_winner() == "Draw") {
        gout << text("Draw");
        }
        else {
        gout << text("The winner is: " + _rules.get_winner());
        }
        gout << move_to(_field_size*2.5, _field_size*5.5)
             << text("[backspace]: exit")
             << refresh;

    }
}

void WidgetControl::display_target(vector<vector<int>> targets) {

    canvas targetmask;
    targetmask.open(_field_size, _field_size);
    targetmask.transparent(true);
    targetmask << move_to(0,0) << color(255,0,0) << box(_field_size, _field_size) << move_to(5,5) <<color(0,0,0) << box(_field_size-10,_field_size-10);
    for(vector<int> cursor:targets) {
        gout << stamp(targetmask,cursor[0]*_field_size,cursor[1]*_field_size);
    }
    gout << refresh;
}

void WidgetControl::setup_storage(int field_size) {
    vector<vector<canvas>> new_piece_storage;
    vector<canvas> n1;
    canvas basic;
    basic.open(field_size,field_size);
    basic.transparent(true);
    basic << move_to(0,0)<< color(0,0,0) << box(field_size, field_size);
    gout << move_to(100,100) << stamp(basic,0,0);
    canvas b1 = basic;
    n1.push_back(b1);
    vector<canvas> n2;
    vector<canvas> c;
    vector<string> s = {"G","B","L","F","K","V"};
    canvas c0;
    canvas c1;
    canvas c2;
    canvas c3;
    canvas c4;
    canvas c5;
    c.push_back(c0);
    c.push_back(c1);
    c.push_back(c2);
    c.push_back(c3);
    c.push_back(c4);
    c.push_back(c5);
    for(int i = 0; i < 6; i++) {
        c[i].open(field_size,field_size);
        c[i].transparent(true);
        c[i].load_font("LiberationMono-Bold.ttf", field_size, true);
        c[i] << move_to(0,0)<< color(0,0,0)<< box(field_size, field_size) << move_to(field_size/5,0) << color(102,51,0) << text(s[i]);
        canvas n20 = c[i];
        n2.push_back(n20);
    }
    vector<canvas> n3;
    vector<canvas> ca;
    canvas ca0;
    canvas ca1;
    canvas ca2;
    canvas ca3;
    canvas ca4;
    canvas ca5;
    ca.push_back(ca0);
    ca.push_back(ca1);
    ca.push_back(ca2);
    ca.push_back(ca3);
    ca.push_back(ca4);
    ca.push_back(ca5);
    for(int i = 0; i < 6; i++) {
        ca[i].open(field_size,field_size);
        ca[i].transparent(true);
        ca[i].load_font("LiberationMono-Bold.ttf", field_size, true);
        ca[i] << move_to(0,0)<< color(0,0,0)<< box(field_size, field_size) << move_to(field_size/5,0) << color(225,225,143) << text(s[i]);
        canvas n20 = ca[i];
        n3.push_back(n20);
    }
    new_piece_storage.push_back(n1);
    new_piece_storage.push_back(n2);
    new_piece_storage.push_back(n3);
    _piece_storage = new_piece_storage;
}

void WidgetControl::reset_pieces() {
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            _game_display[y][x]->field_change(_piece_storage[0][0]);
            if(y == 1) {_game_display[y][x]->field_change(_piece_storage[1][0]);}
            if(y == 6) {_game_display[y][x]->field_change(_piece_storage[2][0]);}
            if(y == 0 && (x == 0 || x == 7)) {_game_display[y][x]->field_change(_piece_storage[1][1]);}
            if(y == 0 && (x == 1 || x == 6)) {_game_display[y][x]->field_change(_piece_storage[1][2]);}
            if(y == 0 && (x == 2 || x == 5)) {_game_display[y][x]->field_change(_piece_storage[1][3]);}
            if(y == 0 && x == 3) {_game_display[y][x]->field_change(_piece_storage[1][5]);}
            if(y == 0 && x == 4) {_game_display[y][x]->field_change(_piece_storage[1][4]);}
            if(y == 7 && (x == 0 || x == 7)) {_game_display[y][x]->field_change(_piece_storage[2][1]);}
            if(y == 7 && (x == 1 || x == 6)) {_game_display[y][x]->field_change(_piece_storage[2][2]);}
            if(y == 7 && (x == 2 || x == 5)) {_game_display[y][x]->field_change(_piece_storage[2][3]);}
            if(y == 7 && x == 4) {_game_display[y][x]->field_change(_piece_storage[2][4]);}
            if(y == 7 && x == 3) {_game_display[y][x]->field_change(_piece_storage[2][5]);}
        }
    }

}
