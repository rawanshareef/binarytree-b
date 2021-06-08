#pragma once
#include <iostream>
#include <stack>

namespace ariel
{
    template <typename T>
    class BinaryTree
    {

    private:
        struct Node // for  Node
        {
            T data; //the value of node

            Node *parent;                                                              //the parent
            Node *left;                                                                //left child
            Node *right;                                                               //right child
            Node(T val) : data(val), parent(nullptr), left(nullptr), right(nullptr){}; //constructor  for Node
            Node() : parent(nullptr), left(nullptr), right(nullptr){};                 //constructor  defult
        };
        Node *root; //the root of the tree

    public:
        BinaryTree<T>()
        {
            root = nullptr;
        }
        ~BinaryTree<T>()
        {
            if (root != nullptr)
            {
                delete root;
            }
        }
        BinaryTree(BinaryTree &&the_tree) noexcept //move constructor
        {
            root = the_tree.root;
            the_tree.root = nullptr;
        }
        BinaryTree(const BinaryTree &the_tree) //dep copy constructor
        {
            if (the_tree.root != nullptr)
            {
                root = new Node{the_tree.root->data};
                copy(root, the_tree.root);
            }
        }

        void copy(Node *first, const Node *sec_node)
        {
            if (first == nullptr && sec_node == nullptr)
            {
                return;
            }
            if (sec_node->right != nullptr)
            {
                first->right = new Node{sec_node->right->data};
                copy(first->right, sec_node->right);
            }
            if (sec_node->left != nullptr)
            {
                first->left = new Node{sec_node->left->data};
                copy(first->left, sec_node->left);
            }
        }
        BinaryTree &operator=(BinaryTree<T> &&the_tree) noexcept
        {

            delete root;
            root = the_tree.root;
            the_tree.root = nullptr;
            return *this;
        }
        BinaryTree &operator=(const BinaryTree<T> &the_tree)
        {
            if (this == &the_tree)
            {
                return *this;
            }
            if (root != nullptr)
            {
                delete root;
            }

            root = new Node{the_tree.root->data};
            copy(root, the_tree.root);
            return *this;
        }

        //********************************************************
        //-------------------class preorder iterator----------------------
        //********************************************************

        //preorder iterator
        class preorder_iterator
        {

        private:
            Node *pointer_to_preorder;
            std::stack<Node *> My_stack1;

        public:
            preorder_iterator(Node *ptr = nullptr) : pointer_to_preorder(ptr)
            { //indicates thecurrent junction
                if (ptr == nullptr)
                {
                    return;
                }
                initTheStack(pointer_to_preorder);
                if (My_stack1.empty())
                {
                    return;
                }
                pointer_to_preorder = My_stack1.top();
                My_stack1.pop();
            }
            void initTheStack(Node *the_node)
            {
                if (the_node == nullptr)
                {
                    return;
                }
                initTheStack(the_node->right);
                initTheStack(the_node->left);
                My_stack1.push(the_node);
            }
            T &operator*() const { return pointer_to_preorder->data; }
            T *operator->() const { return &(pointer_to_preorder->data); }
            preorder_iterator &operator++()
            { //++x
                if (My_stack1.empty())
                { //if the stack is empty thin the node emptiness
                    pointer_to_preorder = nullptr;
                }
                else
                { //if the stack have nodes
                    pointer_to_preorder = My_stack1.top();
                    My_stack1.pop();
                }
                return *this;
            }

            preorder_iterator operator++(int x)
            { //x++
                preorder_iterator help = *this;
                if (My_stack1.empty())
                { //if the stack is empty thin the node emptiness
                    pointer_to_preorder = nullptr;
                }
                else
                { //if the stack have nodes
                    pointer_to_preorder = My_stack1.top();
                    My_stack1.pop();
                }
                return help;
            }
            bool operator==(const preorder_iterator &a) const
            {

                return pointer_to_preorder == a.pointer_to_preorder;
            }
            bool operator!=(const preorder_iterator &a) const
            {
                return !(*this == a);
            }
        };

        //********************************************************
        //-------------------class inorder iterator----------------------
        //********************************************************

        //inorder iterator
        class inorder_iterator
        {

        private:
            Node *pointer_to_inorder;
            std::stack<Node *> My_stack2;

        public:
            inorder_iterator(Node *ptr = nullptr) : pointer_to_inorder(ptr)
            { //indicates thecurrent junction
                if (ptr == nullptr)
                {
                    return;
                }
                initTheStack(pointer_to_inorder);
                if (My_stack2.empty())
                {
                    return;
                }
                //My_stack2 not empty
                pointer_to_inorder = My_stack2.top();
                My_stack2.pop();
            }
            void initTheStack(Node *the_node)
            {
                if (the_node == nullptr)
                {
                    return;
                }
                initTheStack(the_node->right);
                My_stack2.push(the_node);
                initTheStack(the_node->left);
            }
            T &operator*() const { return pointer_to_inorder->data; }
            T *operator->() const { return &(pointer_to_inorder->data); }

            inorder_iterator &operator++()
            { //++x
                if (My_stack2.empty())
                { //if the stack is empty thin the node emptiness
                    pointer_to_inorder = nullptr;
                }
                else
                { //if the stack have nodes
                    pointer_to_inorder = My_stack2.top();
                    My_stack2.pop();
                }
                return *this;
            }
            inorder_iterator operator++(int x)
            { //x++
                inorder_iterator help = *this;
                if (My_stack2.empty())
                { //if the stack is empty thin the node emptiness
                    pointer_to_inorder = nullptr;
                }
                else
                { //if the stack have nodes
                    pointer_to_inorder = My_stack2.top();
                    My_stack2.pop();
                }
                return help;
            }
            bool operator==(const inorder_iterator &a) const
            {

                return (pointer_to_inorder == a.pointer_to_inorder);
            }
            bool operator!=(const inorder_iterator &a) const
            {
                return !(*this == a);
            }
        };
        //********************************************************
        //-------------------class postorder iterator----------------------
        //********************************************************

        //postorder iterator
        class postorder_iterator
        {

        private:
            Node *pointer_to_postorder;
            std::stack<Node *> My_stack3;

        public:
            postorder_iterator(Node *ptr = nullptr) : pointer_to_postorder(ptr)
            { //indicates thecurrent junction
                if (ptr == nullptr)
                {
                    return;
                }
                initTheStack(pointer_to_postorder);
                if (My_stack3.empty())
                {
                    return;
                }
                pointer_to_postorder = My_stack3.top();
                My_stack3.pop();
            }
            void initTheStack(Node *the_node)
            {
                if (the_node == nullptr)
                {
                    return;
                }
                My_stack3.push(the_node);

                initTheStack(the_node->right);
                initTheStack(the_node->left);
            }

            T &operator*() const { return pointer_to_postorder->data; }
            T *operator->() const { return &(pointer_to_postorder->data); }

            postorder_iterator &operator++()
            { //++x
                if (My_stack3.empty())
                { //if the stack is empty thin the node emptiness
                    pointer_to_postorder = nullptr;
                }
                else
                { //if the stack have nodes
                    pointer_to_postorder = My_stack3.top();
                    My_stack3.pop();
                }
                return *this;
            }
            postorder_iterator operator++(int x)
            { //x++
                postorder_iterator help = *this;
                if (My_stack3.empty())
                { //if the stack is empty thin the node emptiness
                    pointer_to_postorder = nullptr;
                }
                else
                { //if the stack have nodes
                    pointer_to_postorder = My_stack3.top();
                    My_stack3.pop();
                }
                return help;
            }
            bool operator==(const postorder_iterator &a) const
            {

                return (pointer_to_postorder == a.pointer_to_postorder);
            }
            bool operator!=(const postorder_iterator &a) const
            {
                return !(*this == a);
            }
        };

        //---------------------------------------------------------//
        //------------------return iterator----- ------------------//
        //---------------------------------------------------------//
        //preorder
        preorder_iterator begin_preorder()
        {
            return preorder_iterator(root);
        }
        preorder_iterator end_preorder()
        {
            return preorder_iterator(nullptr);
        }

        //inorder
        inorder_iterator begin_inorder()
        {
            return inorder_iterator(root);
        }
        inorder_iterator end_inorder()
        {
            return inorder_iterator(nullptr);
        }

        //postorder
        postorder_iterator begin_postorder()
        {
            return postorder_iterator(root);
        }
        postorder_iterator end_postorder()
        {
            return postorder_iterator(nullptr);
        }

        inorder_iterator begin()
        {
            return begin_inorder();
        }

        inorder_iterator end()
        {
            return end_inorder();
        }
        /////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////the func//////////////////////////////////////////

        Node *FoundTheNode(T me_data, Node *search_me)
        {
            if (search_me == nullptr)
            { //if the node not created
                return nullptr;
            }
            if (search_me->data == me_data)
            {
                return search_me;
            }
            Node *the_left = FoundTheNode(me_data, search_me->left);
            Node *the_right = FoundTheNode(me_data, search_me->right);
            if (the_left != nullptr)
            {
                return the_left;
            }

            return the_right;
        }

        //1//

        BinaryTree<T> &add_root(T new_root)
        { //add the new_root to the root
            if (root == nullptr)
            {
                this->root = new Node(new_root);
            }
            else
            {
                this->root->data = new_root;
            }
            return *this;
        }
        //2//
        BinaryTree<T> &add_left(T father, T leftN)
        { //add the father the left node if there is a left child then bully him
            Node *ans = FoundTheNode(father, root);
            if (ans == nullptr)
            {
                std::string message = "The first Node not created";
                throw std::invalid_argument(message);
            }

            if (ans->left == nullptr)
            { //he has not a left son
                ans->left = new Node(leftN);
                ans->left->parent = ans;
            }
            else
            { //he has  a left son
                ans->left->data = leftN;
            }
            return *this;
        }
        //3//
        BinaryTree<T> &add_right(T father, T rightN)
        { //add the father the r night node if there is a right child then bully him
            Node *ans = FoundTheNode(father, root);
            if (ans == nullptr)
            {
                std::string message = "The first Node not created";
                throw std::invalid_argument(message);
            }

            if (ans->right == nullptr)
            { //there is no right son
                ans->right = new Node(rightN);
                ans->right->parent = ans;
            }
            else
            { //there is right son
                ans->right->data = rightN;
            }
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &my_tree) //print the tree
        {
            return os;
        }
    };
}