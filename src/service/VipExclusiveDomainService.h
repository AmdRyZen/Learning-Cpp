//
// Created by Administrator on 2021/10/18.
//
#include <cerrno>
#include <iostream>
using namespace std;

#ifndef STEFANO_VIPEXCLUSIVEDOMAINSERVICE_H
#define STEFANO_VIPEXCLUSIVEDOMAINSERVICE_H

class VipExclusiveDomainService {
public:
    string data;

    virtual string getGuestDomain();

    [[nodiscard]] inline string getGuestDomain(const string &) const;

    VipExclusiveDomainService();

    virtual ~VipExclusiveDomainService();

    static void say(int i) { cout << i << str << endl; };

private:
    static string str;
};

#endif //STEFANO_VIPEXCLUSIVEDOMAINSERVICE_H