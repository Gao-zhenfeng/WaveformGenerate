#ifndef _MODE_H_
#define _MODE_H_
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
/************************************************************************
 *  @fn     void delay(float time)
 *  @brief  延时函数，用于生成小脉宽，time : 1 us ~ 0.1 s
 *  @param  float time				延时的时间
 ************************************************************************/
void delay(float time);

/************************************************************************
 *  @fn     timer(float time)
 *  @brief  定时函数，用于计算较长时间
 *  @param  float time				时间
 *  @param  int   index				定时器编号
 *
 ************************************************************************/
void setTimer(float time, int index);

/************************************************************************
 *  @fn     getTimer(int index)
 *  @brief  定时函数，用于读取计时器进行时间
 *  @param  int   index				定时器编号
 *  @return 如果计时器未结束，返回已进行时间。 若结束返回0
 *
 ************************************************************************/
float getTimer(int index);

/************************************************************************
 *  @fn     setVoltage(float voltage)
 *  @brief  IO口输出电压
 *  @param  float voltage			输出电压
 ************************************************************************/
void setVoltage(float voltage);

/************************************************************************
 *  @fn     void generatePulse(float period, int pulseWidth, float amplitude, int flag);
 *  @brief  产生一个周期的脉冲波形，整体波形的最小单位
 *  @param  float period				脉冲周期
 *  @param  int pulseWidth				脉宽, 0 ~ 100us
 *  @param  float amplitude			    脉冲幅值
 *  @param  int flag					标志位： flag = 0, 产生单向脉冲； flag = 1, 产生双向脉冲
 *
 ************************************************************************/
void generatePulse(float period, float pulseWidth, float amplitude, int flag);

/************************************************************************
 *  @fn     void basicUnit(float period, float envelopWidth, float blankTime, int intensity, float amplitude[])
 *  @brief  该函数是描述敲模式的模板，对该模板进行传参、循环可以复现敲模式的波形
 *			同时，该模板用于敲、脚底、肩颈、上臂、腰、小腿
 *  @param  float period				脉冲周期
 *  @param  float envelopWidth			包络脉宽/持续时间
 *  @param  float blankTime				空闲时间
 *  @param  int intensity				强度，1 ~ 10。强度会影响脉冲周期和幅值
 *  @param  float amplitude[]			脉冲幅值, 包含峰值和幅值
 *
 ************************************************************************/
void basicUnit(float period, float envelopWidth, float blankTime, int intensity, float amplitude[]);

/************************************************************************
 *  @fn     void basicUnit2(float period, float envelopWidth, float blankTime, int intensity, float amplitude[])
 *  @brief  该函数是描述按模式的模板，对该模板进行传参、循环可以复现敲模式的波形
 *			同时，该模板用于按、揉、肩颈、上臂、腰
 *  @param  float period				脉冲周期
 *  @param  float envelopWidth			包络脉宽/持续时间
 *  @param  float blankTime				空闲时间
 *  @param  int intensity				强度，1  ~ 10。强度会影响脉冲周期和幅值
 *  @param  float amplitude[]			脉冲幅值，峰值和幅值
 *
 ************************************************************************/
void basicUnit2(float period, float envelopWidth, float blankTime, int intensity, float amplitude[]);

/************************************************************************
 *  @fn     void basicUnitLeg1(float period, int intensity, float amplitude)
 *  @brief  该函数是描述小腿模式的模板，小腿模式分为三部分， 新模式1、新模式2、敲
 *			此处为描述新模式1的模板
 *  @param  float period				脉冲周期
 *  @param  int intensity				强度，1  ~ 10。强度会影响脉冲周期和幅值
 *  @param  float amplitude				脉冲幅值
 *
 ************************************************************************/
void basicUnitLeg1(float period, int intensity, float amplitude);

/************************************************************************
 *  @fn     basicUnitLeg2(float period, float envelopWidth, int intensity, float amplitude, int flag);
 *  @brief  该函数是描述小腿模式的模板，小腿模式分为三部分， 新模式1、新模式2、敲
 *			此处为描述新模式2的模板
 *  @param  float period				脉冲周期
 *  @param  float envelopWidth			包络脉宽/持续时间
 *  @param  float blankTime				空闲时间
 *  @param  int intensity				强度，1  ~ 10。强度会影响脉冲周期和幅值
 *  @param  float amplitude				脉冲幅值
 *	@param  int flag					标志位： flag = 0, 在该模板内幅值递减； flag = 1, 递增
 *
 ************************************************************************/
void basicUnitLeg2(float period, float envelopWidth, int intensity, float amplitude, int flag);

/************************************************************************
 *  @fn     basicUnitShoulder1(float period, float envelopWidth, float blankTime, int intensity, float amplitude);
 *  @brief  该函数是描述肩颈模式的模板，肩颈模式分为三部分， 新模式1、新模式2、敲
 *			此处为描述新模式1的模板，新模式1由两部分组成，第一部分脉宽不变，第二部分类似于basicUint2(按模式)
 *			该函数只描述新模式1的第一部分
 *  @param  float period				脉冲周期
 *  @param  float envelopWidth			包络脉宽/持续时间
 *  @param  float blankTime				空闲时间
 *  @param  int intensity				强度，1  ~ 10。强度会影响脉冲周期和幅值
 *  @param  float amplitude				脉冲幅值
 *
 ************************************************************************/
void basicUnitShoulder1(float period, float envelopWidth, float blankTime, int intensity, float amplitude);

/************************************************************************
 *  @fn     void basicUnitShoulder2(float period,  int intensity, float amplitude)
 *  @brief  该函数是描述肩颈模式的模板，肩颈模式分为三部分， 新模式1、新模式2、敲
 *			此处为描述新模式2的模板
 *  @param  float period				脉冲周期
 *  @param  int intensity				强度，1  ~ 10。强度会影响脉冲周期和幅值
 *  @param  float amplitude				脉冲幅值
 *
 ************************************************************************/
void basicUnitShoulder2(float period, int intensity, float amplitude);

/************************************************************************
 *  @fn     void qiao(int intensity)
 *  @brief  该函数生成敲模式的波形
 *  @param  int intensity				强度，1  ~ 10。强度会影响脉冲周期和幅值
 *
 ************************************************************************/
void qiao(int intensity);

/************************************************************************
 *  @fn     void an(int intensity)
 *  @brief  该函数生成按模式的波形
 *  @param  int intensity				强度，1  ~ 10。强度会影响脉冲周期和幅值
 *
 ************************************************************************/
void an(int intensity);

/************************************************************************
 *  @fn     void rou(int intensity)
 *  @brief  该函数生成揉模式的波形
 *  @param  int intensity				强度，1  ~ 10。强度会影响脉冲周期和幅值
 *
 ************************************************************************/
void rou(int intensity);

/************************************************************************
 *  @fn     void jianjing(int intensity)
 *  @brief  该函数生成肩颈模式的波形
 *  @param  int intensity				强度，1  ~ 10。强度会影响脉冲周期和幅值
 *
 ************************************************************************/
void jianjing(int intensity);

/************************************************************************
 *  @fn     void shangbi(int intensity)
 *  @brief  该函数生成上臂模式的波形
 *  @param  int intensity				强度，1  ~ 10。强度会影响脉冲周期和幅值
 *
 ************************************************************************/
void shangbi(int intensity);

/************************************************************************
 *  @fn     void yao(int intensity)
 *  @brief  该函数生成腰模式的波形
 *  @param  int intensity				强度，1  ~ 10。强度会影响脉冲周期和幅值
 *
 ************************************************************************/
void yao(int intensity);

/************************************************************************
 *  @fn     void xiaotui(int intensity)
 *  @brief  该函数生成小腿模式的波形
 *  @param  int intensity				强度，1  ~ 10。强度会影响脉冲周期和幅值
 *
 ************************************************************************/
void xiaotui(int intensity);

/************************************************************************
 *  @fn     void jiaodi(int intensity)
 *  @brief  该函数生成脚底模式的波形
 *  @param  int intensity				强度，1  ~ 10。强度会影响脉冲周期和幅值
 *
 ************************************************************************/
void jiaodi(int intensity);
#endif
