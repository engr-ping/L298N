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

#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/
#include <Arduino.h>
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
typedef void (*pwmWirteFunc_t)(uint8_t,float);
typedef struct L298N_PinType{
    int pinNumA;
    int pinNumB;
    pinWirteFunc_t pinWirteFunc;
    int pwmNNum;
    pwmWirteFunc_t pwmWriteFunc;
}L298N_PinType_t;
extern L298N_PinType_t L298N_ChannelCfg[L298N_MOTOR_CHANNEL_MAX];
typedef uint8_t (*MotorControl_t)(void*,uint8_t);
typedef uint8_t (*MotorSpeed_t)(void*,float);
typedef struct{
    L298N_PinType_t* PinCfg;
    MotorControl_t Control;
    MotorSpeed_t Speed;
}L298N_t;


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__L298N__H_*/