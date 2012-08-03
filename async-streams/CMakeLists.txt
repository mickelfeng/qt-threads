set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

find_package(Qt4 REQUIRED)

set(TARGET "async-streams")

set(SRC
  main.cpp
  Application.cpp
)

set(HDR
  Application.h
)

add_definitions("-std=gnu++0x")

qt4_wrap_cpp(HDR_MOC ${HDR})

include(${QT_USE_FILE})

add_definitions(${QT_DEFINITIONS})

add_executable(${TARGET} ${SRC} ${HDR_MOC})

target_link_libraries(${TARGET} ${QT_LIBRARIES})

