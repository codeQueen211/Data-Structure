#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H


#include <iostream>

typedef enum {
    AVL_SUCCESS=0,
    AVL_NULL_PTR=-1,
    AVL_MEMORY_ERROR=-2
} AVLTreeResult;

/**
 * A functor to copy T type variables into a given array.
 * Complexity depends on T operator=() complexity.
 */
template<typename T>
class addToArray {
    T *array;
    int index;
public:
    explicit addToArray(T *arr) : array(arr), index(0) {}

    void operator()(const T& t) {
        array[index]=t;
        index++;
    }
};

/**
* A functor to copy T type variables from a given array.
* Complexity depends on T operator=() complexity.
*/
template<typename T>
class insertData {
    T *array;
    int index;
public:
    explicit insertData(T *arr) : array(arr), index(0) {}

    void operator()(T& t) {
        t=array[index];
        index++;
    }
};

template<typename T>
class AVLTree {
    class Node {
        T data;
        int height;
        //sara added here
        int expenses;
        Node *left;
        Node *right;
        Node *parent;
    public:
        Node(const T& val=T(), int h=0,int exp = 0, Node *l=nullptr,
             Node *r=nullptr, Node *p=nullptr) : data(val), height(h), expenses(exp),//sara added here
                                                 left(l), right(r),
                                                 parent(p) {};

        Node(const Node&) = delete;

        Node& operator=(const Node&) = delete;

        ~Node() = default;

        T& getData() {
            return data;
        }

        int& getHeight() {
            return height;
        }
        //sara added here
        int& getExpenses() {
            return expenses;
        }
        //sara added here 
        void updateExpenses(int expensesToAdd) {
        expenses += expensesToAdd;
        }

        Node *& getLeft() {
            return left;
        }

        Node *& getRight() {
            return right;
        }

        Node *& getParent() {
            return parent;
        }

        /**
         * @return Balance factor of the node in O(1).
         */
        const int getBF() const {
            int l=0, r=0;
            if (left) {
                l=left->getHeight()+1;
            }
            if (right) {
                r=right->getHeight()+1;
            }
            return l-r;
        }
    };

    Node *root;

    static int max(int a, int b) {
        return a>=b ? a : b;
    }
    
    /**
     * Creates an empty complete binary tree with n nodes in O(n).
     * @param parent - A pointer to the current node parent.
     * @param i - Current node index in a sorted array.
     * @param n - Number of nodes in the tree.
     * @return A pointer to the empty complete binary tree root.
     */
    static Node *
    createCompleteTree(Node *parent, int i, int n) {
        if (i>=n) {
            return nullptr;
        }
        try {
            Node *root=new Node(T(), 0, nullptr, nullptr, parent);
            root->getRight()=createCompleteTree(root, i*2+2, n);
            root->getLeft()=createCompleteTree(root, i*2+1, n);
            if (!root->getLeft() && !root->getRight()) {
                root->getHeight()=0;
            } else if (!root->getLeft()) {
                root->getHeight()=(1+root->getRight()->getHeight());
            } else if (!root->getRight()) {
                root->getHeight()=(1+root->getLeft()->getHeight());
            } else {
                root->getHeight()=(1+max(root->getLeft()->getHeight(),
                                         root->getRight()->getHeight()));
            }
            return root;
        } catch (std::bad_alloc& e) {
            throw e;
        }
    }

    /**
     * Returns the minimum value found in n sub-tree.
     * Time complexity of O(log(m)) where m is the size of the sub-tree.
     * @param n - The root of the given sub-tree;
     */
    Node *findMin(Node *n) const {
        Node *current=n;
        while (current->getLeft()!=nullptr) {
            current=current->getLeft();
        }
        return current;
    }

    /**
     * Returns the maximum value found in n sub-tree.
     * Time complexity of O(log(m)) where m is the size of the sub-tree.
     * @param n - The root of the given sub-tree;
     */
    Node *findMax(Node *n) const {
        Node *current=n;
        while (current->getRight()!=nullptr) {
            current=current->getRight();
        }
        return current;
    }

    /**
     * Runs through a given sub-tree inorder, activating a functor on each node.
     * The number of nodes to travel through can be limited.
     * The complexity is O(nm), where n is the number of nodes in the travel and
     * m is the complexity of the functor.
     * @param n - The current node in the run.
     * @param action - The given functor.
     * @param nodes_num - number of nodes left to travel through.
     */
    template<typename Act>
    void inorder(Node *n, Act& action, int *nodes_num) {
        if (!n || !(*nodes_num)) {
            return;
        }
        inorder(n->getLeft(), action, nodes_num);
        if (!(*nodes_num)) {
            return;
        }
        action(n->getData());
        (*nodes_num)--;
        if (!(*nodes_num)) {
            return;
        }
        inorder(n->getRight(), action, nodes_num);
    }

    /**
     * Runs through a given sub-tree inorder, activating a functor on each node.
     * The number of nodes to travel through can be limited.
     * The complexity is O(nm), where n is the number of nodes in the travel and
     * m is the complexity of the functor.
     * @param n - The current node in the run.
     * @param action - The given functor.
     * @param nodes_num - number of nodes left to travel through.
     */
    template<typename Act>
    void inorder(Node *n, Act& action, int *nodes_num) const {
        if (!n || !(*nodes_num)) {
            return;
        }
        inorder(n->getLeft(), action, nodes_num);
        if (!(*nodes_num)) {
            return;
        }
        action(n->getData());
        (*nodes_num)--;
        if (!(*nodes_num)) {
            return;
        }
        inorder(n->getRight(), action, nodes_num);
    }

    /**
     * Runs through a given sub-tree post-order, deleting each node.
     * The complexity is O(n), where n is the number of nodes in the tree.
     * @param n - The current node in the run.
     */
    void postorderDelete(Node *n) {
        if (!n) {
            return;
        }
        postorderDelete(n->getLeft());
        postorderDelete(n->getRight());
        delete n;
    }

    /**
     * Preforms a LL rotation on a given tree in O(1).
     * @param n - The given tree root.
     * @return The rotated tree root.
     */
    Node *leftLeftRotate(Node *n) {
        Node *tmp=n->getLeft();
        n->getLeft()->getParent()=n->getParent();
        n->getLeft()=n->getLeft()->getRight();
        if (tmp->getRight()) {
            tmp->getRight()->getParent()=n;
        }
        if (n->getParent()) {
            if (n->getParent()->getLeft()) {
                if (n->getParent()->getLeft()->getData()==n->getData()) {
                    n->getParent()->getLeft()=tmp;
                } else {
                    n->getParent()->getRight()=tmp;
                }
            } else {
                n->getParent()->getRight()=tmp;
            }
        }
        n->getParent()=tmp;
        tmp->getRight()=n;
        updateHeight(n);
        updateHeight(tmp);
        return tmp;
    }

    /**
     * Preforms a RR rotation on a given tree in O(1).
     * @param n - The given tree root.
     * @return The rotated tree root.
     */
    Node *rightRightRotate(Node *n) {
        Node *tmp=n->getRight();
        n->getRight()->getParent()=n->getParent();
        n->getRight()=n->getRight()->getLeft();
        if (tmp->getLeft()) {
            tmp->getLeft()->getParent()=n;
        }
        if (n->getParent()) {
            if (n->getParent()->getLeft()) {
                if (n->getParent()->getLeft()->getData()==n->getData()) {
                    n->getParent()->getLeft()=tmp;
                } else {
                    n->getParent()->getRight()=tmp;
                }
            } else {
                n->getParent()->getRight()=tmp;
            }
        }
        n->getParent()=tmp;
        tmp->getLeft()=n;
        updateHeight(n);
        updateHeight(tmp);
        return tmp;
    }

    /**
     * Preforms a RL rotation on a given tree in O(1).
     * @param n - The given tree root.
     * @return The rotated tree root.
     */
    Node *rightLeftRotate(Node *n) {
        leftLeftRotate(n->getRight());
        return rightRightRotate(n);
    }

    /**
     * Preforms a LR rotation on a given tree in O(1).
     * @param n - The given tree root.
     * @return The rotated tree root.
     */
    Node *leftRightRotate(Node *n) {
        rightRightRotate(n->getLeft());
        return leftLeftRotate(n);
    }

    /**
     * Finds if a given value is in a sub-tree with n nodes in O(logn).
     * @param n - The given sub-tree root.
     * @param val - The searched value.
     * @return A pointer to the node with the given value or nullptr if such
     * a node doesn't exist in the sub-tree.
     */
    Node *find(Node *n, const T& val) const {
        if (!n) {
            return nullptr;
        } else if (val==n->getData()) {
            return n;
        } else if (val<n->getData()) {
            return find(n->getLeft(), val);
        } else {
            return find(n->getRight(), val);
        }
    }

    /**
     * Updates the given node height in O(1).
     * @param n - The node to update.
     */
    void updateHeight(Node *n) {
        if (!n) {
            return;
        } else if (!n->getLeft() && !n->getRight()) {
            n->getHeight()=0;
        } else if (!n->getLeft()) {
            n->getHeight()=(1+n->getRight()->getHeight());
        } else if (!n->getRight()) {
            n->getHeight()=(1+n->getLeft()->getHeight());
        } else {
            n->getHeight()=(1+max(n->getLeft()->getHeight(),
                                  n->getRight()->getHeight()));
        }
    }

    /**
     * Checks if a given sub-tree is balanced and activates the
     * rotations accordingly in O(1)
     * @param n - The given sub-tree root.
     * @return The balanced sub-tree root.
     */
    Node *balance(Node *n) {
        if (!n) {
            return nullptr;
        } else if (n->getBF()==2 && n->getLeft() &&
                   n->getLeft()->getBF()==-1) {
            return leftRightRotate(n);
        } else if (n->getBF()==-2 && n->getRight() &&
                   n->getRight()->getBF()==1) {
            return rightLeftRotate(n);
        } else if (n->getBF()==2 && n->getLeft() &&
                   n->getLeft()->getBF()>=0) {
            return leftLeftRotate(n);
        } else if (n->getBF()==-2 && n->getRight() &&
                   n->getRight()->getBF()<=0) {
            return rightRightRotate(n);
        } else {
            updateHeight(n);
            return n->getParent();
        }
    }

    /**
     * Handles removing the root when it has either 0 or 1 child,
     * while maintaining the balance in O(1).
     */
    void handleRootRemove() {
        Node *to_remove=root;
        if (!root->getLeft() && !root->getRight()) {
            delete to_remove;
            root=nullptr;
        } else if (!root->getLeft()) {
            to_remove=root->getRight();
            root->getData()=root->getRight()->getData();
            root->getRight()=nullptr;
            updateHeight(root);
            delete to_remove;
        } else {
            to_remove=root->getLeft();
            root->getData()=root->getLeft()->getData();
            root->getLeft()=nullptr;
            updateHeight(root);
            delete to_remove;
        }
    }

    /**
     * Calculates the sub-tree size, in O(n) where n is the number of nodes.
     * @param n - The sub-tree root.
     * @return The sub-tree size.
     */
    int size(Node *n) const {
        if (!n)
            return 0;
        return size(n->getLeft())+size(n->getRight())+1;
    }

    /**
     * Merges 2 sorted arrays in O(n), where n is the sum of their lengths.
     * @param a - First sorted array.
     * @param na - a length.
     * @param b - Second sorted array.
     * @param nb - b length.
     * @param c - A pointer to the merged array.
     * @param nc - c length.
     */
    void merge(T *a, int na, T *b, int nb, T *c, int nc) {
        int ia=0, ib=0, ic=0;
        for (; ia<na && ib<nb; ic++) {
            if (a[ia]<b[ib]) {
                c[ic]=a[ia];
                ia++;
            } else {
                c[ic]=b[ib];
                ib++;
            }
        }
        for (; ia<na; ia++, ic++) {
            c[ic]=a[ia];
        }
        for (; ib<nb; ib++, ic++) {
            c[ic]=b[ib];
        }
    }

public:
    AVLTree() : root(nullptr) {};
      //sara added here
     // Function to get expenses associated with a customer ID
    int getExpenses(int c_id) {
        Node* node = findNode(root, c_id); // Find the node with the given customer ID
        if (node == nullptr) {
            // Node not found, return an appropriate value or throw an exception
            // For now, returning 0 as an example
            return 0;
        } else {
            // Node found, return its expenses
            return node->getExpenses();
        }
    }
    //sara added here
     /**
     * Updates the expenses value of a node with the given value by incrementing it by 1.
     * @param val - The value to update.
     * @return AVL_SUCCESS if the update was successful, AVL_NULL_PTR if the node doesn't exist.
     */
    AVLTreeResult updateExpenses(const T& val) {
        Node* nodeToUpdate = find(root, val);
        if (nodeToUpdate) {
           nodeToUpdate.updateExpenses(val);
            return AVL_SUCCESS;
        }
        return AVL_NULL_PTR;
    }

    /**
     * Constructs an AVLTree from 2 given AVLTrees in O(n), where n is the
     * merged tree size.
     * @param t1 - First AVLTree.
     * @param t2 - Second AVLTree.
     */
    AVLTree(const AVLTree<T>& t1, const AVLTree<T>& t2) {
        try {
            T *t1_arr=new T[t1.size()];
            T *t2_arr=new T[t2.size()];
            addToArray<T> t1_add(t1_arr), t2_add(t2_arr);
            t1.inorder(t1_add);
            t2.inorder(t2_add);
            int total_size=t1.size()+t2.size();
            T *total=new T[total_size];
            merge(t1_arr, t1.size(), t2_arr, t2.size(), total, total_size);
            delete[] t1_arr;
            delete[] t2_arr;
            int tree_size=0;
            for (int i=0; i<total_size; i++) {
                if (i==0) {
                    tree_size++;
                } else {
                    if (total[i]==total[i-1]) {
                        continue;
                    } else {
                        tree_size++;
                    }
                }
            }
            T *new_total=new T[tree_size];
            for (int i=0, j=0; i<tree_size && j<total_size; i++, j++) {
                if (i==0 && j==0) {
                    new_total[i]=total[j];
                } else {
                    if (total[j]==total[j-1]) {
                        i--;
                        continue;
                    } else {
                        new_total[i]=total[j];
                    }
                }
            }
            root=createCompleteTree(nullptr, 0, tree_size);
            insertData<T> insert(new_total);
            inorder(insert);
            delete[] total;
            delete[] new_total;
        } catch (std::bad_alloc& e) {
            throw e;
        }
    }

    /**
     * Destructs the current AVLTree, replacing it with the given AVLTree in
     * O(n+m) where n is the current tree size and m is the given tree size.
     * @param t - The given tree.
     * @return A copy of the given AVLTree.
     */
    AVLTree& operator=(const AVLTree& t) {
        try {
            postorderDelete(root);
            T *t_arr=new T[t.size()];
            addToArray<T> t_add(t_arr);
            t.inorder(t_add);
            root=createCompleteTree(nullptr, 0, t.size());
            insertData<T> insert(t_arr);
            inorder(insert);
            delete[] t_arr;
            return *this;
        } catch (std::bad_alloc& e) {
            throw e;
        }
    }

    ~AVLTree() {
        postorderDelete(root);
        root=nullptr;
    }

    /**
     * Inserts a new value to the AVLTree while maintaining the balance.
     * In O(logn) complexity, where n is the size of the tree.
     * @param val - The data we wish to insert the tree.
     * @return AVL_SUCCESS - if the action succeeded.
     *         AVL_MEMORY_ERROR - if an allocation error occurs.
     */
    AVLTreeResult insert(const T& val, int expenses) {
        if (find(root, val)) {
            return AVL_SUCCESS;
        }
        try {
            Node *to_insert=new Node(val);
            if (!root) {
                root=to_insert;
            } else {
                Node *parent=root;
                while (parent->getLeft() && parent->getRight()) {
                    if (parent->getData()<val) {
                        parent=parent->getRight();
                    } else {
                        parent=parent->getLeft();
                    }
                }
                //added here 
                if (val == n->getData()) {
               // Update the expenses value if the node already exists
                     n->getExpenses() = expenses;
                }
                if (parent->getLeft()) {
                    if (parent->getData()<val) {
                        parent->getRight()=to_insert;
                        to_insert->getParent()=parent;
                    } else {
                        parent=parent->getLeft();
                        if (parent->getData()<val) {
                            parent->getRight()=to_insert;
                            to_insert->getParent()=parent;
                        } else {
                            parent->getLeft()=to_insert;
                            to_insert->getParent()=parent;
                        }
                    }
                } else if (parent->getRight()) {
                    if (parent->getData()>val) {
                        parent->getLeft()=to_insert;
                        to_insert->getParent()=parent;
                    } else {
                        parent=parent->getRight();
                        if (parent->getData()<val) {
                            parent->getRight()=to_insert;
                            to_insert->getParent()=parent;
                        } else {
                            parent->getLeft()=to_insert;
                            to_insert->getParent()=parent;
                        }
                    }
                } else {
                    if (parent->getData()<val) {
                        parent->getRight()=to_insert;
                        to_insert->getParent()=parent;
                    } else {
                        parent->getLeft()=to_insert;
                        to_insert->getParent()=parent;
                    }
                }
                Node *tmp=parent;
                while (parent) {
                    updateHeight(parent);
                    parent=parent->getParent();
                }
                while (tmp) {
                    if (tmp->getParent()==nullptr) {
                        root=tmp;
                    }
                    tmp=balance(tmp);
                }
                return AVL_SUCCESS;
            }
        } catch (std::bad_alloc&) {
            return AVL_MEMORY_ERROR;
        }
        return AVL_SUCCESS;
    }

    /**
     * Finds whether a certain value is in the AVLTree.
     * In O(logn) complexity, where n is the the tree size.
     * @param val - The searched value.
     * @return A pointer to the value, if found.
     * nullptr otherwise.
     */
    T *find(const T& val) const {
        Node *found=find(root, val);
        return found ? &(found->getData()) : nullptr;
    }
    //sara added here
    void findAndUpdate(const T& val, int expenses) const {
        Node *found=find(root, val);
         found ? (found->updateExpenses(expenses)) : nullptr;
    }
    double  findAndGet(const T& val) const {
        Node *found=find(root, val);
         found ? (found->getExpenses(val)) : nullptr;
    }

 
    /**
     * Removes a given value from the AVLTree while maintaining the balance.
     * In O(logn) complexity, where n is the tree size.
     * where n is the size of the tree.
     * @param val - The data we wish to remove from the tree.
     * @return AVL_SUCCESS - if the action succeeded.
     */
    AVLTreeResult remove(const T& val) {
        Node *to_remove=find(root, val);
        if (!to_remove) {
            return AVL_SUCCESS;
        }
        Node *parent=to_remove->getParent();
        if (to_remove->getData()==root->getData() &&
            (!root->getLeft() || !root->getRight())) {
            handleRootRemove();
        } else if (!to_remove->getLeft() && !to_remove->getRight()) {
            if (parent->getLeft() &&
                to_remove->getData()==parent->getLeft()->getData()) {
                parent->getLeft()=nullptr;
            } else {
                parent->getRight()=nullptr;
            }
            delete to_remove;
        } else if (!to_remove->getLeft()) {
            if (parent->getLeft() &&
                to_remove->getData()==parent->getLeft()->getData()) {
                to_remove->getRight()->getParent()=parent;
                parent->getLeft()=to_remove->getRight();
            } else {
                to_remove->getRight()->getParent()=parent;
                parent->getRight()=to_remove->getRight();
            }
            delete to_remove;
        } else if (!to_remove->getRight()) {
            if (parent->getLeft() &&
                to_remove->getData()==parent->getLeft()->getData()) {
                to_remove->getLeft()->getParent()=parent;
                parent->getLeft()=to_remove->getLeft();
            } else {
                to_remove->getLeft()->getParent()=parent;
                parent->getRight()=to_remove->getLeft();
            }
            delete to_remove;
        } else {
            Node *to_replace=to_remove->getRight();
            while (to_replace->getLeft()) {
                to_replace=to_replace->getLeft();
            }
            if (to_replace->getRight()) {
                to_remove->getData()=to_replace->getData();
                to_replace->getData()=to_replace->getRight()->getData();
                delete to_replace->getRight();
                to_replace->getRight()=nullptr;
                parent=to_replace;
            } else {
                parent=to_replace->getParent();
                if (parent->getLeft() &&
                    parent->getLeft()->getData()==to_replace->getData()) {
                    parent->getLeft()=nullptr;
                } else {
                    parent->getRight()=nullptr;
                }
                to_remove->getData()=to_replace->getData();
                delete to_replace;
            }
        }
        Node *tmp=parent;
        while (parent) {
            updateHeight(parent);
            parent=parent->getParent();
        }
        while (tmp) {
            if (tmp->getParent()==nullptr) {
                root=tmp;
            }
            tmp=balance(tmp);
        }
        return AVL_SUCCESS;
    }

    /**
     * Checks whether a given tree is empty in O(1).
     */
    bool isEmpty() {
        return root ? false : true;
    }

    /**
     * @return The tree size in O(n), where n is the number of nodes.
     */
    int size() const {
        return size(root);
    }

    /**
     * Runs through a given AVLTree inorder, activating a functor on each node.
     * The number of nodes to travel through can be limited.
     * The complexity is O(nm), where n is the number of nodes in the travel and
     * m is the complexity of the functor.
     * @param action - The given functor.
     * @param nodes_num - The number of nodes to travel through.
     */
    template<typename Act>
    void inorder(Act& action, int nodes_num=0) {
        int tree_size=size();
        if (nodes_num>0) {
            tree_size=nodes_num;
        }
        inorder(root, action, &tree_size);
    }

    /**
     * Runs through a given AVLTree inorder, activating a functor on each node.
     * The number of nodes to travel through can be limited.
     * The complexity is O(nm), where n is the number of nodes in the travel and
     * m is the complexity of the functor.
     * @param action - The given functor.
     * @param nodes_num - The number of nodes to travel through.
     */
    template<typename Act>
    void inorder(Act& action, int nodes_num=0) const {
        int tree_size=size();
        if (nodes_num>0) {
            tree_size=nodes_num;
        }
        inorder(root, action, &tree_size);
    }

    /**
     * Function to traverse the binary tree inorder without recursion and
     * without stack.
     * The time complexity in O(nm), where n is the number of nodes
     * and m is the complexity of the functor.
     * The space complexity is O(1).
     * @param action - The given functor.
     */
    template<typename Act>
    void morrisTraversalInorder(Act& action) {
        Node *current, *pre;
        if (root==nullptr)
            return;
        current=root;
        while (current!=nullptr) {
            if (current->getLeft()==nullptr) {
                action(current->getData());
                current=current->getRight();
            } else {
                /* Find the inorder predecessor of current */
                pre=current->getLeft();
                while (pre->getRight()!=nullptr && pre->getRight()!=current)
                    pre=pre->getRight();
                /* Make current as the right child of its inorder
                   predecessor */
                if (pre->getRight()==nullptr) {
                    pre->getRight()=current;
                    current=current->getLeft();
                }

                    /* Revert the changes made in the 'if' part to restore
                       the original tree i.e., fix the right child
                       of predecessor */
                else {
                    pre->getRight()=nullptr;
                    action(current->getData());
                    current=current->getRight();
                }
            }
        }
    }

    /**
     * Function to traverse the binary tree inorder without recursion and
     * without stack.
     * The time complexity in O(nm), where n is the number of nodes
     * and m is the complexity of the functor.
     * The space complexity is O(1).
     * @param action - The given functor.
     */
    template<typename Act>
    void morrisTraversalInorder(Act& action) const {
        Node *current, *pre;
        if (root==nullptr)
            return;
        current=root;
        while (current!=nullptr) {
            if (current->getLeft()==nullptr) {
                action(current->getData());
                current=current->getRight();
            } else {
                /* Find the inorder predecessor of current */
                pre=current->getLeft();
                while (pre->getRight()!=nullptr && pre->getRight()!=current)
                    pre=pre->getRight();
                /* Make current as the right child of its inorder
                   predecessor */
                if (pre->getRight()==nullptr) {
                    pre->getRight()=current;
                    current=current->getLeft();
                }

                    /* Revert the changes made in the 'if' part to restore
                       the original tree i.e., fix the right child
                       of predecessor */
                else {
                    pre->getRight()=nullptr;
                    action(current->getData());
                    current=current->getRight();
                }
            }
        }
    }

    /**
     * Finds the inorder successor of a certain value that is in the AVLTree.
     * In O(logn) complexity, where n is the the tree size.
     * @param val - The given value.
     * @return A pointer to the successor, if found.
     * Itself otherwise.
     */
    T *inorderSuccessor(const T& val) const {
        Node *source=find(root, val);
        if (source->getRight()!=nullptr) {
            return &(findMin(source->getRight())->getData());
        }
        Node *succ=nullptr;
        Node *it=root;
        while (it!=nullptr) {
            if (source->getData()<it->getData()) {
                succ=it;
                it=it->getLeft();
            } else if (source->getData()>it->getData()) {
                it=it->getRight();
            } else {
                break;
            }
        }
        if (!succ) {
            return &(source->getData());
        } else {
            return &(succ->getData());
        }
    }

    /**
     * Finds the inorder predecessor of a certain value that is in the AVLTree.
     * In O(logn) complexity, where n is the the tree size.
     * @param val - The given value.
     * @return A pointer to the successor, if found.
     * Itself otherwise.
     */
    T *inorderPredecessor(const T& val) const {
        Node *source=find(root, val);
        if (source->getLeft()!=nullptr) {
            return &(findMax(source->getLeft())->getData());
        }
        Node *pred=nullptr;
        Node *it=root;
        while (it!=nullptr) {
            if (source->getData()>it->getData()) {
                pred=it;
                it=it->getRight();
            } else if (source->getData()<it->getData()) {
                it=it->getLeft();
            } else {
                break;
            }
        }
        if (!pred) {
            return &(source->getData());
        } else {
            return &(pred->getData());
        }
    }

};

#endif //WET1_AVLTREE_H
