cmake_minimum_required(VERSION 3.10)

if(NOT "${CLEAN_BUILD}" STREQUAL "true")
    include(../../vender/tools/get_env.cmake)

    set(WORK_ROOT $ENV{WORK_ROOT})
    if(NOT WORK_ROOT)
        set(WORK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../..")
    endif()

    set(OUT_PATH "${WORK_ROOT}/out/${CMAKE_HOST_SYSTEM_NAME}_${BUILD_ARCH}_${BUILD_TYPE}")
    build("${CMAKE_CURRENT_SOURCE_DIR}" "${OUT_PATH}/program")

    if((NOT ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows") AND ${BUILD_TYPE} STREQUAL "release")
        set(BIN_PATH "${WORK_ROOT}/bin/${CMAKE_HOST_SYSTEM_NAME}_${BUILD_ARCH}_${BUILD_TYPE}")

        execute_process(WORKING_DIRECTORY ${BIN_PATH} COMMAND ${CMAKE_COMMAND} -E tar -zcf fibjs.tar.gz fibjs)
        message("[100%] Built target fibjs.tar.gz")
        
        execute_process(OUTPUT_FILE ${BIN_PATH}/installer.sh
            COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/tools/installer.txt ${BIN_PATH}/fibjs.tar.gz)
        execute_process(COMMAND chmod 777 ${BIN_PATH}/installer.sh)
        message("[100%] Built target install.sh")

        if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
 			if(${BUILD_ARCH} STREQUAL "arm")
                set(BUILD_PREFIX "arm-linux-gnueabihf-")
            elseif(${BUILD_ARCH} STREQUAL "arm64")
                set(BUILD_PREFIX "aarch64-linux-gnu-")
            elseif(${BUILD_ARCH} STREQUAL "mips")
                set(BUILD_PREFIX "mips-linux-gnu-")
            elseif(${BUILD_ARCH} STREQUAL "mips64")
                set(BUILD_PREFIX "mips64-linux-gnuabi64-")
            elseif(${BUILD_ARCH} STREQUAL "ppc")
                set(BUILD_PREFIX "powerpc-linux-gnu-")
            elseif(${BUILD_ARCH} STREQUAL "ppc64")
                set(BUILD_PREFIX "powerpc64-linux-gnu-")
            endif()

            message("")
            message("==== GLIBC ====")
            execute_process(COMMAND ${BUILD_PREFIX}objdump ${BIN_PATH}/fibjs -p COMMAND grep GLIBCX*_[0-9.]* -o COMMAND sort COMMAND uniq)
        endif()
    endif()
endif()