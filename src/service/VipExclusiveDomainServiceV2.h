//
// Created by Administrator on 2021/10/18.
//
#include "VipExclusiveDomainService.h"

#ifndef STEFANO_VIPEXCLUSIVEDOMAINSERVICEV2_H
#define STEFANO_VIPEXCLUSIVEDOMAINSERVICEV2_H

class VipExclusiveDomainServiceV2 : VipExclusiveDomainService {
public:
    std::string getGuestDomain() override;
};

#endif //STEFANO_VIPEXCLUSIVEDOMAINSERVICEV2_H
