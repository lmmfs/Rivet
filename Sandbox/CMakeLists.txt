#
# Sandbox
#

set(SOURCES
    Source/Main.cpp
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


#add_custom_target(copy_shaders
 #       COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Sandbox/Shaders" "${CMAKE_CURRENT_BINARY_DIR}/Shaders"
  #  )
   # add_dependencies(Sandbox copy_shaders)