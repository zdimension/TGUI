/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2015 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_LABEL_HPP
#define TGUI_LABEL_HPP


#include <TGUI/ClickableWidget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Label widget
    ///
    /// Signals:
    ///     - DoubleClicked (double left clicked on top of the label)
    ///         * Optional parameter sf::String: text of the label
    ///         * Uses Callback member 'text'
    ///
    ///     - Inherited signals from ClickableWidget
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Label : public ClickableWidget, public WidgetBorders, public WidgetPadding
    {
    public:

        typedef std::shared_ptr<Label> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const Label> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Label();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the label
        ///
        /// @param themeFileFilename  Filename of the theme file.
        /// @param section            The section in the theme file to read.
        ///
        /// @throw Exception when the theme file could not be opened.
        /// @throw Exception when the theme file did not contain the requested section with the needed information.
        ///
        /// When an empty string is passed as filename, the built-in white theme will be used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Label::Ptr create(const std::string& themeFileFilename = "", const std::string& section = "Label");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another label
        ///
        /// @param label  The other label
        ///
        /// @return The new label
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Label::Ptr copy(Label::ConstPtr label);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// @param position  New position
        ///
        /// @see move, getPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPosition(const Layout& position) override;
        using Transformable::setPosition;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the area of the text that will be drawn.
        ///
        /// @param size  Size of the part to draw
        ///
        /// Only the part of the text that lies within the size will be drawn.
        ///
        /// When a background color is set, the drawn background will have this size.
        /// So setting a size that is bigger than the text will result in a bigger area being filled.
        ///
        /// When this function is called, the label will no longer be auto-sizing.
        ///
        /// @see setAutoSize
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const Layout& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text.
        ///
        /// @param text  The new text
        ///
        /// When the text is auto-sized (default), then the size of the label will be changed to fit the whole text.
        ///
        /// @see setAutoSize
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setText(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text.
        ///
        /// @return Text that is currently used
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::String& getText() const
        {
            return m_string;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the font of the text.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed with the setGlobalFont function from the parent.
        ///
        /// @param font  The new font.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(std::shared_ptr<sf::Font> font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the font of the text.
        ///
        /// @return  Pointer to the font that is currently being used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<sf::Font> getTextFont() const
        {
            return m_font;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the text.
        ///
        /// @param color  New text color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const sf::Color& color)
        {
            m_text.setColor(color);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the color of the text.
        ///
        /// @return The current text color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getTextColor() const
        {
            return m_text.getColor();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the style of the text
        ///
        /// The possible styles can be found in the sf::Text::Style enum.
        /// You can pass a combination of one or more styles, for example sf::Text::Bold | sf::Text::Italic.
        /// The default style is sf::Text::Regular.
        ///
        /// @param style  New text style
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextStyle(sf::Uint32 style);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the style of the text
        ///
        /// @return The current text style
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Uint32 getTextStyle() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character size of the text.
        ///
        /// @param size  The new text size
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character size of the text.
        ///
        /// @return The current text size.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const
        {
            return m_text.getCharacterSize();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the background color of the label.
        ///
        /// @param backgroundColor  New background color
        ///
        /// The background color is transparent by default.
        ///
        /// When auto-size is enabled (default), then the background is just as big as the text.
        /// When a manual size is set, the background will fill this whole area.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(const sf::Color& backgroundColor)
        {
            m_background.setFillColor(backgroundColor);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the background color of the label.
        ///
        /// The background color is transparent by default.
        ///
        /// @return The current background color
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getBackgroundColor() const
        {
            return m_background.getFillColor();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the color of the borders that can optionally be drawn around the label
        ///
        /// @param borderColor  New border color
        ///
        /// @see setBorders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorderColor(const sf::Color& borderColor)
        {
            m_borderColor = borderColor;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the label is auto-sized or not.
        ///
        /// @param autoSize  Should the size of the label be changed when the text changes?
        ///
        /// When the label is in auto-size mode, the width and height of the label will be changed to fit the text.
        /// Otherwise, only the part defined by the size will be visible.
        ///
        /// The label is auto-sized by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setAutoSize(bool autoSize);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the label is auto-sized or not.
        ///
        /// @return Is the size of the label changed when the text changes?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool getAutoSize() const
        {
            return m_autoSize;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the maximum width that the text will have when auto-sizing.
        ///
        /// @param maximumWidth The new maximum text width
        ///
        /// This property is ignored when an exact size has been given.
        /// Pass 0 to this function to disable the maximum.
        ///
        /// When the text is auto-sizing then the text will be split over several lines when its width would exceed th
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumTextWidth(float maximumWidth);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum width that the text will have.
        ///
        /// @return
        ///        - The width of the label minus the padding when a specific size was set.
        ///        - The maximum text width when auto-sizing and a maximum was set.
        ///        - 0 when auto-sizing but there is no maximum width.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getMaximumTextWidth();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the padding.
        ///
        /// @param padding  Size of the padding
        ///
        /// This is the distance between the side of the background and the text.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setPadding(const Padding& padding) override;
        using WidgetPadding::setPadding;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        // Tell the widget about its parent
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const container) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() override
        {
            return std::make_shared<Label>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When the elapsed time has changed then this function is called.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void update() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Rearrange the text, making use of the given size of maximum text width.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rearrangeText();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        sf::RectangleShape m_background;

        sf::String m_string;
        sf::Text   m_text;

        sf::Color  m_borderColor = {0, 0, 0};

        bool m_autoSize = true;

        float m_maximumTextWidth = 0;

        // Will be set to true after the first click, but gets reset to false when the second click does not occur soon after
        bool m_possibleDoubleClick = false;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_LABEL_HPP
