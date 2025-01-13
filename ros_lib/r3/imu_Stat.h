#ifndef _ROS_r3_imu_Stat_h
#define _ROS_r3_imu_Stat_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace r3
{

  class imu_Stat : public ros::Msg
  {
    public:
      typedef int8_t _gyroStat_type;
      _gyroStat_type gyroStat;
      typedef int8_t _accelStat_type;
      _accelStat_type accelStat;
      typedef int8_t _inclStat_type;
      _inclStat_type inclStat;

    imu_Stat():
      gyroStat(0),
      accelStat(0),
      inclStat(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_gyroStat;
      u_gyroStat.real = this->gyroStat;
      *(outbuffer + offset + 0) = (u_gyroStat.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->gyroStat);
      union {
        int8_t real;
        uint8_t base;
      } u_accelStat;
      u_accelStat.real = this->accelStat;
      *(outbuffer + offset + 0) = (u_accelStat.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->accelStat);
      union {
        int8_t real;
        uint8_t base;
      } u_inclStat;
      u_inclStat.real = this->inclStat;
      *(outbuffer + offset + 0) = (u_inclStat.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->inclStat);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_gyroStat;
      u_gyroStat.base = 0;
      u_gyroStat.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->gyroStat = u_gyroStat.real;
      offset += sizeof(this->gyroStat);
      union {
        int8_t real;
        uint8_t base;
      } u_accelStat;
      u_accelStat.base = 0;
      u_accelStat.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->accelStat = u_accelStat.real;
      offset += sizeof(this->accelStat);
      union {
        int8_t real;
        uint8_t base;
      } u_inclStat;
      u_inclStat.base = 0;
      u_inclStat.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->inclStat = u_inclStat.real;
      offset += sizeof(this->inclStat);
     return offset;
    }

    const char * getType(){ return "r3/imu_Stat"; };
    const char * getMD5(){ return "8957f391600c9ff690855ba91295c3ca"; };

  };

}
#endif
