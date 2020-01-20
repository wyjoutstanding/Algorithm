upper = '2014/09/06'
lower = '1814/09/06'
cnt = 0
bmax = lower
bmin = upper
n = eval(input())
for i in range(n):
    name, idate = input().split()
    # yy, mm, dd = sdate.split("/")
    # sdate = yy + mm + dd
    # idate = int(sdate)
    if idate >= lower and idate <= upper:
        cnt += 1
        if idate < bmin:
            older = name
            bmin = idate
        if idate > bmax:
            young = name
            bmax = idate
print(cnt, end='')#不换行
if cnt != 0:
    print(" "+older+" "+young)#,会自动输出一个空格
