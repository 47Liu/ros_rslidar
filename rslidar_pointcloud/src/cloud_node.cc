/*
 *  Copyright (C) 2012 Austin Robot Technology, Jack O'Quin
 *  Copyright (C) 2016 Robosense, Tony Zhang
 *  License: Modified BSD Software License Agreement
 *
 *  $Id$
 */

/** \file

    This ROS node converts raw RSLIDAR LIDAR packets to PointCloud2.

*/
#include "convert.h"

/** Main node entry point. */
int main(int argc, char** argv)
{
  ros::init(argc, argv, "cloud_node");
  ros::NodeHandle node;
  ros::NodeHandle priv_nh("~");

  // create conversion class, which subscribes to raw data
  rslidar_pointcloud::Convert conv(node, priv_nh);//processScan调用unpack来解析收到的LIDAR scan packets，并将解析后的数据
                                                  //封成PointCloud2 message发送出去
  // handle callbacks until shut down
  ros::spin();

  return 0;
}
