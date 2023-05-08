#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include <string>
#include "graphics.hpp"
#include "widget.hpp"

class Text_box :public Widget{
protected:
    bool _checked = false;
public:
    Text_box(int x,int y,int size_x,int size_y,int font_size,std::string value);
    virtual void display_update() override;
    virtual void action(genv::event &ev) override;
    virtual void btn_action_int(int arg) override;
    virtual void check_change();
    void text_change();
};

#endif // TEXTBOX_HPP_INCLUDED
