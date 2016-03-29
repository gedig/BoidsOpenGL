set(ASSET_SOURCE
	"${PROJECT_ASSET_ROOT}/boid.mdl"
	"${PROJECT_ASSET_ROOT}/boid.col")
	
# Tell the compiler/IDE to treat these as headers, ignore when compiling
set_source_files_properties(${ASSET_SOURCE} PROPERTIES HEADER_FILE_ONLY TRUE)

set(ASSET_INCLUDE "${PROJECT_GENERATED_ROOT}/AssetPaths.hpp")

configure_file("${PROJECT_ASSET_ROOT}/AssetPaths.hpp.in" ${ASSET_INCLUDE})

set(ASSET_LIST ${ASSET_SOURCE} ${ASSET_INCLUDE} PARENT_SCOPE)