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
