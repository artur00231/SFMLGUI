#ifndef GUI_ICONS_H
#define GUI_ICONS_H

#include <utility>

namespace gui
{

	class Icons
	{
	public:
		Icons();
		~Icons();

		// All posible icons
		enum Icon {CHECKBOX, RADIO_BUTTON_MARK, RADIO_BUTTON_OUTLINE};

		// Get icon and its size
		static std::pair<unsigned char*, unsigned int> get(Icon);

	private:

		// Icons
		static constexpr unsigned int _checkbox_icon_size = 396;
		static unsigned char _checkbox_icon[_checkbox_icon_size + 1];
		
		static constexpr unsigned int _radio_button_mark_icon_size = 658;
		static unsigned char _radio_button_mark_icon[_radio_button_mark_icon_size + 1];

		static constexpr unsigned int _radio_button_outline_icon_size = 1231;
		static unsigned char _radio_button_outline_icon[_radio_button_outline_icon_size + 1];

	};

}

#endif // !GUI_ICONS_H

