#include <stdbool.h>
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

const char _LP = 'Q';
const char _RP = 'W';

const char left = 'F';
const char right = 'H';
const char up = 'T';
const char bottom = 'G';

const char upper_right = 'Y';
const char upper_left = 'R';

const DWORD period = 17;

enum Direction { LEFT, RIGHT };

void keydown(char key) {
  keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
}

void keyup(char key) {
  keybd_event(key, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void double_upper(void) {
  keyup(bottom); Sleep(period);
  keydown(_LP); Sleep(period); keyup(_LP); Sleep(period);
  keydown(_RP); Sleep(period); keyup(_RP); Sleep(period);
}

void rising_upper(enum Direction dir) {
  const char front = dir == LEFT ? left : right;
  const char back = dir == RIGHT ? left : right;
  bool delay = false;

  if (0x8001 & GetAsyncKeyState(back) ) keyup(back), delay = true;
  if (0x8001 & GetAsyncKeyState(front) ) keyup(front), delay = true;
  if (delay) Sleep(period);

  keydown(front); Sleep(period); keyup(front); Sleep(period);
  keydown(bottom); Sleep(period); keydown(front); keydown(_RP); Sleep(period); keyup(bottom); keyup(front); keyup(_RP);
  Sleep(period);
}

int main(void) {
  while (1) {
    // 반환값 설명
    // 0 : 키가 눌려진적이 없음
    // 1 : 키가 눌려졌었으나, 놓쳤음
    // 0xffff8001 : 키가 새롭게 눌려졌음
    // 0xffff8000 : 키가 계속 눌려져있는 상태임
    DWORD upper_right_down = 0x1 & GetAsyncKeyState(upper_right);
    DWORD upper_left_down = 0x1 & GetAsyncKeyState(upper_left);
    DWORD bottom_currently_down = 0x8001 & GetAsyncKeyState(bottom);

    if (bottom_currently_down) {
      if (upper_left_down || upper_right_down) { double_upper(); }
    } else {
      if (upper_right_down) { rising_upper(RIGHT); }
      else if (upper_left_down) { rising_upper(LEFT); }
    }
    Sleep(period);
  }
}
