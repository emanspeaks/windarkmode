#include "windarkmode.h"
#include <dwmapi.h>
#include <Uxtheme.h>
#include "uxtheme-stub.h"

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

HBRUSH hbrBkgnd = nullptr;

bool isHighContrast() {
  HIGHCONTRAST hc = {sizeof(hc)};
  if (SystemParametersInfo(SPI_GETHIGHCONTRAST, sizeof(hc), &hc, 0)) return HCF_HIGHCONTRASTON & hc.dwFlags;
  return false;
}

bool isSystemDarkModeAvailable() {
  return ShouldAppsUseDarkMode() && !isHighContrast();
}

namespace WinDarkMode {
  void setAppAllowDarkMode() {
    SetPreferredAppMode(PreferredAppMode::AllowDark);
  }

  void clearAppAllowDarkMode() {
    SetPreferredAppMode(PreferredAppMode::Default);
  }

  void setWndAllowDarkMode(HWND hwnd, bool enable) {
    AllowDarkModeForWindow(hwnd, enable);
  }

  void clearWndAllowDarkMode(HWND hwnd) {
    AllowDarkModeForWindow(hwnd, false);
  }

  void refreshWindowDarkMode(HWND hwnd) {
    // I have to be a big B BOOL or DwnSetWindowAttribute will be upset (E_INVALIDARG) when I am passed in.
    const BOOL darkModeAvailable = !!isSystemDarkModeAvailable() && !!IsDarkModeAllowedForWindow(hwnd);;
    SetWindowTheme(hwnd, (darkModeAvailable)? L"DarkMode_Explorer" : L"", nullptr);
    DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkModeAvailable, sizeof(darkModeAvailable));

    EnumChildWindows(hwnd, [](HWND hWnd, LPARAM lParam) -> BOOL {
      setWndAllowDarkMode(hWnd, LOWORD(lParam));
      return TRUE;
    }, MAKELPARAM(darkModeAvailable, 0));
  }

  bool onWmSettingchange(HWND hwnd, LPARAM lParam) {
    bool isDarkMsg = false;
    if (lParam && CompareStringOrdinal(reinterpret_cast<LPCWCH>(lParam), -1, L"ImmersiveColorSet", -1, TRUE) == CSTR_EQUAL)
    {
      RefreshImmersiveColorPolicyState();
      isDarkMsg = true;
    }
    GetIsImmersiveColorUsingHighContrast(IHCM_REFRESH);
    if (isDarkMsg) refreshWindowDarkMode(hwnd);
    return isDarkMsg;
  }

  void onWmThemechanged(HWND hwnd) {
    EnumChildWindows(hwnd, [](HWND hWnd, LPARAM lParam) -> BOOL {
      SendMessage(hWnd, WM_THEMECHANGED, 0, 0);
      return TRUE;
    }, 0);
    InvalidateRect(hwnd, nullptr, TRUE);
  }

  void initDarkMode() {
    setAppAllowDarkMode();
    RefreshImmersiveColorPolicyState();
  }

  HBRUSH setDarkThemeColors(HDC hdc) {
    constexpr COLORREF darkBkColor = 0x383838;
    constexpr COLORREF darkTextColor = 0xFFFFFF;

    if (!hbrBkgnd)
      hbrBkgnd = CreateSolidBrush(darkBkColor);
    SetTextColor(hdc, darkTextColor);
    SetBkColor(hdc, darkBkColor);
    return hbrBkgnd;
  }

  bool onWmErasebkgnd(HWND hwnd, HDC hdc) {
    bool isdark = isSystemDarkModeAvailable() && IsDarkModeAllowedForWindow(hwnd);
    if (isdark)
    {
      RECT rc = {0};
      GetClientRect(hwnd, &rc);
      FillRect(hdc, &rc, setDarkThemeColors(hdc));
    }
    return isdark;
  }

  HBRUSH onWmCtlcolor(HWND hwnd, HDC hdc) {
    if (isSystemDarkModeAvailable() && IsDarkModeAllowedForWindow(hwnd))
      return setDarkThemeColors(hdc);
    return FALSE;
  }

  void destroyDarkMode() {
    if (hbrBkgnd) DeleteObject(hbrBkgnd);
  }
}
