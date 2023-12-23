cmake_minimum_required(VERSION 3.28)
project(simshell)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(simshell main.cpp
        RootBar.cpp
        RootBar.hpp
        SimshellApp.cpp
        SimshellApp.hpp
        RightComponents.cpp
        RightComponents.hpp
        components/BrightnessSlider.cpp
        components/BrightnessSlider.hpp
        services/backlight/BacklightService.cpp
        services/backlight/BacklightService.hpp
        services/backlight/BacklightDevice.cpp
        services/backlight/BacklightDevice.hpp
        CenterComponents.hpp
        CenterComponents.cpp
        components/datetime/DateTimeButton.cpp
        components/datetime/DateTimeButton.hpp
        services/hyprland/HyprlandService.cpp
        services/hyprland/HyprlandService.hpp
        components/workspaces/HyprlandWorkspaces.cpp
        components/workspaces/HyprlandWorkspaces.hpp
        LeftComponents.hpp
        LeftComponents.cpp
        services/mpris/MprisService.cpp
        services/mpris/MprisService.hpp
        services/mpris/MprisPlayer.cpp
        services/mpris/MprisPlayer.hpp
        components/mpris/MprisButton.cpp
        components/mpris/MprisButton.hpp
        components/mpris/MprisPopover.cpp
        components/mpris/MprisPopover.hpp
        components/mpris/MprisPage.cpp
        components/mpris/MprisPage.hpp
        components/active_window/ActiveWindowLabel.cpp
        components/active_window/ActiveWindowLabel.hpp
)

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
