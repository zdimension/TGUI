/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (vdv_b@tgui.eu)
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


#include <TGUI/Objects.hpp>
#include <TGUI/Window.hpp>

#include <SFML/OpenGL.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Window::Window()
    {
        // Create the window
        m_Window = new sf::RenderWindow();

        // The main window is always focused
        m_GroupFocused = true;

        // We created the window
        m_OwningWindow = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Window::Window(sf::RenderWindow& window)
    {
        m_Window = &window;

        // The main window is always focused
        m_GroupFocused = true;

        // We do not own the sfml window
        m_OwningWindow = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Window::Window(sf::VideoMode mode, const std::string& title, sf::Uint32 style, const sf::ContextSettings& settings)
    {
        // Create the window
        m_Window = new sf::RenderWindow(mode, title, style, settings);

        // The main window is always focused
        m_GroupFocused = true;

        // We created the window
        m_OwningWindow = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Window::Window(sf::WindowHandle handle, const sf::ContextSettings& settings)
    {
        // Create the window
        m_Window = new sf::RenderWindow(handle, settings);

        // The main window is always focused
        m_GroupFocused = true;

        // We created the window
        m_OwningWindow = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Window::~Window()
    {
        if (m_OwningWindow)
            delete m_Window;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::handleEvent(sf::Event event)
    {
        // Check if the event is a mouse move or mouse down/press
        if (event.type == sf::Event::MouseMoved)
        {
            Vector2f mouseCoords = m_Window->mapPixelToCoords(Vector2i(event.mouseMove.x, event.mouseMove.y), m_Window->getView());

            // Adjust the mouse position of the event
            event.mouseMove.x = static_cast<int>(mouseCoords.x + 0.5f);
            event.mouseMove.y = static_cast<int>(mouseCoords.y + 0.5f);
        }
        else if ((event.type == sf::Event::MouseButtonPressed) || (event.type == sf::Event::MouseButtonReleased))
        {
            Vector2f mouseCoords = m_Window->mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y), m_Window->getView());

            // Adjust the mouse position of the event
            event.mouseButton.x = static_cast<int>(mouseCoords.x + 0.5f);
            event.mouseButton.y = static_cast<int>(mouseCoords.y + 0.5f);
        }

        // Let the event manager handle the event
        m_EventManager.handleEvent(event);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::drawGUI()
    {
        // Update the time
        updateTime(m_Clock.restart());

        // Check if clipping is enabled
        GLboolean clippingEnabled = glIsEnabled(GL_SCISSOR_TEST);
        GLint scissor[4];

        if (clippingEnabled)
        {
            // Remember the old clipping area
            glGetIntegerv(GL_SCISSOR_BOX, scissor);
        }
        else // Clipping was disabled
        {
            // Enable clipping
            glEnable(GL_SCISSOR_TEST);
            glScissor(0, 0, m_Window->getSize().x, m_Window->getSize().y);
        }

        // Draw the window with all objects inside it
        drawObjectGroup(m_Window, sf::RenderStates::Default);

        // Check if clipping was previously enabled
        if (clippingEnabled)
        {
            // Reset the old clipping
            glScissor(scissor[0], scissor[1], scissor[2], scissor[3]);
        }
        else // Clipping was previously disabled
        {
            // Disable the clipping again
            glDisable(GL_SCISSOR_TEST);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Window::pollCallback(Callback& callback)
    {
        // Check if the callback queue is empty
        if (m_Callback.empty())
            return false;
        else // The queue is not empty
        {
            // Get the next callback
            callback = m_Callback.front();

            // Remove the callback from the queue
            m_Callback.pop();

            return true;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::updateTime(const sf::Time& elapsedTime)
    {
        m_EventManager.updateTime(elapsedTime);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::addChildCallback(Callback& callback)
    {
        // If there is no global callback function then add the callback to the queue
        if (m_GlobalCallbackFunctions.empty())
            m_Callback.push(callback);
        else
        {
            // Loop through all callback functions and call them
            for (std::list< boost::function<void(const Callback&)> >::const_iterator it = m_GlobalCallbackFunctions.begin(); it != m_GlobalCallbackFunctions.end(); ++it)
                (*it)(callback);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f Window::getDisplaySize()
    {
        return Vector2f(m_Window->getSize());
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::create(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
    {
        m_Window->create(mode, title, style, settings);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::create(sf::WindowHandle handle, const sf::ContextSettings& settings)
    {
        m_Window->create(handle, settings);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2u Window::getSize() const
    {
        return m_Window->getSize();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Image Window::capture() const
    {
        return m_Window->capture();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::close()
    {
        m_Window->close();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Window::isOpen() const
    {
        return m_Window->isOpen();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::ContextSettings& Window::getSettings() const
    {
        return m_Window->getSettings();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Window::pollEvent(sf::Event& event)
    {
        return m_Window->pollEvent(event);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Window::waitEvent(sf::Event& event)
    {
        return m_Window->waitEvent(event);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2i Window::getPosition() const
    {
        return m_Window->getPosition();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::setPosition(const Vector2i& position)
    {
        m_Window->setPosition(position);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::setSize(const Vector2u size)
    {
        m_Window->setSize(size);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::setTitle(const sf::String& title)
    {
        m_Window->setTitle(title);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::setIcon(unsigned int width, unsigned int height, const sf::Uint8* pixels)
    {
        m_Window->setIcon(width, height, pixels);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::setVisible(bool visible)
    {
        m_Window->setVisible(visible);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::setVerticalSyncEnabled(bool enabled)
    {
        m_Window->setVerticalSyncEnabled(enabled);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::setMouseCursorVisible(bool visible)
    {
        m_Window->setMouseCursorVisible(visible);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::setKeyRepeatEnabled(bool enabled)
    {
        m_Window->setKeyRepeatEnabled(enabled);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::setFramerateLimit(unsigned int limit)
    {
        m_Window->setFramerateLimit(limit);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::setJoystickThreshold(float threshold)
    {
        m_Window->setJoystickThreshold(threshold);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Window::setActive(bool active) const
    {
        return m_Window->setActive(active);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::display()
    {
        m_Window->display();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::WindowHandle Window::getSystemHandle() const
    {
        return m_Window->getSystemHandle();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::clear(const sf::Color& color)
    {
        m_Window->clear(color);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::setView(const sf::View& view)
    {
        m_Window->setView(view);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::View& Window::getView() const
    {
        return m_Window->getView();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::View& Window::getDefaultView() const
    {
        return m_Window->getDefaultView();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::IntRect Window::getViewport(const sf::View& view) const
    {
        return m_Window->getViewport(view);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f Window::mapPixelToCoords(const Vector2i& point) const
    {
        return m_Window->mapPixelToCoords(point);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f Window::mapPixelToCoords(const Vector2i& point, const sf::View& view) const
    {
        return m_Window->mapPixelToCoords(point, view);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2i Window::mapCoordsToPixel(const Vector2f& point) const
    {
        return m_Window->mapCoordsToPixel(point);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2i Window::mapCoordsToPixel(const Vector2f& point, const sf::View& view) const
    {
        return m_Window->mapCoordsToPixel(point, view);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
    {
        return m_Window->draw(drawable, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::draw(const sf::Vertex* vertices, unsigned int vertexCount, sf::PrimitiveType type, const sf::RenderStates& states)
    {
        return m_Window->draw(vertices, vertexCount, type, states);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::pushGLStates()
    {
        return m_Window->pushGLStates();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::popGLStates()
    {
        return m_Window->popGLStates();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Window::resetGLStates()
    {
        return m_Window->resetGLStates();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
