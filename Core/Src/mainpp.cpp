#include <mainpp.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>

// Node:
ros::NodeHandle nh;
float vels[8];
// Publisher:
int velocityflag = 0;
int i = 0;
std_msgs::Int16 incmsg;
ros::Publisher increment("increment", &incmsg);

// Subscriber:
void vel_cb(const std_msgs::String& msg) {
	const char *tempstr = msg.data;
	char *ikstr = strdup(tempstr);  // Create a copy to preserve the original string
	char *pt;

	int i = 0;

	pt = strtok(ikstr, ",");
	while (pt != NULL) {
		float a = atof(pt);
		vels[i++] = a;
		pt = strtok(NULL, ",");
	}

	free(ikstr);  // Free the memory allocated by strdup
	velocityflag = 1;
    nh.loginfo("Message Received");
//  float a = strtof(ikstr, &split);

}

ros::Subscriber<std_msgs::String> speed_sub("ikstring", &vel_cb);

// Setup node:
void setup(void)
{
  TIM1->CCR1 = 50;
  TIM1->CCR2 = 50;
  TIM1->CCR3 = 50;
  TIM1->CCR4 = 50;
  TIM3->CCR1 = 50;
  TIM3->CCR2 = 50;
  TIM3->CCR3 = 50;
  TIM3->CCR4 = 50;
  TIM4->CCR1 = 50;
  TIM4->CCR2 = 50;
  TIM4->CCR3 = 50;
  TIM4->CCR4 = 50;
  TIM8->CCR1 = 50;
  TIM8->CCR2 = 50;
  TIM8->CCR3 = 50;
  TIM8->CCR4 = 50;
  nh.initNode();
  nh.advertise(increment);
  nh.subscribe(speed_sub);
}

// Loop:
void loop(void) {
  // Publish message:
  incmsg.data = i;
  increment.publish(&incmsg);
  nh.spinOnce();
//FRONT RIGHT
  if (vels[0] >= 0)
  {
	  TIM1 -> CCR1 = vels[0] * 100;
	  TIM1 -> CCR2 = 0;
  }
  else if (vels[0] < 0)
  {
	  TIM1 -> CCR1 = 0;
	  TIM1 -> CCR2 = vels[0] * -100;
  }
//FRONT LEFT
  if (vels[1] >= 0)
  {
	  TIM1 -> CCR3 = vels[1] * 100;
	  TIM1 -> CCR4 = 0;
  }
  else if (vels[1] < 0)
  {
	  TIM1 -> CCR3 = 0;
	  TIM1 -> CCR4 = vels[1] * -100;
  }
//REAR LEFT
  if (vels[2] >= 0)
  {
	  TIM3 -> CCR1 = vels[0] * 100;
	  TIM3 -> CCR2 = 0;
  }
  else if (vels[2] < 0)
  {
	  TIM3 -> CCR1 = 0;
	  TIM3 -> CCR2 = vels[0] * -100;
  }
//REAR RIGHT
  if (vels[3] >= 0)
  {
	  TIM3 -> CCR3 = vels[0] * 100;
	  TIM3 -> CCR4 = 0;
  }
  else if (vels[3] < 0)
  {
	  TIM3 -> CCR3 = 0;
	  TIM3 -> CCR4 = vels[0] * -100;
  }
  i++;
  HAL_Delay(50);
}
