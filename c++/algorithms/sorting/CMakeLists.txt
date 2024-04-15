# CMakeList.txt : CMake project for sorting1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.28)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("sorting")

# Definitions pertaining to "sorting"
## Define variables
set(SRC_DIR "src")
set(INCLUDE_DIR "include") 
set(IXX_DIR "interface") 

## Identify all compilation units to compile.
file(GLOB_RECURSE SRC_FILES 
  ${SRC_DIR}/*.cpp
  ${SRC_DIR}/*.c
)

## Identify all headers to use
file(GLOB_RECURSE HDR_FILES
  ${INCLUDE_DIR}/*.hpp
  ${INCLUDE_DIR}/*.h
)

## 
set(VC_STD_IXX_DIR_RAW "C:\\Program Files\\Microsoft Visual Studio\\2022\\Professional\\VC\\Tools\\MSVC\\14.39.33519\\modules")
string(REPLACE "/" "\\" VC_STD_IXX_DIR "${VC_STD_IXX_DIR_RAW}")
set(VC_STD_IXX "${VC_STD_IXX_DIR}/std.ixx")

include_directories(${VC_STD_IXX_DIR})


## Identify all compilation units to compile.
file(GLOB_RECURSE IXX_FILES 
  ${IXX_DIR}/*.ixx
)

## Define the target; since it's an object we refer to it by target name.
add_library (sorting ${SRC_FILES} ${IXX_FILES})

# Activate c++20 and modules 
set_target_properties(sorting PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED YES
) 

## Add sources to the target

target_sources(sorting PRIVATE ${SRC_FILES}) 

target_sources(sorting PUBLIC FILE_SET "mods" TYPE CXX_MODULES FILES ${IXX_FILES})
  
target_sources(sorting PUBLIC ${HDR_FILES})

target_include_directories(sorting PUBLIC ${VC_STD_IXX_DIR})



## Tell CMake to rerun itself if source files change
set_property(DIRECTORY PROPERTY 
  ADDITIONAL_MAKE_CLEAN_FILES ${SRC_FILES} ${IXX_FILES} ${HDR_FILES}
)

set_property(TARGET sorting PROPERTY
  SOURCE_DIR ${SRC_DIR}
  INCLUDE_DIR ${INCLUDE_DIR} 
  INTERFACE_SOURCES ${IXX_DIR}
)

# Specify module map and interface file
set_target_properties(sorting PROPERTIES
  CXX_MODULE "sorting.modulemap"
  CXX_MODULE_INTERFACE "src/sorting.ixx"
)



# TODO: Add tests and install targets if needed.
