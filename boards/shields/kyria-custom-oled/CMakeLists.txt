zephyr_library()

zephyr_library_sources(${ZEPHYR_BASE}/misc/empty_file.c)
zephyr_library_include_directories(${ZEPHYR_LVGL_MODULE_DIR})
zephyr_library_include_directories(${ZEPHYR_BASE}/lib/gui/lvgl/)
zephyr_library_include_directories(${ZEPHYR_BASE}/drivers)
zephyr_library_include_directories(${CMAKE_SOURCE_DIR}/include)



if(NOT CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  zephyr_library_sources(custom_status_screen.c)
  zephyr_library_sources(widgets/kyrialogo.c)
endif()
