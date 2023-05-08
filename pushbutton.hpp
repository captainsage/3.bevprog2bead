#ifndef PUSHBUTTON_HPP_INCLUDED
#define PUSHBUTTON_HPP_INCLUDED

#include "widget.hpp"
#include "graphics.hpp"

typedef void(*FuncInt)(Widget*,int);
typedef void(*FuncVoid)(Widget*);

class Push_button :public Widget{
protected:
    Widget* _int_target = 0;
    Widget* _void_target = 0;
    FuncInt _func_int = 0;
    FuncVoid _func_void = 0;
    int _arg_func;
public:
    Push_button(int x, int y, int size_x, int size_y, int font_size, genv::canvas skin, FuncInt fi, Widget* target, int arg);
    Push_button(int x, int y, int size_x, int size_y, int font_size, genv::canvas skin, FuncVoid fv, Widget* target);
    void action(genv::event &ev) override;
    void display_update() override;
    void btn_action_int(int arg) override;
};

#endif // PUSHBUTTON_HPP_INCLUDED
