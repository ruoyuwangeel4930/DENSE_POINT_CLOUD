SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O3")

ADD_LIBRARY( pcloudcreator pcloudcreator.cpp )
TARGET_LINK_LIBRARIES(pcloudcreator)

ADD_EXECUTABLE( file_reader_test file_reader_test.cpp )
TARGET_LINK_LIBRARIES(file_reader_test pcloudcreator)

