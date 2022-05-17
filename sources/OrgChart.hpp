#pragma once
#include <iostream>
#include <vector>
#include <deque>
// #include "Node.hpp"
namespace ariel
{   
    class OrgChart
    {
    struct Node
    {
        std::string _data;
        std::vector<Node *> _children;
        Node* _next;

        Node(std::string& data) : _data(data){}
    };

    public:
        class iterator
        {
        private:
            Node *_curr;
            std::string _flag;
            void BFS(Node* root);
            void Reverse_BFS(Node* root);
            void PreOrder(Node* root);
            void reverse(Node* root);
            

        public:
            iterator(std::string order, Node *root);
            ~iterator();
            std::string &operator*() const;
            std::string *operator->() const;
            iterator &operator++();
            const iterator operator++(int);
            bool operator==(const iterator &other);
            bool operator!=(const iterator &other);
        };

    private:
        Node *_root;
        friend std::ostream &operator<<(std::ostream &out, const OrgChart &org);
        
        
    public:
        OrgChart();
        OrgChart(OrgChart &other);                    // copy constructor
        OrgChart(OrgChart &&org) noexcept;            // move constructor
        OrgChart &operator=(const OrgChart &org);     // copy assignment operator
        OrgChart &operator=(OrgChart &&org) noexcept; // move assignment operator
        ~OrgChart();
        OrgChart add_root(std::string name);
        OrgChart add_sub(std::string employer, std::string employee);
        iterator begin_level_order();
        iterator end_level_order();
        iterator begin_reverse_order();
        iterator reverse_order();
        iterator begin_preorder();
        iterator end_preorder();
        iterator begin();
        iterator end();
        OrgChart::Node* find(std::string s);

        
        



    };

}
