#include<bits/stdc++.h>
using namespace std;
int father[26];//并查集
int findFather(int x){//查找父亲结点并进行路径压缩
    if(x==father[x])
        return x;
    int temp=findFather(father[x]);
    father[x]=temp;
    return temp;
}
bool judge(int inDegree[],int outDegree[],int n){//判断是否满足题目要求,参数n表示图中有几个字母结点
    int num=0;//并查集中有几个集合
    for(int i=0;i<26;++i)//查找并查集中有几个集合
        if(father[i]==i)
            ++num;
    if((26-n+1)!=num)//如果除了为出现过的字母外不止一个集合，说明图不连通
        return false;
    int num1=0,num2=0;//入度比出度大1的结点数、入度比出度小1的结点数
    for(int i=0;i<26;++i){
        int j=inDegree[i]-outDegree[i];
        if(abs(j)>1)
            return false;
        else if(j==1)
            ++num1;
        else if(j==-1)
            ++num2;
    }
    return (num1==1&&num2==1)||(num1==0&&num2==0);
}
int main(){
    int T,N;
    string s;
    scanf("%d",&T);
    while(T--){
        scanf("%d%*c",&N);
        iota(father,father+26,0);
        int inDegree[26]={0},outDegree[26]={0};//每个结点的入度、出度
        unordered_set<char>letters;//统计出现过的字母结点个数
        for(int i=0;i<N;++i){
            getline(cin,s);
            ++inDegree[s.back()-'a'];
            ++outDegree[s.front()-'a'];
            letters.insert(s.front());
            letters.insert(s.back());
            int ua=findFather(s.front()-'a'),ub=findFather(s.back()-'a');
            if(ua!=ub)//合并两个集合
                father[ua]=ub;
        }
        if(judge(inDegree,outDegree,letters.size()))
            puts("Ordering is possible.");
        else
            puts("The door cannot be opened.");
    }
    return 0;
}
