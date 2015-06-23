/*************************************************************************************
 File name: PolynomialFitting.c
    Author:   JiangJiXiang
        ID：
   Version:    1.0
      Date:  2014-07-29

Description: 
    1.实现单变量多项式拟合，函数名polyfit，最多支持的阶数4，最多支持的数据个数50
    2.实现多变量线性拟合  ，函数名 linfit，最多支持的数据个数50
    此文件调用math.h中的abs取绝对值函数，除此之外不依赖任何其他模块，此文件的所有函数皆可重入。
    每次调用都需要3K栈内存，无需堆内存。可通过宏定义MAX_DEG和MAX_NUM修改内存占用，同时也会影响使用范围。

Others:
    为避免计算过程中增大误差，建议在编译器中将float类型设置为64位(>=15个有效位)
    polyfit:最多支持的阶数4，最多支持的数据个数50
     linfit:最多支持的数据个数50

    
History:   Date        Author                  Modification
1.      2014-07-29     JiangJiXiang            创建文档
2.      2014-07-30     JiangJiXiang            解决C++动态内存分配与C语法不兼容的问题（将动态内存改为局部变量）。

**************************************************************************************/


#ifndef _FITTING_H_BY_JiangJixiang
#define _FITTING_H_BY_JiangJixiang

#ifdef __cplusplus		   //定义对CPP进行C处理 //开始部分
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
         Calls:   linearfit(模块内部的函数)  // 被本函数调用的函数清单
     Called By:  任意函数可调用              // 调用本函数的函数清单
Table Accessed:   None
 Table Updated:   None

Description:
    该函数实现多项式最小二乘拟合。最多支持4阶拟合
    以2次多项式拟合为例，本函数对y=a[0]+a[1]*x+a[2]*x^2的最佳逼近。

Input:
    float x[] , 自变量
    float y[] , 因变量，与x[]一一对应
    uint d , 拟合的阶数(d次拟合)
    uint n , 数据组数

Output:
    float a[]  ,  y = a[0] + a[1]*x + a[2]*x^2 + ... + a[n]*x^n;

Return:   void

Others:   // 其它说明
*************************************************/
void polyfit(const float x[],const float y[],float a[],const unsigned int d,const unsigned int n);


/*************************************************
      Function:     linfit
         Calls:   linearfit(模块内部的函数)  // 被本函数调用的函数清单
     Called By:  任意函数可调用              // 调用本函数的函数清单
Table Accessed:   None
 Table Updated:   None

Description:
    该函数实现多变量线性最小二乘拟合。
    以2个变量的拟合为例，本函数得到最佳y=a[0]*x[0]+a[1]*x[1]+a[2]的参数a[]。

Input:
    float x[] = {x00,x01,...,x0n-1; x10,x11,...x1n-1; ...,xm0,xm1,...,xm-1n-1}; 自变量
    float y[] = {y0,y1,...,ym-1};  因变量，与x[]一一对应
    uint DEG , 自变量的个数
    uint DatNum , 数据组数

Output:
    float a[] , y = x[0]*a[0]+x[1]*a[1]+...+x[n-1]*a[n-1]+a[n]

Return:   void

Others:   // 其它说明
*************************************************/
void linfit(const float x[],const float y[],float a[],const unsigned int DEG,const unsigned int DatNum);


void testfit(void);


#ifdef __cplusplus		   //定义对CPP进行C处理 //开始部分
}
#endif

#endif
