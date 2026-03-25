#include "../include/mbox.hpp"

int main() {
  {
    mbox::term term;
    size_t y = 0;

    term.printf(0, y++, Style::NONE, Style::NONE,
      "привет from mbox!");                                          // full support of UTF-8
    term.printf(0, y++, Style::NONE, Style::NONE,
      "width=%d height=%d", term.get_width(), term.get_height());    // string formatting
    term.printf(0, y++, Style::BLUE | Style::BRIGHT, Style::NONE, // text attributes
      "PRESS <ESC> to quit");
    term.printf(0, y++, Style::BLUE | Style::BRIGHT, Style::NONE,
      "PRESS <TAB> to toggle mouse capture");
    term.flush();                                                    // flush the buffer manually
    y++;

    bool mouse_mode = true;
    term.capture_mouse(mouse_mode);                                  // opt-in for mouse input

    mbox::event ev;
    while (true) {
      if (y >= term.get_height()) {
        term.clear();
        y = 0;
      };

      ev = term.peek_event(30 * 1000);                               // poll for 30 seconds
      if (ev.key == Key::ESC) break;
      if (ev.key == Key::TAB) term.capture_mouse(mouse_mode = !mouse_mode);

      switch (ev.type) {
        case EventType::KEY:                                         // process every sent key individually
          char utf8[7];
          mbox::utf32_to_utf8(utf8, ev.ch);
          term.printf(0, y++, Style::YELLOW, Style::NONE,
            "KEY:    mod=%d key=%d char=%s", ev.mod, ev.key, utf8);
          break;
        case EventType::RESIZE:                                      // react to resizing
          term.printf(0, y++, Style::CYAN | Style::BRIGHT, Style::NONE,
            "RESIZE: width=%d height=%d", ev.width, ev.height);
          break;
        case EventType::MOUSE:                                       // capture mouse clicking and scrolling
          term.printf(0, y++, Style::GREEN, Style::NONE,
            "MOUSE:  button=%d x=%d y=%d", ev.button, ev.x, ev.y);
          break;
        case EventType::NONE:
          term.printf(0, y++, Style::MAGENTA, Style::NONE,
            "NONE:   nothing happen for 30 seconds");
      }

      term.flush();
    }

    // mbox::term term2; <- will throw `std::logic_error`; `term` is a singleton
  }

  printf("When the `mbox::term` object is destroyed,\n");
  printf("the terminal's state is restored.\n");
}
