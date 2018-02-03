#include "pcloudcreator.h"

using namespace std;

PointCloud::Ptr image2pointcloud(const cv::Mat& rgb, const cv::Mat& depth, const CameraParameters& cp)
{
	PointCloud::Ptr cloud(new PointCloud);
	ushort d; // depth value
	PointT p; // point

	for (int m=0; m < depth.rows; m++)
		for(int n=0; n < depth.cols; n++)
		{
			d = depth.ptr<ushort>(m)[n];

			if (d == 0)
				continue;

			// calculate coords of p
			p.z = double(d) / cp.scale;
			p.x = (n - cp.cx) * p.z / cp.fx;
			p.y = (m - cp.cy) * p.z / cp.fy; 

			// extract rgb
			p.b = rgb.ptr<uchar>(m)[n*3];
			p.g = rgb.ptr<uchar>(m)[n*3+1];
			p.r = rgb.ptr<uchar>(m)[n*3+2];

			cloud->points.push_back(p);
		}

	cloud->height = 1;
	cloud->width = cloud->points.size();
	cloud->is_dense = false;

	return cloud;
}
