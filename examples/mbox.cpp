#include "../include/mbox.hpp"

using namespace mbox;
using namespace mbox::Style;

int main() {
  {
    term term;
    size_t y = 0;

    term.printf(0, y++, 0, 0, "привет from mbox!");                   // full support of UTF-8
    term.printf(0, y++, DIM, 0, "width=%d height=%d", term.get_width(), term.get_height());
    term.printf(0, y++, BLUE | BOLD, 0, "PRESS <ESC> to quit");       // text attributes from mbox::Style
    term.printf(0, y++, BLUE | BOLD, 0, "PRESS <TAB> to toggle mouse capture");
    term.flush();                                                     // flush the buffer manually
    y++;

    bool mouse_mode = true;
    term.capture_mouse(mouse_mode);                                   // opt-in for mouse input

    event ev;
    while (true) {
      if (y >= term.get_height()) {
        term.clear();
        y = 0;
      }

      ev = term.peek_event(30 * 1000);                                // poll for 30 seconds
      if (ev.key == Key::ESC) break;
      if (ev.key == Key::TAB) {
        term.capture_mouse(mouse_mode = !mouse_mode);

        term.set_cell(0, y, 0, 0, U'🔶');                             // write to any cell
        uint16_t color = supports_rgb() ? rgb_color(5, 2, 1) : RED;   // 256 colors!!!
        term.printf(3, y++, color | BOLD, 0, "Toggled mouse input");
      }

      switch (ev.type) {
        case EventType::KEY:                                          // process every keystroke
          char utf8[7];
          mbox::utf32_to_utf8(utf8, ev.ch);
          term.printf(0, y++, YELLOW, 0, "KEY:    mod=%d key=%d char=%s", ev.mod, ev.key, utf8);
          break;
        case EventType::RESIZE:                                       // react to resizing
          term.printf(0, y++, CYAN | BRIGHT, 0, "RESIZE: width=%d height=%d", ev.width, ev.height);
          break;
        case EventType::MOUSE:                                        // capture mouse interactions
          term.printf(0, y++, GREEN, 0, "MOUSE:  button=%d x=%d y=%d", ev.button, ev.x, ev.y);
          break;
        case EventType::NONE:
          term.printf(0, y++, MAGENTA, 0, "NONE:   nothing happen for 30 seconds");
      }

      term.flush();
    }

    // mbox::term term2; <- will throw `std::logic_error`; `term` is a singleton
  }

  printf("When the `mbox::term` object is destroyed,\n");
  printf("the terminal's state is restored.\n");
}
