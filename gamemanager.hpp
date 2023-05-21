#ifndef GAMEMANAGER_HPP_INCLUDED
#define GAMEMANAGER_HPP_INCLUDED

#include "widget.hpp"
#include "widgetcontrol.hpp"
#include "chesspiecewidget.hpp"
#include <vector>
#include <cmath>
#include <string>


struct PieceInfo {
    std::string _role;
    bool _white;
    bool _is_piece;
    bool _targeted =false;
    bool _is_ranged;
    int _value;
    std::vector<int> _first_step;
    std::vector<int> _second_step;

    PieceInfo();
    PieceInfo(std::string role, bool white, bool ranged, int value, std::vector<int> first_step, std::vector<int> second_step);
};
class GameManager {
protected:
    std::vector<std::vector<PieceInfo>> _game;
    std::vector<std::vector<std::vector<std::vector<int>>>> _all_possible_targets = {{{{0}}}};
    bool _whites_turn;
    std::vector<bool> _black_white_check = {false,false};
    std::string _winner = "None";
    bool simulation =  false;
public:
    GameManager();
    void reset_game();
    void target_clear();
    void set_simulation();
    void calculate_targets();
    void set_winner();
    int count_all_targets();
    bool selectable(int cx, int cy);
    bool check();
    bool piece_move(int cx, int cy, int tx, int ty);
    std::string get_winner();
    std::vector<std::vector<int>> target_fields(int cx, int cy);
    std::vector<std::vector<int>> select_target(int cx, int cy);
    std::vector<std::vector<int>> simulate(int cx, int cy, std::vector<std::vector<int>> raw_targets);
    std::vector<bool> get_check();
};


#endif // GAMEMANAGER_HPP_INCLUDED
