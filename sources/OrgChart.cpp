#include "OrgChart.hpp"
#include <algorithm>
#include <stack>
#include<map>
#include<queue>

namespace ariel
{
    OrgChart::OrgChart()
    {
        this->_root = nullptr;
        this->_height = 0;
    }
    OrgChart::OrgChart(OrgChart &other)
    {
        this->_root = other._root;
        this->_height = other._height;
    }
    OrgChart::OrgChart(OrgChart &&org) noexcept
    {
        this->_root = org._root;
        this->_height = org._height;
        org._root = nullptr;
    }
    OrgChart &OrgChart::operator=(const OrgChart &org)
    {
        this->_root = org._root;
        this->_height = org._height;
        return *this;
    }
    OrgChart &OrgChart::operator=(OrgChart &&org) noexcept
    {
        this->_root = org._root;
        this->_height = org._height;
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
            this->_height = 1; 
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
        if(n->_children.empty()){
            this->_height++;
        }
        boss->_children.push_back(n);
        return *this;
    }

    OrgChart::iterator OrgChart::begin_level_order()
    {
        return OrgChart::iterator("level", this->_root, this->_height);
    }
    OrgChart::iterator OrgChart::end_level_order()
    {
        return OrgChart::iterator("end", nullptr, this->_height);
    }
    OrgChart::iterator OrgChart::begin_reverse_order()
    {
        return OrgChart::iterator("reverse", this->_root, this->_height);
    }
    OrgChart::iterator OrgChart::reverse_order()
    {
        return OrgChart::iterator("end", nullptr, this->_height);
    }
    OrgChart::iterator OrgChart::begin_preorder()
    {
        return OrgChart::iterator("preOrder", this->_root, this->_height);
    }
    OrgChart::iterator OrgChart::end_preorder()
    {
        return OrgChart::iterator("end", nullptr, this->_height);
    }
    OrgChart::iterator OrgChart::begin()
    {
        return begin_level_order();
    }
    OrgChart::iterator OrgChart::end()
    {
        return end_level_order();
    }

    std::ostream &operator<<(std::ostream &out, const OrgChart &org)
    {
        std::deque<OrgChart::Node *> q;
        if (!org._root)
        {
            throw std::out_of_range("OrgChart is empty");
        }
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
            q.pop_front();
            for (Node *child : tmp->_children)
            {
                q.push_back(child);
            }
            tmp->_nextL = q.front();
        }
    }

    void OrgChart::iterator::Reverse_BFS(Node *root)
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
            q.pop_front();
            std::reverse(tmp->_children.begin(), tmp->_children.end());
            for (Node *child : tmp->_children)
            {
                q.push_back(child);
            }
            tmp->_nextR = q.front();
        }
        reverse(root);
    }
    void OrgChart::iterator::reverse(Node *root)
    {
        // Initialize current, previous and next pointers
        Node *current = root;
        Node *prev = nullptr, *next = nullptr;

        while (current != nullptr)
        {
            // Store next
            next = current->_nextR;
            // Reverse current node's pointer
            current->_nextR = prev;
            // Move pointers one position ahead.
            prev = current;
            current = next;
        }

        _curr = prev;
    }

    void OrgChart::iterator::PreOrder(Node *root)
    {
        if (!root)
        {
            throw std::out_of_range("OrgChart is empty");
        }
        std::stack<Node *> st;
        st.push(root);
        while (!st.empty())
        {
            Node *tmp = st.top();
            st.pop();
            std::reverse(tmp->_children.begin(), tmp->_children.end());
            for (Node *child : tmp->_children)
            {
                st.push(child);
            }
            if (!st.empty())
            {
                tmp->_nextR = st.top();
            }
        }
    }

    /*iterator*/
    OrgChart::iterator::iterator(std::string flag, OrgChart::Node *root, int height)
        : _flag(flag), _curr(root), _h(height)
    {

        if (flag == "level")
        {
            BFS(root);
        }
        else if (flag == "reverse")
        {
            Reverse_BFS(root);
        }
        else if (flag == "preOrder")
        {
            PreOrder(root);
        }
    }

    OrgChart::iterator::~iterator() {
        this->_curr = nullptr;
    }
    std::string &OrgChart::iterator::operator*() const
    {
        return _curr->_data;
    }
    std::string *OrgChart::iterator::operator->() const
    {
        return &(_curr->_data);
    }
    OrgChart::iterator::iterator(iterator &other)
    {
        this->_curr = other._curr;
        this->_flag = other._flag;
    }
    OrgChart::iterator::iterator(iterator &&other) noexcept
    {
        this->_curr = other._curr;
        this->_flag = other._flag;
        other._curr = nullptr;
    }
    OrgChart::iterator &OrgChart::iterator::operator=(const iterator &other)
    {
        this->_curr = other._curr;
        this->_flag = other._flag;
        return *this;
    }
    OrgChart::iterator& OrgChart::iterator::operator=(iterator&& other) noexcept{ //TODO
        this->_curr = other._curr;
        this->_flag = other._flag;
        other._curr = nullptr;
        return *this;
    }

    OrgChart::iterator &OrgChart::iterator::operator++()
    {
        if (_flag == "level")
        {
            _curr = _curr->_nextL;
        }
        else if (_flag == "reverse")
        {
            _curr = _curr->_nextR;
        }
        else if (_flag == "preOrder")
        {
            _curr = _curr->_nextP;
        }
        return *this;
    }
    const OrgChart::iterator OrgChart::iterator::operator++(int)
    {
        iterator tmp = *this;
        (*this)++;
        return tmp;
    }
    bool OrgChart::iterator::operator==(const OrgChart::iterator &other)
    {
        return this->_curr == other._curr;
    }
    bool OrgChart::iterator::operator!=(const OrgChart::iterator &other)
    {
        return this->_curr != other._curr;
    }


}