#include <cassert>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>


#include <conio.h> 
#include <cstdio>   

#include <chrono>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/Header.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Accel.h>
#include <sensor_msgs/Joy.h>

#include <winsock2.h>
#include <windows.h>
#include <iphlpapi.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <Xinput.h>



#pragma comment(lib, "Xinput.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")


double ros_period = 15;


using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main( int argc, char* argv[] )
{

    ////////////////// ROS ///////////////

    sensor_msgs::Joy joy_msg;
    std_msgs::String joy_status;
    ros::NodeHandle nh;


    char ros_master[] = "localhost:11411"; //"192.168.127.111:11411";

    std::cout << "Connecting to server at " << ros_master << std::endl;
    nh.initNode(ros_master);




    XINPUT_BATTERY_INFORMATION joy_battery;
    XINPUT_STATE state;
    DWORD dwLastPacketNumber = 0;
    DWORD dwStartTime = GetTickCount64();

    joy_msg.axes_length = 6;
    joy_msg.axes = new float[joy_msg.axes_length];
    joy_msg.buttons_length = 12;
    joy_msg.buttons = new int32_t[joy_msg.buttons_length];


    ros::Publisher joy_pub("joystick", &joy_msg);
    ros::Publisher joy_status_pub("joystick_status", &joy_status);

    nh.advertise(joy_pub);
    nh.advertise(joy_status_pub);
    nh.spinOnce();

    std::cout << "Joystick running!\n";


    auto t1 = high_resolution_clock::now();



    while (!_kbhit())
    {
        t1 = high_resolution_clock::now();


        DWORD result = XInputGetState(0, &state);


        if (result != ERROR_SUCCESS)
        {
            joy_msg.axes[0] = 0;
            joy_msg.axes[1] = 0;
            joy_msg.axes[2] = 0;
            joy_msg.axes[3] = 0;
            joy_msg.axes[4] = 0;
            joy_msg.axes[5] = 0;
            joy_msg.buttons[0] = 0;
            joy_msg.buttons[1] = 0;
            joy_msg.buttons[2] = 0;
            joy_msg.buttons[3] = 0;
            joy_msg.buttons[4] = 0;
            joy_msg.buttons[5] = 0;
            joy_msg.buttons[6] = 0;
            joy_msg.buttons[7] = 0;
            joy_msg.buttons[8] = 0;
            joy_msg.buttons[9] = 0;
            joy_msg.buttons[10] = 0;
            joy_msg.buttons[11] = 0;
            joy_status.data = "Disconnected";
            
        }
        else
        {
            DWORD result_battery = XInputGetBatteryInformation(0, BATTERY_DEVTYPE_GAMEPAD, &joy_battery);

            if (joy_battery.BatteryLevel == BATTERY_LEVEL_LOW) {
                joy_status.data = "Low battery";
            }
            else if (joy_battery.BatteryLevel == BATTERY_LEVEL_MEDIUM) {
                joy_status.data = "Medium battery";
            }
            else if (joy_battery.BatteryLevel == BATTERY_LEVEL_FULL) {
                joy_status.data = "Full battery";
            }
            else if (joy_battery.BatteryLevel == BATTERY_LEVEL_EMPTY) {
                joy_status.data = "Empty battery";
            }

            joy_msg.axes[0] = state.Gamepad.sThumbLX / 32767.0;
            joy_msg.axes[1] = state.Gamepad.sThumbLY / 32767.0;
            joy_msg.axes[2] = state.Gamepad.sThumbRX / 32767.0;
            joy_msg.axes[3] = state.Gamepad.sThumbRY / 32767.0;
            joy_msg.axes[4] = state.Gamepad.bLeftTrigger / 255.0;
            joy_msg.axes[5] = state.Gamepad.bRightTrigger / 255.0;

            joy_msg.buttons[0] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) ? 1 : 0;
            joy_msg.buttons[1] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) ? 1 : 0;
            joy_msg.buttons[2] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) ? 1 : 0;
            joy_msg.buttons[3] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) ? 1 : 0;
            joy_msg.buttons[4] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? 1 : 0;
            joy_msg.buttons[5] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? 1 : 0;
            joy_msg.buttons[6] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) ? 1 : 0;
            joy_msg.buttons[7] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) ? 1 : 0;
            joy_msg.buttons[8] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? 1 : 0;
            joy_msg.buttons[9] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? 1 : 0;

            joy_msg.buttons[10] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? 1 : ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? -1 : 0);
            joy_msg.buttons[11] = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) ? 1 : ((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? -1 : 0);

        }


        joy_pub.publish(&joy_msg);
        joy_status_pub.publish(&joy_status);


        nh.spinOnce();


        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        while (ms_double.count() < ros_period) {
            t2 = high_resolution_clock::now();
            ms_double = t2 - t1;

        }

        //std::cout << ms_double.count() << "ms\n";
    }
    joy_msg.axes[0] = 0;
    joy_msg.axes[1] = 0;
    joy_msg.axes[2] = 0;
    joy_msg.axes[3] = 0;
    joy_msg.axes[4] = 0;
    joy_msg.axes[5] = 0;
    joy_msg.buttons[0] = 0;
    joy_msg.buttons[1] = 0;
    joy_msg.buttons[2] = 0;
    joy_msg.buttons[3] = 0;
    joy_msg.buttons[4] = 0;
    joy_msg.buttons[5] = 0;
    joy_msg.buttons[6] = 0;
    joy_msg.buttons[7] = 0;
    joy_msg.buttons[8] = 0;
    joy_msg.buttons[9] = 0;
    joy_msg.buttons[10] = 0;
    joy_msg.buttons[11] = 0;
    joy_pub.publish(&joy_msg);
    joy_status.data = "Disconnected";
    joy_status_pub.publish(&joy_status);
    nh.spinOnce();
    std::cout << "Bye ROS..." << std::endl;
}