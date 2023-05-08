#ifndef NUMBER_INPUT_W_HPP_INCLUDED
#define NUMBER_INPUT_W_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include "pushbutton.hpp"
#include "vector"
class Number_input_w : public Widget{
protected:
    int  _range_floor, _range_ceiling;
    Push_button* _increase_btn = 0;
    Push_button* _decrease_btn = 0;
public:
    Number_input_w(int x, int y, int size_x, int size_y, int font_size, int value, int range_floor, int range_ceiling);
    void display_update() override;
    void value_validator();
    void value_change(int diff);
    void action(genv::event &ev) override;
    void btn_action_int(int arg) override;
    std::vector<Widget*> get_sub_widgets() override;
    std::vector<genv::canvas> button_generate();
};

#endif // NUMBER_INPUT_W_HPP_INCLUDED
