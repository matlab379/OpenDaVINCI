# DataStructureGenerator- IDL tool to describe exchangeable data.
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
PROJECT (libtest8)
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
IF("${CXXTEST_INCLUDE_DIR}" STREQUAL "")
    SET (CXXTEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../cxxtest")
ENDIF()
INCLUDE (CheckCxxTestEnvironment)
IF("${OPENDAVINCI_DIR}" STREQUAL "")
    SET(OPENDAVINCI_DIR "${CMAKE_INSTALL_PREFIX}")
ELSE()
    SET(CMAKE_MODULE_PATH "${OPENDAVINCI_DIR}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules" ${CMAKE_MODULE_PATH})
ENDIF()
FIND_PACKAGE (OpenDaVINCI REQUIRED)
# Include directories from core.
INCLUDE_DIRECTORIES (${OPENDAVINCI_INCLUDE_DIRS})
INCLUDE_DIRECTORIES (include)
# Recipe for building libtest8.
FILE(GLOB_RECURSE libtest8-sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
ADD_LIBRARY (test8-core OBJECT ${libtest8-sources})
ADD_LIBRARY (test8-static STATIC $<TARGET_OBJECTS:test8-core>)
IF(NOT WIN32)
    ADD_LIBRARY (test8 SHARED $<TARGET_OBJECTS:test8-core>)
ENDIF()
IF("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    TARGET_LINK_LIBRARIES(test8 ${OPENDAVINCI_LIBRARIES})
ENDIF()
# Installing libtest8.
INSTALL(TARGETS test8-static DESTINATION lib COMPONENT odtest8lib)
IF(NOT WIN32)
    INSTALL(TARGETS test8 DESTINATION lib COMPONENT odtest8lib)
ENDIF()
# Install header files.
INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION include/ COMPONENT odtest8lib)
# Install proto files.
INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/proto/" DESTINATION share/proto/ COMPONENT odtest8lib)
# Install CMake modules locally.
IF(UNIX)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindTest8.cmake" DESTINATION share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules COMPONENT odtest8lib)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindTest8.cmake" DESTINATION share/cmake-2.8/Modules COMPONENT odtest8lib)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindTest8.cmake" DESTINATION share/cmake-3.0/Modules COMPONENT odtest8lib)
ENDIF()
IF(WIN32)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake.Modules/FindTest8.cmake" DESTINATION CMake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules COMPONENT odtest8lib)
ENDIF()
IF(CXXTEST_FOUND)
FILE(GLOB libtest8-testsuites "${CMAKE_CURRENT_SOURCE_DIR}/testsuites/*.h")
FOREACH(testsuite ${libtest8-testsuites})
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
        IF(WIN32)
            SET_SOURCE_FILES_PROPERTIES(${testsuite-short}-TestSuite.cpp PROPERTIES COMPILE_FLAGS "")
        ENDIF()
        IF(   WIN32
           OR ("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin") )
            TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite test8-static ${OPENDAVINCI_LIBRARIES})
        ELSE()
            TARGET_LINK_LIBRARIES(${testsuite-short}-TestSuite test8 ${OPENDAVINCI_LIBRARIES})
        ENDIF()
    ENDFOREACH()
ENDIF(CXXTEST_FOUND)
IF(    (UNIX)
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "DragonFly")
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "OpenBSD")
   AND (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "NetBSD") )
    SET(CPACK_GENERATOR "DEB;RPM")
    SET(CPACK_PACKAGE_CONTACT "First name Last name")
    SET(CPACK_PACKAGE_VENDOR "${CPACK_PACKAGE_CONTACT}")
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "This is a libtest8, a library containing data structures for distributed software systems realized with OpenDaVINCI.")
    SET(CPACK_PACKAGE_NAME libtest8)
    SET(CPACK_PACKAGE_VERSION_MAJOR "1")
    SET(CPACK_PACKAGE_VERSION_MINOR "0")
    SET(CPACK_PACKAGE_VERSION_PATCH "0")
    SET(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
    SET(CPACK_COMPONENTS_ALL odtest8lib)
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
#    SET(CPACK_DEB_COMPONENT_INSTALL ON)
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "ant,default-jre,default-jdk")
    # RPM packages:
    IF("${ARMHF}" STREQUAL "YES")
        SET(ARCH "armhf")
        SET(CPACK_RPM_PACKAGE_PROVIDES "libtest8.so()(armhf)")
    ELSE()
        IF("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
            SET(ARCH "x86_64")
            SET(CPACK_RPM_PACKAGE_PROVIDES "libtest8.so()(64bit)")
        ELSE()
            SET(ARCH "i686")
            SET(CPACK_RPM_PACKAGE_PROVIDES "libtest8.so")
        ENDIF()
    ENDIF()
    SET(CPACK_RPM_PACKAGE_BUILDARCH "Buildarch: ${CPACK_RPM_PACKAGE_ARCHITECTURE}")
#    SET(CPACK_RPM_COMPONENT_INSTALL ON)
    SET(CPACK_RPM_PACKAGE_LICENSE "LGPL")
    SET(CPACK_RPM_PACKAGE_DEPENDS "ant")
    # Resulting package name:
    SET(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${ARCH})
ENDIF()
INCLUDE(CPack)
