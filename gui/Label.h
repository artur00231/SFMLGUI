#ifndef GUI_LABEL_H
#define GUI_LABEL_H

#include "passive_gui_object.h"
#include "Imp\LabelImp.h"

namespace gui {

	namespace modifier
	{

		class Label_modifier
		{
		public:
			Label_modifier() {};

			Label_modifier(Label_modifier&&) = default;
			Label_modifier& operator=(Label_modifier&&) = default;

			virtual void setColor(const sf::Color & color) = 0;
			virtual bool setFont(const std::string & path) = 0;
			virtual void setCharacterSize(unsigned int size) = 0;
			virtual void setString(const sf::String & text) = 0;
			virtual void setStyle(sf::Uint32 style) = 0;
			virtual void setTextStyle(const Text_style & text_style) = 0;
			virtual void setAlign(Align align) = 0;

			virtual const sf::Color& getColor() const = 0;
			virtual unsigned int getCharacterSize() const = 0;
			virtual const sf::String& getString() const = 0;
			virtual const Text_status& getStatus() const = 0;
			virtual int getStyle() const = 0;
			virtual Align getAlign() = 0;

			// Label_modifier can not by copied
			Label_modifier(const Label_modifier&) = delete;
			Label_modifier& operator=(const Label_modifier&) = delete;

			virtual ~Label_modifier() {};

		};

	}

	class Label : public passive_gui_object, private Imp::LabelImp, public modifier::Label_modifier
	{
	public:
		explicit Label(const sf::String& = {}, const Text_style* = {});

		Label(const Label&) = default;
		Label& operator=(const Label&) = default;
		Label(Label&&) = default;
		Label& operator=(Label&&) = default;

		void setSize(const sf::Vector2f & size) override;
		void setPosition(const sf::Vector2f & position) override;
		void setColor(const sf::Color & color) override;

		const sf::Vector2f& getSize() const override;
		const sf::Vector2f& getPosition() const override;
		const sf::Rect<float> getGlobalBounds() const override;
		const sf::Color& getColor() const override;

		void draw(sf::RenderTarget & render_target) const override;

		void setOwner(owner & owner) override;

		bool setFont(const std::string & path) override;
		void setCharacterSize(unsigned int size) override;
		void setString(const sf::String & text) override;
		void setStyle(sf::Uint32 style) override;
		void setTextStyle(const Text_style & text_style) override;
		void setAlign(Align align) override;

		unsigned int getCharacterSize() const override;
		const sf::String& getString() const override;
		const Text_status& getStatus() const override;
		int getStyle() const override;
		Align getAlign() override;

		~Label() {};

	protected:
		void resize();
	};

}

#endif // !GUI_LABEL_H
