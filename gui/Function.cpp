#include "Function.h"

void gui::Function::set(gui::function * function)
{
	_function_1.reset(function);
	_function_2 = nullptr;
	_function_3 = nullptr;
	_function_4 = nullptr;
}

void gui::Function::set(std::function<void(const Mouse_info&, gui::duration&, active_gui_object*)> function)
{
	_function_1.reset();
	_function_2.swap(function);
	_function_3 = nullptr;
	_function_4 = nullptr;
}

void gui::Function::set(std::function<void(active_gui_object*)> function)
{
	_function_1.reset();
	_function_2 = nullptr;
	_function_3.swap(function);
	_function_4 = nullptr;
}

void gui::Function::set(std::function<void()> function)
{
	_function_1.reset();
	_function_2 = nullptr;
	_function_3 = nullptr;
	_function_4.swap(function);
}

void gui::Function::unset()
{
	_function_1.reset();
	_function_2 = nullptr;
	_function_3 = nullptr;
	_function_4 = nullptr;
}

void gui::Function::operator()(const Mouse_info & mouse_info, gui::duration & duration, active_gui_object * object)
{
	if (_function_1)
	{
		(*_function_1)(mouse_info, duration, object);
	}
	else if (_function_2)
	{
		_function_2(mouse_info, duration, object);
	}
	else if (_function_3)
	{
		_function_3(object);
	}
	else if (_function_4)
	{
		_function_4();
	}
}
