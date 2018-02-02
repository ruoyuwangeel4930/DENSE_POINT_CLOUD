SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O3")

# 增加PCL库的依赖
FIND_PACKAGE( PCL REQUIRED COMPONENTS common io visualization filters )
list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4") # use this in Ubuntu 16.04

# 增加opencv的依赖
FIND_PACKAGE( OpenCV REQUIRED )

# 添加头文件和库文件
ADD_DEFINITIONS( ${PCL_DEFINITIONS} )
INCLUDE_DIRECTORIES( ${PCL_INCLUDE_DIRS}  )
LINK_LIBRARIES( ${PCL_LIBRARY_DIRS} )

ADD_LIBRARY( CameraTrackReader CameraTrackReader.cpp )
TARGET_LINK_LIBRARIES(CameraTrackReader)

ADD_LIBRARY( AssociationReader AssociationReader.cpp )
TARGET_LINK_LIBRARIES(AssociationReader)

ADD_LIBRARY( CameraReader CameraReader.cpp )
TARGET_LINK_LIBRARIES(CameraReader)

ADD_EXECUTABLE( file_reader_test file_reader_test.cpp )
TARGET_LINK_LIBRARIES(file_reader_test 
		      CameraTrackReader 
                      AssociationReader
		      CameraReader)



