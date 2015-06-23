/*************************************************************************************
 File name: PolynomialFitting.c
    Author:   JiangJiXiang
        ID��
   Version:    1.0
      Date:  2014-07-29

Description: 
    1.ʵ�ֵ���������ʽ��ϣ�������polyfit�����֧�ֵĽ���4�����֧�ֵ����ݸ���50
    2.ʵ�ֶ�����������  �������� linfit�����֧�ֵ����ݸ���50
    ���ļ�����math.h�е�absȡ����ֵ����������֮�ⲻ�����κ�����ģ�飬���ļ������к����Կ����롣
    ÿ�ε��ö���Ҫ3Kջ�ڴ棬������ڴ档��ͨ���궨��MAX_DEG��MAX_NUM�޸��ڴ�ռ�ã�ͬʱҲ��Ӱ��ʹ�÷�Χ��

Others:
    Ϊ�����������������������ڱ������н�float��������Ϊ64λ(>=15����Чλ)
    polyfit:���֧�ֵĽ���4�����֧�ֵ����ݸ���50
     linfit:���֧�ֵ����ݸ���50

    
History:   Date        Author                  Modification
1.      2014-07-29     JiangJiXiang            �����ĵ�
2.      2014-07-30     JiangJiXiang            ���C++��̬�ڴ������C�﷨�����ݵ����⣨����̬�ڴ��Ϊ�ֲ���������

**************************************************************************************/


#ifndef _FITTING_H_BY_JiangJixiang
#define _FITTING_H_BY_JiangJixiang

#ifdef __cplusplus		   //�����CPP����C���� //��ʼ����
extern "C" {
#endif

/*******************************************************************************
    linear fit for data to get D,K,F, a[0]=D=b,a[1]=K=K,a[2]=F=-(a+bK)
    x[]={x01,x02,...,x0n-1, x11,x12,...x1n-1, ...,xm1,xm2,...,xm-1n-1};
    y[]={y0,y1,...,ym-1};
    DEG == n; // number of variables
    DatNum = m;//number of data
    y = x0*a0+x1*a1+...+xn-1*an-1;
*******************************************************************************/
void linearfit(const float* x,const float* y,float* a,const unsigned int DEG,const unsigned int DatNum);

/*************************************************
      Function:     polyfit
         Calls:   linearfit(ģ���ڲ��ĺ���)  // �����������õĺ����嵥
     Called By:  ���⺯���ɵ���              // ���ñ������ĺ����嵥
Table Accessed:   None
 Table Updated:   None

Description:
    �ú���ʵ�ֶ���ʽ��С������ϡ����֧��4�����
    ��2�ζ���ʽ���Ϊ������������y=a[0]+a[1]*x+a[2]*x^2����ѱƽ���

Input:
    float x[] , �Ա���
    float y[] , ���������x[]һһ��Ӧ
    uint d , ��ϵĽ���(d�����)
    uint n , ��������

Output:
    float a[]  ,  y = a[0] + a[1]*x + a[2]*x^2 + ... + a[n]*x^n;

Return:   void

Others:   // ����˵��
*************************************************/
void polyfit(const float x[],const float y[],float a[],const unsigned int d,const unsigned int n);


/*************************************************
      Function:     linfit
         Calls:   linearfit(ģ���ڲ��ĺ���)  // �����������õĺ����嵥
     Called By:  ���⺯���ɵ���              // ���ñ������ĺ����嵥
Table Accessed:   None
 Table Updated:   None

Description:
    �ú���ʵ�ֶ����������С������ϡ�
    ��2�����������Ϊ�����������õ����y=a[0]*x[0]+a[1]*x[1]+a[2]�Ĳ���a[]��

Input:
    float x[] = {x00,x01,...,x0n-1; x10,x11,...x1n-1; ...,xm0,xm1,...,xm-1n-1}; �Ա���
    float y[] = {y0,y1,...,ym-1};  ���������x[]һһ��Ӧ
    uint DEG , �Ա����ĸ���
    uint DatNum , ��������

Output:
    float a[] , y = x[0]*a[0]+x[1]*a[1]+...+x[n-1]*a[n-1]+a[n]

Return:   void

Others:   // ����˵��
*************************************************/
void linfit(const float x[],const float y[],float a[],const unsigned int DEG,const unsigned int DatNum);


void testfit(void);


#ifdef __cplusplus		   //�����CPP����C���� //��ʼ����
}
#endif

#endif
