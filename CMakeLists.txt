cmake_minimum_required(VERSION 3.16)

project(ODEVisualizator VERSION 0.1.0 LANGUAGES CXX)

# -------------------- Qt meta‑build options --------------------
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------------------
# Tell CMake where to look for Qt 6 packages (Qt6Config.cmake)
# --------------------------------------------------------------
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/msvc2022_64" CACHE STRING "Qt6 install path")

# Core Qt modules needed by the application
find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)
find_package(OpenGL REQUIRED)

# --------------------------------------------------------------
# Fetch & build Qt‑Advanced‑Docking‑System (shared library)
# --------------------------------------------------------------
include(FetchContent)

set(ADS_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ADS_BUILD_TESTS    OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    qtads
    GIT_REPOSITORY https://github.com/githubuser0xFFFF/Qt-Advanced-Docking-System.git
    GIT_TAG        4.4.0
)
FetchContent_MakeAvailable(qtads)     # creates target qtadvanceddocking-qt6

set(QTADS_LIB qtadvanceddocking-qt6)

# --------------------------------------------------------------
# Sources / headers
# --------------------------------------------------------------
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/ui/MainWindow.cpp
    src/ui/WorkspaceDockWidget.cpp
    src/ui/WorkspaceContainer.cpp

    src/workspaces/Viewport3DWorkspace.cpp
    src/workspaces/LyapunovWorkspace.cpp

    src/camera/Camera.cpp

    src/renderers/AxisRenderer.cpp 
    src/renderers/GridRenderer.cpp

    include/ui/WorkspaceDockWidget.h
    include/ui/MainWindow.h
    include/ui/WorkspaceContainer.h

    include/workspaces/Viewport3DWorkspace.h
    include/workspaces/LyapunovWorkspace.h 

    include/camera/Camera.h

    include/renderers/AxisRenderer.h 
    include/renderers/GridRenderer.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# --------------------------------------------------------------
# Link libraries
# --------------------------------------------------------------

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        Qt6::Widgets 
        Qt6::OpenGL 
        Qt6::OpenGLWidgets 
        OpenGL::GL 
        ${QTADS_LIB}
)

# --------------------------------------------------------------
# Ensure the ADS DLL appears next to the executable              
# (windeployqt знает только о Qt‑dll, но не о сторонних).
# --------------------------------------------------------------
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${QTADS_LIB}>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMENT "Copy qtadvanceddocking DLL next to the exe")

# --------------------------------------------------------------
# Finish linking of the Qt executable (RCC, QML, etc.)
# --------------------------------------------------------------
qt_finalize_executable(${PROJECT_NAME})

# --------------------------------------------------------------
# Run windeployqt so that ALL necessary Qt runtimes land          
# in the same folder.
# --------------------------------------------------------------
find_program(WINDEPLOYQT_EXECUTABLE
             NAMES windeployqt windeployqt6
             HINTS "${Qt6_DIR}/../../../bin" )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${WINDEPLOYQT_EXECUTABLE}"
            --no-opengl-sw            # не трогаем ANGLE / software OpenGL
            --debug                  # вытаскиваем debug‑версии DLL
            --compiler-runtime       # MSVC runtime DLL‑ы
            --verbose 0
            "$<TARGET_FILE:${PROJECT_NAME}>"
    COMMENT "Deploying Qt runtime with windeployqt")

# --------------------------------------------------------------
# Where the final exe + dlls live (bin/)
# --------------------------------------------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
