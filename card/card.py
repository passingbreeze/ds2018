#-*-coding:utf-8-*-

def readFile(cmdList):
    with open("card.inp", "rb") as inp:
        getNum = inp.readline().split()
        for order in inp:
            cmdList.append(order.rstrip())
    return getNum

class cardDeck :
    def __init__(self, cardNum):
        self.card = [i for i in xrange(1,cardNum+1)]
        self.midIdx = 0

        if cardNum%2 == 0:
            self.midIdx = int(cardNum/2)
        else :
            self.midIdx = int(cardNum/2)+1

        self.top_mid = self.card[:self.midIdx]
        self.mid_bottom = self.card[self.midIdx:]

    def shuffle(self):
        self.card = self.top_mid
        shuffleIdx = 1
        for n in self.mid_bottom:
            self.card.insert(shuffleIdx, n)
            shuffleIdx += 2
        self.top_mid = self.card[:self.midIdx]
        self.mid_bottom = self.card[self.midIdx:]

    def cut(self, beg, end):
        cutPart = self.card[beg-1:end]
        del self.card[beg-1:end]
        self.card += cutPart
        self.top_mid = self.card[:self.midIdx]
        self.mid_bottom = self.card[self.midIdx:]

    def card_Top_Mid_Bottom(self):
        midIdx = int(len(self.card)/2)-1
        bottomIdx = len(self.card) - 1
        result = [str(self.card[0]), str(self.card[midIdx]), str(self.card[bottomIdx])]
        with open("card.out", "wb") as out:
            out.write(' '.join(result))

def main():
    cmd = []
    cardNum, operNum = map(int, readFile(cmd))
    # set cardNum, operNum and Command list

    pack = cardDeck(cardNum)
    for line in cmd: # read Command list by line
        if 'Shuffle' in line:
            pack.shuffle()
        if 'Cut' in line:
            cutCmd = line.split()
            cutCmd.pop(0) # remove 'Cut' command
            # cutCmd = ['cutBeginNum', 'cutEndNum']
            cutBeg, cutEnd = map(int, cutCmd)
            pack.cut(cutBeg, cutEnd)

    pack.card_Top_Mid_Bottom()
    return

if __name__ == '__main__':
    main()