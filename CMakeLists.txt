cmake_minimum_required(VERSION 3.21)
project(project_name LANGUAGES CXX)

#-------------------------- COMPILATION FLAGS ----------------------------------

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++20 -save-temps")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static ") #
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ") # -mwindows
endif()

#SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
#SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
#SET(CMAKE_INSTALL_RPATH "$\{ORIGIN\}/lib")

#------------------------ BINARY FILES LOCATION --------------------------------

set(FullOutputDir "${CMAKE_SOURCE_DIR}/bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

#--------------------------- OBJECT DECLARATION --------------------------------

include_directories(include src test)

set(Executables
   # "main"
    "geralt_eats/geralt_eats"
    "lemmings/lemmings"
)

# Header Only
set(HeaderOnlyProjects
    
)

set(SubProjects

)

set(Modules
    # Order matters! If A depends on B, B must be higher than A (not really)
    "geometry/ray"
    "geometry/transform"

    "math/math"

    "lib/spectrum"
    "lib/texture"

    "engine/engine"
    "engine/entity"
    "engine/render_2D"
    "engine/physics"
    "engine/game"
    "engine/rigid_body"
    "engine/fixed_text"
)

#--------------------------- EXTERNAL LIBRARIES --------------------------------

set(Libraries
    SDL2
    SDL2_image
    SDL2_mixer
)

INCLUDE(FindPkgConfig)

foreach(Lib IN LISTS Libraries)
    find_package(${Lib} REQUIRED)
endforeach()

set(LibDirectories
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_image_INCLUDE_DIRS}
    ${SDL2_mixer_INCLUDE_DIRS}
)

set(Targets
    SDL2::SDL2main SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
)

#---------------------------- OBJECT COMPILATION -------------------------------

#Header only Subprojects
foreach(Header IN LISTS HeaderOnlyProjects)
    include_directories("lib/${Header}/include")
endforeach()

#Compiled Subprojects
foreach(Project IN LISTS SubProjects)
    include_directories("lib/${Project}/include")
    if(NOT TARGET ${Project})
        add_subdirectory("lib/${Project}")
    endif()
endforeach()

#Project modules
foreach(Mod IN LISTS Modules)
    set(ModList "${ModList};src/${Mod}.cpp")
endforeach()

add_library(ProjectModules STATIC ${ModList})
foreach(Dir IN LISTS LibDirectories)
    target_include_directories(ProjectModules PUBLIC ${LibDirectories})
endforeach()

#----------------------- EXECUTABLE FILES COMPILATION --------------------------

foreach(Executable IN LISTS Executables)

    string(FIND ${Executable} "/" BarPos REVERSE)
    if (${BarPos} EQUAL -1)
        set(ExecutablePath "src/${Executable}.cpp")
        set(ExecutableName "${Executable}")
    else()
        MATH(EXPR BarPos "${BarPos} + 1")
        string(SUBSTRING ${Executable} ${BarPos} -1 ExecutableName)
        set(ExecutablePath "src/${Executable}.cpp")
    endif()

    add_executable(${ExecutableName} "${ExecutablePath}")

    target_link_libraries(${ExecutableName} PUBLIC ProjectModules) 

    foreach(Project IN LISTS SubProjects)
        target_link_libraries(${ExecutableName} PUBLIC  ${Project})
    endforeach()

    foreach(Target IN LISTS Targets)
        target_link_libraries(${ExecutableName} PUBLIC  ${Target})
    endforeach()

endforeach()
#---
