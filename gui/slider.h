#ifndef GUI_SLIDER_H
#define GUI_SLIDER_H

#include "active_gui_object.h"

namespace gui
{

	class slider : active_gui_object
	{
	public:
		virtual void setValue(long long value) = 0;
		virtual void setMinMax(long long min, long long max) = 0;
		virtual void setStepValue(long long step) = 0;

		virtual long long getNumber() = 0;
		virtual std::pair<long long, long long> getMInMax() = 0;
		virtual long long getStepValue() = 0;
	};

}

#endif // !GUI_SLIDER_H
