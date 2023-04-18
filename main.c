#include <X11/Xlib.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void run_auto_layout(char script_path[]) {

  char command[100];
  sprintf(command, "bash %s", script_path);
  system(command);
}

int errorHandler(Display *display, XErrorEvent *event) {
  if (event->error_code == BadWindow) {
    printf("X11 error: bad window (invalid window parameter)\n");
    return 0; // Return 0 to indicate that the error has been handled
  }
  return 1; // Return 1 to indicate that the error has not been handled
}

int main() {
  Display *display;
  Window root;
  XEvent event;
  XWindowAttributes attr;

  // Set up the X11 error handler
  XSetErrorHandler(errorHandler);

  char path[1000];
  char *script_path;
  if (readlink("/proc/self/exe", path, sizeof(path)) != -1) {
    script_path = dirname(path);
    strcat(script_path, "/script");
  }

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
        run_auto_layout(script_path);
      }
    }
  }

  XCloseDisplay(display);
  return 0;
}
