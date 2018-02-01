SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O3")

ADD_LIBRARY( CameraTrackReader CameraTrackReader.cpp )
TARGET_LINK_LIBRARIES(CameraTrackReader)

ADD_LIBRARY( AssociationReader AssociationReader.cpp )
TARGET_LINK_LIBRARIES(AssociationReader)

ADD_EXECUTABLE( file_reader_test file_reader_test.cpp )
TARGET_LINK_LIBRARIES(file_reader_test 
		      CameraTrackReader 
                      AssociationReader)

