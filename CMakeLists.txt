cmake_minimum_required(VERSION 3.16)

project(test_nodes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    gui/mainwindow.cpp
    logic/Node.cpp
    nodefactory.cpp
    gui/NodeItem.cpp
    gui/WorkflowView.cpp
    gui/propertieswidget.cpp
    gui/portitem.cpp
    gui/EdgeItem.cpp
    workflowexecutor.cpp
)

set(HEADERS
    gui/mainwindow.h
    logic/Node.h
    IVna.h
    nodefactory.h
    gui/NodeItem.h
    gui/WorkflowView.h
    gui/propertieswidget.h
    gui/portitem.h
    gui/EdgeItem.h
    workflowexecutor.h
)

add_executable(test_nodes
    ${SOURCES}
    ${HEADERS}
    CompositeNode.h CompositeNode.cpp
    logic/Port.h logic/Port.cpp
    NodeContext.h
    logic/Graph.h logic/Graph.cpp
    logic/Edge.h logic/Edge.cpp
    MethodNodeFactoryHybrid.h
    gui/GraphItem.h gui/GraphItem.cpp
)

target_link_libraries(test_nodes PRIVATE Qt5::Widgets)
