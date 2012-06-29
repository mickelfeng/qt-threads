set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

find_package(Qt4 REQUIRED)

set(SRC
  main.cpp
  Thread.cpp
  MainWindow.cpp
)

set(HDR
  Thread.h
  MainWindow.h
)

qt4_wrap_cpp(HDR_MOC ${HDR})

include(${QT_USE_FILE})

add_definitions(${QT_DEFINITIONS})

add_executable(qt-threads ${SRC} ${HDR_MOC})

target_link_libraries(qt-threads ${QT_LIBRARIES})

