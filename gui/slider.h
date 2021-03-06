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

		virtual long long getValue() const = 0;
		virtual std::pair<long long, long long> getMinMax() const = 0;
		virtual long long getMaxSteps() const = 0;
		virtual float getMinButtonSize() const = 0;
	};

}

#endif // !GUI_SLIDER_H
