class parkingLot :
    def __init__(self):
        self.logTable = []
        with open("parking.inp", "rb") as inp :
            for line in inp :
                if len(line.rstrip().split()) > 1:
                    self.minSlot, self.carNum = map(int, line.rstrip().split())
                else :
                    self.logTable.append(int(line.rstrip()))

    def letsParking(self):
        slotNum = self.minSlot
        slotLim = 0
        parkSlot = []
        eleNum = 0

        for carN in self.logTable:
            if carN > 0 :
                if eleNum == slotNum:
                    slotNum <<= 1
                    slotLim =  slotNum / 3
                try :
                    inpIdx = parkSlot.index(0)
                    parkSlot[inpIdx] = carN
                except ValueError :
                    parkSlot.append(carN)
                eleNum += 1

            elif carN < 0:
                exIdx = parkSlot.index(-carN)
                parkSlot[exIdx] = 0
                eleNum -= 1
                if self.logTable.index(carN) == len(self.logTable) - 1:
                    break
                if eleNum == slotLim :
                    slotNum = int(slotNum >> 1)
                    if slotNum < self.minSlot :
                        slotNum = self.minSlot
                    temp = []
                    for i in parkSlot :
                        if i > 0:
                            temp.append(i)
                    parkSlot = temp
                    slotLim = slotNum/3

        with open("parking.out", "wb") as out :
            outstr = ""
            for k,v in enumerate(parkSlot):
                if v > 0:
                    outstr += str(k + 1) + ' ' + str(v) + '\n'
            out.write(outstr.rstrip())

def main():
    ex = parkingLot()
    ex.letsParking()
    return

if __name__ == '__main__':
    main()