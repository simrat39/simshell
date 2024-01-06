cmake_minimum_required(VERSION 3.28)
project(simshell)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(simshell src/main.cpp
        src/OSD.cpp
        src/SimshellApp.cpp
        src/RootBar.cpp
        src/RightComponents.cpp
        src/CenterComponents.cpp
        src/LeftComponents.cpp

        src/components/BrightnessSlider.cpp
        src/components/datetime/DateTimeButton.cpp
        src/components/workspaces/HyprlandWorkspaces.cpp
        src/components/workspaces/HyprlandWorkspaceButton.cpp
        src/components/active_window/ActiveWindowLabel.cpp
        src/components/mpris/MprisButton.cpp
        src/components/mpris/MprisPopover.cpp
        src/components/mpris/MprisPage.cpp
        src/components/power/PowerMenuButton.cpp
        src/components/power/PowerPopover.cpp

        src/services/backlight/BacklightService.cpp
        src/services/backlight/BacklightDevice.cpp
        src/services/hyprland/HyprlandService.cpp
        src/services/mpris/MprisService.cpp
        src/services/mpris/MprisPlayer.cpp
        src/services/battery/BatteryService.cpp
        src/services/battery/BatteryDevice.cpp
)

target_include_directories(simshell PUBLIC include)

# GTKmm
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
link_libraries(${GTKMM_LIBRARIES})

target_link_libraries(simshell ${GTKMM_LIBRARIES})

# gtk-layer-shell
pkg_check_modules(LAYERSHELL REQUIRED gtk4-layer-shell-0)

include_directories(${LAYERSHELL_INCLUDE_DIRS})
link_directories(${LAYERSHELL_LIBRARY_DIRS})
link_libraries(${LAYERSHELL_LIBRARIES})

target_link_libraries(simshell ${LAYERSHELL_LIBRARIES})

# gudev
pkg_check_modules(GUDEV REQUIRED gudev-1.0)

include_directories(${GUDEV_INCLUDE_DIRS})
link_directories(${GUDEV_LIBRARY_DIRS})
link_libraries(${GUDEV_LIBRARIES})

target_link_libraries(simshell ${GUDEV_LIBRARIES})

# playerctl
pkg_check_modules(PLAYERCTL REQUIRED playerctl)

include_directories(${PLAYERCTL_INCLUDE_DIRS})
link_directories(${PLAYERCTL_LIBRARY_DIRS})
link_libraries(${PLAYERCTL_LIBRARIES})

target_link_libraries(simshell ${PLAYERCTL_LIBRARIES})

# libsoup
pkg_check_modules(LIBSOUP REQUIRED libsoup-3.0)

include_directories(${LIBSOUP_INCLUDE_DIRS})
link_directories(${LIBSOUP_LIBRARY_DIRS})
link_libraries(${LIBSOUP_LIBRARIES})

target_link_libraries(simshell ${LIBSOUP_LIBRARIES})

# json
pkg_check_modules(JSON REQUIRED nlohmann_json)

include_directories(${JSON_INCLUDE_DIRS})
link_directories(${JSON_LIBRARY_DIRS})
link_libraries(${JSON_LIBRARIES})

target_link_libraries(simshell ${JSON_LIBRARIES})

# upower-glib
pkg_check_modules(UPOWER REQUIRED upower-glib)

include_directories(${UPOWER_INCLUDE_DIRS})
link_directories(${UPOWER_LIBRARY_DIRS})
link_libraries(${UPOWER_LIBRARIES})

target_link_libraries(simshell ${UPOWER_LIBRARIES})
