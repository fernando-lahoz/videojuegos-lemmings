cmake_minimum_required(VERSION 3.21)
project(project_name LANGUAGES CXX)

#-------------------------- COMPILATION FLAGS ----------------------------------

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++20 -save-temps") # -static-libstdc++ -static-libgcc -static
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Ofast -DNDEBUG")

if (WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mwindows")
endif()

#------------------------ BINARY FILES LOCATION --------------------------------

set(FullOutputDir "${CMAKE_SOURCE_DIR}/bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

#--------------------------- OBJECT DECLARATION --------------------------------

include_directories(include src test)

set(Executables
    "main"
)

# Header Only
set(HeaderOnlyProjects
    
)

set(SubProjects

)

set(Modules
    # Order matters! If A depends on B, B must be higher than A
    "geometry/ray"
    "math/math"
)

#--------------------------- EXTERNAL LIBRARIES --------------------------------

set(Libraries
    SDL2
    SDL2_image
    SDL2_mixer
)

set(Targets
    SDL2::SDL2main SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
)

foreach(Lib IN LISTS Libraries)
    find_package(${Lib} REQUIRED GLOBAL)
endforeach()

set(LibDirectories
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_image_INCLUDE_DIRS}
    ${SDL2_mixer_INCLUDE_DIRS}
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
    string(FIND ${Mod} "/" BarPos REVERSE)
    if (${BarPos} EQUAL -1)
        set(ModName ${Mod})
        set(ModNames "${ModNames};${ModName}")
    else()
        MATH(EXPR BarPos "${BarPos} + 1")
        string(SUBSTRING ${Mod} ${BarPos} -1 ModName)
        set(ModNames "${ModNames};${ModName}")
    endif()
    add_library(${ModName} STATIC "src/${Mod}.cpp")

    foreach(Dir IN LISTS LibDirectories)
        target_include_directories(${ModName} PUBLIC ${Dir})
    endforeach()
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
        set(ExecutablePath "${Executable}.cpp")
    endif()

    add_executable(${ExecutableName} "${ExecutablePath}")

    foreach(Target IN LISTS Targets)
        target_link_libraries(${ExecutableName} LINK_PUBLIC ${Target})
    endforeach()

    foreach(Mod IN LISTS ModNames)
        target_link_libraries(${ExecutableName} LINK_PUBLIC ${Mod}) 
    endforeach()

    foreach(Project IN LISTS SubProjects)
        target_link_libraries(${ExecutableName} LINK_PUBLIC ${Project})
    endforeach()

    install(TARGETS ${ExecutableName}
        RUNTIME ARCHIVE LIBRARY RUNTIME FRAMEWORK BUNDLE PUBLIC_HEADER RESOURCE)
    install(TARGETS ${ExecutableName}
        COMPONENT ${ExecutableName}
        RUNTIME_DEPENDENCIES
        PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
        POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
        DIRECTORIES bin)

endforeach()
#---
