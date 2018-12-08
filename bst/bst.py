#-*-coding:utf-8-*-

class Node:
    def __init__(self, name, depth):
        self.name = name
        self.depth = depth
        self.left = None
        self.right = None

class BinarySearchTree:
    def __init__(self):
        self.root = None
        self.leaflist = []
        self.depmap = {}

    def insert(self, inpdata, depth):
        self.root = self.insnode(self.root, inpdata, depth)
        return self.root is not None

    def insnode(self, node, inpdata, level):
        if node is None:
            node = Node(inpdata, level)
        else :
            if node.name <= inpdata :
                level+=1
                node.left = self.insnode(node.left, inpdata, level)
            else :
                level+=1
                node.right = self.insnode(node.right, inpdata, level)
        return node

    def findleaf(self):
        self.getleaf(self.root)
        return " ".join(self.leaflist)

    def getleaf(self, root):
        if root.left is None and root.right is None :
            self.leaflist.append(root.name)
        if root.left is not None :
            root = self.getleaf(root.left)
        if root.right is not None :
            root = self.getleaf(root.right)

    def depth(self, key):
        deps = []
        self.finddepth(self.root, key)
        i = len(self.depmap)
        while i > 0:
            if self.depmap[key] is None :
                deps.append("NO")
            else:
                deps.append(self.depmap[key])
            i-=1
        return " ".join(deps)

    def finddepth(self, root, k):
        if root.depth == k :
            self.depmap[k] = root.name
        if root.left is not None :
            self.finddepth(root.left, k)
        if root.right is not None :
            self.finddepth(root.right, k)

    def findMaxMin(self, root):
        temp = sub = None
        if root.left is not None :
            temp = root.left
            sub = root.left
            while temp.right is not None :
                sub = temp.right
                temp = temp.right
        elif root.right is not None :
            temp = root.right
            sub = root.right
            while temp.left is not None :
                sub = temp.left
                temp = temp.left
        return sub

    def remove(self, root):
        if root.left is None and root.right is None :
            root = None
        else :
            sub = self.findMaxMin(root)
            root.name = sub.name
            self.remove(root)

    def delNode(self, root, inpdata):
        if root is not None:
            if root.name == inpdata :
                self.remove(root)
            elif root.name > inpdata :
                self.delNode(root.left, inpdata)
            elif self.root.name < inpdata :
                self.delNode(root.right, inpdata)

def main():
    cmdList = []
    with open("bst.inp", "rb") as inp :
        cmdNum = int(inp.readline())
        for line in inp :
            cmdList.append(line.rstrip())
    defDepth = 1

    bst = BinarySearchTree()
    result = ""

    for line in cmdList :
        if "+" in line:
            cutCmd = line.split()
            cutCmd.pop(0) # delete "+"
            key = cutCmd[0]
            bst.insert(key, defDepth)
        elif "-" in line:
            cutCmd = line.split()
            cutCmd.pop(0)  # delete "-"
            key = cutCmd[0]
            bst.delNode(bst.root,key)
        elif "depth" in line:
            cutCmd = line.split()
            cutCmd.pop(0)
            key = cutCmd[0]
            result+=bst.depth(key)+"\n"
        elif "leaf" in line:
            result+=bst.findleaf()+"\n"

    result.rstrip()
    with open("bst.out", "wb") as out:
        out.write(result)
    return

if __name__ == '__main__':
    main()