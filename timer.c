#include "STC15FXX.H"
#include "HARDWARE\timer.h"
extern unsigned char allowsend;
extern unsigned char th,tl,hu;
unsigned char intercnt;
void    Timer0_init(void)
{
        TR0 = 0;    //ֹͣ����
		IP=0X10;
    #if (Timer0_Reload < 64)    // ����û�����ֵ�����ʣ� ��������ʱ��
        #error "Timer0���õ��жϹ���!"

    #elif ((Timer0_Reload/12) < 65536UL)    // ����û�����ֵ�����ʣ� ��������ʱ��
        ET0 = 1;    //�����ж�
    //  PT0 = 1;    //�����ȼ��ж�
        TMOD &= ~0x03;
        TMOD |= 0;  //����ģʽ, 0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
    //  TMOD |=  0x04;  //����������Ƶ
        TMOD &= ~0x04;  //��ʱ
    //  INT_CLKO |=  0x01;  //���ʱ��
        INT_CLKO &= ~0x01;  //�����ʱ��

        #if (Timer0_Reload < 65536UL)
            AUXR |=  0x80;  //1T mode
            TH0 = (unsigned char)((65536UL - Timer0_Reload) / 256);
            TL0 = (unsigned char)((65536UL - Timer0_Reload) % 256);
        #else
            AUXR &= ~0x80;  //12T mode
            TH0 = (unsigned char)((65536UL - Timer0_Reload/12) / 256);
            TL0 = (unsigned char)((65536UL - Timer0_Reload/12) % 256);
        #endif

        TR0 = 1;    //��ʼ����
		EA=1;
    #else
        #error "Timer0���õ��жϹ���!"
    #endif
}
void timer0 (void) interrupt 1
{
  	intercnt++;
	if(intercnt>=200)//2 second
	{
		intercnt=0;
		send(th,tl,hu);
	}
		serial_pro();
}