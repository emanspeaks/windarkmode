add_library(windarkmode STATIC)
target_link_libraries(windarkmode uxtheme-stub)

add_subdirectory(include)
add_subdirectory(src)
