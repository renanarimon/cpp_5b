#pragma once
#include <iostream>
#include <string>
#include <vector>
namespace ariel
{
    class Node1
    {
    public:
        std::string _data;
        std::vector<Node1 *> _children;

        Node1(std::string name) : _data(name){}

        Node1(Node1& other) : _data(other._name){}

        ~Node1() {}
    };

}