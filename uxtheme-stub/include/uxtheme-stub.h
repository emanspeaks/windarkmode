#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Uxtheme.h>
#pragma comment(lib, "delayimp")
#pragma comment(lib, "uxtheme")

enum IMMERSIVE_HC_CACHE_MODE
{
	IHCM_USE_CACHED_VALUE,
	IHCM_REFRESH
};

// 1903 18362
enum class PreferredAppMode
{
	Default,
	AllowDark,
	ForceDark,
	ForceLight,
	Max
};

extern "C" {
	// 1809 17763
	THEMEAPI_(bool) ShouldAppsUseDarkMode(); // ordinal 132
	THEMEAPI_(bool) AllowDarkModeForWindow(HWND hWnd, bool allow); // ordinal 133
	// THEMEAPI_(bool) AllowDarkModeForApp(bool allow); // ordinal 135, in 1809
	THEMEAPI_(VOID) FlushMenuThemes(); // ordinal 136
	THEMEAPI_(VOID) RefreshImmersiveColorPolicyState(); // ordinal 104
	THEMEAPI_(bool) IsDarkModeAllowedForWindow(HWND hWnd); // ordinal 137
	THEMEAPI_(bool) GetIsImmersiveColorUsingHighContrast(IMMERSIVE_HC_CACHE_MODE mode); // ordinal 106
	THEMEAPI_(HTHEME) OpenNcThemeData(HWND hWnd, LPCWSTR pszClassList); // ordinal 49

	// 1903 18362
	THEMEAPI_(bool) ShouldSystemUseDarkMode(); // ordinal 138
	THEMEAPI_(PreferredAppMode) SetPreferredAppMode(PreferredAppMode appMode); // ordinal 135, in 1903
	THEMEAPI_(bool) IsDarkModeAllowedForApp(); // ordinal 139
}
