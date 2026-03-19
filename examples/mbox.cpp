#include "../include/mbox.hpp"

int main() {
  {
    mbox::term term;
    size_t y = 0;

    term.printf(0, y++, Style::DEFAULT, Style::DEFAULT,
      "привет from mbox!"); // full support of Unicode
    term.printf(0, y++, Style::DEFAULT, Style::DEFAULT,
      "width=%d height=%d", term.get_width(), term.get_height()); // classical string formatting
    term.printf(0, y++, Style::BLUE | Style::BRIGHT, Style::DEFAULT, // attributes can be combined
      "버튼을 <ESC> to quit");
    term.flush(); // decide when to flush the buffer manually
    y++;

    term.set_input_mode(InputMode::MOUSE); // opt-in for mouse input

    mbox::event ev;
    while (ev.key != Key::ESC) {
      if (y >= term.get_height()) {
        term.clear();
        y = 0;
      };

      ev = term.peek_event(20 * 1000); // poll for 30 seconds
      switch (ev.type) {
        case EventType::KEY:    // process each keystroke individually
          char utf8[7];
          mbox::utf32_to_utf8(utf8, ev.ch);
          term.printf(0, y++, Style::YELLOW, Style::DEFAULT,
            "KEY:    mod=%d key=%d char=%s", ev.mod, ev.key, utf8);
          break;
        case EventType::RESIZE: // react to resizing
          term.printf(0, y++, Style::CYAN | Style::BRIGHT, Style::DEFAULT,
            "RESIZE: width=%d height=%d", ev.width, ev.height);
          break;
        case EventType::MOUSE:  // intercept mouse clicks and wheel scrolls
          term.printf(0, y++, Style::GREEN, Style::DEFAULT,
            "MOUSE:  button=%d x=%d y=%d", ev.button, ev.x, ev.y);
          break;
        case EventType::NONE:
          term.printf(0, y++, Style::MAGENTA, Style::DEFAULT,
            "NONE:   nothing happen for 20 seconds");
      }

      term.flush();
    }

    // mbox::term term2; <- will throw `std::logic_error`; `term` is a singleton
  }

  printf("When the `mbox::term` object is destroyed,\n");
  printf("the terminal's state is restored.\n");
}
