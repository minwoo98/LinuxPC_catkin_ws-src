#include "ros/ros.h"
#include "ros_practice/MsgPractice.h"

void msgCallback(const ros_practice::MsgPractice::ConstPtr& msg)
{
	ROS_INFO("recieve msg = %d", msg->stamp.sec);
	ROS_INFO("recieve msg = %d", msg->stamp.nsec);
	ROS_INFO("recieve msg = %d", msg->data);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "practice_subscriber");
	ros::NodeHandle nh;

	ros::Subscriber practice_sub = nh.subscribe("ros_practice_msg", 100, msgCallback);

	ros::spin();

	return 0;
}
