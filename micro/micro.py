#-*-coding:utf-8-*-

class slideglass :
    def __init__(self):
        self.viruscount = []
        self.map = []
        with open("micro.inp", "rb") as inp:
            self.col, self.row, self.stdsize = map(int, inp.readline().split())
            for line in inp:
                self.map.append(line.split())

    def findVirus(self):
        virusPos = []
        visitQ = []
        for r in xrange(self.row):
            for c in xrange(self.col):
                if self.map[r][c] == "#" :
                    virusPos.append([r,c])

        while len(virusPos) > 0 :
            size = 1
            visitQ.append(virusPos.pop(0))
            while len(visitQ) > 0 :
                if [visitQ[0][0]-1, visitQ[0][1]] in virusPos :
                    size+=1
                    virusPos.remove([visitQ[0][0]-1, visitQ[0][1]])
                    if [visitQ[0][0]-1, visitQ[0][1]] not in visitQ:
                        visitQ.append([visitQ[0][0]-1, visitQ[0][1]])
                if [visitQ[0][0], visitQ[0][1]+1] in virusPos :
                    size+=1
                    virusPos.remove([visitQ[0][0], visitQ[0][1]+1])
                    if [visitQ[0][0], visitQ[0][1]+1] not in visitQ:
                        visitQ.append([visitQ[0][0], visitQ[0][1]+1])
                if [visitQ[0][0]+1, visitQ[0][1]] in virusPos :
                    size+=1
                    virusPos.remove([visitQ[0][0]+1, visitQ[0][1]])
                    if [visitQ[0][0]+1, visitQ[0][1]] not in visitQ:
                        visitQ.append([visitQ[0][0]+1, visitQ[0][1]])
                if [visitQ[0][0], visitQ[0][1]-1] in virusPos :
                    size+=1
                    virusPos.remove([visitQ[0][0], visitQ[0][1]-1])
                    if [visitQ[0][0], visitQ[0][1]-1] not in visitQ:
                        visitQ.append([visitQ[0][0], visitQ[0][1]-1])
                visitQ.pop(0)
            if size >= self.stdsize:
                self.viruscount.append(size)

    def getResult(self):
        with open("micro.out", "wb") as out:
            out.write(str(len(self.viruscount))+ " " + str(max(self.viruscount)))

def main():
    exp = slideglass()
    exp.findVirus()
    exp.getResult()
    return

if __name__ == '__main__':
    main()