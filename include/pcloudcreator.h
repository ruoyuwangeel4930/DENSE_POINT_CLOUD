#ifndef PCLOUD_CREATOR_H
#define PCLOUD_CREATOR_H

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>

//pcl
/*# include <pcl/io/pcd_io.h>
# include <pcl/point_types.h>
# include <pcl/common/transforms.h>
# include <pcl/visualization/cloud_viewer.h>
# include <pcl/filters/voxel_grid.h>
# include <pcl/filters/passthrough.h>*/

using namespace std;

//type define
//typedef pcl::PointXYZRGBA PointT;
//typedef pcl::PointCloud<PointT> PointCloud;

//return the time stamp of depth image for corresponding rgb image
//return point cloud
//PointCloud::Ptr image2pointcloud(cv::Mat& rgb, cv::Mat& depth, CameraParameters& cp);

struct CameraParameters
{
	double cx, cy, fx, fy, scale;
};

struct KeyFrameParameters
{
	string timeStamp; // unique ID of each keyframe
	
	// coordinates of camera centers
	double x_c; 
	double y_c;
	double z_c;

	// x, y, z, w of quaternion
	double x;
	double y;
	double z;
	double w;
};

class CameraTrackReader
{
private:
	//string fileName;
	vector<KeyFrameParameters>* data;

public:
	CameraTrackReader(string fileName);
	// void ClearData();
	// void getframe(KeyFrameParameters& kfp);
	~CameraTrackReader();
	void get_frame(int i, KeyFrameParameters& kfp);
	int data_size();
};

class AssociationReader
{

}

#endif