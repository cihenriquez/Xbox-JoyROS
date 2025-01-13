#ifndef _ROS_r3_dueInfo_h
#define _ROS_r3_dueInfo_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/time.h"

namespace r3
{

  class dueInfo : public ros::Msg
  {
    public:
      int32_t pwm_r3[4];
      float sens[10];
      typedef ros::Time _time_type;
      _time_type time;

    dueInfo():
      pwm_r3(),
      sens(),
      time()
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
      for( uint32_t i = 0; i < 10; i++){
      union {
        float real;
        uint32_t base;
      } u_sensi;
      u_sensi.real = this->sens[i];
      *(outbuffer + offset + 0) = (u_sensi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sensi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sensi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sensi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sens[i]);
      }
      *(outbuffer + offset + 0) = (this->time.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time.sec);
      *(outbuffer + offset + 0) = (this->time.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time.nsec);
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
      for( uint32_t i = 0; i < 10; i++){
      union {
        float real;
        uint32_t base;
      } u_sensi;
      u_sensi.base = 0;
      u_sensi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sensi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sensi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sensi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->sens[i] = u_sensi.real;
      offset += sizeof(this->sens[i]);
      }
      this->time.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->time.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->time.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->time.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->time.sec);
      this->time.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->time.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->time.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->time.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->time.nsec);
     return offset;
    }

    const char * getType(){ return "r3/dueInfo"; };
    const char * getMD5(){ return "aada8a9d25d5f72f38d4c59c6c9f7d8c"; };

  };

}
#endif
