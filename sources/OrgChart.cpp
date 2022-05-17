#include "OrgChart.hpp"
// #include"Node.hpp"

namespace ariel
{
    OrgChart::OrgChart()
    {
        this->_root = nullptr;
    }
    OrgChart::OrgChart(OrgChart &other)
    {
        this->_root = other._root;
    }
    OrgChart::OrgChart(OrgChart &&org) noexcept
    {
        this->_root = org._root;
        org._root = nullptr;
    }
    OrgChart &OrgChart::operator=(const OrgChart &org)
    {
        this->_root = org._root;
        return *this;
    }
    OrgChart &OrgChart::operator=(OrgChart &&org) noexcept
    {
        this->_root = org._root;
        org._root = nullptr;
        return *this;
    }
    OrgChart::~OrgChart() {}
    OrgChart OrgChart::add_root(std::string name) { 
        if(this->_root){
            this->_root->_data = name;
        }
        else{
            this->_root = new Node(name);
        }
        
        return *this; }


    OrgChart OrgChart::add_sub(std::string employer, std::string employee) { 
        
        return *this; }
    std::string *OrgChart::begin_level_order()
    {
        std::string a = "a";
        std::string *ptr;
        return ptr;
    }
    std::string *OrgChart::end_level_order()
    {
        std::string a = "a";
        std::string *ptr;
        return ptr;
    }
    std::string *OrgChart::begin_reverse_order()
    {
        std::string a = "a";
        std::string *ptr;
        return ptr;
    }
    std::string *OrgChart::reverse_order()
    {
        std::string a = "a";
        std::string *ptr;
        return ptr;
    }
    std::string *OrgChart::begin_preorder()
    {
        std::string a = "a";
        std::string *ptr;
        return ptr;
    }
    std::string *OrgChart::end_preorder()
    {
        std::string a = "a";
        std::string *ptr;
        return ptr;
    }
    std::string *OrgChart::begin()
    {
        std::string a = "a";
        std::string *ptr;
        return ptr;
    }
    std::string *OrgChart::end()
    {
        std::string a = "a";
        std::string *ptr;
        return ptr;
    }

    std::ostream &operator<<(std::ostream &out, const OrgChart &org)
    {
        return out;
    }

    OrgChart::Node* OrgChart::find(std::string s){
        if(!this->_root){
            return nullptr;
        }

    }

    void OrgChart::iterator::BFS(Node *root)
    {
        std::deque<Node*> q;
        if (!root)
        {
            throw std::out_of_range("OrgChart is empty");
        }
        // this->_order.clear();

        q.push_back(root);

        while (!q.empty())
        {
            Node* tmp = q.front();
            this->_order.push_back(tmp);
            for(Node* child : tmp->_children){
                q.push_back(child);
            }
            q.pop_front();
        }
        
    }


}