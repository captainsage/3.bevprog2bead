#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "textbox.hpp"
#include "graphics.hpp"
#include "widget.hpp"
#include <string>
#include <vector>

class Menu : public Widget {
protected:
    int _list_ycoord = 0;
    std::vector<Text_box*> _menu_options;
    genv::canvas _text_box_list;
    Text_box* _selected_item=0;
public:
    Menu(int x,int y,int size_x,int size_y,int font_size,std::vector<std::string> values);
    void display_update();
    void action(genv::event &ev);
    void btn_action_int(int arg);
    void draw_widget(genv::canvas *target) override;
    bool is_selected(int mpos_x, int mpos_y) override;
};

#endif // MENU_HPP_INCLUDED
