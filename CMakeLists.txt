cmake_minimum_required(VERSION 3.16...3.27)
project(GlassDose)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Исполняемый файл
add_executable(GlassDose main.cc ${sources} ${headers})
target_link_libraries(GlassDose ${Geant4_LIBRARIES})

# Выходная директория
set_target_properties(GlassDose PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/$<CONFIG>
)

# Копирование файлов vis.mac и config.json к исполняемому файлу
set(GlassDose_SCRIPTS vis.mac config.json)

foreach(_script ${GlassDose_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
  )

  add_custom_command(TARGET GlassDose POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${PROJECT_SOURCE_DIR}/${_script}"
      "$<TARGET_FILE_DIR:GlassDose>/${_script}")
endforeach()
