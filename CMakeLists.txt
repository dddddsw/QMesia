cmake_minimum_required(VERSION 3.31)
project(Mesia)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

list(APPEND CMAKE_PREFIX_PATH
        "D:/Qt/6.10.1/msvc2022_64"
        "E:/dsw/code/Meleoa/install"
)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

find_package(Meleoa REQUIRED)

add_executable(Mesia
        main.cpp
        src/app/Application.cpp
        src/util/VectorPathUtil.cpp
        src/model/ObjectTreeItem.cpp
        src/model/ObjectTreeModel.cpp
        src/model/QCanvasModel.cpp
        src/TreeModel/ObjectTreeItem.cpp
        src/TreeModel/ObjectTreeModel.cpp
        src/TreeModel/ShapeBaseItem.cpp
        src/TreeModel/ShapeLayerItem.cpp
        src/TreeModel/ShapeGroupItem.cpp
        src/TreeModel/RectangleItem.cpp
        src/views/MainWindow.cpp
        src/views/canvas/GraphicsView.cpp
        src/views/canvas/GraphicsScene.cpp
        src/views/canvas/GraphicsItem.cpp
        src/views/canvas/GraphicsItemsBoundingBox.cpp
        src/views/canvas/InteractionModeManager.cpp
        src/views/canvas/actions/UndoAction.cpp
        src/views/canvas/actions/MoveItemsAction.cpp
        src/views/canvas/tools/GraphicsToolManager.cpp
        src/views/canvas/tools/GraphicsTool.cpp
        src/views/canvas/tools/GraphicsSelectTool.cpp
        src/views/canvas/tools/GraphicsMoveTool.cpp
        src/views/canvas/tools/GraphicsResizeTool.cpp
        src/views/canvas/tools/GraphicsRotateTool.cpp
)

target_compile_definitions(Mesia PRIVATE Meleoa_STATIC)

target_link_libraries(Mesia
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Meleoa::Meleoa
)

target_include_directories(Mesia PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_custom_command(TARGET Mesia
        POST_BUILD
        COMMAND Qt6::windeployqt "${CMAKE_BINARY_DIR}"
        COMMENT "Run Qt6::windeployqt")