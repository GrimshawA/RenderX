


file(GLOB rex_sources
    "src/rex/*.cpp"
    "src/rex/*.hpp"
)

file(GLOB gl_sources
    "src/rex/opengl/*.cpp"
    "src/rex/opengl/*.hpp"
)

file(GLOB vk_sources
    "src/rex/vulkan/*.cpp"
    "src/rex/vulkan/*.hpp"
)

add_library(rex SHARED ${rex_sources} 
					   ${gl_sources}
					   #${vk_sources}
					   )

if (Vulkan_FOUND)
	target_include_directories(rex PRIVATE ../glfw/include
	                                       ${Vulkan_INCLUDE_DIR})

	target_link_libraries(rex ${OPENGL_gl_LIBRARY} ${Vulkan_LIBRARY} glfw) 
	
endif(Vulkan_FOUND)
