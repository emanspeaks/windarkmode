add_library(uxtheme-stub SHARED)
target_link_options(uxtheme-stub PRIVATE /IGNORE:4070)
target_link_options(uxtheme-stub INTERFACE /DELAYLOAD:uxtheme.dll)

add_subdirectory(include)
add_subdirectory(src)
