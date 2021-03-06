#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>


using namespace std;

struct termios cooked;

class Reader {

public:
	Reader();
	void enableRawMode(); //change console from cooked to raw mode
	void disableRawMode(); //change console from raw mode back to cooked mode
};
void Reader::disableRawMode(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &cooked); //set the console back to how it was
}
void Reader::enableRawMode() {
	tcgetattr(STDIN_FILENO, &cooked); //save current console config to cooked struct
	struct termios raw = cooked; //copy struct for modifying
	raw.c_lflag &= ~(ECHO | ICANON); //disable echo and canonic mode
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); //set console to raw config
}

Reader::Reader(){
	enableRawMode();
}



Reader input;

class KeyboardPublisher {

public:
	KeyboardPublisher();
	void keyLoop(); //loop to read keys
private:
	ros::NodeHandle n;
  	double linear, angular;
  	ros::Publisher twist_pub;

};

KeyboardPublisher::KeyboardPublisher(): linear(0), angular(0) {
	twist_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1); //set up broadcaster on the cmd_vel topic
}

void KeyboardPublisher::keyLoop() {
	char c;
	bool changed = false; //bool to keep track of it new key has been pressed

	cout << "Reading from keyboard" << endl;
	cout << "Use arrow keys to control robot" << endl;
	cout << "Press 'q' to quit" << endl;
	
	//will read byte by byte until q is pressed or EOF
	while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){
		if(c == '\x1b'){ //if c is an escape character
			char arr[2];
			read(STDIN_FILENO, &arr[0], 1); //read first byte, which will be a bracket
			read(STDIN_FILENO, &arr[1], 1);	//read second byte, which will be A,B,C, or D
			c = arr[1]; //we want to use the second byte so assign it to c
		}

		angular=linear=0; //reset to 0 else previous key will effect new key

		switch(c) { //depending on which arrow key pressed, angular/linear assigned
			case 'a':
				ROS_DEBUG("left");
				angular = -1.0;
				changed = true;
				break;
			case 'd':
				ROS_DEBUG("right");
				angular = 1.0;
				changed = true;
				break;
			case 'w':
				ROS_DEBUG("up");
				linear = 1.0;
				changed = true;
				break;
			case 's':
				ROS_DEBUG("stop");
				linear = 0.0;
				changed = true;
				break;	
                        case 'x':
				ROS_DEBUG("down");
				linear = -1.0;
				changed = true;
				break;	
		}
		geometry_msgs::Twist msg; //twist object to be published
		msg.angular.z = angular; //assigning angular to the twist
		msg.linear.x = linear;  //assigning linear to the twist
		if(changed){ //if new key pressed, update published twist
			twist_pub.publish(msg); //publish the twist object
			changed = false; //reset to false
		}
	}
	return;
}



void quit(int sig) { //function to be executed at exit
  	(void)sig;
  	input.disableRawMode();
 	ros::shutdown();
  	exit(0);
}

int main(int argc, char** argv) {
  	ros::init(argc, argv, "keymove_publisher");
  	KeyboardPublisher keyboard_publisher;

  	signal(SIGINT,quit); //assign quit() to be run if SIGINT signal is sent (CTRL-C)

  	keyboard_publisher.keyLoop();
  	quit(0);
  
 	return(0);
}



