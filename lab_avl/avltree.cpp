/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->right;
    t->right = y->left;
    y->left = t;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right)) + 1;
    t = y;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->left;
    t->left = y->right;
    y->right = t;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right)) + 1;
    t = y;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    
    if (balance >= 2) {
      int rightBalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
      if (rightBalance >= 1) rotateLeft(subtree);
      else rotateRightLeft(subtree);
    }
    if (balance <= -2) {
      int leftBalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
      if (leftBalance <= -1) rotateRight(subtree);
      else rotateLeftRight(subtree);
    }
    subtree->height = max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right)) + 1;   
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL)
	subtree = new Node(key, value);
    if(key > subtree->key) insert(subtree->right, key, value);
    if(key < subtree->key) insert(subtree->left, key, value);

    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
	remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
	remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
	    delete subtree;
	    subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
	    Node* IOP = subtree->left;
            while (IOP->right != NULL) 
		IOP = IOP->right;	// Find IOP
            swap(subtree, IOP);
	    remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
	    Node* temp = subtree;
	    if (subtree->left != NULL && subtree->right == NULL) subtree = subtree->left;
	    if (subtree->left == NULL && subtree->right != NULL) subtree = subtree->right;
	    delete temp;
	    temp = NULL;
        }
        // your code here
	
    }
    if (subtree != NULL)
	rebalance(subtree);
}
