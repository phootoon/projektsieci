cmake_minimum_required(VERSION 3.5)

project(projektsieci2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(projektsieci2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        client/Client.h client/Client.cpp
        client/Death_screen.h client/Death_screen.cpp
        client/Game_window.h client/Game_window.cpp
        client/Lobby_window.h client/Lobby_window.cpp
        client/main.cpp
        client/Network_client.h client/Network_client.cpp
        server/Game_state.h server/Game_state.cpp
        server/main.cpp
        server/Network_server.h server/Network_server.cpp
        server/Player.h server/Player.cpp
        server/Server.h server/Server.cpp
        client/Death_screen.ui



        client/lobbywindow.ui
        client/gamewindow.ui
        client/background.qrc
        client/connect_window.h client/connect_window.cpp
        client/connectwindow.ui
        server/Server_window.h server/Server_window.cpp
        server/serverwindow.ui
        client/Game_state_client.h
        client/Game_state_client.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET projektsieci2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(projektsieci2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(projektsieci2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(projektsieci2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(projektsieci2 PRIVATE Qt6::Network)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.projektsieci2)
endif()
set_target_properties(projektsieci2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS projektsieci2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(projektsieci2)
endif()
