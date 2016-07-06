#include<iostream>
using namespace std;
#define MinNumber -200
int CUT_ROD(int p[],int n)
{
    int q;
    if(n==0)
       return0;
    q=MinNumber;
    for(inti=1;i<=n;i++)
    {
       q=max(q,p[i]+CUT_ROD(p,n-i));
    }
    return q;
 
}
//提升性能加入备忘机制
 
#define Maxnum 20
#define Minnum -200
 
//自底向上版本
int Bottom_UP_ROD(int p[],int n,int r[])
{
    int q;
    for(inti=1;i<=n;i++)
       r[i]=Minnum;
    r[0]=0;
    for(intj=1;j<=n;j++)
    {
       q=Minnum;
       for(inti=1;i<=j;i++)
       {
           q=max(q,p[i]+r[j-i]);
       }
       r[j]=q;
    }
    returnr[n];
}
int MEMOIZED_CUT_ROD_AUX(int p[],int n,int r[])
{
    int q;
    if(r[n]>
=0)
       returnr[n];
    if(n==0)
       q=0;
    else
    {
       q=Minnum;
       for(inti=1;i<=n;i++)
           q=max(q,p[i]+MEMOIZED_CUT_ROD_AUX(p,n-i,r));
    }
    r[n]=q;
    return q;
}
void MEMOIZED_CUT_ROD(int p[],int n)
{
    intr[Maxnum];
    for(inti=1;i<=n;i++)
       r[i]=Minnum;
 
}
//DOWN_UP_ROD扩展版本
void EXTEND_DOWN_UP_ROD(int r[],int s[],int p[],intn)
{
    r[0]=0;
    for(intj=1;j<=n;j++)
    {
       intq=Minnum;
       for(inti=1;i<=j;i++)
       {
           if(q<p[i]+r[j-i])
           {
              q=p[i]+r[j-i];
              s[j]=i;
           }
       }
       r[j]=q;
    }
 
}
 
//递归打印出方案：
void Print_CUT_ROD_SOLUTION(int p[],int n,int s[])
{
    cout<<"----------------------------"<<endl;
    cout<<"长度为："<<n<<"的切割方案为"<<endl;
    while(n>
0)
    {
       cout<<s[n]<<",";
       n=n-s[n];
    }
    cout<<endl;
}
void Printvalue()
{
 
}
int main()
{
    int p[]={0,1,5,8,9,10,17,17,20,24};
    intr[Maxnum];
    ints[Maxnum];
   
  //cout<<"最大收益"<<Bottom_UP_ROD(p,9,r)<<endl;
    EXTEND_DOWN_UP_ROD(r,s,p,9);
   for(inti=1;i<=9;i++)
       cout<<"长度为："<<i<<"收益最大为："<<r[i]<<endl;
  Print_CUT_ROD_SOLUTION(p,9,s);
    return 0;
}