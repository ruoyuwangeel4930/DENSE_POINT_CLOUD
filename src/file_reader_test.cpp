# include "pcloudcreator.h"
# include <string>

# include <Eigen/Core>
# include <Eigen/Geometry>

using namespace std;

int main(int argc, char** argv)
{
	CameraTrackReader ctr(argv[1]);
	AssociationReader ar(argv[2]);
	CameraReader cr(argv[3]);

	KeyFrameParameters kfp;
	string depthTimeStamp;
	CameraParameters cp;

	cr.get_camera(cp);
	cout << "cx: " << cp.cx << " cy: " << cp.cy 
		 << " fx: " << cp.fx << " fy: " << cp.fy <<" scale: " << cp.scale << endl;

	/*for (size_t i = 0; i < ctr.data_size(); i++)
	{
		ctr.get_frame(i, kfp);
		ar.get_depth_timestamp(kfp.timeStamp, depthTimeStamp);
		
		
		cout <<"frame: " << i <<" "<<kfp.timeStamp<<" "
    				 			   <<kfp.x_c<<" "
    				               <<kfp.y_c<<" "
    				               <<kfp.z_c<<" "
    				               <<kfp.x<<" "
    				               <<kfp.y<<" "
    				               <<kfp.z<<" "
    				               <<kfp.w<<" " << endl;

		cout << "rgb: " << kfp.timeStamp << ".png "
			 << "depth: " << depthTimeStamp << ".png" << endl;

	}*/

	// show point cloud;

	string index = argv[4]; 

	ctr.get_frame(atoi(index.c_str()), kfp);
	ar.get_depth_timestamp(kfp.timeStamp, depthTimeStamp);
	cv::Mat rgb = cv::imread("../data/rgb/" + kfp.timeStamp + ".png");
	cv::Mat depth = cv::imread("../data/depth/" + depthTimeStamp + ".png", -1);

	PointCloud::Ptr cloud(new PointCloud);
	cloud = image2pointcloud(rgb, depth, cp);

	/*pcl::visualization::CloudViewer viewer("viewer");
	viewer.showCloud(cloud);
	while(!viewer.wasStopped())
	{

	}

	return 0;*/

	typedef Eigen::Transform<float, 3, Eigen::Affine> AffineTransformaion;
	typedef Eigen::Quaternion<float> Rotation;
	typedef Eigen::Translation<float, 3> Translation;

	AffineTransformaion T;
	T = Translation(kfp.x_c, kfp.y_c, kfp.z_c) * Rotation(kfp.w, kfp.x, kfp.y, kfp.z); // * Eigen::Scaling(1.0);

	PointCloud::Ptr tmp(new PointCloud);
	pcl::transformPointCloud(*cloud, *tmp, T);

	index = "0"; 

	ctr.get_frame(atoi(index.c_str()), kfp);
	ar.get_depth_timestamp(kfp.timeStamp, depthTimeStamp);
	rgb = cv::imread("../data/rgb/" + kfp.timeStamp + ".png");
	depth = cv::imread("../data/depth/" + depthTimeStamp + ".png", -1);

	PointCloud::Ptr cloud2(new PointCloud);

	cloud2 = image2pointcloud(rgb, depth, cp);
	*cloud2 += *tmp;

	pcl::visualization::CloudViewer viewer("viewer");
	viewer.showCloud(cloud2);
	while(!viewer.wasStopped())
	{

	}

	return 0;
}
