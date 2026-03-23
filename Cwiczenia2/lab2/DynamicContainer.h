//Pawel Jandula Zadanie 3
#pragma once
#include <iostream>
#include "Box.h"
#include<memory>
class Container{
    // Exercise 2: Use smart pointer.
    std::unique_ptr<Box> pbox = nullptr;
public:
    static bool verbose;
    Container(int content): pbox(std::make_unique<Box>(content)){
        if(verbose) std::cout << "Creating Container" << std::endl;
    }
    Container(const Container & container): pbox(std::make_unique<Box>(*container.pbox)){
        if(verbose) std::cout << "Creating copy of Container\n";//deep copy - nowa pamiec
    }
    Container & operator=(const Container &container){
        if(this != &container) {
            if(verbose) std::cout << "Copying Container\n";
            *pbox = *container.pbox;
        }
        return *this;
    }
    Container(Container && container) = default;
    Container & operator=(Container && container) = default;
    ~Container(){
        if(verbose) std::cout << "Destroying Container \n";
    }
    friend Container operator+(const Container & p1, const Container & p2);
    friend std::ostream & operator << (std::ostream & out, const Container & p){
        return (out << " [" << p.pbox->getContent() << "] ");
    }
};

bool Container::verbose = false;

inline Container operator+(const Container & p1, const Container & p2){
    Container suma(p1.pbox->getContent() + p2.pbox->getContent());
    return suma;
}
