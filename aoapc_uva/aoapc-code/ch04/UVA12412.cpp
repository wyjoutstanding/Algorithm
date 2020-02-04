#include<bits/stdc++.h>
using namespace std;
#define mainMenu "Welcome to Student Performance Management System (SPMS).\n\n1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n\n"
string tips[6] = {"","Please enter the SID, CID, name and four scores. Enter 0 to finish.",
                "Please enter SID or name. Enter 0 to finish.","Please enter SID or name. Enter 0 to finish.",
                "Showing the ranklist hurts students' self-esteem. Don't do that.", "Please enter class ID, 0 for the whole statistics."};
string courses[4] = {"Chinese", "Mathematics", "English", "Programming"};
string stamess[5] = {"failed all", "passed 1 or more", "passed 2 or more", "passed 3 or more", "passed all"}; // 统计提示信息
typedef struct Student {
    string sid, name;
    int cid, score[4], tot;
}Student;
Student stu;
vector<Student> stuVec; // 数据库
int opt, num = 0, ranks[410]; // 当前选项
bool isChangeRank = true, isChangeSta = true; // 记录是否有插入或删除操作，便于计算总分排名
map<string, int> sidMp; // sid -> student存放位置
map<string, set<int> > nameMp; // name -> student存放位置
typedef struct Statistics { // 资料统计
    int totScore[4], num, pass[4], overall[5]; // 总分，总人数，每科通过人数，汇总数据
}Statistics;
vector<Statistics> info;
void add() { // 插入学生
    while(cin >>stu.sid && stu.sid != "0") {
        cin >>stu.cid >>stu.name; stu.tot = 0;
        for (int i = 0; i < 4; i ++) {
            scanf("%d", &stu.score[i]);
             stu.tot += stu.score[i]; // 计算总分
        }
        if (sidMp.find(stu.sid) == sidMp.end()) { // sid不存在
            isChangeRank = isChangeSta = true; // 标记被改变
            stuVec.push_back(stu); // 保存
            sidMp.insert({stu.sid, num});
            nameMp[stu.name].insert(num++);
        }
        else cout <<"Duplicated SID." <<endl; // sid已存在
        cout <<tips[opt] <<endl; // 提示输入语句
    }
}
void remove() { // 删除学生
    string s; 
    while (cin >>s && s != "0") {
        int cnt = 0;
        if (isdigit(s[0])) { // sid
            if (sidMp.find(s) != sidMp.end()) { // 存在此sid学生
                isChangeRank = isChangeSta = true; cnt = 1; // 删除人数
                nameMp[stuVec[sidMp[s]].name].erase(sidMp[s]); // 维护nameMp
                sidMp.erase(s); // 维护sidMp
            }
        }
        else { // name
            if (nameMp.find(s) != nameMp.end()) { // 存在此名字学生
                isChangeRank = isChangeSta = true; cnt = nameMp[s].size(); // 删除人数
                for (auto i : nameMp[s]) sidMp.erase(stuVec[i].sid); // 维护sidMp
                nameMp.erase(s); // 维护nameMp
            }
        }
        printf("%d student(s) removed.\n", cnt); // 对齐2个宽度，没对齐
        cout <<tips[opt] <<endl; // 提示信息
    }
}
void calRanks() { // 计算总分排名（所有班级）
    int cnt[410] = {0}; // 每个总分出现次数
    for (auto p : sidMp) cnt[stuVec[p.second].tot] ++; // 所有班级的学生
    bool isFirst = true; 
    fill(ranks, ranks+410, 0); // 初始化
    for (int i = 400; i >= 0; i --) { // 计算每个总分对应的排名
        if (isFirst && cnt[i] != 0) ranks[i] = 1, isFirst = false; // 第一个不为0的是rank-1
        else ranks[i] = ranks[i+1] + cnt[i+1];
    }
    isChangeRank = false; // 标记已更新
}
void query() { // 根据sid/name查询学生
    string s;
    while (cin >>s && s != "0") {
        set<int> query; // 存放要输出的学生标号(stuVec下标)，自动有序，按输入顺序排列
        if (isdigit(s[0])) { // sid
            if (sidMp.find(s) != sidMp.end()) query.insert(sidMp[s]);
        }
        else { // name
            if (nameMp.find(s) != nameMp.end()) query = nameMp[s];
        }
        if (isChangeRank) calRanks(); // 有插入或删除需重新计算排名，这里只是为了提高效率
        for (auto i : query) { // 按输入顺序输出结果
            auto p = stuVec[i];
            printf("%d %s %d %s", ranks[p.tot], p.sid.c_str(), p.cid, p.name.c_str());
            for (int j = 0; j < 4; j ++) printf(" %d", p.score[j]);
            printf(" %d %.2lf\n", p.tot, (double)p.tot / 4.0);
        }
        cout <<tips[opt] <<endl; // 提示语句
    }
}
void calStatistics() { // 计算统计结果
    vector<Statistics> vec(25);
    set<int> classes; // 存在的班级
    vec[0].num = sidMp.size(); // 综合统计（所有班级）,所有班级总人数
    for (auto kv : sidMp) { // 遍历所有学生
        auto p = stuVec[kv.second]; // 学生
        vec[p.cid].num ++; // 班级cid的总人数
        classes.insert(p.cid); // 记录存在的班级
        int cnt = 0; // 统计此人通过的数量(>=60)
        for (int i = 0; i < 4; i ++) {
            vec[p.cid].totScore[i] += p.score[i];
            vec[0].totScore[i] += p.score[i]; // 综合统计（所有班级）
            if (p.score[i] >= 60) {
                vec[p.cid].pass[i] ++; // 班级cid中i学科通过人数
                vec[0].pass[i] ++; // 综合统计（所有班级）,通过该课人数
                cnt ++; // 未挂科数量
            }
        }
        vec[p.cid].overall[cnt] ++; // 计算通过i科的人数
        vec[0].overall[cnt] ++; // 综合统计（所有班级）,通过i科人数
    }
    classes.insert(0); // 综合统计
    for (auto c : classes) { // 计算overall
        for (int i = 3; i >= 1; i --) vec[c].overall[i] += vec[c].overall[i+1];
    }
    info = vec; // 保存结果
}
void showStatistics() { // 显示统计数据
    int cid; cin >>cid;
    if (isChangeSta) calStatistics(); // 被改变，需先更新统计数据
    auto p = info[cid];
    for (int i = 0; i < 4; i ++) {
        cout <<courses[i] <<endl;
        double f;
        if (p.num == 0) f = 0.00; // 分母为0！！！
        else {
            f = (double)p.totScore[i] / p.num + 1e-5; // 加上损失精度
            f = floor(f*100 + 0.5) / 100; // 四舍五入，精确到百分位
        }
        printf("Average Score: %.2lf\n", f);
        printf("Number of passed students: %d\nNumber of failed students: %d\n\n", p.pass[i], p.num - p.pass[i]);
    }
    printf("Overall:\n");
    for (int i = 4; i >= 0; i --) {
        printf("Number of students who %s subjects: %d\n", stamess[i].c_str(), p.overall[i]);
    }
    puts(""); // 空行
}
int main() {
    do {
        printf(mainMenu); // 主界面
        scanf("%d", &opt);
        if (opt != 0) cout <<tips[opt] <<endl; // 提示信息
        switch (opt) {
            case 0: opt = -1; break;        // 结束
            case 1: add(); break;           // 增加
            case 2: remove(); break;        // 移除
            case 3: query(); break;         // 查询
            case 4: break;   // 显示排名
            case 5: showStatistics(); break; // 显示统计结果
        }
    } while (opt != -1);
    return 0;
}