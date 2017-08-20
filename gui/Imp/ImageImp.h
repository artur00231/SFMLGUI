#ifndef GUI_IMAGEIMP_H
#define GUI_IMAGEIMP_H

#include "SFML\Graphics.hpp"

namespace gui
{

	namespace Imp
	{

		class ImageImp
		{
		public:
			explicit ImageImp(const std::string & path = {});

			void setSize(const sf::Vector2f & size);
			void setPosition(const sf::Vector2f & position);
			void setColor(const sf::Color & color);

			const sf::Vector2f& getSize() const;
			const sf::Vector2f& getPosition() const;
			const sf::Rect<float> getGlobalBounds() const;
			const sf::Color& getColor() const;

			void draw(sf::RenderTarget & render_target) const;

			void setTexture(const std::string & path);
			void setTexture(const std::string & path, const sf::Rect<int> & part);
			void setTexture(const sf::Image & image);
			void setTexture(const sf::Image & image, const sf::Rect<int> & part);
			// Set the external texture
			void setTexture(const sf::Texture * texture);
			void setTexture(const void * data, std::size_t size);
			void setRepeated(bool repeated);
			void setSmooth(bool smooth);

			const sf::Texture* getTexture();
			bool getRepeated();
			bool getSmooth();

			~ImageImp() {};

		private:
			sf::Texture _texture;
			sf::Sprite _sprite;

			sf::Vector2u _orginal_size;
			mutable sf::Vector2f _size;

		};

		inline ImageImp::ImageImp(const std::string & path)
		{
			_sprite.setTexture(_texture);

			// By default, set the texture smooth
			setSmooth(true);

			if (path != "")
			{
				setTexture(path);
			}
		}

		inline void ImageImp::setSize(const sf::Vector2f & size)
		{
			// If the texture exist, set the scale
			if (_orginal_size != sf::Vector2u{ 0, 0 })
			{
				float x_factor = size.x / static_cast<float>(_orginal_size.x);
				float y_factor = size.y / static_cast<float>(_orginal_size.y);

				_sprite.setScale(x_factor, y_factor);
			}
		}

		inline void ImageImp::setPosition(const sf::Vector2f & position)
		{
			_sprite.setPosition(position);
		}

		inline void ImageImp::setColor(const sf::Color & color)
		{
			_sprite.setColor(color);
		}

		inline const sf::Vector2f & ImageImp::getSize() const
		{
			sf::Vector2f scale = _sprite.getScale();

			// Calculate size from scale and original size
			_size = { scale.x * static_cast<float>(_orginal_size.x), scale.x *static_cast<float>(_orginal_size.y) };
			return _size;
		}

		inline const sf::Vector2f & ImageImp::getPosition() const
		{
			return _sprite.getPosition();
		}

		inline const sf::Rect<float> ImageImp::getGlobalBounds() const
		{
			return sf::Rect<float>();
		}

		inline const sf::Color & ImageImp::getColor() const
		{
			return _sprite.getColor();
		}

		inline void ImageImp::draw(sf::RenderTarget & render_target) const
		{
			render_target.draw(_sprite);
		}

		inline void ImageImp::setTexture(const std::string & path)
		{
			_texture.loadFromFile(path);
			_orginal_size = _texture.getSize();

			// Reset sprite to new texture size
			_sprite.setTexture(_texture, true);
		}

		inline void ImageImp::setTexture(const std::string & path, const sf::Rect<int> & part)
		{
			_texture.loadFromFile(path, part);
			_orginal_size = _texture.getSize();

			// Reset sprite to new texture size
			_sprite.setTexture(_texture, true);
		}

		inline void ImageImp::setTexture(const sf::Image & image)
		{
			_texture.loadFromImage(image);
			_orginal_size = _texture.getSize();

			// Reset sprite to new texture size
			_sprite.setTexture(_texture, true);
		}

		inline void ImageImp::setTexture(const sf::Image & image, const sf::Rect<int> & part)
		{
			_texture.loadFromImage(image, part);
			_orginal_size = _texture.getSize();

			// Reset sprite to new texture size
			_sprite.setTexture(_texture, true);
		}

		inline void ImageImp::setTexture(const sf::Texture * texture)
		{
			_orginal_size = texture->getSize();

			// Reset sprite to new texture size
			_sprite.setTexture(*texture, true);
		}

		inline void ImageImp::setTexture(const void * data, std::size_t size)
		{
			_texture.loadFromMemory(data, size);
			_orginal_size = _texture.getSize();

			// Reset sprite to new texture size
			_sprite.setTexture(_texture, true);
		}

		inline void ImageImp::setRepeated(bool repeated)
		{
			_texture.setRepeated(repeated);
		}

		inline void ImageImp::setSmooth(bool smooth)
		{
			_texture.setSmooth(smooth);
		}

		inline const sf::Texture * ImageImp::getTexture()
		{
			return &_texture;
		}

		inline bool ImageImp::getRepeated()
		{
			return _texture.isRepeated();
		}

		inline bool ImageImp::getSmooth()
		{
			return _texture.isSmooth();
		}


	}
}

#endif // !GUI_IMAGEIMP_H