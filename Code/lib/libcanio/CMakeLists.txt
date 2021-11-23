#considered bad practice
file(GLOB libcanio_src "src/*.cpp")
add_library(canio STATIC ${libcanio_src})
set_target_properties(canio PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libcanio.a"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include"
)
target_include_directories(canio PUBLIC include/canio)
