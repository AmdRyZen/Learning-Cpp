#include <iostream>
#include <filesystem>
#include "src/threadPool/threadPool.h"
#include "atomic"
#include "src/service/VipExclusiveDomainService.h"
#include "src/service/VipExclusiveDomainServiceV2.h"
#include "ccomplex"
#include "src/service/DemoService.h"
#include "src/service/SortService.h"
#include "config.h.in"
#include <optional>

using namespace std;

std::atomic<int64_t> value(0);

inline void threadF() {
    for (int i = 0; i < 100; ++i) {
        value++;
    }
}

[[maybe_unused]] void signalHandler(int signum) {
    cout << "Interrupt signal (" << signum << ") received.\n";
    // 清理并关闭
    // 终止程序
    exit(signum);
}

int main() {
    string path;
    path.append(PROJECT_PATH);
    std::cout << "PROJECT_PATH: " << path << endl;
    DemoService::filter1();
    DemoService::filter2();

    auto *p2 = new complex<int>;
    *p2 = 10;
    cout << "p2 : " << *p2 << endl;
    delete p2;

    ThreadPool pool(4);
    std::vector<std::future<int> > results;
    results.reserve(4);
    for (int i = 0; i < 4; ++i) {
        results.emplace_back(
                pool.enqueue([i] {
                    std::this_thread::sleep_for(std::chrono::microseconds (10));
                    return i * i;
                })
        );
    }

    for (auto &&result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;

    std::vector<std::thread> threads;
    threads.reserve(10);
    for (int i = 0; i < 10; i++) {
        threads.emplace_back(threadF);
    }
    for (auto &thread: threads)
        thread.join();
    cout << "value = " << value << endl;

    unique_ptr<string> str(new string("rust"));
    cout << "str = " << *str << endl;

    int arr[10] = {4, 1, 8, 3, 0, 9, 6, 7, 2, 5};
    auto t1 = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000; ++i) {
        SortService::QuickSort(arr, 0, 9);
        //sort(arr, arr+20);
    }
    auto t2 = std::chrono::steady_clock::now();
    double dr_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();
    string aa = "";
    for (const auto &item : arr) {
        aa.append(to_string(item)).append(",");
    }
    std::cout << "[cost: " << dr_ms << " ms]" << "QuickSort arr.item =" << " => " << aa << std::endl;

    int arr1[10] = {4, 1, 8, 3, 0, 9, 6, 7, 2, 5};
    auto t1_1 = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000; ++i) {
        SortService::BubbleSort(arr1, 10);
    }
    auto t2_1 = std::chrono::steady_clock::now();
    double dr_ms_1 = std::chrono::duration<double, std::milli>(t2_1 - t1_1).count();
    string aa_1 = "";
    for (const auto &item : arr1) {
        aa_1.append(to_string(item)).append(",");
    }
    std::cout << "[cost: " << dr_ms_1 << " ms]" << "BubbleSort arr1.item =" << " => " << aa_1 << std::endl;

    for (auto s : {"42", "077", "hello", "0x33"}) {
        std::optional<int> oi = DemoService::asInt(s);
        if (oi) {
            cout << "convert = " << s << " to int : " << oi.value() << endl;
        } else {
            cout << "can't convert = " << s << endl;
        }
    }

    DemoService::filter3();
    return 0;
}