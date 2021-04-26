#include "mode.h"

void delay(float time)
{
}

void setVoltage(float voltage)
{
}

void setTimer(float time, int index)
{
}

float getTimer(int index)
{
	float time = 0.0;

	return time;
}

void generatePulse(float period, float pulseWidth, float amplitude, int flag)
{
	if (flag == 0)
	{
		setVoltage(amplitude);	//置位
		delay(pulseWidth);		//延时

		setVoltage(0);			//产生pulseWidth长度的脉冲后，之后电压为0
		delay(period - (float)pulseWidth);
	}
	else if (flag == 1)
	{
		setVoltage(amplitude);	//置位
		delay(pulseWidth);		//延时

		setVoltage(0);	//置位
		delay(pulseWidth);		//延时

		setVoltage(-amplitude);	//置位
		delay(period - 2 * pulseWidth);		//延时
	}
	else
	{
		printf("flag must be 1 or 0");
	}
}

void basicUnit(float period, float envelopWidth, float blankTime, int intensity, float amplitude[])
{
	// 在 0 ~ changeTime 内，脉宽变化。如在强度10， 脉宽从0递增至100us
	float changeTime = envelopWidth / 2;
	// 初始幅值高于稳定值，0 ~ fallTime幅值降到amplitude
	float fallTime = envelopWidth / 3;
	float maxPulseWidth[10] = { 4e-5f, 4e-5f , 4e-5f , 6e-5f, 6e-5f, 6e-5f, 8e-5f, 8e-5f, 1e-4f, 1e-4f };
	// 脉宽最小值
	float minPulseWidth = maxPulseWidth[intensity] / 5;
	float pulseWidth = 0.0;
	float time = 0;
	float delta = amplitude[0] - amplitude[1];
	setTimer(envelopWidth, 0);
	setTimer(changeTime, 1);
	setTimer(fallTime, 2);

	while (getTimer(0))			// 0 ~ envelopWidth
	{
		while (getTimer(1))		// 0 ~ changeTime
		{
			while (getTimer(2)) // 0 ~ fallTime
			{
				time = getTimer(2);
				pulseWidth = ceil(time / changeTime * 4) * minPulseWidth;
				generatePulse(period, pulseWidth, amplitude[0] - time / fallTime * delta, 1);
			}
			time = getTimer(1);
			pulseWidth = ceil(time / changeTime * 4) * minPulseWidth;
			generatePulse(period, pulseWidth, amplitude[1], 1);
		}
		pulseWidth = maxPulseWidth[intensity];
		generatePulse(period, pulseWidth, amplitude[1], 1);
	}
}

void basicUnit2(float period, float envelopWidth, float blankTime, int intensity, float amplitude[])
{
	// 在 0 ~ changeTime 内，脉宽变化。如在强度10， 脉宽从0递增至100us
	float changeTime = envelopWidth / 2;
	// 初始幅值高于稳定值，0 ~ fallTime幅值降到amplitude
	float fallTime = envelopWidth / 3;
	float maxPulseWidth[10] = { 4e-5f, 4e-5f , 4e-5f , 6e-5f, 6e-5f, 6e-5f, 8e-5f, 8e-5f, 1e-4f, 1e-4f };
	// 脉宽最小值
	float minPulseWidth = maxPulseWidth[intensity] / 5;
	float pulseWidth = 0.0;
	float time = 0.0f;
	float delta = amplitude[0] - amplitude[1];

	// 打开定时器
	setTimer(envelopWidth, 0);
	setTimer(changeTime, 1);
	setTimer(fallTime, 2);

	while (getTimer(0))			// 0 ~ envelopWidth
	{
		while (getTimer(1))		// 0 ~ changeTime
		{
			while (getTimer(2)) // 0 ~ fallTime
			{
				time = getTimer(2);
				pulseWidth = ceil(time / changeTime * 4) * minPulseWidth;
				generatePulse(period, pulseWidth, amplitude[0] - time / fallTime * delta, 0);
			}
			time = getTimer(1);
			pulseWidth = ceil(time / changeTime * 4) * minPulseWidth;
			generatePulse(period, pulseWidth, amplitude[1], 0);
		}
		pulseWidth = maxPulseWidth[intensity];
		generatePulse(period, pulseWidth, amplitude[1], 0);
	}

	setVoltage(0);
	delay(blankTime);

	// 打开定时器
	setTimer(envelopWidth, 0);
	setTimer(changeTime, 1);
	setTimer(fallTime, 2);
	while (getTimer(0))			// 0 ~ envelopWidth
	{
		while (getTimer(1))		// 0 ~ changeTime
		{
			while (getTimer(2)) // 0 ~ fallTime
			{
				time = getTimer(2);
				pulseWidth = ceil(time / changeTime * 4) * minPulseWidth;
				generatePulse(period, pulseWidth, -amplitude[0] + time / fallTime * delta, 0);
			}
			time = getTimer(1);
			pulseWidth = ceil(time / changeTime * 4) * minPulseWidth;
			generatePulse(period, pulseWidth, -amplitude[1], 0);
		}
		pulseWidth = maxPulseWidth[intensity];
		generatePulse(period, pulseWidth, -amplitude[1], 0);
	}

	setVoltage(0);
	delay(blankTime);
}

void basicUnitLeg1(float period, int intensity, float amplitude)
{
	float maxPulseWidth[10] = { 4e-5f, 4e-5f , 4e-5f , 6e-5f, 6e-5f, 6e-5f, 8e-5f, 8e-5f, 1e-4f, 1e-4f };
	for (int i = 0; i < 6; i++)
	{
		generatePulse(period, maxPulseWidth[intensity], -amplitude, 0);
	}

	delay(0.3);

	for (int i = 0; i < 6; i++)
	{
		generatePulse(period, maxPulseWidth[intensity], amplitude, 0);
	}

	delay(0.3);
}

void basicUnitLeg2(float period, float envelopWidth, int intensity, float amplitude, int flag)
{
	float maxPulseWidth[10] = { 4e-5f, 4e-5f , 4e-5f , 6e-5f, 6e-5f, 6e-5f, 8e-5f, 8e-5f, 1e-4f, 1e-4f };
	float pulseWidth = maxPulseWidth[intensity];
	setTimer(envelopWidth, 0);
	float time = 0;
	while (getTimer(0))
	{
		if (flag == 0)
		{
			time = getTimer(0);
			generatePulse(period, pulseWidth, amplitude - time / envelopWidth * 2, 1);
		}
		else
		{
			time = getTimer(0);
			generatePulse(period, pulseWidth, amplitude + time / envelopWidth * 2, 1);
		}
	}

	delay(0.1);
}

void basicUnitShoulder1(float period, float envelopWidth, float blankTime, int intensity, float amplitude)
{
	float maxPulseWidth[10] = { 4e-5f, 4e-5f , 4e-5f , 6e-5f, 6e-5f, 6e-5f, 8e-5f, 8e-5f, 1e-4f, 1e-4f };
	float pulseWidth = maxPulseWidth[intensity];
	setTimer(envelopWidth, 0);
	// 产生正向脉冲
	while (getTimer(0))
	{
		generatePulse(period, pulseWidth, amplitude, 0);
	}

	delay(blankTime);

	setTimer(envelopWidth, 0);
	// 产生反向脉冲
	while (getTimer(0))
	{
		generatePulse(period, pulseWidth, -amplitude, 0);
	}

	delay(blankTime);
}

void basicUnitShoulder2(float period, int intensity, float amplitude)
{
	float maxPulseWidth[10] = { 4e-5f, 4e-5f , 4e-5f , 6e-5f, 6e-5f, 6e-5f, 8e-5f, 8e-5f, 1e-4f, 1e-4f };
	float pulseWidth = maxPulseWidth[intensity];

	//负向脉冲， 三个小脉冲未一组，重复五组
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			generatePulse(period, pulseWidth, -amplitude, 0);
		}
		setVoltage(0);
		delay(0.4);
	}

	//正向脉冲， 三个脉冲为一组，重复五组
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			generatePulse(period, pulseWidth, amplitude, 0);
		}
		setVoltage(0);
		delay(0.4);
	}
}

void qiao(int intensity)
{
	// 敲模式脉冲周期变化，先从1 ~ 0.0647递减，后0.0647 ~ 1递增
	float period[15] = { 1, 0.9236, 0.8455, 0.7556, 0.6649, 0.5733, 0.4843, 0.3986,
		0.3163, 0.2542, 0.2, 0.1537, 0.1151, 0.09, 0.0647 };
	float amplitude[10][4] = { 20, 20, 10, 5,
								25, 25, 10, 5,
								30, 30, 15, 10,
								35, 35, 15, 10,
								35, 35, 20, 15,
								40, 40, 25, 20,
								45, 45, 30, 25,
								50, 50, 35, 30,
								55, 55, 35, 30,
								60, 60, 40, 35 };
	float blankTime = 0;
	float envelopWidth = 3;
	float amplitude1[2] = { amplitude[intensity - 1][2], amplitude[intensity - 1][3] };
	float amplitude2[2] = { amplitude[intensity - 1][0], amplitude[intensity - 1][1] };
	for (int i = 0; i < 15; i++)
	{
		if (period[i] < 0.18)
			basicUnit(period[i], envelopWidth, blankTime, intensity, amplitude1);
		else
		{
			basicUnit(period[i], envelopWidth, blankTime, intensity, amplitude2);
		}
	}

	for (int i = 14; i >= 0; i--)
	{
		if (period[i] < 0.18)
			basicUnit(period[i], envelopWidth, blankTime, intensity, amplitude1);
		else
		{
			basicUnit(period[i], envelopWidth, blankTime, intensity, amplitude2);
		}
	}
}

void an(int intensity)
{
	float period = 0.01;
	float envelopWidth[12] = { 5, 4.5, 4, 3.5, 3, 2.5, 2, 2.5, 3, 3.5, 4, 4.5 };
	// 强度10下的峰值与稳定值
	float amplitude10[2] = { 50, 32.8 };
	float amplitude[2] = { amplitude10[0] - 3 * (10 - intensity), amplitude10[1] - 1.5 * (10 - intensity) };
	float blankTime = 1;
	for (int i = 0; i < 12; i++)
	{
		basicUnit2(period, envelopWidth[i], blankTime, intensity, amplitude);
	}
}

void rou(int intensity)
{
	float period = 0.02;
	float envelopWidth[16] = { 0.37, 0.47, 0.67, 0.77, 1.16, 1.46, 1.76, 2.25,
							3.35, 2.25, 1.76, 1.46, 1.16, 0.77, 0.67, 0.47 };
	float blankTime = 1;
	float amplitude[2] = { 50 - 3 * (10 - intensity), 39.21 - 2 * (10 - intensity) };
	for (int i = 0; i < 16; i++)
	{
		basicUnit2(period, envelopWidth[i], blankTime, intensity, amplitude);
	}
}

void jianjing(int intensity)
{
	float period = 0.02;
	float envelopWidth[2] = { 4, 3 };
	float blankTime = 1;
	float amplitude = 40 - (10 - intensity) * 2.6;
	float amplitude2[2] = { 52 - (10 - intensity) * 4, 39 - (10 - intensity) * 2.6 };
	float envelopWidth2[5] = { 2, 1, 2, 3, 4 };

	// 肩颈新模式1
	for (int i = 0; i < 2; i++)
	{
		basicUnitShoulder1(period, envelopWidth[i], blankTime, intensity, amplitude);
	}

	for (int i = 0; i < 5; i++)
	{
		basicUnit2(period, envelopWidth2[i], blankTime, intensity, amplitude2);
	}

	// 肩颈新模式2
	amplitude = 53.57 - (10 - intensity) * 4;
	for (int i = 0; i < 10; i++)
	{
		basicUnitShoulder2(period, intensity, amplitude);
	}

	// 敲模式
	qiao(intensity);
}

void shangbi(int intensity)
{
	float period = 0.01;
	float envelopWidth[12] = { 5, 5, 4, 4, 3, 3, 2, 2, 3, 3, 4, 4 };
	float blankTime = 0;
	float amplitude[2] = { 46.37 - 3 * (10 - intensity), 30.78 - 1.5 * (10 - intensity) };
	// 敲模式
	qiao(intensity);
	// 按模式
	for (int i = 0; i < 2; i++)
	{
		basicUnit2(period, envelopWidth[i], blankTime, intensity, amplitude);
	}
}

void yao(int intensity)
{
	float period[14] = { 0.5007f, 0.3351f, 0.2508f, 0.200f, 0.125f, 0.10f, 0.068f, 0.05f,
	0.068f, 0.10f, 0.125f, 0.200f, 0.2508f, 0.3351f };
	float periodAn[8] = { 0.05, 0.035, 0.021, 0.035, 0.05, 0.035, 0.021, 0.035 };
	float periodNew[30] = { 0.75, 0.25, 0.5, 0.25, 0.5, 0.75,
		0.50, 0.50, 0.626, 0.126, 0.5, 0.5,
		0.5, 0.5, 1.5, 0.5, 1.5, 0.5,
		0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
		0.5, 1.0, 0.5, 0.5, 0.5, 0.25
	};
	float amplitude[10][4] = { 20, 20, 10, 5,
							15, 15, 10, 5,
							20, 20, 15, 10,
							25, 25, 15, 10,
							30, 30, 20, 15,
							35, 35, 25, 20,
							40, 40, 30, 25,
							45, 45, 35, 30,
							50, 50, 40, 35,
							55, 55, 45, 40
	};
	float amplitudeNew = 50 - 5 * (10 - intensity);
	float amplitudeAn[8][2] = { 55, 47.13,
		54.71, 43.98,
		52.66, 39.21,
		54.39, 44.15,
		55.76, 46.99,
		53.83, 44.32,
		51.39, 39.25,
		55.02, 44.28
	};

	int flag = 1;
	float blankTime = 0;
	float envelopWidth = 2.5;
	float envelopWidthAn = 3.45;
	float Amplitude[2] = { 0.0f, 0.0f };
	float AmplitudeAn[2] = { 0.0f, 0.0f };
	// 敲模式
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (period[j] < 0.12)
			{
				Amplitude[0] = amplitude[intensity][2];
				Amplitude[1] = amplitude[intensity][3];
				basicUnit(period[j], envelopWidth, blankTime, intensity, Amplitude);
			}
			else
			{
				Amplitude[0] = amplitude[intensity][0];
				Amplitude[1] = amplitude[intensity][1];
				basicUnit(period[j], envelopWidth, blankTime, intensity, Amplitude);
			}
		}
	}

	delay(0.3);

	// 新模式部分

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			generatePulse(period[i], 1e-4, amplitudeNew - 20 + rand() % 40, 1);
		}
	}

	// 按模式
	for (int i = 0; i < 8; i++)
	{
		AmplitudeAn[0] = amplitudeAn[i][0] - 4 * (10 - intensity);
		AmplitudeAn[1] = amplitudeAn[i][1] - 3 * (10 - intensity);

		basicUnit2(periodAn[i], envelopWidthAn, 1, intensity, AmplitudeAn);
	}
}

void xiaotui(int intensity)
{
	float periodNew1[6] = { 0.5, 0.3351, 0.2508, 0.2006, 0.1254, 0.1013 };
	float periodNew2[9] = { 0.5, 0.25, 0.1685, 0.1264, 0.10, 0.1264, 0.1685, 0.25, 0.5 };
	float periodQiao[15] = { 0.4997, 0.3341, 0.2498, 0.1996, 0.1244, 0.1, 0.0672, 0.05,
		0.0672, 0.1, 0.1244, 0.1996, 0.2498, 0.3341, 0.4997
	};
	float amplitudeNew1[6] = { 58.42, 61.79, 60.6, 64.16, 65.15, 60.48 };
	float amplitudeNew2[9] = { 59.0000, 54.3333, 49.6667, 45.0000, 45.0000, 48.5000, 52.0000, 55.5000, 59.0000 };
	float amplitudeQiao[10][4] = { 20, 20, 10, 5,
									25, 25, 10, 5,
									30, 30, 15, 10,
									35, 35, 15, 10,
									35, 35, 20, 15,
									40, 40, 25, 20,
									45, 45, 30, 25,
									50, 50, 35, 30,
									55, 55, 35, 30,
									60, 60, 40, 35
	};
	float AmplitudeQiao[2] = { 0.0f, 0.0f };
	// 新模式1
	for (int i = 0; i < 6; i++)
	{
		basicUnitLeg1(periodNew1[i], intensity, amplitudeNew1[i] - (10 - intensity) * 5);
	}

	// 新模式2
	for (int i = 0; i < 9; i++)
	{
		if (i <= 4)
		{
			basicUnitLeg2(periodNew2[i], 2.5, intensity, amplitudeNew2[i] - (10 - intensity) * 5, 0);
		}
		else
		{
			basicUnitLeg2(periodNew2[i], 2.5, intensity, amplitudeNew2[i] - (10 - intensity) * 5, 1);
		}
	}

	// 敲
	for (int i = 0; i < 15; i++)
	{
		if (periodQiao[i] < 0.12)
		{
			AmplitudeQiao[0] = amplitudeQiao[intensity][2];
			AmplitudeQiao[1] = amplitudeQiao[intensity][3];
			basicUnit(periodQiao[i], 2.5, 0, intensity, AmplitudeQiao);
		}
		else
		{
			AmplitudeQiao[0] = amplitudeQiao[intensity][0];
			AmplitudeQiao[1] = amplitudeQiao[intensity][1];
			basicUnit(periodQiao[i], 2.5, 0, intensity, AmplitudeQiao);
		}
	}
}

void jiaodi(int intensity)
{
	float period[16] = { 0.03, 0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.02,
		0.0261, 0.0261, 0.03, 0.03, 0.05, 0.05, 0.05, 0.05 };
	float envelopWidth[16] = { 3.94, 3.94, 3.94, 3.94,
								2.96, 2.96, 2.96, 2.96,
								2.97, 2.97,
								3.85, 3.85,
								2.9, 2.9, 2.9, 2.9 };

	float amplitude[16][2] = { 44.7, 32.04,
								44.7,  32.04,
								44.7,  32.04,
								44.7,  32.04,
								42.74, 28.7,
								42.74, 28.7,
								42.74, 28.7,
								42.74, 28.7,
								43.95, 30.78,
								43.95, 30.78,
								45.09, 32.17,
								45.09, 32.17,
								43.76, 34.87,
								43.76, 34.87,
								43.76, 34.87,
								43.76, 34.87
	};

	float Amplitude[2] = { 0.0f, 0.0f };
	for (int i = 0; i < 16; i++)
	{
		Amplitude[0] = amplitude[intensity][0] - 3 * (10 - intensity);
		Amplitude[1] = amplitude[intensity][1] - 3 * (10 - intensity);

		basicUnit(period[i], envelopWidth[i], 1, intensity, Amplitude);
	}
}