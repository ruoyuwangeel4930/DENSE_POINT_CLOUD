#ifndef PCLOUD_CREATOR_H
#define PCLOUD_CREATOR_H

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <map>
//# include <string>

//pcl
# include <pcl/io/pcd_io.h>
# include <pcl/point_types.h>
# include <pcl/common/transforms.h>
# include <pcl/visualization/cloud_viewer.h>
# include <pcl/filters/voxel_grid.h>
# include <pcl/filters/passthrough.h>

using namespace std;

//type define
typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloud;

//return point cloud
void image2pointcloud(const cv::Mat& rgb, const cv::Mat& depth, const CameraParameters& cp, PointCloud::Ptr& cloud);

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
	vector<KeyFrameParameters>* data;

public:
	CameraTrackReader(const string& fileName);
	// void ClearData();
	// void getframe(KeyFrameParameters& kfp);
	~CameraTrackReader();
	void get_frame(const int i, KeyFrameParameters& kfp);
	int data_size();
};

class CameraReader
{
private:
	map<string, string>* camParams;

public:
	CameraReader(const string& fileName);
	~CameraReader();
	
	double get_data(const string& paramName);
	void get_camera(CameraParameters& cp);
};

class AssociationReader
{
private:
	map<string, string>* ptrRGB2DepthMap;

public:
	AssociationReader(const string& fileName);
	~AssociationReader();

	void get_depth_timestamp(const string& rgbTimeStamp, string& depthTimeStamp);
};



#endif