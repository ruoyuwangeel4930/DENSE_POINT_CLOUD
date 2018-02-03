# include "pcloudcreator.h"
# include <string>

# include <Eigen/Core>
# include <Eigen/Geometry>

# include <pcl/filters/voxel_grid.h>
# include <pcl/filters/passthrough.h>

using namespace std;

typedef Eigen::Transform<float, 3, Eigen::Affine> AffineTransformaion;
typedef Eigen::Quaternion<float> Rotation;
typedef Eigen::Translation<float, 3> Translation;

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


    cout << "joining point cloud..." << endl;
    PointCloud::Ptr output(new PointCloud); // gobal map
    PointCloud::Ptr tmp(new PointCloud);
    //PointCloud::Ptr newCloud;

    pcl::VoxelGrid<PointT> voxel;
    pcl::PassThrough<PointT> pass;

    pass.setFilterFieldName("z");
    pass.setFilterLimits(0.0, 40.0);

    voxel.setLeafSize(0.01, 0.01, 0.01);

    cv::Mat rgb, depth;

    AffineTransformaion T;

    for (size_t i = 0; i < ctr.data_size(); i++)
    {
    	ctr.get_frame(i, kfp);
		ar.get_depth_timestamp(kfp.timeStamp, depthTimeStamp);
		rgb = cv::imread("../data/rgb/" + kfp.timeStamp + ".png");
		depth = cv::imread("../data/depth/" + depthTimeStamp + ".png", -1);

		T = Translation(kfp.x_c, kfp.y_c, kfp.z_c) * Rotation(kfp.w, kfp.x, kfp.y, kfp.z);

		tmp = image2pointcloud(rgb, depth, cp);

		// filter
		pass.setInputCloud(tmp);
		pass.filter(*tmp);

		// add to global map
		pcl::transformPointCloud(*tmp, *tmp, T);

		*output += *tmp;

		tmp->clear();

		cout << "rgb: " << kfp.timeStamp << " depth: " << depthTimeStamp << " joined!" << endl;
	}

	voxel.setInputCloud(output);
	voxel.filter(*output);

	pcl::visualization::CloudViewer viewer("viewer");
	viewer.showCloud(output);
	while(!viewer.wasStopped())
	{

	}

	pcl::io::savePCDFile("pointcloud.pcd", *output);

	cout << "pointcloud.pcd is saved." << endl;

	output->clear();
	
	return 0;
}