##########################################################
#
#       Filename: m_combination.py
#        Created: 2017년 01월 14일
#       Compiler: python3
#         Author: Park seon_jun, bsj0206@naver.com
#        Company: Chonnam National University
#
#
#    Discription: nCk = (n-1Ck) + (n-1Ck-1) 
#                 time complexity O(n*k)
#                 memory complexity O(k)
#
##########################################################

dp = []
n = 0
while n >= 0:
    out = ""
    now = []
    for k in range (0, n+1, 1):
        var = 0
        if n==k or k == 0:
            var = 1
        else:
            var = dp[k]+dp[k-1]
        now.append(var)
        out +="%dC%d = %d  " % (n, k, now[k])
    n+=1
    print(out)
    dp = now



