set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

set(TARGET "concurrent")

find_package(Qt4 REQUIRED)

set(SRC
  main.cpp
  Application.cpp
  Processor.cpp
  PrintResult.cpp
)

set(HDR
  Application.h
  Processor.h
  PrintResult.h
)

qt4_wrap_cpp(HDR_MOC ${HDR})

include(${QT_USE_FILE})

add_definitions(${QT_DEFINITIONS})
add_definitions("-std=gnu++0x")

add_executable(${TARGET} ${SRC} ${HDR_MOC})

target_link_libraries(${TARGET} ${QT_LIBRARIES})

