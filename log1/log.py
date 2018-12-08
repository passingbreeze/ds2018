import time
import bisect

class connectLog :
    def __init__(self):
        self.table = []
        with open("syslog.txt", "rb") as logF:
            for line in logF:
                temp = line
                self.table.append([int(x) for x in temp.split() if int(x) > 0])
        self.logLine = self.table[0][0]
        del self.table[0]

    def findNum(self):
        outF = open("log.out", "wb")
        self.inpTab = []
        with open("log.inp", "rb") as inpF:
            for line in inpF:
                temp = line
                self.inpTab.append([x for x in temp.split()])
        self.recLine = int(self.inpTab[0][0])
        del self.inpTab[0]

        cnt = 0
        for i in xrange(self.recLine) :
            d_beg, t_beg, d_end, t_end = map(int, self.inpTab[i])
            for j in xrange(self.logLine):
                d_beg_idx = bisect.bisect_left(self.table[j], d_beg)
                d_end_idx = bisect.bisect_left(self.table[j], d_end)
                print str(j), d_beg_idx, d_end_idx
                if d_beg == d_end and self.table[j][0] == d_beg:
                    t_beg_idx = bisect.bisect_left(self.table[j], t_beg, lo=1, hi=len(self.table[j]))
                    t_end_idx = bisect.bisect_left(self.table[j], t_end, lo=1, hi=len(self.table[j]))
                    cnt+=(len(self.table[j])-1) - (t_end_idx-t_beg_idx)
                    #
                    # for k in xrange(1, len(self.table[j])):
                    #     if self.table[j][k] < t_beg or self.table[j][k] > t_end :
                    #         cnt -= 1
                elif self.table[j][0] > d_beg and self.table[j][0] < d_end :
                    cnt += (len(self.table[j])-1)

                elif self.table[j][0] == d_beg :
                    t_beg_idx = bisect.bisect_left(self.table[j], t_beg, lo=1, hi=len(self.table[j]))
                    cnt += (len(self.table[j])-1) - t_beg_idx
                    # for k in xrange(1, len(self.table[j])):
                    #     if self.table[j][k] < t_beg :
                    #         cnt -= 1
                elif self.table[j][0] == d_end :
                    t_end_idx = bisect.bisect_left(self.table[j], t_end, lo=1, hi=len(self.table[j]))
                    cnt += (t_end_idx-1)
                    # for k in xrange(1, len(self.table[j])):
                    #     if self.table[j][k] > t_end :
                    #         cnt -= 1
            if i < self.recLine :
                outF.write(str(cnt)+'\n')
            else :
                outF.write(str(cnt))
            cnt = 0

        outF.close()

def main():
    beg = time.time()

    set_beg = time.time()
    ex = connectLog()
    print "setting time -> " + str(time.time() - set_beg) + " sec(s)"

    find_beg = time.time()
    ex.findNum()
    print "searching time -> " + str(time.time() - find_beg) + " sec(s)"

    print "total time -> " + str(time.time() - beg)  + " sec(s)"
    return

if __name__ == '__main__':
    main()
