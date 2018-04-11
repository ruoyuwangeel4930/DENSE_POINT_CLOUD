#include <cloudbuilder.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/common/transforms.h>

using namespace std;

dec::CloudBuilder::CloudBuilder(const string traj_fname, const string assoc_fname, const string cam_fname)
{
    ifstream ftraj;
    ftraj.open(traj_fname.c_str());
    while(!ftraj.eof())
    {
        string str;
        getline(ftraj, str);
        if(!str.empty())
        {
            stringstream ss;
            ss << str;
            double tstamp;
            ss >> tstamp;
            this->kf_tstamp.push_back(tstamp);
            dec::SE3 se3;
            ss >> se3.tx;
            ss >> se3.ty;
            ss >> se3.tz;
            ss >> se3.x;
            ss >> se3.y;
            ss >> se3.z;
            ss >> se3.w;
            this->vSE3.push_back(se3);
        }
    }
    ftraj.close();

    ifstream fassoc;
    fassoc.open(assoc_fname.c_str());
    while(!fassoc.eof())
    {
        string str;
        getline(fassoc, str);
        if(!str.empty())
        {
            stringstream ss;
            ss << str;
            double tstamp;
            string fname;
            ss >> tstamp;
            this->rgb_tstamp.push_back(tstamp);
            ss >> fname;
            this->rgb_fname.push_back(fname);
            ss >> tstamp;
            this->dep_tstamp.push_back(tstamp);
            ss >> fname;
            this->dep_fname.push_back(fname);
        }
    }
    fassoc.close();

    ifstream fcam;
    fcam.open(cam_fname.c_str());
    while(!fcam.eof())
    {
        string str;
        vector<string> params;
        getline(fcam, str);
        if (str[0] == '#' || str[0] == '%' || str == "")
            continue;
        boost::split(params, str, boost::is_any_of(":"));
        boost::trim(params[0]);
        boost::trim(params[1]);
        this->parameters[params[0]] = params[1];
    }
    fcam.close();

    this->cam.cx = atof(this->parameters["Camera.cx"].c_str());
    this->cam.cy = atof(this->parameters["Camera.cy"].c_str());
    this->cam.fx = atof(this->parameters["Camera.fx"].c_str());
    this->cam.fy = atof(this->parameters["Camera.fy"].c_str());
    this->cam.scale = atof(this->parameters["DepthMapFactor"].c_str());
}

dec::PointCloud::Ptr dec::CloudBuilder::image2pointcloud(const cv::Mat& rgb, const cv::Mat& depth)
{
    dec::PointCloud::Ptr cloud(new dec::PointCloud);
    ushort d; // depth value
    dec::PointT p; // point

    for (int m=0; m < depth.rows; m++)
        for(int n=0; n < depth.cols; n++)
        {
            d = depth.ptr<ushort>(m)[n];

            if (d == 0)
                continue;

            // calculate coords of p
            p.z = double(d) / this->cam.scale;
            p.x = (n - this->cam.cx) * p.z / this->cam.fx;
            p.y = (m - this->cam.cy) * p.z / this->cam.fy; 

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

dec::PointCloud::Ptr dec::CloudBuilder::buildPointCloud(const float near, const float far, const float leaf_sz, const int start, const int end, const int step)
{
    map<double, string> rgbt2rgbfname;
    map<double, string> rgbt2depfname;

    for (size_t i = 0; i < this->rgb_tstamp.size(); ++i)
    {
        rgbt2rgbfname[rgb_tstamp[i]] = this->rgb_fname[i];
        rgbt2depfname[rgb_tstamp[i]] = this->dep_fname[i];
    }

    dec::PointCloud::Ptr final_map(new dec::PointCloud);
    dec::PointCloud::Ptr tmp_map(new dec::PointCloud);
    
    pcl::PassThrough<dec::PointT> pass;
    pcl::VoxelGrid<dec::PointT> voxel;
    pass.setFilterFieldName("z");
    pass.setFilterLimits(near, far);
    voxel.setLeafSize(leaf_sz, leaf_sz, leaf_sz);

    for (size_t i = start; i < end; i+=step)
    {
        cv::Mat rgb = cv::imread(rgbt2rgbfname[kf_tstamp[i]]);
        cv::Mat dep = cv::imread(rgbt2depfname[kf_tstamp[i]], -1);

        dec::PointCloud::Ptr kf_map(new dec::PointCloud);
        kf_map = this->image2pointcloud(rgb, dep);

        dec::PointCloud::Ptr kf_map_filtered(new dec::PointCloud);
        pass.setInputCloud(kf_map);
        pass.filter(*kf_map_filtered);
        kf_map->clear();

        dec::SE3 se3 = this->vSE3[i];
        dec::Affine pose;
        dec::Trans trans = dec::Trans(se3.tx, se3.ty, se3.tz);
        dec::Rot rot = dec::Rot(se3.w, se3.x, se3.y, se3.z);
        pose = trans * rot;
        dec::PointCloud::Ptr kf_map_transformed(new dec::PointCloud);
        pcl::transformPointCloud(*kf_map_filtered, *kf_map_transformed, pose);
        kf_map_filtered->clear();

        *tmp_map += *kf_map_transformed;
        kf_map_transformed->clear();
        std::cout << "keyframe [" << rgbt2rgbfname[kf_tstamp[i]] << " " << rgbt2depfname[kf_tstamp[i]] <<"] is registered." << std::endl; 
    }

    voxel.setInputCloud(tmp_map);
    voxel.filter(*final_map);
    tmp_map->clear();

    return final_map;
}