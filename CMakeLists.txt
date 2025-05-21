cmake_minimum_required(VERSION 3.16...3.27)
project(GlassDose)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(GlassDose main.cc ${sources} ${headers})
target_link_libraries(GlassDose ${Geant4_LIBRARIES})

set(GlassDose_SCRIPTS
  vis.mac
  run.mac
)

foreach(_script ${GlassDose_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
  )
endforeach()
