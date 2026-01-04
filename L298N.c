/*
*     _______ .__   __.   _______  __  .__   __.  _______  _______ .______         .______    __  .__   __.   _______
*    |   ____||  \ |  |  /  _____||  | |  \ |  | |   ____||   ____||   _  \        |   _  \  |  | |  \ |  |  /  _____|
*    |  |__   |   \|  | |  |  __  |  | |   \|  | |  |__   |  |__   |  |_)  |       |  |_)  | |  | |   \|  | |  |  __  
*    |   __|  |  . `  | |  | |_ | |  | |  . `  | |   __|  |   __|  |      /        |   ___/  |  | |  . `  | |  | |_ |
*    |  |____ |  |\   | |  |__| | |  | |  |\   | |  |____ |  |____ |  |\  \----.   |  |      |  | |  |\   | |  |__| |
*    |_______||__| \__|  \______| |__| |__| \__| |_______||_______|| _| `._____|   | _|      |__| |__| \__|  \______|
*                                                                                                                    
*/

#ifdef __cplusplus
extern "C"{
#endif
#include "stddef.h"
#include "L298N.h"

uint8_t L298N_MotorControl(L298N_t* instance,unsigned char rotation )
{
    if(instance == NULL)
    {
        return 1;
    }
    L298N_PinType_t* pinControl = instance->PinCfg;
    if(pinControl->pinWirteFunc == NULL)
    {
        return 1;
    }
    if(rotation == MOTOR_FORWARD)
    {
        pinControl->pinWirteFunc(pinControl->pinNumA,1);
        pinControl->pinWirteFunc(pinControl->pinNumB,0);
    }
    else if(rotation == MOTOR_REVERSE)
    {
        pinControl->pinWirteFunc(pinControl->pinNumA,0);
        pinControl->pinWirteFunc(pinControl->pinNumB,1);
    }
    else
    {
        pinControl->pinWirteFunc(pinControl->pinNumA,0);
        pinControl->pinWirteFunc(pinControl->pinNumB,0);
    }
    return 0;
}


uint8_t L298N_MotorSpeed(L298N_t* instance,float speed)
{

    L298N_PinType_t* pinControl = instance->PinCfg;
    if(pinControl->pwmWriteFunc == NULL)
    {
        return 1;
    }
    pinControl->pwmWriteFunc(pinControl->pwmNNum,speed);
    return 0;
}
static L298N_t L298N_Instances[L298N_MOTOR_CHANNEL_MAX];
static L298N_PinType_t L298N_pinCfg[L298N_MOTOR_CHANNEL_MAX];

L298N_t* L298N_Create(L298N_PinType_t* pinCfg)
{
    if(pinCfg == NULL)
    {
        return NULL;
    }
    static channel = 0;
    L298N_t* instance = &L298N_Instances[channel];
    instance->PinCfg = &L298N_pinCfg[channel];
    
    instance->PinCfg->pinNumA = pinCfg->pinNumA;
    instance->PinCfg->pinNumB = pinCfg->pinNumB;
    if (pinCfg->pinWirteFunc == NULL)
    {
        instance->PinCfg->pinWirteFunc = digitalWrite;
    }
    else
    {
        instance->PinCfg->pinWirteFunc = pinCfg->pinWirteFunc;
    }

    instance->PinCfg->pwmNNum = pinCfg->pwmNNum;
    if (pinCfg->pwmWriteFunc == NULL)
    {
        instance->PinCfg->pwmWriteFunc = analogWrite;
    }
    else
    {
        instance->PinCfg->pwmWriteFunc = pinCfg->pwmWriteFunc;
    }

    instance->Control = L298N_MotorControl;
    instance->Speed = L298N_MotorSpeed;

    channel++;
    return instance;
}


#ifdef __cplusplus
}
#endif