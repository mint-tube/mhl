#include "../include/mbox.hpp"

using namespace mbox;
using namespace mbox::style;

int main() {
  {
    term term;
    size_t y = 0;

    term.print(0, y++, 0, 0, "привет from mbox!");                  // full support of UTF-8
    term.printf(0, y++, DIM, 0, "width=%d height=%d", term.get_width(), term.get_height());
    term.print(0, y++, BLUE | BOLD, 0, "PRESS <ESC> to quit");      // cool styling attributes
    term.print(0, y++, BLUE | BOLD, 0, "PRESS <TAB> to toggle mouse capture");
    term.flush();                                                   // flush the buffer manually
    y++;

    bool mouse_mode = true;
    term.set_mouse_mode(MouseMode::DRAG);                           // opt-in for mouse input

    event ev;
    while (true) {
      if (y >= term.get_height()) {
        term.clear();
        y = 0;
      }

      ev = term.peek_event(30 * 1000);                               // poll for 30 seconds
      if (ev.key == Key::ESC || ev.key == Key::CTRL_C) break;        // Ctrl+C is NOT special.
      if (ev.key == Key::TAB) {
        if (mouse_mode) term.set_mouse_mode(MouseMode::OFF);
        else            term.set_mouse_mode(MouseMode::DRAG);
        mouse_mode = !mouse_mode;

        term.set_cell(0, y, 0, 0, U'🔶');                            // write to arbitrary cell
        uint32_t color = supports_rgb() ? rgb(248, 157, 20) : RED; // rgb!!!
        term.printf(3, y++, color | BOLD, 0, "Mouse input is %s", mouse_mode ? "on" : "off");
      }

      switch (ev.type) {
        case EventType::KEY:                                         // process every keystroke
          char utf8[7];
          mbox::utf32_to_utf8(utf8, ev.ch);
          term.printf(0, y++, YELLOW, 0, "KEY:    mod=%d key=%d char=%s", ev.mod, ev.key, utf8);
          break;
        case EventType::RESIZE:                                      // react to resizing
          term.printf(0, y++, CYAN | BRIGHT, 0, "RESIZE: width=%d height=%d", ev.width, ev.height);
          break;
        case EventType::MOUSE:                                       // capture mouse interactions
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
