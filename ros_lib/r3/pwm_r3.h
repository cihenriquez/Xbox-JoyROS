#ifndef _ROS_r3_pwm_r3_h
#define _ROS_r3_pwm_r3_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace r3
{

  class pwm_r3 : public ros::Msg
  {
    public:
      int32_t pwm_r3[4];

    pwm_r3():
      pwm_r3()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pwm_r3i;
      u_pwm_r3i.real = this->pwm_r3[i];
      *(outbuffer + offset + 0) = (u_pwm_r3i.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pwm_r3i.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pwm_r3i.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pwm_r3i.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pwm_r3[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_pwm_r3i;
      u_pwm_r3i.base = 0;
      u_pwm_r3i.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pwm_r3i.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pwm_r3i.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pwm_r3i.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pwm_r3[i] = u_pwm_r3i.real;
      offset += sizeof(this->pwm_r3[i]);
      }
     return offset;
    }

    const char * getType(){ return "r3/pwm_r3"; };
    const char * getMD5(){ return "05e66db73a14768fc093f08fc6c7dedc"; };

  };

}
#endif
