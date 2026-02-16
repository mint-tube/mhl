#include "../include/mbox.hpp"

int main() {
  mbox::event ev;
  size_t y = 0;

  try {
    mbox::init();
  } catch (std::runtime_error const& e) { // deinitializes automatically on exceptions
    printf("Failed to initialize: %s", e.what()); // informative exceptions
  }

  mbox::printf(0, y++, mbox::Style::DEFAULT, mbox::Style::DEFAULT,
    "привет from termbox!"); // full support for non-ASCII characters
  mbox::printf(0, y++, mbox::Style::DEFAULT, mbox::Style::DEFAULT,
    "width=%d height=%d", mbox::width(), mbox::height()); // string formatting as in std::printf()
  mbox::printf(0, y++,
    mbox::Style::BLUE | mbox::Style::BRIGHT, mbox::Style::DEFAULT, // attributes can be combined
    "버튼을 <ESC> to quit");
  mbox::flush(); // flush the buffer manually
  y++;

  mbox::set_input_mode(mbox::InputMode::MOUSE); // optional support of mouse input
  while (ev.key != mbox::Key::ESC) {
    if (y >= mbox::height()) {
      mbox::clear();
      y = 0;
    };
    mbox::poll_event(&ev);
    switch (ev.type) {
      case mbox::EventType::KEY:
        mbox::printf(0, y++, mbox::Style::YELLOW, mbox::Style::DEFAULT,
          "KEY:    mod=%d key=%d char=%c", ev.mod, ev.key, ev.ch);
        break;
      case mbox::EventType::RESIZE:
        mbox::printf(0, y++, mbox::Style::CYAN | mbox::Style::BRIGHT, mbox::Style::DEFAULT,
          "RESIZE: width=%d height=%d", ev.width, ev.height);
        break;
      case mbox::EventType::MOUSE:
        mbox::printf(0, y++, mbox::Style::GREEN, mbox::Style::DEFAULT,
          "MOUSE:  button=%d x=%d y=%d", ev.button, ev.x, ev.y);
        break;
    }

    mbox::flush();
  }

  mbox::shutdown(); // shutdown explicitly or wile things will happen
}