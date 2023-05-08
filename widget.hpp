#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

#include "graphics.hpp"
#include <vector>
#include <string>

struct Stored_value{
    int i = 0;
    std::string s = "";
    bool contains_value = false;
};


class Widget {
protected:
    Stored_value _stored_value;
    int _x, _y, _size_x, _size_y, _font_size;
    bool _selected = false;
    bool _changed = true;
    genv::canvas _display;
public:
    Widget(int x, int y, int size_x, int size_y, int font_size);
    virtual void draw_widget(genv::canvas *target);
    virtual bool is_selected(int mpos_x, int mpos_y);
    virtual void display_update() = 0;
    virtual void action(genv::event &ev) = 0;
    virtual void btn_action_int(int arg) = 0;
    virtual std::vector<Widget*> get_sub_widgets();
    static void co_caller_int(Widget* w, int arg);
    genv::canvas get_display();
    virtual Stored_value the_stored_value_is();
};

#endif
