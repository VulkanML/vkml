
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm-project/_build/)
    file( DOWNLOAD "https://github.com/llvm/llvm-project/releases/download/llvmorg-${MLIR_VERSION}/llvm-project-${MLIR_VERSION}.src.tar.xz"  ${CMAKE_CURRENT_SOURCE_DIR}/llvm-project-${MLIR_VERSION}.src.tar.xz )
    file(ARCHIVE_EXTRACT INPUT ${CMAKE_CURRENT_SOURCE_DIR}/llvm-project-${MLIR_VERSION}.src.tar.xz DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
    file(REMOVE ${CMAKE_CURRENT_SOURCE_DIR}/llvm-project-${MLIR_VERSION}.src.tar.xz)
    file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/llvm-project-${MLIR_VERSION}.src ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm-project NO_REPLACE)
    file(REMOVE_RECURSE ${CMAKE_CURRENT_SOURCE_DIR}/llvm-project-${MLIR_VERSION}.src)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm-project/_build)
endif()

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm-project/_build/CMakeCache.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm-project/llvm
        -DCMAKE_BUILD_TYPE=Release
        -DLLVM_ENABLE_PROJECTS=mlir
        -DLLVM_INCLUDE_TESTS=OFF
        -DLLVM_INCLUDE_RUNTIMES=OFF
        -DLLVM_INCLUDE_BENCHMARKS=OFF 
        -DLLVM_INCLUDE_DOCS=OFF 
        -DLLVM_ENABLE_ZLIB=OFF
        -DLLVM_ENABLE_LIBPFM=OFF
        -DLLVM_INCLUDE_EXAMPLES=OFF
        -DLLVM_BUILD_RUNTIMES=OFF 
        -DLLVM_BUILD_UTILS=ON
        -DLLVM_TARGETS_TO_BUILD=
        -DLLVM_EXPERIMENTAL_TARGETS_TO_BUILD=SPIRV
        -DLLVM_ENABLE_IDE=OFF
        -DLLVM_ENABLE_BACKTRACES=OFF
        -DLLVM_ENABLE_ASSERTIONS=OFF
        -DLLVM_ENABLE_OCAMLDOC=OFF
        -DLLVM_BUILD_INSTRUMENTED_COVERAGE=OFF
        -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/out/llvm-project/_build
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm-project/_build
    )
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build . --target install --config Debug --parallel WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out/llvm-project/_build)

