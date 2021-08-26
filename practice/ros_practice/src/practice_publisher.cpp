#include "ros/ros.h"
#include "ros_practice/MsgPractice.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "practice_publisher");
	ros::NodeHandle nh;

	ros::Publisher practice_pub = nh.advertise<ros_practice::MsgPractice>("ros_practice_msg", 100);

	ros::Rate  loop_rate(10);

	ros_practice::MsgPractice msg;
	int cnt = 0;

	while(ros::ok())
	{
		msg.stamp = ros::Time::now();
		msg.data = cnt;

		ROS_INFO("send msg = %d", msg.stamp.sec);
		ROS_INFO("send msg = %d", msg.stamp.nsec);
		ROS_INFO("send msg = %d", msg.data);

		practice_pub.publish(msg);

		loop_rate.sleep();

		++cnt;

	}
	return 0;
}
