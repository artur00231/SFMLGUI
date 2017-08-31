#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

#include "passive_gui_object.h"
#include "Imp\ImageImp.h"

namespace gui
{

	namespace modifier
	{

		class Image_modifier
		{
		public:
			Image_modifier() = default;

			Image_modifier(Image_modifier&&) = default;
			Image_modifier& operator=(Image_modifier&&) = default;

			virtual void setColor(const sf::Color & color) = 0;
			virtual void setTexture(const std::string & path) = 0;
			virtual void setTexture(const std::string & path, const sf::Rect<int> & part) = 0;
			virtual void setTexture(const sf::Image & image) = 0;
			virtual void setTexture(const sf::Image & image, const sf::Rect<int> & part) = 0;
			// Set the external texture
			virtual void setTexture(const sf::Texture * texture) = 0;
			virtual void setRepeated(bool repeated) = 0;
			virtual void setSmooth(bool smooth) = 0;

			virtual const sf::Color& getColor() const = 0;
			virtual const sf::Texture* getTexture() = 0;
			virtual bool getRepeated() = 0;
			virtual bool getSmooth() = 0;

			// Image_modifier can not by copied
			Image_modifier(const Image_modifier&) = delete;
			Image_modifier& operator=(const Image_modifier&) = delete;

			~Image_modifier() {};
		};

	}

	class Image : public passive_gui_object, private Imp::ImageImp, public modifier::Image_modifier
	{
	public:
		explicit Image(const std::string & path = {});

		Image(const Image&) = default;
		Image& operator=(const Image&) = default;
		Image(Image&&) = default;
		Image& operator=(Image&&) = default;

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

		void setTexture(const std::string & path) override;
		void setTexture(const std::string & path, const sf::Rect<int> & part) override;
		void setTexture(const sf::Image & image) override;
		void setTexture(const sf::Image & image, const sf::Rect<int> & part) override;
		// Set the external texture
		void setTexture(const sf::Texture * texture) override;
		void setTexture(const void * data, size_t size);
		void setRepeated(bool repeated) override;
		void setSmooth(bool smooth) override;

		const sf::Texture* getTexture() override;
		bool getRepeated() override;
		bool getSmooth() override;


		~Image() {};

	};

}

#endif // !GUI_IMAGE_H
