/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:58:27 by svilla-d          #+#    #+#             */
/*   Updated: 2025/03/01 20:58:29 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>
#include <algorithm>
#include <list>

void test_simple(MutantStack<int> &mstack) {
    std::cout << "\n---------- Simple tests ----------" << std::endl;
    if (!mstack.empty())
        std::cout << "Stack isn't empty" << std::endl;

    std::cout << "Stack size: " << mstack.size() << std::endl;
    std::cout << "Top: " << mstack.top() << std::endl;
    mstack.pop();
    std::cout << "New size: " << mstack.size() << std::endl;
    std::cout << "New top: " << mstack.top() << std::endl;
}

void test_cmp_list() {
    std::cout << "\n---------- Compare with List tests ----------" << std::endl;
    std::list<int> nlist;
    nlist.push_back(5);
    nlist.push_back(17);
    
    std::cout << "Top: " << nlist.back() << std::endl;
    
    nlist.pop_back();
    std::cout << "Size after pop: " << nlist.size() << std::endl;
    
    nlist.push_back(3);
    nlist.push_back(5);
    nlist.push_back(737);
    //[...]
    nlist.push_back(0);

    std::list<int>::iterator it = nlist.begin();
    std::list<int>::iterator ite = nlist.end();
    
    ++it;
    --it;
    
    std::cout << "Elementos de la MutantStack:" << std::endl;
    while (it != ite) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}

void test_cmp_mutanstack()  {
    std::cout << "\n---------- Mutanstack tests ----------" << std::endl;
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    
    std::cout << "Top: " << mstack.top() << std::endl;
    
    mstack.pop();
    std::cout << "Size after pop: " << mstack.size() << std::endl;
    
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    //[...]
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    
    ++it;
    --it;
    
    std::cout << "Elementos de la MutantStack:" << std::endl;
    while (it != ite) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
}

void test_copy(const MutantStack<int> &mstack) {
    std::cout << "\n---------- Copy Constructor tests ----------" << std::endl;
    MutantStack<int> copyStack(mstack);
    std::cout << "Elements in copied MutantStack: " << std::endl;
    for (MutantStack<int>::const_iterator it = copyStack.begin(); it != copyStack.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void test_assignment(const MutantStack<int> *mstack) {
    std::cout << "\n---------- Assignment Operator tests ----------" << std::endl;

    if (!mstack) {
        std::cerr << "Error: Null MutantStack pointer!" << std::endl;
        return;
    }

    MutantStack<int> assignedStack;
    assignedStack = *mstack;
    std::cout << "Elements in assigned MutantStack: " << std::endl;
    for (MutantStack<int>::iterator it = assignedStack.begin(); it != assignedStack.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void doubleValue(int &n) {
    n *= 2;
}

void test_modify(MutantStack<int> &mstack) {
    std::cout << "\n---------- Modification tests ----------" << std::endl;

    std::cout << "Original elements: " << std::endl;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::for_each(mstack.begin(), mstack.end(), doubleValue);
    std::cout << "Elements after modification (multiplied by 2): " << std::endl;
    for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

int main() {
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    test_simple(mstack);
    test_cmp_list();
    test_cmp_mutanstack();
    test_copy(mstack);
    test_assignment(&mstack);
    test_modify(mstack);

    return 0;
}
