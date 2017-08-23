#ifndef FUNCTION_FOR_ACTIVE_GUI_OBJECT_H
#define FUNCTION_FOR_ACTIVE_GUI_OBJECT_H

#include "deque"
#include "active_gui_object.h"
#include <memory>
#include <functional>

namespace gui
{

	class function
	{
	public:
		virtual void operator()(const Mouse_info&, gui::duration&, active_gui_object*) = 0;
	};

	namespace modifier
	{

		class Function_modifier
		{
		public:
			Function_modifier() {};

			Function_modifier(Function_modifier&&) = default;
			Function_modifier& operator=(Function_modifier&&) = default;

			virtual void set(function * function_object) = 0;
			virtual void set(std::function<void(const Mouse_info&, gui::duration&, active_gui_object*)> function) = 0;
			virtual void set(std::function<void(active_gui_object*)> function) = 0;
			virtual void set(std::function<void()> function) = 0;

			virtual void unset() = 0;

			// Function_modifier can not by copied
			Function_modifier(const Function_modifier&) = delete;
			Function_modifier& operator=(const Function_modifier&) = delete;

			virtual ~Function_modifier() {};
		};

	}

	class Function : public modifier::Function_modifier
	{
	public:
		Function() {};

		Function(Function&&) = default;
		Function& operator=(Function&&) = default;

		void set(function * function_object) override;
		void set(std::function<void(const Mouse_info&, gui::duration&, active_gui_object*)> function) override;
		void set(std::function<void(active_gui_object*)> function) override;
		void set(std::function<void()> function) override;

		void unset() override;

		void operator()(const Mouse_info & mouse_info, gui::duration & time_elapsed, active_gui_object * object);

		~Function() {};

	private:
		std::unique_ptr<function> _function_1;
		std::function<void(const Mouse_info&, gui::duration&, active_gui_object*)> _function_2;
		std::function<void(active_gui_object*)> _function_3;
		std::function<void()> _function_4;
	};
}

#endif // !FUNCTION_ACTIVE_GUI_OBJECT_H

