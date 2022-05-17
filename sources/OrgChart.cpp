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
    OrgChart OrgChart::add_root(std::string name)
    {
        if (this->_root)
        {
            this->_root->_data = name;
        }
        else
        {
            this->_root = new Node(name);
        }

        return *this;
    }

    OrgChart OrgChart::add_sub(std::string employer, std::string employee)
    {
        OrgChart::Node *boss = find(employer);
        if (!boss)
        {
            throw std::invalid_argument("employer doesn't exist");
        }
        Node *n = new Node(employee);
        boss->_children.push_back(n);
        return *this;
    }

    OrgChart::iterator OrgChart::begin_level_order()
    {
        return OrgChart::iterator("level", this->_root);
    }
    OrgChart::iterator OrgChart::end_level_order()
    {
        return OrgChart::iterator("end", nullptr);
    }
    OrgChart::iterator OrgChart::begin_reverse_order()
    {
        return OrgChart::iterator("reverse", this->_root);
    }
    OrgChart::iterator OrgChart::reverse_order()
    {
        return OrgChart::iterator("end", nullptr);
    }
    OrgChart::iterator OrgChart::begin_preorder()
    {
        return OrgChart::iterator("preOrder", this->_root);
    }
    OrgChart::iterator OrgChart::end_preorder()
    {
        return OrgChart::iterator("end", nullptr);
    }
    OrgChart::iterator OrgChart::begin()
    {
        return OrgChart::iterator("level", this->_root);
    }
    OrgChart::iterator OrgChart::end()
    {
        return OrgChart::iterator("end", nullptr);
    }

    std::ostream &operator<<(std::ostream &out, const OrgChart &org)
    {
        std::deque<OrgChart::Node *> q;
        if (!org._root)
        {
            throw std::out_of_range("OrgChart is empty");
        }
        // out << org._root->_data << "\n";
        q.push_back(org._root);
        while (!q.empty())
        {
            size_t len = q.size();
            for (size_t i = 0; i < len; i++)
            {
                OrgChart::Node *tmp = q.front();
                out << tmp->_data << "  ";
                if (!tmp->_children.empty())
                {
                    for (OrgChart::Node *child : tmp->_children)
                    {
                        // out << child->_data << "    ";
                        q.push_back(child);
                    }
                }
                q.pop_front();
            }
            out << "\n";
        }

        return out;
    }

    OrgChart::Node *OrgChart::find(std::string s)
    {
        if (!this->_root)
        {
            return nullptr;
        }
        std::deque<Node *> q;
        q.push_back(this->_root);

        while (!q.empty())
        {
            Node *tmp = q.front();
            if (tmp->_data == s)
            {
                return tmp;
            }
            for (Node *child : tmp->_children)
            {
                q.push_back(child);
            }
            q.pop_front();
        }
        return nullptr;
    }

    void OrgChart::iterator::BFS(Node *root)
    {
        std::deque<Node *> q;
        if (!root)
        {
            throw std::out_of_range("OrgChart is empty");
        }
        q.push_back(root);

        while (!q.empty())
        {
            Node *tmp = q.front();
            this->_order.push_back(tmp);
            for (Node *child : tmp->_children)
            {
                q.push_back(child);
            }
            q.pop_front();
        }
    }

    void OrgChart::iterator::Reverse_BFS(Node *root)
    {
        std::cout << "Reverse_BFS" << std::endl;
        if (!root)
        {
            throw std::out_of_range("OrgChart is empty");
        }
        std::deque<Node *> q;
        q.push_back(root);

        while (!q.empty())
        {
            std::cout << "q: " << std::endl;
            for (Node* a : q)
            {
                std::cout << a->_data << std::endl;
            }
            
            Node *tmp = q.front();
            q.pop_front();
            std::cout<< "tmp: " << tmp->_data << std::endl;
            this->_order.push_back(tmp);
            if(!tmp->_children.empty()){
                std::cout << "children[0]: " << tmp->_children.at(0)->_data<< std::endl;

                for (size_t i=tmp->_children.size()-1; i>0; i--)
                {
                    std::cout<< tmp->_children.at(i)->_data << std::endl;
                    q.push_back(tmp->_children.at(i));
                }

                
                std::cout<<"size: "<< q.empty()<< std::endl;
            }
            
        }
        std::reverse(this->_order.begin(), this->_order.end());
    }

    /*iterator*/
    OrgChart::iterator::iterator(std::string flag, OrgChart::Node *root)
    : _flag(flag), _curr(root), _index(0){
        _order.clear();
        if(flag == "level"){
            BFS(root);
        }
        else if(flag == "reverse"){
            Reverse_BFS(root);
        }
        // else if(flag == "preOrder"){
        //     PreOrder(root);
        // }
        
    }

    OrgChart::iterator::~iterator(){}
    std::string &OrgChart::iterator::operator*() const{
        return _curr->_data;
    }
    std::string *OrgChart::iterator::operator->() const{
        return &(_curr->_data);
    }
    OrgChart::iterator &OrgChart::iterator::operator++(){
        _curr = _order[_index++];
        return *this;
    }
    const OrgChart::iterator OrgChart::iterator::operator++(int){
        iterator tmp = *this;
        (*this)++;
        return tmp;
    }
    bool OrgChart::iterator::operator==(const OrgChart::iterator &other){
        return this->_curr == other._curr;
    }
    bool OrgChart::iterator::operator!=(const OrgChart::iterator &other){
        return this->_curr != other._curr;
    }

}