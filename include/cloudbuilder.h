#ifndef CLOUDBUILDER_H
#define CLOUDBUILDER_H

#include <vector>
#include <map>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

namespace dec
{
typedef Eigen::Transform<double, 3, Eigen::Affine> Affine;
typedef Eigen::Quaternion<double> Rot;
typedef Eigen::Translation<double, 3> Trans;
typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloud;

struct CameraParameters
{
	double cx, cy, fx, fy, scale;
};

struct SE3
{
	double tx, ty, tz, x, y, z, w;
};

class CloudBuilder
{
public:
	CloudBuilder(const string traj_fname, const string assoc_fname, const string cam_fname);
	PointCloud::Ptr buildPointCloud(const float near, const float far, const float leaf_sz);
private:
	map<string, string> parameters;
	CameraParameters cam;
	vector<string> rgb_fname;
	vector<string> dep_fname;
	vector<double> rgb_tstamp;
	vector<double> dep_tstamp;
	vector<double> kf_tstamp;
	vector<SE3> vSE3;

	PointCloud::Ptr image2pointcloud(const cv::Mat& rgb, const cv::Mat& depth);
}; 
};

#endif
