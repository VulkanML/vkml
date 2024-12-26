include (cmake/llvm.cmake)
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/mlir/_build)
file( DOWNLOAD "https://github.com/llvm/llvm-project/releases/download/llvmorg-${MLIR_VERSION}/mlir-${MLIR_VERSION}.src.tar.xz"  ${CMAKE_CURRENT_SOURCE_DIR}/mlir-${MLIR_VERSION}.tar.xz
		STATUS DOWNLOAD_STATUS )
	message(STATUS " MLIR Download status: ${DOWNLOAD_STATUS}")
	
	file(ARCHIVE_EXTRACT INPUT ${CMAKE_CURRENT_SOURCE_DIR}/mlir-${MLIR_VERSION}.tar.xz DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
	file(REMOVE mlir-${MLIR_VERSION}.tar.xz)
	file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/mlir-${MLIR_VERSION}.src ${CMAKE_CURRENT_SOURCE_DIR}/mlir NO_REPLACE)
	file(REMOVE_RECURSE ${CMAKE_CURRENT_SOURCE_DIR}/mlir-${MLIR_VERSION}.src)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mlir/_build)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mlir/_install)
    message(STATUS " MLIR Extraction done")
endif()

if(NOT EXISTS ${MLIR_DIR})
	execute_process(COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} ${CMAKE_CURRENT_SOURCE_DIR}/mlir -DCMAKE_PREFIX_PATH=${CMAKE_CURRENT_SOURCE_DIR}/llvm/_install -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/mlir/_install WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mlir/_build)
	execute_process(COMMAND ${CMAKE_COMMAND} --build . --target install --parallel WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mlir/_build)	
	message(STATUS " MLIR Building done")
endif()

set(MLIR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mlir/_install/lib/cmake/mlir CACHE STRING "File path to mlir dir")
