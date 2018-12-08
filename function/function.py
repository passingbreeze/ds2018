#-*-coding:utf-8-*-

funcStmt = []   # function statement
mainMem = {}    # in main memory
dlChk = {}      # check deadlock
callPos = []    # saving calling position
result = ["NONE","NONE"]

def getFile():
    with open("function.inp","rb") as inp:
        for line in inp:
            funcStmt.append(line.split())
        global numF, fPos, sPos # number of functions, first position, second position
        numF, fPos, sPos = map(int, funcStmt.pop(0))
        for i in xrange(numF):
            mainMem[funcStmt[i].pop(0)] = i

def funcCall():
    i,j,cnt = mainMem['M'], 0, 0
    callPos.append(list(('M', mainMem['M'])))
    dlChk[funcStmt[i][j]] = 1

    while True:
        if len(funcStmt[i][j]) == 1 and funcStmt[i][j].isupper() :
            if funcStmt[i][j] not in dlChk.keys():
                dlChk[funcStmt[i][j]] = 1
            elif funcStmt[i][j] in dlChk.keys() and dlChk[funcStmt[i][j]] == 1 :
                with open("function.out", "wb") as out:
                    out.write("DEADLOCK")
                return

            callPos.append(list((funcStmt[i][j], j)))
            i = mainMem[funcStmt[i][j]]
            j = 0

        elif funcStmt[i][j] == "$":
            j = callPos[-1][1] + 1
            dlChk[callPos[-1][0]]=0
            callPos.pop()
            if len(callPos) == 0:
                break
            i = mainMem[callPos[-1][0]]

        else :
            if cnt == fPos-1:
                result[0] = callPos[-1][0] + "-" + funcStmt[i][j]
            elif cnt == sPos-1:
                result[1] = callPos[-1][0] + "-" + funcStmt[i][j]
            j+=1
            cnt+=1

    with open("function.out", "wb") as out:
        out.write('\n'.join(result))
    return

def main():
    getFile()
    funcCall()
    return

if __name__ == '__main__':
    main()