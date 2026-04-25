#
# Sandbox
#

set(SOURCES
    Source/Main.cpp
    Source/Scene2D.h
    Source/Scene2D.cpp
    Source/Scene3D.h
    Source/Scene3D.cpp
)

add_executable(Sandbox)

target_sources(Sandbox PRIVATE ${SOURCES})

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)

target_link_libraries(Sandbox Rivet)

target_include_directories(Sandbox PRIVATE Source)

# Set working directory for VS debugger
set_target_properties(Sandbox PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Sandbox"
)

add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Sandbox/shaders"
        "$<TARGET_FILE_DIR:Sandbox>/shaders"
    COMMENT "Copying Sandbox shaders to build directory"
)

add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Sandbox/assets"
        "$<TARGET_FILE_DIR:Sandbox>/assets"
    COMMENT "Copying Sandbox assets to build directory"
)

# ---- Locate and copy a system TTF font for the UI demo ---------------------
set(FONT_DEST "${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts")
file(MAKE_DIRECTORY "${FONT_DEST}")

set(SYSTEM_FONT_CANDIDATES
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
    "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf"
    "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf"
    "/usr/share/fonts/TTF/DejaVuSans.ttf"
)

if (NOT EXISTS "${FONT_DEST}/font.ttf")
    foreach(FONT_PATH ${SYSTEM_FONT_CANDIDATES})
        if (EXISTS "${FONT_PATH}")
            message(STATUS "Copying UI demo font from: ${FONT_PATH}")
            configure_file("${FONT_PATH}" "${FONT_DEST}/font.ttf" COPYONLY)
            break()
        endif()
    endforeach()
    if (NOT EXISTS "${FONT_DEST}/font.ttf")
        message(WARNING "[Sandbox] No system TTF found — place a font.ttf in Sandbox/assets/fonts/")
    endif()
endif()