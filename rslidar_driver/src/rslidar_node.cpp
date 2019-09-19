/*
 *  Copyright (C) 2012 Austin Robot Technology, Jack O'Quin
 *	Copyright (C) 2017 Robosense, Tony Zhang
 *
 *  License: Modified BSD Software License Agreement
 *
 *  $Id$
 */
//ROS系统中激光雷达的底层驱动，通过socket或pcap文件直接读取雷达数据。 
/** \file
 *
 *  ROS driver node for the Robosense 3D LIDARs.
 */
#include <ros/ros.h>
#include "rsdriver.h"
#include "std_msgs/String.h"

using namespace rslidar_driver;
volatile sig_atomic_t flag = 1;

static void my_handler(int sig)
{
  flag = 0;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "rsdriver");
  ros::NodeHandle node;
  ros::NodeHandle private_nh("~");

  signal(SIGINT, my_handler);

  // start the driver
  rslidar_driver::rslidarDriver dvr(node, private_nh);
  // loop until shut down or end of file
  while (ros::ok() && dvr.poll())//poll（）位于rsdriver.cpp中，该文件中调用了getPacket来将UDP数据包中的数据存到
  {                              //LIDAR packet里面，随后在poll里将多个LIDAR packet封装成LIDAR scan packets
    ros::spinOnce();             //需要注意的是，LIDAR packet里的时间戳是由ROS系统时间所指示的getPacket函数运行中间时刻，
  }                              //而LIDAR scan packets里的时间戳则是最后一个LIDAR packet的时间戳

  return 0;
}
