//
// Created by Administrator on 2021/10/18.
//
#include "../VipExclusiveDomainService.h"
#include <iostream>

using namespace std;

string VipExclusiveDomainService::str;

VipExclusiveDomainService::VipExclusiveDomainService() : data("卧槽") {
    str = "尼玛";
    cout << "VipExclusiveDomainServiceImpl -- " << "begin" << endl;
}

VipExclusiveDomainService::~VipExclusiveDomainService() {
    cout << "VipExclusiveDomainServiceImpl -- " << "end" << endl;
}

inline string VipExclusiveDomainService::getGuestDomain() {
    return data + "-" + str;
}

inline string VipExclusiveDomainService::getGuestDomain(string const &basicString) const {
    return data + basicString + "纳尼";
}