#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_auto_layout() {
  char script[] = "script";
  char command[100];
  sprintf(command, "bash %s", script);
  system(command);
}

int main() {
  Display *display;
  Window root;
  XEvent event;
  XWindowAttributes attr;

  display = XOpenDisplay(NULL);
  if (display == NULL) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  int screen = DefaultScreen(display);
  root = RootWindow(display, screen);

  XSelectInput(display, root, SubstructureNotifyMask);

  while (1) {
    XNextEvent(display, &event);
    if (event.type == CreateNotify) {
      XGetWindowAttributes(display, event.xcreatewindow.window, &attr);
      if (attr.override_redirect == False) {
        run_auto_layout();
      }
    }
  }

  XCloseDisplay(display);
  return 0;
}
