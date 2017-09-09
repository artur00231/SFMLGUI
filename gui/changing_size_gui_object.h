#ifndef GUI_CHANGING_SIZE_GUI_OBJECT
#define GUI_CHANGING_SIZE_GUI_OBJECT

#include "active_gui_object.h"

namespace gui
{
	
	class changing_size_gui_object : public active_gui_object
	{
	public:
		virtual void extend(bool extend) = 0;

		virtual bool isExtended() const = 0;
	};

}

#endif // !GUI_CHANGING_SIZE_GUI_OBJECT
