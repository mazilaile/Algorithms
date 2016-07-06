//合唱队形问题:  
//  问题描述:   给定一串整数 从中剔除一些数 使得其按从从小到大 再从大到小的顺序排列 如: 1 2 3 6 5 4 要求留下的数字尽可能多   
//  输入:     数组大小 数组数据  
//  输出:     能得到的最优队列元素个数 并输出元素队列  
#include <iostream>  
using namespace std;  
  
//用于保存子问题最优解的备忘录  
typedef struct    
{  
    int maxlen; //当前子问题最优解  
    int prev;   //构造该子问题所用到的下一级子问题序号(用于跟踪输出最优队列)  
}Memo;  
  
//用于递归输出Memo B中的解  
void Display(int* A, Memo* M, int i)  
{  
    if (M[i].prev == -1)  
    {  
        cout<<A[i]<<" ";  
        return;  
    }  
    Display(A, M, M[i].prev);  //递归调用，按从低到高顺序输出
    cout<<A[i]<<" ";  
}  
  
//算法主要部分  
void GetBestQuence(int* A, int n)  
{  
    //定义备忘录 并作必要的初始化  
    Memo *B = new Memo[n];              //B[i]代表从A[0]到A[i]满足升序剔除部分元素后能得到的最多元素个数  
    Memo *C = new Memo[n];              //C[i]代表从A[i]到A[n-1]满足降序剔除部分元素后能得到的最多元素个数  
    B[0].maxlen = 1;        //由于B[i]由前向后构造 初始化最前面的子问题  (元素本身就是一个满足升序降序的序列)  
    C[n-1].maxlen = 1;      //同样C[i]由后向前构造  
    for (int i=0; i<n; i++) //为前一个最优子问题序号给定一个特殊标识-1   
                            //用于在跟踪路径时终止递归或迭代(因为我们并不知道最终队列从哪里开始)  
    {  
        B[i].prev = -1;  
        C[i].prev = -1;  
    }  
    //这里以A[i]为队形的中心！！！
    for (int i=1; i<n; i++)      //构造B[n]  i为1时就是求B[1]即从A[0]到A[1]满足升序排列的最多元素个数
    {  
        int max=1;  
        for (int j=i-1; j>=0; j--)               //查看前面的子问题 找出满足条件的最优解 并且记录  
        {  
            if (A[j]<A[i] && B[j].maxlen+1>max)  //B[j].maxlen+1>max这里一定是大于
            {  
                max = B[j].maxlen+1;            //跟踪当前最优解  
                B[i].prev = j;                  //跟踪构造路径  
            }  
        }  
        B[i].maxlen = max;                      //构造最优解  
    }  
      
    for (int i=n-1; i>=0; i--)  //C[i]是从后往前算的
    {  
        int max=1;  
        for (int j=i; j<n; j++)          //从后往前构造 这是为了后面在统筹最终解时可以直接用B[i]+C[i]-1  
                            //否则我们得到的最优解始终为B[n-1]+C[n-1]  
        {  
            if (A[j]<A[i] && C[j].maxlen+1>max)   //比当前长度更长 记录并构造  
            {  
                max = C[j].maxlen+1;  
                C[i].prev = j;  
            }  
        }  
        C[i].maxlen = max;  
    }  
  
    //遍历i 得到最大的B[i]+C[i]-1(-1是因为我们在B[i]和C[i]中 均加上了A[i]这个数 因此需要减去重复的)  
    int maxQuence = 0;  //记录当前最优解  
    int MostTall;       //记录i 用于跟踪构造路径   
    for (int i=0; i<n; i++)  
    {  
        if (B[i].maxlen+C[i].maxlen-1 > maxQuence)  
        {  
            maxQuence = B[i].maxlen+C[i].maxlen-1;  
            MostTall = i;  
        }  
    }  
      
    cout<<"最大合唱队形长度: "<<maxQuence<<endl;  
      
    //B由前向后构造 因此prev指向前面的元素 需要递归输出  
    Display( A, B, MostTall);  //输出递增序列
    //C的prev指向后面元素 直接迭代输出  
    while (C[MostTall].prev != -1)   //输出递减序列
    {  
        MostTall = C[MostTall].prev;  
        cout<<A[MostTall]<<" ";  
    }  
    cout<<endl;  
      
    delete []B;  
    delete []C;  
}  
int main()  
{  
    //测试  
    int *A;  
    int n;  
    cout<<"请输入合唱队员个数: "<<endl;  
    cin>>n;  
  
    A = new int[n];  
    cout<<"输入队员身高 :"<<endl;  
    for (int i=0; i<n; i++)  
    {  
        cin>>A[i];  
    }  
	
	/*
	int n=8;
	int A[8]={186,186,150,200,160,130,197,200};
	*/

    GetBestQuence(A, n);  
    delete []A;  
	system("pause");
    return 0;  
}