/*************************************************************************************
 Copyright: Chongqing DATA Technologies Co., Ltd. 1998-2014. All rights reserved.
 File name: PolynomialFitting.c
    Author:   JiangJiXiang
        ID��
   Version:    1.0
      Date:  2014-07-29

Description:
    1.ʵ�ֵ���������ʽ��ϣ�������polyfit�����֧�ֵĽ���4�����֧�ֵ����ݸ���50
    2.ʵ�ֶ�����������  �������� linfit�����֧�ֵ����ݸ���50
    ���ļ�����math.h�е�absȡ����ֵ����������֮�ⲻ�����κ�����ģ�飬���ļ������к����Կ����롣
    ���ε�������ջ�ڴ�3K�����ڴ�0K���ڴ�Ҫ��ɸ��ݾ��������ͨ���궨��MAX_DEG��MAX_NUM���ڡ�

Others:
    Ϊ�����������������������ڱ������н�float��������Ϊ64λ(>=15����Чλ)
    polyfit:���֧�ֵĽ���4�����֧�ֵ����ݸ���50
     linfit:���֧�ֵ����ݸ���50


History:   Date        Author          Modification
1.      2014-07-29     JiangJiXiang    �����ĵ�
2.      2014-07-30     JiangJiXiang    ���C++��̬�ڴ������C�﷨�����ݵ����⣨����̬�ڴ��Ϊ�ֲ���������

**************************************************************************************/
#include "typesdef.h"
#include <stdio.h>
#include <math.h>
#include "PolynomialFitting.h"

#define MAX_DEG (16) // ֧�ֵ�������
#define MAX_NUM (20)// ���֧�ֵ����ݸ���
#define ABS(x) (((x)>=0)?(x):(-(x))) // ȥ����ֵ
static float X[(MAX_DEG+1)*(MAX_DEG+1)] = {0};
static float Y[MAX_DEG+1] = {0};

/*******************************************************************************
    linear fit for data to get D,K,F, a[0]=D=b,a[1]=K=K,a[2]=F=-(a+bK)
    x[]={x01,x02,...,x0n-1, x11,x12,...x1n-1, ...,xm1,xm2,...,xm-1n-1};
    y[]={y0,y1,...,ym-1};
    DEG == n; // number of variables
    DatNum = m;//number of data
    y = x0*a0+x1*a1+...+xn-1*an-1;
*******************************************************************************/
void linearfit(const float* x,const float* y,float* a,const unsigned int DEG,const unsigned int DatNum)
{
    unsigned int r=0,c=0,i=0,maxInd = 0;
    float temp = 0,k = 0;

    for(r=0;r<DEG;r++)// ����X
    {
        for(c=0;c<=r;c++)
        {
            X[r*DEG+c] = 0;
            for(i=0;i<DatNum;i++) X[r*DEG+c] += x[i*DEG+r]*x[i*DEG+c];
            X[c*DEG+r] = X[r*DEG+c];
        }
    }
    for(i=0;i<DEG;i++)// ����Y
    {
        Y[i] = 0;
        for(r=0;r<DatNum;r++)
        {
            Y[i] += y[r]*x[r*DEG+i];
        }
    }
    // ���������� Y=X*a;
    for(c=0;c<DEG;c++)// ��˹��Ԫ
    {
        for(r=c,maxInd=c;r<DEG;r++)// ����Ԫ��
        {
            if(ABS(X[maxInd*DEG+c]) < ABS(X[r*DEG+c]))
                maxInd = r;
        }
        // ������в���c�У���c�л���
        if(maxInd != c)
        {
            for(i=c;i<DEG;i++)
            {
                temp = X[maxInd*DEG+i];
                X[maxInd*DEG+i] = X[c*DEG+i];
                X[c*DEG+i] = temp;
            }
            temp = Y[maxInd];
            Y[maxInd] = Y[c];
            Y[c] = temp;
        }
        // ������ȥ
        for(r=c+1;r<DEG;r++)
        {
            k = X[r*DEG+c]/X[c*DEG+c];
            X[r*DEG+c] = 0;
            for(i=c+1;i<DEG;i++)
            {
                X[r*DEG+i] -= X[c*DEG+i]*k;
            }
            Y[r] -= Y[c]*k;
        }
    }
    // �ش����a
    for(r=DEG-1;;r--)
    {
        a[r]=Y[r];
        for(i=DEG-1;i>r;i--) a[r] -= a[i]*X[r*DEG+i];
        a[r] /= X[r*DEG+r];
        if(r==0) break;
    }
    //delete X;// �ͷ�Xָ��Ŀռ�
    //delete Y;// �ͷ�Yָ��Ŀռ�
}

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
void polyfit(const float x[],const float y[],float a[],const unsigned int Degree,const unsigned int num)
{
    unsigned int r,c,DEG;
    float X[MAX_NUM*(MAX_DEG+1)];
    DEG = Degree+1;// ϵ������
    for(r=0;r<num;r++)// ����XX
    {
        for(c=0;c<DEG;c++)
        {
            if(c==0)
                X[r*DEG+c] = 1;
            else
                X[r*DEG+c] = X[r*DEG+c-1]*x[r];
        }
    }
    linearfit(X,y,a,DEG,num);
    //delete X;
}


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
void linfit(const float x[],const float y[],float a[],const unsigned int DEG,const unsigned int DatNum)
{
    unsigned int r=0,c=0;
    float XX[(MAX_DEG+1)*MAX_NUM];

    for(r=0;r<DatNum;r++)// ����XX
    {
        for(c=0;c<DEG;c++)
            XX[r*(DEG+1)+c] = x[r*DEG+c];
        XX[r*(DEG+1)+DEG] = 1;
    }
    linearfit(XX,y,a,DEG+1,DatNum);
}


void zcslinearfit(const float* x, const float y, float* a)
{
    #define DEG (12)
    
    static float X[(DEG+1) * (DEG+1)] = {0};
    static float Y[DEG + 1] = {0};

    unsigned int r = 0, c = 0, i = 0, maxInd = 0;
    float temp = 0, k = 0;

    for(r = 0; r < DEG; r++)// ����X
    {
        for(c = 0; c <= r; c++)
        {
            X[r*DEG+c] = 0;
            for(i = 0; i < DEG;i++) X[r*DEG+c] += x[i*DEG+r] * x[i*DEG+c];
            X[c*DEG+r] = X[r*DEG+c];
        }
    }
    for(i = 0; i < DEG; i++)// ����Y
    {
        Y[i] = 0;
        for(r = 0; r < DEG; r++)
        {
            Y[i] += y * x[r*DEG+i];
        }
    }
    // ���������� Y=X*a;
    for(c = 0; c < DEG; c++)// ��˹��Ԫ
    {
        for(r = c, maxInd = c; r < DEG; r++)// ����Ԫ��
        {
            if(ABS(X[maxInd*DEG+c]) < ABS(X[r*DEG+c]))
                maxInd = r;
        }
        // ������в���c�У���c�л���
        if(maxInd != c)
        {
            for(i = c; i < DEG; i++)
            {
                temp = X[maxInd*DEG+i];
                X[maxInd*DEG+i] = X[c*DEG+i];
                X[c*DEG+i] = temp;
            }
            temp = Y[maxInd];
            Y[maxInd] = Y[c];
            Y[c] = temp;
        }
        // ������ȥ
        for(r = c + 1; r < DEG; r++)
        {
            k = X[r*DEG+c]/X[c*DEG+c];
            X[r*DEG+c] = 0;
            for(i = c + 1; i < DEG; i++)
            {
                X[r*DEG+i] -= X[c*DEG+i]*k;
            }
            Y[r] -= Y[c]*k;
        }
    }
    
    // �ش����a
    for(r = DEG-1; ; r--)
    {
        a[r]=Y[r];
        for(i=DEG-1;i>r;i--) a[r] -= a[i]*X[r*DEG+i];
        a[r] /= X[r*DEG+r];
        if(r==0) break;
    }
}


static void zcs_linfit(void)
{
    int i=0,j=0;
    float a[12] = {0};
    //                    ad1     ad2    ad3   ad4
    float xx[12 * 12] = {995.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f,
                          0.0f, 1000.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 5.0f, 995.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 5.0f, 0.0f, 1200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 5.0f, 0.0f, 0.0f, 1005.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 990.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f,
                          0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 980.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 970.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1000.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1010.0f, 0.0f, 0.0f,
                          0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1015.0f, 0.0f,
                          0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 1000.0f
                          };

    printf("\nZCS�������:\n");
    zcslinearfit(xx,1000.0f, a);
    for(j=0;j<12;j++)
    {
        printf("\ta[%d]=%f\n",j,a[j]);
    }
}

void testfit(void)
{
    float x[20] = {0,0.333333333333333,0.666666666666667,1,1.33333333333333,1.66666666666667,2,2.33333333333333,2.66666666666667,3};
    float y[20] = {-0.331083453936105,-0.526928383727243,-0.00972007372060824,-0.443595047773436,1.18268329967307,2.60525836403058,4.87627221027883,8.36623233721162,13.6739320053251,20.4820220610319};
    float a[12] = {0};
    float x1[100] = {0.295235260345369,0.358033508186404,0.271573421028167,0.890348226218803,-0.582130155147954,0.418563405421090,-0.527538846012407,
-0.761207504405389,0.214607881371269,-0.0997246060682080,-0.0825490127022643,0.323889503811304,0.540571029607320,-0.299563973117790,0.324019196718269,
-0.167682820060407,0.683858305382618,0.665833638150432,-0.487118015541705,0.226921473625751};
    float y1[100] = {-0.114755841823736,0.0632586715365796,-1.20234973628810,-1.66380559893072,-0.429092189096527,-0.665836460883003,-0.0231003037231075,-0.281292984793161,0.503295574752465,-1.17855313464991};
    int i=0,j=0;


    for(i=1;i<=4;i++)
    {
        polyfit(x,y,a,i,10);
        printf("\n%d�����:\n",i);
        for(j=0;j<5;j++)
        {
            printf("\ta[%d]=%f\n",j,a[j]);  a[j] = 0;
        }
    }
    printf("\n�������:\n");
    linfit(x1,y1,a,2,10);
    for(j=0;j<5;j++)
    {
        printf("\ta[%d]=%f\n",j,a[j]);
    }

    zcs_linfit();
}

