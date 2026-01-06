/*
*     _______ .__   __.   _______  __  .__   __.  _______  _______ .______         .______    __  .__   __.   _______
*    |   ____||  \ |  |  /  _____||  | |  \ |  | |   ____||   ____||   _  \        |   _  \  |  | |  \ |  |  /  _____|
*    |  |__   |   \|  | |  |  __  |  | |   \|  | |  |__   |  |__   |  |_)  |       |  |_)  | |  | |   \|  | |  |  __  
*    |   __|  |  . `  | |  | |_ | |  | |  . `  | |   __|  |   __|  |      /        |   ___/  |  | |  . `  | |  | |_ |
*    |  |____ |  |\   | |  |__| | |  | |  |\   | |  |____ |  |____ |  |\  \----.   |  |      |  | |  |\   | |  |__| |
*    |_______||__| \__|  \______| |__| |__| \__| |_______||_______|| _| `._____|   | _|      |__| |__| \__|  \______|
*                                                                                                                    
*/

#ifndef __L298N__H_
#define __L298N__H_
#include <Arduino.h>
#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

#define MOTOR_FORWARD 2U
#define MOTOR_REVERSE 1U
#define MOTOR_STOP    0U

#ifdef L298N_NUM
#define L298N_MOTOR_CHANNEL_MAX L298N_NUM*2U
#else
#define L298N_MOTOR_CHANNEL_MAX 2U
#endif

#ifndef uint8_t
typedef unsigned char uint8_t;
#endif

typedef void (*pinWirteFunc_t)(uint8_t,uint8_t);
typedef void (*pwmWirteFunc_t)(uint8_t,int);
typedef struct L298N_PinType{
    int pinNumA;
    int pinNumB;
    pinWirteFunc_t pinWirteFunc;
    int pwmNNum;
    pwmWirteFunc_t pwmWriteFunc;
}L298N_PinType_t;
extern L298N_PinType_t L298N_ChannelCfg[L298N_MOTOR_CHANNEL_MAX];

struct L298N_tag;

typedef uint8_t (*MotorControl_t)(struct L298N_tag* self,uint8_t rotation);
typedef uint8_t (*MotorSpeed_t)(struct L298N_tag* self,int speed);
typedef struct L298N_tag{
    L298N_PinType_t* PinCfg;
    MotorControl_t Control;
    MotorSpeed_t Speed;
}L298N_t;

extern L298N_t* L298N_Create(L298N_PinType_t* pinCfg);
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__L298N__H_*/