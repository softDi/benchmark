#include <stdio.h>
#include <stdlib.h>

class RBTreeNode {
    int key;
    int value;
    bool visited;
    RBTreeNode *lc, *rc;

public:
    RBTreeNode(const int& in_key, const int& in_value)
    {
        key = in_key;
        value = in_value;
    }
    RBTreeNode()
    {
        key = 0;
        value = 0;
    }

    int search(const RBTreeNode& node, const int& key);
    void travel(void);
    static void release(RBTreeNode* node);
    void insert(const int& key, const int& value);
};

void RBTreeNode::insert(const int& key, const int& value)
{
    bool bInsertToLeft = true;

    if (key > this->key) {
        bInsertToLeft = false;
    }

    if (bInsertToLeft) {
        if (lc) {
            lc->insert(key, value);
        } else {
            lc = new RBTreeNode(key, value);
        }
    } else {
        if (rc) {
            rc->insert(key, value);
        } else {
            rc = new RBTreeNode(key, value);
        }
    }
}

int RBTreeNode::search(const RBTreeNode& node, const int& key)
{
    if (key == node.key) {
        return node.value;
    } else {
        if (key > node.key) {
            return search(*node.lc, key);
        } else {
            return search(*node.rc, key);
        }
    }
}

void RBTreeNode::travel(void)
{
    printf("[%d]=%d\n", key, value);
    if (lc) {
        lc->travel();
    }
    if (rc) {
        rc->travel();
    }
}

void RBTreeNode::release(RBTreeNode* node)
{
    if (node) {
        if (node->lc) {
            RBTreeNode::release(node->lc);
        }
        if (node->rc) {
            RBTreeNode::release(node->rc);
        }
        delete node;
    }
}

int main(int argc, char* argv[])
{
    RBTreeNode* rbtree = new RBTreeNode(3, 9);
    rbtree->insert(13, 9);
    rbtree->insert(1, 3);
    rbtree->insert(2, 4);
    rbtree->travel();
    RBTreeNode::release(rbtree);
    return 0;
}
