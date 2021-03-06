# OpenDaVINCI - Portable middleware for distributed components.
# Copyright (C) 2008 - 2015  Christian Berger
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT (libopendavinci)

###########################################################################
# Set the search path for .cmake files.
SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules" ${CMAKE_MODULE_PATH})

# Add a local CMake module search path dependent on the desired installation destination.
# Thus, artifacts from the complete source build can be given precendence over any installed versions.
IF(UNIX)
    SET (CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" ${CMAKE_MODULE_PATH})
ENDIF()
IF(WIN32)
    SET (CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/CMake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" ${CMAKE_MODULE_PATH})
ENDIF()

###########################################################################
# Include flags for compiling.
INCLUDE (CompileFlags)

###########################################################################
# Find and configure CxxTest.
SET (CXXTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../cxxtest") 
INCLUDE (CheckCxxTestEnvironment)

###########################################################################
# Check for syslog.
FIND_PACKAGE (Syslog)
IF(NOT ("${SYSLOG_INCLUDE_DIR}" STREQUAL "SYSLOG_INCLUDE_DIR-NOTFOUND"))
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_SYSLOG")
ENDIF()

###########################################################################
# Check for a working threading and potential realtime library environment.
FIND_PACKAGE (Threads REQUIRED)
FIND_PACKAGE (LibRT)
IF(    (LIBRT_FOUND)
   AND ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux") )
    MESSAGE(STATUS "Using RT on Linux for libopendavinci.")
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_LINUX_RT")
ENDIF()

###########################################################################
# Try to find the odDataStructureGenerator to generate our own data structures.
#
# We need Java to run the odDataStructureGenerator tool.
INCLUDE(FindJava REQUIRED)

# Specify an additional search path to find odDataStructureGenerator.
SET(ODDATASTRUCTUREGENERATOR_PATH "${CMAKE_INSTALL_PREFIX}")
INCLUDE(FindodDataStructureGenerator)

###########################################################################
###########################################################################
# Define the directory where odDataStructureGenerator is generating the sources.
SET(COREDATA_DIR ${CMAKE_BINARY_DIR}/coredata)

# This step invokes the data structure generator during the initial cmake phase.
# Thus, it is ensured that the recursive file globbing below succeeds to collect
# all automatically generated source files.
IF(NOT EXISTS ${COREDATA_DIR}/include/opendavinci/GeneratedHeaders_OpenDaVINCI.h)
    MESSAGE("")
    MESSAGE("Generating data structures from ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCI.odvd in ${COREDATA_DIR}")

    IF(UNIX)
        EXECUTE_PROCESS(COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generateDataStructures.sh ${Java_JAVA_EXECUTABLE} ${ODDATASTRUCTUREGENERATOR_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCI.odvd ${CMAKE_BINARY_DIR}/coredata)
    ENDIF()
    IF(WIN32)
        EXECUTE_PROCESS(COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generateDataStructures.bat ${Java_JAVA_EXECUTABLE} ${ODDATASTRUCTUREGENERATOR_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCI.odvd ${CMAKE_BINARY_DIR}/coredata)
    ENDIF()

    MESSAGE("")
ENDIF()

# This custom command ensures that on changes to CoreData.odvd, the sources are re-generated.
IF(UNIX)
    ADD_CUSTOM_COMMAND(OUTPUT ${COREDATA_DIR}/include/opendavinci/GeneratedHeaders_OpenDaVINCI.h
                       COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generateDataStructures.sh ${Java_JAVA_EXECUTABLE} ${ODDATASTRUCTUREGENERATOR_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCI.odvd ${CMAKE_BINARY_DIR}/coredata
                       DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCI.odvd)
ENDIF()
IF(WIN32)
    ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_BINARY_DIR}/coredata/include/GeneratedHeaders_OpenDaVINCI.h
                       COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generateDataStructures.bat ${Java_JAVA_EXECUTABLE} ${ODDATASTRUCTUREGENERATOR_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCI.odvd ${CMAKE_BINARY_DIR}/coredata
                       DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCI.odvd)
ENDIF()
ADD_CUSTOM_TARGET(GenerateDataStructures DEPENDS ${COREDATA_DIR}/include/opendavinci/GeneratedHeaders_OpenDaVINCI.h)

###########################################################################
###########################################################################
# Define the directory where odDataStructureGenerator is generating the sources.
SET(TESTDATA_DIR ${CMAKE_BINARY_DIR}/testdata)

# This step invokes the data structure generator during the initial cmake phase.
# Thus, it is ensured that the recursive file globbing below succeeds to collect
# all automatically generated source files.
IF(NOT EXISTS ${TESTDATA_DIR}/include/opendavincitestdata/GeneratedHeaders_OpenDaVINCITestData.h)
    MESSAGE("")
    MESSAGE("Generating test data structures from ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCITestData.odvd in ${TESTDATA_DIR}")

    IF(UNIX)
        EXECUTE_PROCESS(COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generateDataStructures.sh ${Java_JAVA_EXECUTABLE} ${ODDATASTRUCTUREGENERATOR_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCITestData.odvd ${CMAKE_BINARY_DIR}/testdata)
    ENDIF()
    IF(WIN32)
        EXECUTE_PROCESS(COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generateDataStructures.bat ${Java_JAVA_EXECUTABLE} ${ODDATASTRUCTUREGENERATOR_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCITestData.odvd ${CMAKE_BINARY_DIR}/testdata)
    ENDIF()

    MESSAGE("")
ENDIF()

# This custom command ensures that on changes to CoreData.odvd, the sources are re-generated.
IF(UNIX)
    ADD_CUSTOM_COMMAND(OUTPUT ${TESTDATA_DIR}/include/opendavincitestdata/GeneratedHeaders_OpenDaVINCITestData.h
                       COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generateDataStructures.sh ${Java_JAVA_EXECUTABLE} ${ODDATASTRUCTUREGENERATOR_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCITestData.odvd ${CMAKE_BINARY_DIR}/testdata
                       DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCITestData.odvd)
ENDIF()
IF(WIN32)
    ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_BINARY_DIR}/testdata/include/GeneratedHeaders_OpenDaVINCITestData.h
                       COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generateDataStructures.bat ${Java_JAVA_EXECUTABLE} ${ODDATASTRUCTUREGENERATOR_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCITestData.odvd ${CMAKE_BINARY_DIR}/testdata
                       DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/OpenDaVINCITestData.odvd)
ENDIF()
ADD_CUSTOM_TARGET(GenerateDataStructuresTestData DEPENDS ${TESTDATA_DIR}/include/opendavincitestdata/GeneratedHeaders_OpenDaVINCITestData.h)

###########################################################################
# Set linking libraries to successfully link test suite binaries.
SET (LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
IF(LIBRT_FOUND)
    SET(LIBRARIES ${LIBRARIES} ${LIBRT_LIBRARIES})
ENDIF()

# Add CoreFoundation and IOKit on Mac OS X.
IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    FIND_LIBRARY(COREFOUNDATION_FRAMEWORK CoreFoundation)
    FIND_LIBRARY(IOKIT_FRAMEWORK IOKit)
    SET (LIBRARIES ${LIBRARIES} ${COREFOUNDATION_FRAMEWORK} ${IOKIT_FRAMEWORK})
ENDIF()

# On Windows, we need to add setupapi for the serial port library.
IF(WIN32)
    SET(LIBRARIES ${LIBRARIES} setupapi)
ENDIF()

# No shared libraries on Mac OS X.
IF(WIN32)
    SET (OPENDAVINCI_LIB opendavinci-static)
ELSE()
    SET (OPENDAVINCI_LIB opendavinci)
ENDIF()

###############################################################################
# Include directories for shipped 3rd party libraries.
SET(zlib_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/zlib-1.2.8")
SET(libzip_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/libzip-0.9")
SET(libwjwwoodserial_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/wjwwood-serial-1.2.1")
SET(jpegcompressor_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/jpeg-compressor")

INCLUDE_DIRECTORIES (${zlib_SOURCE_DIR})
SET (zlib-sources
    ${zlib_SOURCE_DIR}/adler32.c
    ${zlib_SOURCE_DIR}/compress.c
    ${zlib_SOURCE_DIR}/crc32.c
    ${zlib_SOURCE_DIR}/deflate.c
    ${zlib_SOURCE_DIR}/gzclose.c
    ${zlib_SOURCE_DIR}/gzlib.c
    ${zlib_SOURCE_DIR}/gzread.c
    ${zlib_SOURCE_DIR}/gzwrite.c
    ${zlib_SOURCE_DIR}/infback.c
    ${zlib_SOURCE_DIR}/inffast.c
    ${zlib_SOURCE_DIR}/inflate.c
    ${zlib_SOURCE_DIR}/inftrees.c
    ${zlib_SOURCE_DIR}/trees.c
    ${zlib_SOURCE_DIR}/uncompr.c
    ${zlib_SOURCE_DIR}/zutil.c
)
# Set compile flags for libzip sources.
IF(UNIX)
    SET(ZLIB_COMPILE_FLAGS "-Wno-error -Wno-implicit-function-declaration")
    SET_SOURCE_FILES_PROPERTIES(${zlib_SOURCE_DIR}/gzlib.c PROPERTIES COMPILE_FLAGS "${ZLIB_COMPILE_FLAGS}")
    SET_SOURCE_FILES_PROPERTIES(${zlib_SOURCE_DIR}/gzread.c PROPERTIES COMPILE_FLAGS "${ZLIB_COMPILE_FLAGS}")
    SET_SOURCE_FILES_PROPERTIES(${zlib_SOURCE_DIR}/gzwrite.c PROPERTIES COMPILE_FLAGS "${ZLIB_COMPILE_FLAGS}")
ENDIF()

INCLUDE_DIRECTORIES (${libzip_SOURCE_DIR}/include)
SET (libzip-sources
    ${libzip_SOURCE_DIR}/src/mkstemp.c
    ${libzip_SOURCE_DIR}/src/zip_add.c
    ${libzip_SOURCE_DIR}/src/zip_add_dir.c
    ${libzip_SOURCE_DIR}/src/zip_close.c
    ${libzip_SOURCE_DIR}/src/zip_delete.c
    ${libzip_SOURCE_DIR}/src/zip_dirent.c
    ${libzip_SOURCE_DIR}/src/zip_entry_free.c
    ${libzip_SOURCE_DIR}/src/zip_entry_new.c
    ${libzip_SOURCE_DIR}/src/zip_error.c
    ${libzip_SOURCE_DIR}/src/zip_error_clear.c
    ${libzip_SOURCE_DIR}/src/zip_error_get.c
    ${libzip_SOURCE_DIR}/src/zip_error_get_sys_type.c
    ${libzip_SOURCE_DIR}/src/zip_error_strerror.c
    ${libzip_SOURCE_DIR}/src/zip_error_to_str.c
    ${libzip_SOURCE_DIR}/src/zip_err_str.c
    ${libzip_SOURCE_DIR}/src/zip_fclose.c
    ${libzip_SOURCE_DIR}/src/zip_file_error_clear.c
    ${libzip_SOURCE_DIR}/src/zip_file_error_get.c
    ${libzip_SOURCE_DIR}/src/zip_file_get_offset.c
    ${libzip_SOURCE_DIR}/src/zip_filerange_crc.c
    ${libzip_SOURCE_DIR}/src/zip_file_strerror.c
    ${libzip_SOURCE_DIR}/src/zip_fopen.c
    ${libzip_SOURCE_DIR}/src/zip_fopen_index.c
    ${libzip_SOURCE_DIR}/src/zip_fread.c
    ${libzip_SOURCE_DIR}/src/zip_free.c
    ${libzip_SOURCE_DIR}/src/zip_get_archive_comment.c
    ${libzip_SOURCE_DIR}/src/zip_get_archive_flag.c
    ${libzip_SOURCE_DIR}/src/zip_get_file_comment.c
    ${libzip_SOURCE_DIR}/src/zip_get_name.c
    ${libzip_SOURCE_DIR}/src/zip_get_num_files.c
    ${libzip_SOURCE_DIR}/src/zip_memdup.c
    ${libzip_SOURCE_DIR}/src/zip_name_locate.c
    ${libzip_SOURCE_DIR}/src/zip_new.c
    ${libzip_SOURCE_DIR}/src/zip_open.c
    ${libzip_SOURCE_DIR}/src/zip_rename.c
    ${libzip_SOURCE_DIR}/src/zip_replace.c
    ${libzip_SOURCE_DIR}/src/zip_set_archive_comment.c
    ${libzip_SOURCE_DIR}/src/zip_set_archive_flag.c
    ${libzip_SOURCE_DIR}/src/zip_set_file_comment.c
    ${libzip_SOURCE_DIR}/src/zip_set_name.c
    ${libzip_SOURCE_DIR}/src/zip_source_buffer.c
    ${libzip_SOURCE_DIR}/src/zip_source_file.c
    ${libzip_SOURCE_DIR}/src/zip_source_filep.c
    ${libzip_SOURCE_DIR}/src/zip_source_free.c
    ${libzip_SOURCE_DIR}/src/zip_source_function.c
    ${libzip_SOURCE_DIR}/src/zip_source_zip.c
    ${libzip_SOURCE_DIR}/src/zip_stat.c
    ${libzip_SOURCE_DIR}/src/zip_stat_index.c
    ${libzip_SOURCE_DIR}/src/zip_stat_init.c
    ${libzip_SOURCE_DIR}/src/zip_strerror.c
    ${libzip_SOURCE_DIR}/src/zip_unchange_all.c
    ${libzip_SOURCE_DIR}/src/zip_unchange_archive.c
    ${libzip_SOURCE_DIR}/src/zip_unchange.c
    ${libzip_SOURCE_DIR}/src/zip_unchange_data.c    
)
# Set compile flags for libzip sources.
IF(UNIX)
    SET(ZIP_COMPILE_FLAGS "-Wno-error -Wno-implicit-function-declaration")
    SET_SOURCE_FILES_PROPERTIES(${libzip_SOURCE_DIR}/src/mkstemp.c PROPERTIES COMPILE_FLAGS "${ZIP_COMPILE_FLAGS}")
    SET_SOURCE_FILES_PROPERTIES(${libzip_SOURCE_DIR}/src/zip_close.c PROPERTIES COMPILE_FLAGS "${ZIP_COMPILE_FLAGS}")
ENDIF()

INCLUDE_DIRECTORIES (${libwjwwoodserial_SOURCE_DIR}/include)
IF(UNIX)
    SET (libwjwwoodserial-sources
         ${libwjwwoodserial_SOURCE_DIR}/src/serial.cc
         ${libwjwwoodserial_SOURCE_DIR}/src/impl/unix.cc
         ${libwjwwoodserial_SOURCE_DIR}/src/impl/list_ports/list_ports_linux.cc
         ${libwjwwoodserial_SOURCE_DIR}/src/impl/list_ports/list_ports_osx.cc
    )

    # Set compile flags for wjwwood serial library.
    SET(WJWWOOD_SERIAL_COMPILE_FLAGS "-Wno-effc++ -Wno-error -Wno-sign-compare")
    IF (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
        SET(WJWWOOD_SERIAL_COMPILE_FLAGS "${WJWWOOD_SERIAL_COMPILE_FLAGS} -Wno-unused-but-set-variable -Wno-suggest-attribute=format -Wno-stack-protector")
    ENDIF()
    SET_SOURCE_FILES_PROPERTIES(${libwjwwoodserial_SOURCE_DIR}/src/serial.cc PROPERTIES COMPILE_FLAGS "${WJWWOOD_SERIAL_COMPILE_FLAGS}")
    SET_SOURCE_FILES_PROPERTIES(${libwjwwoodserial_SOURCE_DIR}/src/impl/unix.cc PROPERTIES COMPILE_FLAGS "${WJWWOOD_SERIAL_COMPILE_FLAGS}")
    SET_SOURCE_FILES_PROPERTIES(${libwjwwoodserial_SOURCE_DIR}/src/impl/list_ports/list_ports_linux.cc PROPERTIES COMPILE_FLAGS "${WJWWOOD_SERIAL_COMPILE_FLAGS}")
    SET_SOURCE_FILES_PROPERTIES(${libwjwwoodserial_SOURCE_DIR}/src/impl/list_ports/list_ports_osx.cc PROPERTIES COMPILE_FLAGS "${WJWWOOD_SERIAL_COMPILE_FLAGS}")
ENDIF()

IF(WIN32)
    SET (libwjwwoodserial-sources
         ${libwjwwoodserial_SOURCE_DIR}/src/serial.cc
         ${libwjwwoodserial_SOURCE_DIR}/src/impl/win.cc
         ${libwjwwoodserial_SOURCE_DIR}/src/impl/list_ports/list_ports_win.cc
    )
ENDIF()

INCLUDE_DIRECTORIES (${jpegcompressor_SOURCE_DIR})
SET (jpegcompressor-headers
    ${jpegcompressor_SOURCE_DIR}/jpgd.h
    ${jpegcompressor_SOURCE_DIR}/jpge.h
)
SET (jpegcompressor-sources
    ${jpegcompressor_SOURCE_DIR}/jpgd.cpp
    ${jpegcompressor_SOURCE_DIR}/jpge.cpp
)
# Set compile flags for jpeg-compressor sources.
IF(UNIX)
    SET(JPEG_COMPILE_FLAGS "-Wno-effc++ -Wno-error -Wno-sign-compare -Wno-unused-parameter -Wno-shadow")
    IF (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
        SET(JPEG_COMPILE_FLAGS "${JPEG_COMPILE_FLAGS} -Wno-unused-but-set-variable -Wno-suggest-attribute=format")
    ENDIF()
    SET_SOURCE_FILES_PROPERTIES(${jpegcompressor_SOURCE_DIR}/jpgd.cpp PROPERTIES COMPILE_FLAGS "${JPEG_COMPILE_FLAGS}")
    SET_SOURCE_FILES_PROPERTIES(${jpegcompressor_SOURCE_DIR}/jpge.cpp PROPERTIES COMPILE_FLAGS "${JPEG_COMPILE_FLAGS}")
ENDIF()

###############################################################################
# Set header files for coredata files generated from OpenDaVINCI.odvd.
INCLUDE_DIRECTORIES(${COREDATA_DIR}/include)
# Set header files for testdata files generated from OpenDaVINCITestData.odvd.
INCLUDE_DIRECTORIES(${TESTDATA_DIR}/include)
# Set include directory.
INCLUDE_DIRECTORIES(include)

###############################################################################
# Set sources for coredata files generated from OpenDaVINCI.odvd.
FILE(GLOB_RECURSE libopendavinci-coredata-sources "${COREDATA_DIR}/src/*.cpp")
# Set sources for testdata files generated from OpenDaVINCITestData.odvd.
FILE(GLOB_RECURSE libopendavinci-testdata-sources "${TESTDATA_DIR}/src/*.cpp")
# Collect all source files.
FILE(GLOB_RECURSE libopendavinci-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

###############################################################################
# Remove POSIX files on WIN32.
IF(WIN32)
    # Set flag for exporting symbols.
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DOPENDAVINCI_EXPORTS")
    
    # Exclude POSIX files.
    FOREACH(item ${libopendavinci-sources})
      IF(${item} MATCHES "POSIX.+.cpp")
        LIST(REMOVE_ITEM libopendavinci-sources ${item})
      ENDIF()
    ENDFOREACH()
ENDIF()

###############################################################################
# Remove WIN32 files on POSIX.
IF(UNIX)
    # Exclude WIN32 files.
    FOREACH(item ${libopendavinci-sources})
      IF(${item} MATCHES "WIN32.+.cpp")
        LIST(REMOVE_ITEM libopendavinci-sources ${item})
      ENDIF()
    ENDFOREACH()
ENDIF()

###############################################################################
# Resulting artifacts.
ADD_LIBRARY (opendavinci-core OBJECT ${libopendavinci-sources}
                                     ${libopendavinci-coredata-sources}
                                     ${libwjwwoodserial-sources}
                                     ${libzip-sources}
                                     ${zlib-sources}
                                     ${jpegcompressor-sources})
ADD_LIBRARY (opendavinci-static STATIC $<TARGET_OBJECTS:opendavinci-core>)
IF(NOT WIN32)
    ADD_LIBRARY (opendavinci    SHARED $<TARGET_OBJECTS:opendavinci-core>)
ENDIF()

TARGET_LINK_LIBRARIES(opendavinci-static ${LIBRARIES})
IF(NOT WIN32)
    TARGET_LINK_LIBRARIES(opendavinci    ${LIBRARIES})
ENDIF()

SET(OPENDAVINCI_LIB_FOR_TESTSUITES opendavinci-static-for-testsuites)
ADD_LIBRARY (${OPENDAVINCI_LIB_FOR_TESTSUITES} STATIC
                                     $<TARGET_OBJECTS:opendavinci-core>
                                     ${libopendavinci-testdata-sources}
)

# Add dependency to generate data structures before building the sources.
ADD_DEPENDENCIES(opendavinci-core GenerateDataStructures)
ADD_DEPENDENCIES(opendavinci-core GenerateDataStructuresTestData)

###############################################################################
# Enable CxxTest for all available testsuites.
IF(CXXTEST_FOUND)
    FILE(GLOB libopendavinci-testsuites "${CMAKE_CURRENT_SOURCE_DIR}/testsuites/*.h")

    FOREACH(testsuite ${libopendavinci-testsuites})
        STRING(REPLACE "/" ";" testsuite-list ${testsuite})

        LIST(LENGTH testsuite-list len)
        MATH(EXPR lastItem "${len}-1")
        LIST(GET testsuite-list "${lastItem}" testsuite-short)

        SET(CXXTEST_TESTGEN_ARGS ${CXXTEST_TESTGEN_ARGS} --world=${PROJECT_NAME}-${testsuite-short})
        CXXTEST_ADD_TEST(${testsuite-short}-TestSuite ${testsuite-short}-TestSuite.cpp ${testsuite})
        IF(UNIX)
            IF( (   ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
                 OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD")
                 OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly") )
                AND (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") )
                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal -Wno-error=suggest-attribute=noreturn")
            ELSE()
                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal")
            ENDIF()
        ENDIF()
        SET_TESTS_PROPERTIES(${testsuite-short}-TestSuite PROPERTIES TIMEOUT 3000)
        TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite ${OPENDAVINCI_LIB_FOR_TESTSUITES} ${LIBRARIES})
    ENDFOREACH()

    FILE(GLOB libopendavinci-coredata-testsuites "${COREDATA_DIR}/testsuites/*.h")
    FOREACH(testsuite ${libopendavinci-coredata-testsuites})
        STRING(REPLACE "/" ";" testsuite-list ${testsuite})

        LIST(LENGTH testsuite-list len)
        MATH(EXPR lastItem "${len}-1")
        LIST(GET testsuite-list "${lastItem}" testsuite-short)

        SET(CXXTEST_TESTGEN_ARGS ${CXXTEST_TESTGEN_ARGS} --world=${PROJECT_NAME}-${testsuite-short})
        CXXTEST_ADD_TEST(${testsuite-short}-TestSuite ${testsuite-short}-TestSuite.cpp ${testsuite})
        IF(UNIX)
            IF( (   ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
                 OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD")
                 OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly") )
                AND (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") )
                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal -Wno-error=suggest-attribute=noreturn")
            ELSE()
                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal")
            ENDIF()
        ENDIF()

        SET_TESTS_PROPERTIES(${testsuite-short}-TestSuite PROPERTIES TIMEOUT 3000)
        TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite ${OPENDAVINCI_LIB_FOR_TESTSUITES} ${LIBRARIES})
    ENDFOREACH()

    FILE(GLOB libopendavinci-testdata-testsuites "${TESTDATA_DIR}/testsuites/*.h")
    FOREACH(testsuite ${libopendavinci-testdata-testsuites})
        STRING(REPLACE "/" ";" testsuite-list ${testsuite})

        LIST(LENGTH testsuite-list len)
        MATH(EXPR lastItem "${len}-1")
        LIST(GET testsuite-list "${lastItem}" testsuite-short)

        SET(CXXTEST_TESTGEN_ARGS ${CXXTEST_TESTGEN_ARGS} --world=${PROJECT_NAME}-${testsuite-short})
        CXXTEST_ADD_TEST(${testsuite-short}-TestSuite ${testsuite-short}-TestSuite.cpp ${testsuite})
        IF(UNIX)
            IF( (   ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
                 OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD")
                 OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly") )
                AND (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") )
                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal -Wno-error=suggest-attribute=noreturn")
            ELSE()
                SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "-Wno-effc++ -Wno-float-equal")
            ENDIF()
        ENDIF()

        SET_TESTS_PROPERTIES(${testsuite-short}-TestSuite PROPERTIES TIMEOUT 3000)
        TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite ${OPENDAVINCI_LIB_FOR_TESTSUITES} ${LIBRARIES})
    ENDFOREACH()
ENDIF(CXXTEST_FOUND)

###############################################################################
# Installing "libopendavinci".
INSTALL(TARGETS opendavinci-static DESTINATION lib COMPONENT lib)
IF(NOT WIN32)
    INSTALL(TARGETS opendavinci    DESTINATION lib COMPONENT lib)
ENDIF()

# Install header files.
INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION include/ COMPONENT lib)
# Merge header files from generated data structures with the rest of OpenDaVINCI to avoid specifying another include directory at the users' end.
INSTALL(DIRECTORY "${COREDATA_DIR}/include/" DESTINATION include/ COMPONENT lib)

# Install proto file.
INSTALL(DIRECTORY "${COREDATA_DIR}/proto/" DESTINATION share/proto/ COMPONENT lib)

# Install CMake modules locally.
IF(UNIX)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindOpenDaVINCI.cmake" DESTINATION share/cmake-2.8/Modules COMPONENT lib)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindLibRT.cmake" DESTINATION share/cmake-2.8/Modules COMPONENT lib)

    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindOpenDaVINCI.cmake" DESTINATION share/cmake-3.0/Modules COMPONENT lib)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindLibRT.cmake" DESTINATION share/cmake-3.0/Modules COMPONENT lib)

    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindOpenDaVINCI.cmake" DESTINATION share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules COMPONENT lib)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindLibRT.cmake" DESTINATION share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules COMPONENT lib)
ENDIF()
IF(WIN32)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindOpenDaVINCI.cmake" DESTINATION CMake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules COMPONENT lib)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindLibRT.cmake" DESTINATION CMake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules COMPONENT lib)
ENDIF()

###########################################################################
# Enable CPack to create .deb and .rpm.
#
# Read version from first line of ChangeLog
FILE (STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog" BUILD_NUMBER)
MACRO (setup_package_version_variables _packageName)
        STRING (REGEX MATCHALL "[0-9]+" _versionComponents "${_packageName}")
        LIST (LENGTH _versionComponents _len)
        IF (${_len} GREATER 0)
            LIST(GET _versionComponents 0 MAJOR)
        ENDIF()
        IF (${_len} GREATER 1)
            LIST(GET _versionComponents 1 MINOR)
        ENDIF()
        IF (${_len} GREATER 2)
            LIST(GET _versionComponents 2 PATCH)
        ENDIF()
ENDMACRO()
setup_package_version_variables(${BUILD_NUMBER})

IF(    (UNIX)
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly")
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "OpenBSD")
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "NetBSD") )
    SET(CPACK_GENERATOR "DEB;RPM")

    SET(CPACK_PACKAGE_CONTACT "Christian Berger")
    SET(CPACK_PACKAGE_VENDOR "${CPACK_PACKAGE_CONTACT}")
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OpenDaVINCI is a lean and highly portable middleware written in C++ to develop distributed software systems.")
    SET(CPACK_PACKAGE_NAME "opendavinci")
    SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR}")
    SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR}")
    SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH}")
    SET(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
    SET(CPACK_COMPONENTS_ALL lib)

    # Debian packages:
    SET(CPACK_DEBIAN_PACKAGE_SECTION "devel")
    SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
    IF("${ARMHF}" STREQUAL "YES")
        SET(ARCH "armhf")
    ELSE()
        IF("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
            SET(ARCH "amd64")
        ELSE()
            SET(ARCH "i386")
        ENDIF()
    ENDIF()
    SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${ARCH}")
    SET(CPACK_DEB_COMPONENT_INSTALL ON)
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "build-essential,rpm,cmake,git")

    # RPM packages:
    IF("${ARMHF}" STREQUAL "YES")
        SET(ARCH "armhf")
    ELSE()
        IF("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
            SET(ARCH "x86_64")
            SET(CPACK_RPM_PACKAGE_PROVIDES "libopendavinci.so()(64bit)")
        ELSE()
            SET(ARCH "i686")
            SET(CPACK_RPM_PACKAGE_PROVIDES "libopendavinci.so")
        ENDIF()
    ENDIF()
    SET(CPACK_RPM_PACKAGE_BUILDARCH "Buildarch: ${CPACK_RPM_PACKAGE_ARCHITECTURE}")
    SET(CPACK_RPM_COMPONENT_INSTALL ON)
    SET(CPACK_RPM_PACKAGE_LICENSE "LGPL")
    SET(CPACK_RPM_PACKAGE_DEPENDS "cmake, gcc, gcc-c++, git")

    # Resulting package name:
    SET(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${ARCH})
ENDIF()

INCLUDE(CPack)

