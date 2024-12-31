
include (cmake/llvm.cmake)
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir/_build)
file( DOWNLOAD "https://github.com/llvm/llvm-project/releases/download/llvmorg-${MLIR_VERSION}/mlir-${MLIR_VERSION}.src.tar.xz"  ${CMAKE_CURRENT_SOURCE_DIR}/mlir-${MLIR_VERSION}.tar.xz
		STATUS DOWNLOAD_STATUS )
	message(STATUS " MLIR Download status: ${DOWNLOAD_STATUS}")
	
	file(ARCHIVE_EXTRACT INPUT ${CMAKE_CURRENT_SOURCE_DIR}/mlir-${MLIR_VERSION}.tar.xz DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
	file(REMOVE mlir-${MLIR_VERSION}.tar.xz)
    message(STATUS " MLIR Extraction done")

	file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/mlir-${MLIR_VERSION}.src ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir NO_REPLACE)
	file(REMOVE_RECURSE ${CMAKE_CURRENT_SOURCE_DIR}/mlir-${MLIR_VERSION}.src)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir/_build)
	message(STATUS " MLIR file processing done")
endif()

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir/_build/lib/cmake/mlir)
	execute_process(COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir 
		-DCMAKE_BUILD_TYPE=Release
		-DCMAKE_PREFIX_PATH=${CMAKE_CURRENT_SOURCE_DIR}/out/llvm/_build
		-DMLIR_ENABLE_DIALECT_STANDARD=ON
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir/_build)
	execute_process(COMMAND ${CMAKE_COMMAND} --build . --target mlir-tblgen --parallel WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir/_build)	
	execute_process(COMMAND ${CMAKE_COMMAND} --build . --target mlir-opt --parallel WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir/_build)	
	execute_process(COMMAND ${CMAKE_COMMAND} --build . --target mlir-translate --parallel WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir/_build)	
	execute_process(COMMAND ${CMAKE_COMMAND} --build . --target mlir-lsp-server --parallel WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/mlir/_build)	
	message(STATUS " MLIR Building done")
endif()


