#ifndef GUI_LABELIMP_H
#define GUI_LABELIMP_H


#include "SFML\Graphics.hpp"
#include "..\Styles.h"

namespace gui {

	enum class Text_status { OK, TOO_BIG };
	enum class Align { CENTER, LEFT, RIGHT };

	namespace Imp
	{

		class LabelImp
		{
		public:
			explicit LabelImp(const sf::String & text = {}, const Text_style * text_style = {});

			void setSize(const sf::Vector2f & size);
			void setPosition(const sf::Vector2f & position);
			void setCharacterColor(const sf::Color & color);
			void setFont(const sf::Font & font);
			void setCharacterSize(unsigned int size);
			void setString(const sf::String & text);
			void setStyle(sf::Uint32 style);
			void setTextStyle(const Text_style & text_style);
			void setAlign(Align align);

			const sf::Vector2f& getSize() const;
			const sf::Vector2f& getPosition() const;
			const sf::Rect<float> getGlobalBounds() const;
			const sf::Color& getCharacteColor() const;
			const sf::Font& getFont() const;
			unsigned int getCharacterSize() const;
			const sf::String& getString() const;
			const Text_status& getStatus() const;
			sf::Uint32 getStyle() const;
			Align getAlign();

			void draw(sf::RenderTarget & render_target) const;


		protected:
			void resize();


		private:
			const sf::Font * _font{};
			sf::Text _text;
			sf::RectangleShape _rectangle;
			Text_status _text_status = Text_status::OK;
			Align _align = Align::CENTER;
			float _padding_left = 0, _padding_top_bottom = 0;
			float _min_padding = 5.0f;
		};

		inline LabelImp::LabelImp(const sf::String & text, const Text_style * text_style)
		{
			_text.setFont(*_font);
			_text.setString(text);

			if (text_style)
			{
				setTextStyle(*text_style);
			}
		}

		inline void LabelImp::setSize(const sf::Vector2f & size)
		{
			_rectangle.setSize(size);

			// Resize text
			resize();
		}

		inline void LabelImp::setPosition(const sf::Vector2f & position)
		{
			_rectangle.setPosition(position);

			// Round text position for sharp edges
			_text.setPosition(std::round(position.x + _padding_left), std::round(position.y + _padding_top_bottom));
		}

		inline void LabelImp::setCharacterColor(const sf::Color & color)
		{
			_text.setFillColor(color);
		}

		inline void LabelImp::setFont(const sf::Font & font)
		{
			_font = &font;

			_text.setFont(font);

			// Resize text
			resize();
		}

		inline void LabelImp::setCharacterSize(unsigned int size)
		{
			_text.setCharacterSize(size);
			
			// Resize text
			resize();
		}

		inline void LabelImp::setString(const sf::String & text)
		{
			_text.setString(text);
			
			// Resize text
			resize();
		}

		inline void LabelImp::setStyle(sf::Uint32 style)
		{
			_text.setStyle(style);
			
			// Resize text
			resize();
		}

		inline void LabelImp::setTextStyle(const Text_style & text_style)
		{
			setFont(text_style._font);
			_text.setCharacterSize(text_style._character_size);
			_text.setFillColor(text_style._color);
			_text.setStyle(text_style._style);
			
			// Resize text
			resize();
		}

		inline void LabelImp::setAlign(Align align)
		{
			_align = align;
			
			// Resize text
			resize();
		}

		inline const sf::Vector2f & LabelImp::getSize() const
		{
			return _rectangle.getSize();
		}

		inline const sf::Vector2f & LabelImp::getPosition() const
		{
			return _rectangle.getPosition();
		}

		inline const sf::Rect<float> LabelImp::getGlobalBounds() const
		{
			return _rectangle.getGlobalBounds();
		}

		inline const sf::Color & LabelImp::getCharacteColor() const
		{
			return _text.getFillColor();
		}

		inline const sf::Font & LabelImp::getFont() const
		{
			return *_font;
		}

		inline unsigned int LabelImp::getCharacterSize() const
		{
			return _text.getCharacterSize();
		}

		inline const sf::String & LabelImp::getString() const
		{
			return _text.getString();
		}

		inline const Text_status & LabelImp::getStatus() const
		{
			return _text_status;
		}

		inline sf::Uint32 LabelImp::getStyle() const
		{
			return _text.getStyle();
		}

		inline Align LabelImp::getAlign()
		{
			return _align;
		}

		inline void LabelImp::draw(sf::RenderTarget & render_target) const
		{
			// If the text has a good size then draw it
			if (_text_status == Text_status::OK)
			{
				render_target.draw(_text);
			}
		}

		inline void LabelImp::resize()
		{
			sf::Rect<float> rectangle_bounds = _rectangle.getLocalBounds();
			sf::Rect<float> text_bounds = _text.getLocalBounds();

			sf::Text exemplary_text = _text;

			// Set exemplary_text
			// Note: exemplary_text must have the height of all possible texts
			exemplary_text.setString(L"y”");
			sf::Rect<float> exemplary_text_bounds = exemplary_text.getLocalBounds();


			if (text_bounds.width > (rectangle_bounds.width - _min_padding) || text_bounds.height > rectangle_bounds.height)
			{
				// The text is too large to be display
				_text_status = Text_status::TOO_BIG;
				return;
			}

			switch (_align)
			{
			case gui::Align::CENTER:
				_padding_left = (rectangle_bounds.width - text_bounds.width) / 2;
				_padding_top_bottom = rectangle_bounds.height / 2 - exemplary_text_bounds.top - exemplary_text_bounds.height / 2;
				break;
			case gui::Align::LEFT:
				_padding_left = _min_padding;
				_padding_top_bottom = rectangle_bounds.height / 2 - exemplary_text_bounds.top - exemplary_text_bounds.height / 2;
				break;
			case gui::Align::RIGHT:
				_padding_left = (rectangle_bounds.width - text_bounds.width) - _min_padding;
				_padding_top_bottom = rectangle_bounds.height / 2 - exemplary_text_bounds.top - exemplary_text_bounds.height / 2;
				break;
			default:
				break;
			}

			// The text can be display
			_text_status = Text_status::OK;

			// Fix weird error
			// NOTE: String must by replace by another, different string,
			// NOTE: after wich the text will by dislpayed correctly
			auto string = _text.getString();
			_text.setString("");
			_text.setString(string);

			setPosition(_rectangle.getPosition());
		}

	}
}

#endif // !GUI_LABELIMP_H
