#include <stdbool.h>

//
// FFI
//
typedef unsigned char BYTE;
typedef short SHORT;
typedef unsigned long DWORD;
typedef unsigned long *ULONG_PTR;

extern void __stdcall Sleep(DWORD);
extern SHORT __stdcall GetAsyncKeyState(int);
extern void __stdcall keybd_event(BYTE, BYTE, DWORD, ULONG_PTR);

#define KEYEVENTF_EXTENDEDKEY 0x0001
#define KEYEVENTF_KEYUP 0x0002

//
// constants
//
static const char _LP = 'Q';
static const char _RP = 'W';

static const char left = 'F';
static const char right = 'H';
static const char up = 'T';
static const char bottom = 'G';
static const char upper_right = 'Y';
static const char upper_left = 'R';

// keydown, synthesize press key event
static void d(char key) {
  keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
}

// keyup, synthesize release key event
static void u(char key) {
  keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

// Skip 1 frame
static void f() {
  Sleep(17);
}

static void double_upper(void) {
  u(bottom); f();
  d(_LP); f(); u(_LP); f();
  d(_RP); f(); u(_RP); f();
}

static void rising_upper(bool is1P) {
  const char front = is1P ? right : left;
  const char back = is1P ? left : right;
  bool delay = false;

  if (0x8001 & GetAsyncKeyState(back) ) { u(back); delay = true; }
  if (0x8001 & GetAsyncKeyState(front) ) { u(front); delay = true; }
  if (delay) { f(); }

  d(front); f(); u(front); f();
  d(bottom); f(); d(front); d(_RP); f(); u(bottom); u(front); u(_RP);
  f();
}

int main(void) {
  while (true) {
    // TODO: Should not rely on LSB of GetAsyncKeyState
    //
    // Reference: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate
    SHORT upper_right_down = 0x1 & GetAsyncKeyState(upper_right);
    SHORT upper_left_down = 0x1 & GetAsyncKeyState(upper_left);
    SHORT bottom_currently_down = 0x8001 & GetAsyncKeyState(bottom);

    if (bottom_currently_down && (upper_left_down || upper_right_down)) {
      double_upper();
    } else if (upper_right_down) {
      rising_upper(true);
    } else if (upper_left_down) {
      rising_upper(false);
    }
    f();
  }
}
