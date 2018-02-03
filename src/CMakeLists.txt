# 增加一个可执行的二进制
#ADD_EXECUTABLE( main main.cpp )

# 增加PCL库的依赖
FIND_PACKAGE( PCL REQUIRED COMPONENTS common io )
LINK_LIBRARIES("/usr/lib/x86_64-linux-gnu/libpcl_visualization.so")
LINK_LIBRARIES("/usr/lib/x86_64-linux-gnu/libpcl_filters.so")

list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4") # use this in Ubuntu 16.04

# 增加opencv的依赖
FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )
#LINK_LIBRARIES("/usr/lib/libopencv_core.so")
#LINK_LIBRARIES("/usr/lib/libopencv_highgui.so")

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

ADD_LIBRARY( image2pointcloud image2pointcloud.cpp )
TARGET_LINK_LIBRARIES(image2pointcloud)


ADD_EXECUTABLE( file_reader_test file_reader_test.cpp )
TARGET_LINK_LIBRARIES(file_reader_test 
		      CameraTrackReader 
                      AssociationReader
		      CameraReader
		      image2pointcloud
		     ${OpenCV_LIBS} 
                     ${PCL_LIBRARIES})

ADD_EXECUTABLE( create_point_cloud create_point_cloud.cpp )
TARGET_LINK_LIBRARIES(create_point_cloud 
		      CameraTrackReader 
                      AssociationReader
		      CameraReader
		      image2pointcloud
		     ${OpenCV_LIBS} 
                     ${PCL_LIBRARIES})



