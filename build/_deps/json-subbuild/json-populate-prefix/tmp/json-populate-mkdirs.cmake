# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Program Files/Geant4-11.3/share/Geant4/projects/Geant4GlassDose/build/_deps/json-src"
  "C:/Program Files/Geant4-11.3/share/Geant4/projects/Geant4GlassDose/build/_deps/json-build"
  "C:/Program Files/Geant4-11.3/share/Geant4/projects/Geant4GlassDose/build/_deps/json-subbuild/json-populate-prefix"
  "C:/Program Files/Geant4-11.3/share/Geant4/projects/Geant4GlassDose/build/_deps/json-subbuild/json-populate-prefix/tmp"
  "C:/Program Files/Geant4-11.3/share/Geant4/projects/Geant4GlassDose/build/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp"
  "C:/Program Files/Geant4-11.3/share/Geant4/projects/Geant4GlassDose/build/_deps/json-subbuild/json-populate-prefix/src"
  "C:/Program Files/Geant4-11.3/share/Geant4/projects/Geant4GlassDose/build/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Program Files/Geant4-11.3/share/Geant4/projects/Geant4GlassDose/build/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Program Files/Geant4-11.3/share/Geant4/projects/Geant4GlassDose/build/_deps/json-subbuild/json-populate-prefix/src/json-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
