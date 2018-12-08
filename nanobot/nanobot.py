import time
class nanobot :
    def __init__(self, col, row):
        self.table = [[0]*(row+1) for x in range(col+1)]

        leftBottom, leftUp, rightUp, rightBottom = {'X': 1, 'Y': 1}, {'X': 1, 'Y': row}, {'X': col, 'Y': row}, {
            'X': col, 'Y': 1}

        n = 1
        while n <= (row*col):
            for i in range(leftBottom['Y'], leftUp['Y'] + 1):
                self.table[(leftUp['X'])][i] = n
                n += 1

            leftUp['X'] += 1
            leftBottom['X'] += 1

            for i in range(leftUp['X'], rightUp['X'] + 1):
                self.table[i][(leftUp['Y'])] = n
                n += 1

            rightUp['Y'] -= 1
            leftUp['Y'] -= 1

            for i in range(rightUp['Y'], rightBottom['Y'] - 1, -1):
                self.table[(rightUp['X'])][i] = n
                n += 1

            rightUp['X'] -= 1
            rightBottom['X'] -= 1

            for i in range(rightBottom['X'], leftBottom['X'] - 1, -1):
                self.table[i][(rightBottom['Y'])] = n
                n += 1

            leftBottom['Y'] += 1
            rightBottom['Y'] += 1

    def findElement(self, r, c):
        return str(self.table[r][c])

    def findCoordinate(self, val):
        for r in range(len(self.table)):
            for c in range(len(self.table[r])):
                if self.table[r][c] == val :
                    return str(r)+' '+str(c)

if __name__ == '__main__':
    # start_time = time.time()
    botFile = open("nanobot.inp", "rb")
    findbotFile = open("nanobot.out", "wb")
    rowcol = [int(x) for x in botFile.readline().split()]
    find = [int(x) for x in botFile.readline().split()]
    findPos = int(botFile.readline())

    col, row = rowcol[0], rowcol[1]
    findRow, findCol = find[0], find[1]

    bot = nanobot(col, row)

    findbotFile.write(bot.findElement(findRow, findCol) + '\n')
    findbotFile.write(bot.findCoordinate(findPos))

    findbotFile.close()
    botFile.close()
    # print "%s seconds" % (time.time() - start_time)
