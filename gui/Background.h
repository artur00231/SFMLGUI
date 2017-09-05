#ifndef GUI_BACKGROUND_H
#define GUI_BACKGROUND_H

#include "Image.h"
#include <memory>

namespace gui
{

	enum class Background_type { IMAGE, COLOR };

	namespace modifier
	{

		class Background_modifier
		{
		public:
			Background_modifier() = default;

			Background_modifier(Background_modifier&&) = default;
			Background_modifier& operator=(Background_modifier&&) = default;

			virtual void setColor(const sf::Color & color) = 0;
			virtual void setBackground_type(Background_type background_type) = 0;
			virtual void setImage(Image * image) = 0;

			virtual const sf::Color& getColor() const = 0;
			virtual Background_type getBackground_type() const = 0;
			virtual modifier::Image_modifier* getImage() = 0;

			virtual ~Background_modifier() {};

		protected:
			// Background_modifier can not by copied
			Background_modifier(const Background_modifier&) = default;
			Background_modifier& operator=(const Background_modifier&) = default;
		};

	}

	class Background : public passive_gui_object, public modifier::Background_modifier
	{
	public:
		Background();

		Background(const Background&);
		Background& operator=(const Background&);
		Background(Background&&) = default;
		Background& operator=(Background&&) = default;

		void setSize(const sf::Vector2f & size) override;
		void setPosition(const sf::Vector2f & position) override;
		void setColor(const sf::Color & color) override;

		const sf::Vector2f& getSize() const override;
		const sf::Vector2f& getPosition() const override;
		const sf::Rect<float> getGlobalBounds() const override;
		const sf::Color& getColor() const override;

		void draw(sf::RenderTarget & render_target) const override;

		void setOwner(owner & owner) override;
		void removeFromOwner(owner & owner) override;

		void setBackground_type(Background_type background_type) override;
		void setImage(Image * image) override;

		Background_type getBackground_type() const override;
		modifier::Image_modifier* getImage() override;

		void fitTo(const gui_object & object);
		void fitTo(const sf::Rect<float> & rectangle);

		~Background() {};

	private:
		Background_type _background_type = Background_type::COLOR;
		std::unique_ptr<Image> _image;
		sf::RectangleShape _rectangle;

	};

}

#endif // !GUI_BACKGROUND_H
