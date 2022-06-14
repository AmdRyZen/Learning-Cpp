#include "atomic"
#include "ccomplex"
#include "config.h.in"
#include "src/service/DemoService.h"
#include "src/service/SortService.h"
#include "src/service/VipExclusiveDomainService.h"
#include "src/service/VipExclusiveDomainServiceV2.h"
#include "src/threadPool/threadPool.h"
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include "game.pb.h"

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

    pt::rsp_login rsp{};
    rsp.set_ret(pt::rsp_login_RET_SUCCESS);
    auto user_info = rsp.mutable_user_info();
    user_info->set_nickname("dsw");
    user_info->set_icon("345DS55GF34D774S");
    user_info->set_coin(2000);
    user_info->set_location("zh");

    for (int i = 0; i < 5; i++) {
      auto record = rsp.add_record();
      record->set_time("2017/4/13 12:22:11");
      record->set_kill(i * 4);
      record->set_dead(i * 2);
      record->set_assist(i * 5);
    }

    std::string buff{};
    rsp.SerializeToString(&buff);
    //------------------解析----------------------
    pt::rsp_login rsp2{};
    if (!rsp2.ParseFromString(buff)) {
      std::cout << "parse error\n";
    }

    auto temp_user_info = rsp2.user_info();
    std::cout << "nickname:" << temp_user_info.nickname() << std::endl;
    std::cout << "coin:" << temp_user_info.coin() << std::endl;
    for (int m = 0; m < rsp2.record_size(); m++) {
      auto temp_record = rsp2.record(m);
      std::cout << "time:" << temp_record.time() << " kill:" << temp_record.kill() << " dead:" << temp_record.dead() << " assist:" << temp_record.assist() << std::endl;
    }

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