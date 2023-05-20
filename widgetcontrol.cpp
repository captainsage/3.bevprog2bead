#include "graphics.hpp"
#include "widget.hpp"
#include "chesspiecewidget.hpp"
#include "widgetcontrol.hpp"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using namespace genv;

GameField::GameField(int field_size) {
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
    //gout << stamp(*_piece_storage[0][0],10,10); //<< color(200,200,0) << box(field_size,field_size);
    field_draw();
    gout << refresh;
}

void GameField::field_draw() {
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            _game_display[y][x]->draw_widget(&gout);
        }
    }
}

void GameField::run() {
    event ev;
    while(gin >> ev && ev.keycode != key_escape) {
    }
}

void GameField::setup_storage(int field_size) {
    vector<vector<canvas>> new_piece_storage;
    vector<canvas> n1;
    canvas basic;
    basic.open(field_size,field_size);
    //cout << field_size;
    basic.transparent(true);
    basic << move_to(0,0)<< color(0,0,0) << box(field_size, field_size);
    gout << move_to(100,100) << stamp(basic,0,0);
    canvas b1 = basic;
    //gout<< stamp(*b1, 100, 100);
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
        c[i] << move_to(0,0)<< color(0,0,0)<< box(field_size, field_size) << move_to(field_size/5,0) << color(255,0,0) << text(s[i]);
        canvas n20 = c[i];
        //cout << n2.size();
        n2.push_back(n20);
    }
    //cout << n2.size();
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
        ca[i] << move_to(0,0)<< color(0,0,0)<< box(field_size, field_size) << move_to(field_size/5,0) << color(0,255,0) << text(s[i]);
        canvas n20 = ca[i];
        n3.push_back(n20);
    }
    new_piece_storage.push_back(n1);
    new_piece_storage.push_back(n2);
    new_piece_storage.push_back(n3);
    _piece_storage = new_piece_storage;
    //cout << _piece_storage[2][0];
}

void GameField::reset_pieces() {
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            //gout << stamp(_piece_storage[0][0],0,0);
            _game_display[y][x]->field_refresh(_piece_storage[0][0]);
            if(y == 1) {_game_display[y][x]->field_refresh(_piece_storage[1][0]);}
            if(y == 6) {_game_display[y][x]->field_refresh(_piece_storage[2][0]);}
            if(y == 0 && (x == 0 || x == 7)) {_game_display[y][x]->field_refresh(_piece_storage[1][1]);}
            if(y == 0 && (x == 1 || x == 6)) {_game_display[y][x]->field_refresh(_piece_storage[1][2]);}
            if(y == 0 && (x == 2 || x == 5)) {_game_display[y][x]->field_refresh(_piece_storage[1][3]);}
            if(y == 0 && x == 3) {_game_display[y][x]->field_refresh(_piece_storage[1][5]);}
            if(y == 0 && x == 4) {_game_display[y][x]->field_refresh(_piece_storage[1][4]);}
            if(y == 7 && (x == 0 || x == 7)) {_game_display[y][x]->field_refresh(_piece_storage[2][1]);}
            if(y == 7 && (x == 1 || x == 6)) {_game_display[y][x]->field_refresh(_piece_storage[2][2]);}
            if(y == 7 && (x == 2 || x == 5)) {_game_display[y][x]->field_refresh(_piece_storage[2][3]);}
            if(y == 7 && x == 4) {_game_display[y][x]->field_refresh(_piece_storage[2][4]);}
            if(y == 7 && x == 3) {_game_display[y][x]->field_refresh(_piece_storage[2][5]);}
        }
    }

}
