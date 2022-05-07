//
// Created by Administrator on 2021/9/4.
//
#include <iostream>
#include "../SiteDomainService.h"

using namespace std;

int SiteDomainService::swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    cout << "swap a  = " << a << endl;
    cout << "swap b  = " << b << endl;
    return 0;
}

int SiteDomainService::swap2(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    cout << "swap a  = " << *a << endl;
    cout << "swap b  = " << *b << endl;
    return 0;
}