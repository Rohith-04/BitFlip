cmake_minimum_required(VERSION 3.5)

project(BitFlip VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    newproject.cpp
    connection.cpp
    canvas.cpp
    component.cpp
    andgate.cpp
    inputitem.cpp
    outputitem.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BitFlip
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        canvas.h
        component.h
        andgate.h
        inputitem.h
        newproject.h
        outputitem.h
        connection.h
        mainwindow.h
        assets.qrc
    )
    qt_finalize_executable(BitFlip)
else()
    if(ANDROID)
        add_library(BitFlip SHARED
            ${PROJECT_SOURCES}
            canvas.h
            component.h
            andgate.h
            inputitem.h
            newproject.h
            outputitem.h
        )
        # Set Android-specific properties here
    else()
        add_executable(BitFlip
            ${PROJECT_SOURCES}
            canvas.h
            component.h
            andgate.h
            inputitem.h
            newproject.h
            outputitem.h
        )
    endif()
endif()

target_link_libraries(BitFlip PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# macOS and Windows properties
if(${QT_VERSION_MAJOR} EQUAL 6)
    set_target_properties(BitFlip PROPERTIES
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BitFlip
    )
endif()

include(GNUInstallDirs)
install(TARGETS BitFlip
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
