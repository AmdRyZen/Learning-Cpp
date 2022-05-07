//
// Created by 天使之王·彦 on 2021/11/16.
//

#include <unordered_set>
#include <src/service/TrieService.h>
#include <iostream>
#include <vector>
#include <src/service/DemoService.h>
#include <src/service/VipExclusiveDomainService.h>
#include <src/service/VipExclusiveDomainServiceV2.h>
#include <src/service/SiteDomainService.h>
#include "config.h.in"
#include <optional>
#include <map>
#include <chrono>

void DemoService::filter1() {
    std::unordered_set<std::wstring> sensitive = {
            L"fuck",
            L"微信",
    };
    std::unordered_set<wchar_t> stop_words = {
            L'@',
            L'!',
            L'%',
            L'。',
    };
    TrieService trieService;
    trieService.loadFromMemory(sensitive);
    trieService.loadStopWordFromMemory(stop_words);

    std::string str = "fUcK，你是逗比吗？ｆｕｃｋ，你竟然用微信，微@!!%%%。信";
    std::wstring result = trieService.replaceSensitive(SbcConvertService::s2ws(str));
    std::cout << SbcConvertService::ws2s(result) << std::endl;
}

void DemoService::filter2() {
    std::vector<std::string> words = {
            // 字母
            "FUCK",     // 全大写
            "FuCk",     // 混合
            "F&uc&k",   // 特殊符号
            "F&uc&&&k",  // 连续特殊符号
            "ＦＵｃｋ",   // 全角大小写混合
            "F。uc——k",  // 全角特殊符号
            "fＵｃk",    // 全角半角混合
            "fＵ😊ｃk",  // Emotion表情，测试

            // 简体中文
            "微信",
            "微——信",   // 全角符号
            "微【】、。？《》信", // 全角重复词
            "微。信",
            "VX",
            "vx", // 小写
            "V&X", // 特殊字符
            "微!., #$%&*()|?/@\"';[]{}+~-_=^<>信", // 30个特殊字符 递归
            "扣扣",
            "扣_扣",
            "QQ",
            "Qq",
    };

    TrieService trieService;
    std::string word_path;
    std::string stopped_path;
    word_path.append(PROJECT_PATH).append("/public/word.txt");
    stopped_path.append(PROJECT_PATH).append("/public/stopped.txt");
    trieService.loadFromFile(word_path);
    trieService.loadStopWordFromFile(stopped_path);

    for (auto &item: words) {
        auto t1 = std::chrono::steady_clock::now();

        std::wstring result = trieService.replaceSensitive(SbcConvertService::s2ws(item));

        auto t2 = std::chrono::steady_clock::now();
        double dr_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();
        std::cout << "[cost: " << dr_ms << " ms]" << item << " => " << SbcConvertService::ws2s(result) << std::endl;
    }
}

template<typename T>
inline T const &Max(T const &a, T const &b) {
    return a < b ? b : a;
}

[[maybe_unused]] [[maybe_unused]] void DemoService::test() {
    string_view s("abscissa");
    string_view ss = s.substr(0, 5);
    cout << "ss : " << ss << endl;

    int x = 1;
    auto foo = [=, &x] { return x += 1; };
    foo();
    cout << "x : " << x << endl;

    //system("pause");
    float aa = 5.6;
    int bb = 5;
    cout << "static_cast aa: " << static_cast<int>(aa) << endl;
    cout << "static_cast bb: " << static_cast<float>(bb) << endl;

    try {
        int i1 = 39;
        int j1 = 20;
        cout << "Max(i, j): " << Max(i1, j1) << endl;

        double f1 = 13.5;
        double f2 = 20.7;
        cout << "Max(f1, f2): " << Max(f1, f2) << endl;

        string s1 = "Hello";
        string s2 = "World";
        cout << "Max(s1, s2): " << Max(s1, s2) << endl;
    } catch (exception e) {
        cout << e.what() << endl;
    } catch (...) {
        cout << "......" << endl;
    }

    [[maybe_unused]] int sc;
    static_assert(sizeof(sc) < 5, "10");

    vector<int> vec;
    vec.push_back(1);
    vec.push_back(6);
    vec.push_back(9);
    vec.push_back(22);

    SiteDomainService siteDomainService;
    siteDomainService.swap();
    siteDomainService.swap(1, 9);

    VipExclusiveDomainService::say(100);

    volatile int i = 10;
    int j = i;
    cout << "j = " << j << endl;
    int k = i;
    cout << "k = " << k << endl;

    cout << "------------------------ " << endl;

    const string STEFANO = "rust";
    cout << "STEFANO = " << STEFANO << endl;
    cout << "STEFANO = " << sizeof(STEFANO) << endl;

    float f = 3.1415926f;
    cout << "f = " << f << endl;

    double d = 3.1415926;
    cout << "d = " << d << endl;

    cout << "max = " << max(1, 5) << endl;

    {
        VipExclusiveDomainServiceV2 vipExclusiveDomainServiceV2;
        cout << "vipExclusiveDomainServiceV2 = " << vipExclusiveDomainServiceV2.getGuestDomain() << endl;
    }

    {
        VipExclusiveDomainService vipExclusiveDomainService;
        cout << "getGuestDomain = " << vipExclusiveDomainService.getGuestDomain() << endl;
    }

    {
        VipExclusiveDomainService vip = *new VipExclusiveDomainService;
        cout << "vip = " << vip.getGuestDomain() << endl;
        vip.data = "sss";
        cout << "vip1 = " << vip.getGuestDomain() << endl;
    }

    float *p = nullptr;
    p = &f;
    cout << "p = " << p << endl;
    cout << "&p = " << &p << endl;
    cout << "*p = " << *p << endl;

    volatile int *p1 = &i;
    *p = 200;
    cout << "*p1 = " << *p1 << endl;

    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *ar = arr;
    ar++;
    cout << "*ar = " << arr[*ar] << endl;

    siteDomainService.swap2(&arr[2], &arr[7]);
}

std::optional<int> DemoService::asInt(const string &str) {
    try {
        return std::stoi(str);
    } catch (...) {
        return std::nullopt;
    }
}

void DemoService::filter3() {
    map<string, string> map1 = {
        { "user_id", "10000" },
        { "name", "tom" },
        { "status", "1" }
    };
    map<string, string> map2 = {
            { "user_id", "10001" },
            { "name", "bb" },
            { "status", "2" }
    };
    map<string, string> map3 = {
            { "user_id", "10002" },
            { "name", "dd" },
            { "status", "4" }
    };
    std::vector<std::map<string , string> > vector1;
    map<string , string> arr[ 3 ];
    vector1.push_back(map1);
    vector1.push_back(map2);
    vector1.push_back(map3);
    for ( int i = 0; i < 3; i++ )
    {
        arr[ i ] = map1;
    }
    string user_ids = "";
    for (map<string , string> &item: vector1) {
        user_ids.append(item.find("user_id")->second).append(",");
    }
    cout << "user_ids= " << user_ids.substr(0,user_ids.length() - 1 ) << endl;
}

