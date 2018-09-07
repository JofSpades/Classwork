#include <iostream>
using namespace std;
 
// Struct for tree nodes
struct treeNode {
    int data;
    int level;  // The level of the node in the tree.
    treeNode *pLeft;
    treeNode *pRight;
};
 
// Make a new tree node, returning its address
treeNode * newTreeNode(int value, treeNode *left, treeNode *right, int level)
{
    treeNode *pTemp = new treeNode;
     
    pTemp->data = value;
    pTemp->pLeft = left;
    pTemp->pRight = right;
    pTemp->level = level;
     
    return pTemp;
}
 
// Perform a recursive in-order traversal
void inOrderTraversal( treeNode * pRoot)
{
    if( pRoot != NULL) {
        inOrderTraversal(pRoot->pLeft);   // recurse down to the left
        cout << "Data: " << pRoot->data << " ";
        cout << "Level: " << pRoot->level << "\n";
        inOrderTraversal(pRoot->pRight);  // recurse down to the right
    }
}
 
// Insert a value into the tree in order.
//
// TODO 1 : Change this function to assgin correct value to level.
void insertIntoTree(treeNode *&pCurrent, int value, int level)
{
    if( pCurrent == NULL) {
        pCurrent = newTreeNode( value, NULL, NULL, level + 1);
    }
    else if( value == pCurrent->data ) {
        cout << "Skipping that value, as it is already in tree.\n";
    }
    else if( value < pCurrent->data) {
        // Search for insert position in the left subtree.
        insertIntoTree(pCurrent->pLeft, value, level + 1);
    }
    else {
        // Search for insert position in the right subtree.
        insertIntoTree(pCurrent->pRight, value, level + 1);
    }
}
// Alternate function signature
void insertIntoTree(treeNode *&pCurrent, int value) {
    insertIntoTree(pCurrent, value, 0);
}
 
// Declare structure for a queue node
struct queueNode {
    treeNode * treeN; // Each queueNode holds a pointer to a treeNode
    queueNode * pNext;
};
 
// Add a new node to the end of the queue
void addToBack(queueNode *& pFront, queueNode *& pBack, treeNode *treeNode) {
     
    queueNode * pTemp = new queueNode;
    pTemp->treeN = treeNode;
    pTemp->pNext = NULL;
     
    // See if this is the first node.
    if (pBack == NULL) {
        // pBack is NULL, so this is the first node.
        // Adjust pFront as well.
        pFront = pTemp;
    } else {
        // Append to back of queue.
        pBack->pNext = pTemp;
         
    }
     
    // Reset back pointer to point to new back of queue
    pBack = pTemp;
}
 
// Pop one node from the front of the queue,
// return the treeNode that was stored in that node.
treeNode * removeFromFront(queueNode *& pFront, queueNode *& pBack) {
     
    if (pFront == NULL) return NULL;
     
    treeNode * returnNode = pFront->treeN;
    queueNode * pTemp = pFront;
     
    pFront = pFront->pNext;
     
    // If that was the last node and was just removed, also adjust the back pointer
    if (pFront == NULL) pBack = NULL;
     
    delete pTemp;
     
    return returnNode;
}
 
void displayQueue(queueNode *pFront) {
    cout << "\nFrom front to back queue is:  ";
    while(pFront != NULL) {
        cout << pFront->treeN << " ";
        pFront = pFront->pNext;
    }
    cout << "\n";
}
 
// TASK 2 : Implement BFS and output the tree, one level at a time, starting from the root. 
// IMPORTANT: Each level should be on a new line.


void BFS(treeNode * pRoot) {
    queueNode * pFront = NULL;
    queueNode * pEnd = NULL;

    addToBack(pFront, pEnd, pRoot);

    while(pFront != NULL){

        if(pRoot->pLeft->level == pRoot->level - 1){

            addToBack(pFront, pEnd, pRoot->pLeft);

        }

        if(pRoot->pRight->level == pRoot->level - 1){

            addToBack(pFront, pEnd, pRoot->pRight);

        }

        pRoot = pRoot->pLeft;

    }

    displayQueue(pFront);
}
 
// TASK 3 : Implement BFS without using level info.
 
void BFSNotUsingLevel(treeNode * pRoot) {
    queueNode * pFront = NULL;
    queueNode * pEnd = NULL;
     
    treeNode * pEndOfLevel = NULL; // This is a hint...
}
 
int main(int argc, const char * argv[])
{
    treeNode * pRoot = NULL;
     
    insertIntoTree(pRoot, 5);
    insertIntoTree(pRoot, 2);
    insertIntoTree(pRoot, 8);
    insertIntoTree(pRoot, 1);
    insertIntoTree(pRoot, 4);
    insertIntoTree(pRoot, 6);
    insertIntoTree(pRoot, 9);
    insertIntoTree(pRoot, 3);
    insertIntoTree(pRoot, 7);
     
    cout << "In order traversal: " << endl;
    inOrderTraversal(pRoot);
    cout << endl;
     
    cout << "Breadth-first traversal, using level: " << endl;
    BFS(pRoot);
    cout << endl;
     
    cout << "Breadth-first traversal, NOT using level: " << endl;
    BFSNotUsingLevel(pRoot);
    cout << endl;
     
    return 0;
}