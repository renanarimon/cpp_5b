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

        Node(std::string& data) : _data(data){}
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
        std::string *begin_level_order();
        std::string *end_level_order();
        std::string *begin_reverse_order();
        std::string *reverse_order();
        std::string *begin_preorder();
        std::string *end_preorder();
        std::string *begin();
        std::string *end();
        OrgChart::Node* find(std::string s);


        class iterator
        {
        private:
            std::string *_curr;
            std::deque<Node*> _order;
            void BFS(Node* root);
            void Reverse_BFS(Node* root);
            void PreOrder(Node* root);

        public:
            iterator(std::string o, Node *root);
            ~iterator();
            std::string &operator*() const;
            std::string *operator->() const;
            iterator &operator++();
            const iterator operator++(int);
            bool operator==(const iterator &other);
            bool operator!=(const iterator &other);
        };
    };

}
