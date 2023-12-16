// heavily adapted from the following sources:
// https://github.com/microsoft/terminal/blob/ab68c8152ba971435330ee2ce858c8e0c44ef920/src/interactivity/win32/windowtheme.cpp
// https://github.com/notepad-plus-plus/notepad-plus-plus/pull/9587
// https://github.com/ysc3839/win32-darkmode

#pragma once

#pragma comment(lib, "dwmapi")

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace WinDarkMode {
  void setAppAllowDarkMode();
  void clearAppAllowDarkMode();
  void setWndAllowDarkMode(HWND hwnd, bool enable = true);
  void clearWndAllowDarkMode(HWND hwnd);
  void refreshWindowDarkMode(HWND hwnd);
  bool onWmSettingchange(HWND hwnd, LPARAM lParam);
  void onWmThemechanged(HWND hwnd);
  HBRUSH onWmCtlcolor(HWND hwnd, HDC hdc);
  void initDarkMode();
  bool setDarkThemeColors(HBRUSH& hbrBkgnd, HDC hdc);
  void destroyDarkMode();
  bool onWmErasebkgnd(HWND hwnd, HDC hdc);
}
