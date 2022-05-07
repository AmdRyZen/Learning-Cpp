//
// Created by 天使之王·彦 on 2021/11/16.
//

#ifndef LEARNING_CPP_DEMOSERVICE_H
#define LEARNING_CPP_DEMOSERVICE_H

#include <optional>

class DemoService {
public:
    DemoService() = delete;

    ~DemoService() = delete;

    static void filter1();

    static void filter2();

    static void filter3();

    static std::optional<int> asInt(const std::string& str);

    [[maybe_unused]] static void test();
};

#endif //LEARNING_CPP_DEMOSERVICE_H
