cmake_minimum_required(VERSION 3.16)
project(ODEVisualizator VERSION 0.1.0 LANGUAGES CXX)

# Включаем автоматический запуск moc, uic и rcc
 set(CMAKE_AUTOMOC ON)
 set(CMAKE_AUTOUIC ON)
 set(CMAKE_AUTORCC ON)

# Включаем C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Укажите здесь путь к установке Qt6 (где лежат Qt6Config.cmake)
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/msvc2022_64" CACHE STRING "Qt6 install path")

# Где искать модули Qt6
find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED)
find_package(OpenGL REQUIRED) 

# Собираем исполняемый файл
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/ui/MainWindow.cpp
    src/ui/WorkspaceDockWidget.cpp

    src/workspaces/Viewport3DWorkspace.cpp
    src/workspaces/LyapunovWorkspace.cpp

    src/camera/Camera.cpp

    src/renderers/AxisRenderer.cpp 
    src/renderers/GridRenderer.cpp
    
    include/ui/WorkspaceDockWidget.h
    include/ui/MainWindow.h

    include/workspaces/Viewport3DWorkspace.h
    include/workspaces/LyapunovWorkspace.h 
    
    include/camera/Camera.h

    include/renderers/AxisRenderer.h 
    include/renderers/GridRenderer.h



)

# Пусть компилятор ищет наши .h в папке include/
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Линкуем с Qt6 Widgets и OpenGL
target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets OpenGL::GL
)

# Устанавливаем папку для сборки ui/ресурсов
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
