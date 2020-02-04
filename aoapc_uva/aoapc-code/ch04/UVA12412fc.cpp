#include<bits/stdc++.h>
using namespace std;
const double limit=1e-6;
struct Student{
    long long SID;
    int CID,score[4],rank=1,totalScore=0;
    double averageScore=0.0;
    string name;
    Student(long long s,int c,string n,int a[]):SID(s),CID(c),name(n){
        for(int i=0;i<4;++i){
            score[i]=a[i];
            totalScore+=a[i];
        }
        averageScore=totalScore/4.0;
    }
};
vector<Student>students;
void split(string&line,vector<string>&s){
    string temp="";
    for(int i=0;i<=line.size();++i)
        if(i==line.size()||line[i]==' '){
            s.push_back(temp);
            temp="";
        }else
            temp+=line[i];
}
void outputMainMenu(){
    printf("Welcome to Student Performance Management System (SPMS).\n\n1 - Add\n"
           "2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n\n");
}
void addStudent(){
    printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
    string input;
    while(getline(cin,input)&&input!="0"){
        vector<string>s;
        split(input,s);
        long long SID=stoll(s[0]);
        if(find_if(students.begin(),students.end(),[SID](const Student&stu){
                   return stu.SID==SID;})!=students.end())
            printf("Duplicated SID.\n");
        else{
            int score[4];
            for(int i=0;i<4;++i)
                score[i]=stoi(s[i+3]);
            students.push_back(Student(SID,stoi(s[1]),s[2],score));
        }
        printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
    }
}
void removeStudent(){
    printf("Please enter SID or name. Enter 0 to finish.\n");
    string input;
    while(getline(cin,input)&&input!="0"){
        int num=0,SID=-1;
        if(isdigit(input[0]))
            SID=stoll(input);
        for(auto i=students.begin();i!=students.end();){
            if(i->SID==SID||i->name==input){
                i=students.erase(i);
                ++num;
            }else
                ++i;
        }
        printf("%d student(s) removed.\n",num);
        printf("Please enter SID or name. Enter 0 to finish.\n");
    }
}
void queryStudent(){
    printf("Please enter SID or name. Enter 0 to finish.\n");
    vector<pair<int,int>>rank;
    for(int i=0;i<students.size();++i)
        rank.push_back({students[i].totalScore,i});
    sort(rank.begin(),rank.end(),[](const pair<int,int>&a,const pair<int,int>&b){
        return a.first>b.first;});
    for(int i=1;i<rank.size();++i)
        if(rank[i].first==rank[i-1].first)
            students[rank[i].second].rank=students[rank[i-1].second].rank;
        else
            students[rank[i].second].rank=i+1;
    string input;
    while(getline(cin,input)&&input!="0"){
        int SID=-1;
        if(isdigit(input[0]))
            SID=stoll(input);
        for(Student&stu:students)
            if(stu.SID==SID||stu.name==input)
                printf("%d %010lld %d %s %d %d %d %d %d %.2f\n",stu.rank,stu.SID,stu.CID,
                       stu.name.c_str(),stu.score[0],stu.score[1],stu.score[2],
                        stu.score[3],stu.totalScore,stu.averageScore+limit);
        printf("Please enter SID or name. Enter 0 to finish.\n");
    }
}
void showStatistics(){
    printf("Please enter class ID, 0 for the whole statistics.\n");
    int input,pass[5]={0};
    double statistics[4][3]={0.0};
    string subject[4]={
        "Chinese", "Mathematics", "English" , "Programming"
    };
    scanf("%d",&input);
    for(Student&stu:students){
        if(input==0||stu.CID==input){
            int passNum=0;
            for(int i=0;i<4;++i){
                statistics[i][0]+=stu.score[i]*1.0;
                if(stu.score[i]>=60){
                    ++passNum;
                    ++statistics[i][1];
                }else
                    ++statistics[i][2];
            }
            if(passNum>0)
                for(int i=passNum;i>0;--i)
                    ++pass[i];
            else
                ++pass[0];
        }
    }
    for(int i=0;i<4;++i){
        statistics[i][0]/=statistics[i][1]+statistics[i][2];
        printf("%s\nAverage Score: %.2f\nNumber of passed students: %.0f\n"
               "Number of failed students: %.0f\n\n",
               subject[i].c_str(),statistics[i][0]+limit,statistics[i][1],statistics[i][2]);
    }
    printf("Overall:\nNumber of students who passed all subjects: %d\n"
           "Number of students who passed 3 or more subjects: %d\n"
           "Number of students who passed 2 or more subjects: %d\n"
           "Number of students who passed 1 or more subjects: %d\n"
           "Number of students who failed all subjects: %d\n\n",
           pass[4],pass[3],pass[2],pass[1],pass[0]);
}
int main(){
    outputMainMenu();
    int input;
    while(~scanf("%d",&input)&&input!=0){
        getchar();
        if(input==1)    addStudent();
        else if(input==2)   removeStudent();
        else if(input==3)   queryStudent();
        else if(input==4)
            printf("Showing the ranklist hurts students\' self-esteem. Don\'t do that.\n");
        else if(input==5)   showStatistics();
        outputMainMenu();
    }
    return 0;
}
