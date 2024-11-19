 
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(test CANTest.cpp)

target_link_libraries(test gtest_main gmock_main CANLib) #need to link test ! dont forget
#target_link_libraries(${PROJECT_NAME} PRIVATE CANLib)