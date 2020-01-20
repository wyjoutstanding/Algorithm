mp = {}#dic初始化
n = eval(input())
for i in range(n):
    name, id, score = input().split()#分割出来的均是字符串
    name_id = f"{name} {id}"#格式拼接
    score = int(score)
    mp[score] = name_id
lmp = list(mp.keys())#dic的keys转换为list进行排序
lmp.sort()#升序排列
print(mp[lmp[n-1]])
print(mp[lmp[0]])