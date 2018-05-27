
find_package(OpenGL)

file(GLOB rex_sources
    "src/rex/*.cpp"
    "src/rex/*.hpp"
)

file(GLOB gl_sources
    "src/rex/opengl/*.cpp"
    "src/rex/opengl/*.hpp"
    "src/rex/opengl/glew/*.c"
)

file(GLOB vk_sources
    "src/rex/vulkan/*.cpp"
    "src/rex/vulkan/*.hpp"
)

if (REX_BUILD_VULKAN)
    set(rex_sources ${rex_sources} ${vk_sources})
endif()

add_library(rex SHARED ${rex_sources} 
                       ${gl_sources})

target_include_directories(rex PRIVATE src/rex
                                        src/rex/opengl/glew)
             target_link_libraries(rex ${OPENGL_gl_LIBRARY})

if (Vulkan_FOUND)
	target_include_directories(rex PRIVATE ../glfw/include
                                               ${Vulkan_INCLUDE_DIR})
target_link_libraries(rex ${Vulkan_LIBRARY} glfw)
	
endif(Vulkan_FOUND)
