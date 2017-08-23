#ifndef GUI_ACTIVE_GUI_OBJECT_H
#define GUI_ACTIVE_GUI_OBJECT_H

#include "gui_object.h"
#include "Mouse_info.h"
#include <chrono>
#include <deque>



namespace gui
{

	class Event;

	using duration = std::chrono::duration<long long, std::micro>;

	class active_gui_object : public gui::gui_object
	{
	public:

		virtual void up_date(gui::duration time_elapsed, const Mouse_info & mouse_info ) = 0;

		virtual bool isActive() const = 0;
		virtual bool isHover() const = 0;
		virtual bool isClicked() const = 0;
		virtual bool isFocused() const = 0;
		virtual bool isHoverChange() const = 0;
		virtual bool isClickedChange() const = 0;
		virtual bool isNeedResize() const = 0;

		virtual void setActive(bool active) = 0;
		virtual void setFocus(bool focus) = 0;

		friend class Event;

		virtual void resize() = 0;

	protected:
		virtual void setHover(bool hover) = 0;
		virtual void setClicked(bool Clicked) = 0;
		virtual void setHoverChange(bool hover_change) = 0;
		virtual void setClickedChange(bool clicked_change) = 0;

	};

}

#endif // !GUI_ACTIVE_GUI_OBJECT_H

