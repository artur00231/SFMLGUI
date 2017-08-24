#ifndef GUI_SLIDER_H
#define GUI_SLIDER_H

#include "active_gui_object.h"

namespace gui
{

	class slider : public active_gui_object
	{
	public:
		virtual void setValue(long long value) = 0;
		virtual void setMinMax(long long min, long long max) = 0;

		virtual long long getNumber() = 0;
		virtual std::pair<long long, long long> getMinMax() = 0;
	};

}

#endif // !GUI_SLIDER_H
