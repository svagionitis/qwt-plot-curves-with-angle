cmake_minimum_required(VERSION 3.5)

project(qwt-plot-curves-with-angle VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

option(ENABLE_QWT "Use the Qwt library" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable the compile_commands.json
# See https://cmake.org/cmake/help/latest/variable/CMAKE_EXPORT_COMPILE_COMMANDS.html
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Gui Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Gui Svg)

if (ENABLE_QWT)
    # FIXME: If the Qt5 is used, then use the qwt-q5
    # else use the qwt
    # FIXME: What happens in Windows
    find_library(LibQwt qwt REQUIRED
                 NAMES qwt qwt-qt5
                 PATHS /usr/lib /usr/local/qwt-6.2.0-dev/lib)

    find_path(LIBQWT_INCLUDE_DIRECTORIES qwt_plot.h
              PATHS /usr/include /usr/local/qwt-6.2.0-dev/include)

    # If the library is not installed in the OS,
    # then download and build it.
    if (NOT LibQwt)
        message(STATUS "LibQwt not found. Trying to download and build it.")

        if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
            set(QT_QMAKE_EXECUTABLE "${QT6_INSTALL_PREFIX}/${QT6_INSTALL_BINS}/qmake")
        else()
            # FIXME: Not tested
            set(QT_QMAKE_EXECUTABLE "${QT5_INSTALL_PREFIX}/${QT5_INSTALL_BINS}/qmake")
        endif()
        include(DownloadQwt)

        find_library(LibQwt qwt REQUIRED
                     NAMES qwt
                     PATHS ${CMAKE_BINARY_DIR}/qwt-build/lib)

        find_path(LIBQWT_INCLUDE_DIRECTORIES qwt_plot.h
              PATHS ${CMAKE_BINARY_DIR}/qwt-build/include)

    endif()

    message(STATUS "LibQwt found: ${LibQwt}")
    message(STATUS "LibQwt include directories: ${LIBQWT_INCLUDE_DIRECTORIES}")
endif ()

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        PlotCurvesWithAngle.cpp
        PlotCurvesWithAngle.h
        TrigonometricUtils.cpp
        TrigonometricUtils.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

set(TARGET_LINK_LIBRARIES_PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
                                  Qt${QT_VERSION_MAJOR}::Gui
                                  Qt${QT_VERSION_MAJOR}::Svg)

set(TARGET_INCLUDE_DIRECTORIES)

if (ENABLE_QWT)
    list(APPEND TARGET_LINK_LIBRARIES_PRIVATE
                    ${LibQwt})

    list(APPEND TARGET_INCLUDE_DIRECTORIES
            ${LIBQWT_INCLUDE_DIRECTORIES})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${TARGET_LINK_LIBRARIES_PRIVATE})

target_include_directories(${PROJECT_NAME}
                           PUBLIC
                            ${TARGET_INCLUDE_DIRECTORIES})

# See https://stackoverflow.com/a/55208743
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/images
                   $<TARGET_FILE_DIR:${PROJECT_NAME}>/images)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
