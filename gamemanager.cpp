#include "widget.hpp"
#include "widgetcontrol.hpp"
#include "gamemanager.hpp"
#include "chesspiecewidget.hpp"
#include <iostream>
#include <vector>

using namespace std;

PieceInfo::PieceInfo(): _role(""), _white(false), _is_piece(false), _value(0), _is_ranged(false),_first_step({}),_second_step({}) {}
PieceInfo::PieceInfo(string role, bool white, bool ranged, int value, vector<int> first_step, vector<int> second_step) :_role(role), _white(white),_is_piece(true), _is_ranged(ranged), _value(value), _first_step(first_step), _second_step(second_step){}

GameManager::GameManager() :_whites_turn(true){
    reset_game();
}

void GameManager::reset_game() {
    vector<vector<PieceInfo>> new_game;
    for(int y = 0; y < 8; y++) {
        vector<PieceInfo> p;
        for(int x = 0; x < 8; x++) {
            p.push_back(PieceInfo());
        }
        new_game.push_back(p);
    }
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            if(y == 1) {new_game[y][x] = PieceInfo("gyalog",false,true,1,{1},{-1,0,1});}
            if(y == 6) {new_game[y][x] = PieceInfo("gyalog",true,true,1,{-1},{-1,0,1});}
            if(y == 0 && (x == 0 || x == 7)) {new_game[y][x] = PieceInfo("bastya",false,true,5,{-1,0,1},{-1,0,1});}
            if(y == 0 && (x == 1 || x == 6)) {new_game[y][x] = PieceInfo("lo",false,false,3,{-2,-1,1,2},{-2,-1,1,2});}
            if(y == 0 && (x == 2 || x == 5)) {new_game[y][x] = PieceInfo("futo",false,true,3,{-1,1},{-1,1});}
            if(y == 0 && x == 3) {new_game[y][x] = PieceInfo("vezer",false,true,9,{-1,0,1},{-1,0,1});}
            if(y == 0 && x == 4) {new_game[y][x] = PieceInfo("kiraly",false,false,10,{-1,0,1},{-1,0,1});}
            if(y == 7 && (x == 0 || x == 7)) {new_game[y][x] = PieceInfo("bastya",true,true,5,{-1,0,1},{-1,0,1});}
            if(y == 7 && (x == 1 || x == 6)) {new_game[y][x] = PieceInfo("lo",true,false,3,{-2,-1,1,2},{-2,-1,1,2});}
            if(y == 7 && (x == 2 || x == 5)) {new_game[y][x] = PieceInfo("futo",true,true,3,{-1,1},{-1,1});}
            if(y == 7 && x == 4) {new_game[y][x] = PieceInfo("kiraly",true,false,10,{-1,0,1},{-1,0,1});}
            if(y == 7 && x == 3) {new_game[y][x] = PieceInfo("vezer",true,true,9,{-1,0,1},{-1,0,1});}
        }
    }
    _game = new_game;
    calculate_targets();
}
void GameManager::calculate_targets() {
    vector<vector<vector<vector<int>>>> update_targets;
    for(int y = 0; y < 8; y++) {
        vector<vector<vector<int>>> update_row;
        for(int x = 0; x < 8; x++) {
            if(selectable(x,y)){update_row.push_back(target_fields(x,y));}
            else {update_row.push_back({{}});}
        }
        update_targets.push_back(update_row);
    }
    _all_possible_targets = update_targets;
}

int GameManager::count_all_targets() {
    int sum = 0;

    for(vector<vector<vector<int>>> y :_all_possible_targets) {
        for(vector<vector<int>> x :y) {
            sum += x.size();
        }
    }
    return sum;
}

void GameManager::target_clear()  {
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            _game[y][x]._targeted = false;
        }
    }
}

bool GameManager::selectable(int cx, int cy) {
    return _game[cy][cx]._is_piece && _game[cy][cx]._white == _whites_turn;
}


bool GameManager::piece_move(int cx, int cy, int tx, int ty) {
    int all_targets = 0;
    if(_game[ty][tx]._targeted && !(cx == tx && cy == ty)) {
        _game[ty][tx] = _game[cy][cx];
        _game[cy][cx] = PieceInfo();
        target_clear();
        check();
        _whites_turn = !_whites_turn;
        if(!simulation) {
            calculate_targets();
        }
        check();
        if(!simulation) {
            set_winner();
        }
        return true;
    }
    target_clear();
    return false;
}

void GameManager::set_winner() {
    int all_targets_sum = count_all_targets();
    if(all_targets_sum == 64 && _black_white_check[0] && !_whites_turn) {
        _winner = "White";
    }
    if(all_targets_sum == 64 && _black_white_check[1] && _whites_turn) {
        _winner = "Black";
    }
    if(all_targets_sum == 64 && !(_black_white_check[0] || _black_white_check[1])) {
        _winner = "Draw";
    }
}

bool GameManager::check() {
    int kx, ky;
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            if(_game[y][x]._is_piece && _game[y][x]._white == _whites_turn && _game[y][x]._role == "kiraly") {
                kx = x;
                ky = y;
            }
        }
    }
    vector<vector<int>> targeted;
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            if(_game[y][x]._is_piece && _game[y][x]._white != _whites_turn) {
                targeted = target_fields(x,y);
                for(vector<int> cursor : targeted) {
                    vector<int> kiraly_koord = {kx,ky};
                    if(cursor == kiraly_koord &&!(kx == x && ky == y)) {
                        _black_white_check[_whites_turn] = true;
                        target_clear();
                        return true;
                    }
                }
            }
        }
    }
    _black_white_check[_whites_turn] = false;
    target_clear();
    return false;
}

std::vector<bool> GameManager::get_check() {return _black_white_check;}

string GameManager::get_winner(){return _winner;}

void GameManager::set_simulation(){simulation = true;}

std::vector<std::vector<int>> GameManager::simulate(int cx, int cy, std::vector<std::vector<int>> raw_targets) {
    vector<vector<int>> filtered_targets;
    for(vector<int> cursor:raw_targets) {
        GameManager sim = *this;
        sim.set_simulation();
        sim.piece_move(cx, cy,cursor[0],cursor[1]);
        if(!sim.get_check()[_whites_turn]) {
            filtered_targets.push_back(cursor);
        }
    }
    return filtered_targets;
}

vector<vector<int>> GameManager::target_fields(int cx, int cy) {
    vector<vector<int>> targets;
    targets.push_back({cx,cy});
    _game[cy][cx]._targeted = true;
    //cout << "halo";
    for(int y:_game[cy][cx]._first_step) {
        for(int x:_game[cy][cx]._second_step) {
            for(int z = 1; z <= (6*_game[cy][cx]._is_ranged)+1; z++) {

                int tx = cx + x*z;
                int ty = cy + y*z;
                if(tx < 8 && tx > -1 && ty < 8 && ty > -1 &&(!_game[ty][tx]._is_piece || (_game[ty][tx]._white != _game[cy][cx]._white))) {
                    if((_game[cy][cx]._role != "lo" && _game[cy][cx]._role != "bastya" && _game[cy][cx]._role != "gyalog" /*&& !sim.get_check()[_whites_turn]*/)
                       || (_game[cy][cx]._role == "lo" && abs(y)+abs(x) == 3)
                       || (_game[cy][cx]._role == "bastya" && (x == 0 || y == 0))
                       || (z == 1 && _game[cy][cx]._role == "gyalog" && ((abs(x) == 1 && _game[ty][tx]._is_piece) || (x == 0  && !_game[ty][tx]._is_piece) ))
                       || (z == 2 && _game[cy][cx]._role == "gyalog" && x == 0 && ((_game[cy][cx]._white && cy == 6) || (!_game[cy][cx]._white && cy == 1)))) {

                        targets.push_back({tx,ty});
                        _game[ty][tx]._targeted = true;
                        if(_game[ty][tx]._is_piece) {break;}
                    }
                }
                else break;
            }
        }
    }
    if(!simulation){return simulate(cx, cy, targets);}
    return targets;
}

std::vector<std::vector<int>> GameManager::select_target(int cx, int cy) {
    target_clear();
    for(vector<int>cursor :_all_possible_targets[cy][cx]) {
            _game[cursor[1]][cursor[0]]._targeted = true;
    }
    return _all_possible_targets[cy][cx];
}

