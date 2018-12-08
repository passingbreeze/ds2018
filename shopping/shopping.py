from collections import deque

class shopping :
    def __init__(self):
        self.Q = []
        with open("shopping.inp", "rb") as inp:
            self.pplNum, self.QNum = map(int, inp.readline().split())
            for i in xrange(self.QNum):
                if i==self.pplNum:
                    self.QNum = self.pplNum
                    break
                self.Q.append(deque())
                self.Q[i].append(map(int, reversed(inp.readline().split())))
            for line in inp:
                temp = map(int, reversed(line.split()))
                minv = self.Q[0][0][0]
                minIdx = 0
                for i in xrange(self.QNum):
                    if minv > self.Q[i][0][0]:
                        minv = self.Q[i][0][0]
                        minIdx = i
                temp[0] += self.Q[minIdx][0][0]
                self.Q[minIdx].appendleft(temp)

    def getOrd(self):
        result = []
        minIdx = 0
        while self.QNum > 0:
            minv = self.Q[minIdx][-1][0]
            for i in xrange(self.QNum):
                if minv > self.Q[i][-1][0]:
                    minv = self.Q[i][-1][0]
            for i in xrange(self.QNum-1, -1, -1):
                if minv == self.Q[i][-1][0]:
                    result.append(str(self.Q[i][-1][1]))
                    minIdx = i
                    self.Q[minIdx].pop()
                    break
            if len(self.Q[minIdx]) == 0:
                self.Q.pop(minIdx)
                self.QNum -= 1
                minIdx=0
        with open("shopping.out", "wb") as out:
            out.write('\n'.join(result))

def main():
    solv = shopping()
    solv.getOrd()
    return
if __name__ == '__main__':
    main()
