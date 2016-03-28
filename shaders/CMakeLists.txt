set(SHADER_SOURCE
	"${PROJECT_SHADER_ROOT}/boid.fs.glsl"
	"${PROJECT_SHADER_ROOT}/boid.vs.glsl")
	
# Tell the compiler/IDE to treat these as headers, ignore when compiling
set_source_files_properties(${SHADER_SOURCE} PROPERTIES HEADER_FILE_ONLY TRUE)

set(SHADER_INCLUDE "${PROJECT_GENERATED_ROOT}/ShaderPaths.hpp")

configure_file("${PROJECT_SHADER_ROOT}/ShaderPaths.hpp.in" ${SHADER_INCLUDE})

set(SHADER_LIST ${SHADER_SOURCE} ${SHADER_INCLUDE} PARENT_SCOPE)