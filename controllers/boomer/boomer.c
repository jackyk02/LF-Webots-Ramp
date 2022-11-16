#include <stdio.h>
#include <string.h>
#include <webots/keyboard.h>
#include <webots/motor.h>
#include <webots/robot.h>

// to be used as array indices
enum { X, Y, Z };

// This needs to be changed if the .wbt model changes
#define FRONT_WHEEL_RADIUS 0.38

// devices
WbDeviceTag left_steer, right_steer;
WbDeviceTag left_front_wheel, right_front_wheel;

// misc variables
int time_step = -1;
double speed = 0.0;
double steering_angle = 0.0;
double manual_steering = 0.0;

void print_help() {
  printf("You can drive this vehicle!\n");
  printf("Select the 3D window and then use the cursor keys to:\n");
  printf("[LEFT]/[RIGHT] - steer\n");
  printf("[UP]/[DOWN] - accelerate/slow down\n");
}

// positive: turn right, negative: turn left
void set_steering_angle(double wheel_angle) {
  steering_angle = wheel_angle;
  wb_motor_set_position(left_steer, steering_angle);
  wb_motor_set_position(right_steer, steering_angle);
}

void change_manual_steer_angle(double inc) {
  double new_manual_steering = manual_steering + inc;
  printf("steer %f\n", new_manual_steering);
  if (new_manual_steering <= 0.94 && new_manual_steering >= -0.94) {
    manual_steering = new_manual_steering;
    set_steering_angle(manual_steering);
  }

  if (manual_steering == 0)
    printf("going straight\n");
  else
    printf("turning %.2f rad (%s)\n", steering_angle, steering_angle < 0 ? "left" : "right");
}

int main(int argc, char **argv) {
  wb_robot_init();

  time_step = (int)wb_robot_get_basic_time_step();

  // find wheels
  left_front_wheel = wb_robot_get_device("left wheel motor");
  right_front_wheel = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_front_wheel, INFINITY);
  wb_motor_set_position(right_front_wheel, INFINITY);
  wb_motor_set_velocity(left_front_wheel, 3.1);
  wb_motor_set_velocity(right_front_wheel, 3.1);
  printf("You are driving this vehicle!\n");
  
  while (wb_robot_step(time_step) != -1) {
    wb_motor_set_velocity(left_front_wheel, speed);
    wb_motor_set_velocity(right_front_wheel, speed);
    speed=speed+1;
    if(speed>10){
      speed=10;
    }
  }
 
  /* get steering motors
  left_steer = wb_robot_get_device("left_steer");
  right_steer = wb_robot_get_device("right_steer");
  // start engine
  set_speed(-1.0);  // km/h
  print_help();
  // allow to switch to manual control
  wb_keyboard_enable(time_step);

  // main loop
  while (wb_robot_step(time_step) != -1) {
    // get user input
    check_keyboard();

    // read sensors
    // const unsigned char *camera_image = wb_camera_get_image(camera);
    // const float *sick_data = wb_lidar_get_range_image(sick);

    // update stuff
  }

  wb_robot_cleanup();

  return 0;  // ignored */
}