#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <ranges>
#include <string>
#include <vector>

#ifdef PARALLEL
// clang-format off
#include <execution>
// clang-format on
namespace execution = std::execution;
#else
enum class execution { seq, unseq, par_unseq, par };
#endif

void measure([[maybe_unused]] auto policy, const std::string policy_name,
             std::vector<std::uint64_t> v) {
    const auto start = std::chrono::steady_clock::now();
#ifdef PARALLEL
    std::sort(policy, v.begin(), v.end());
#else
    std::sort(v.begin(), v.end());
#endif
    const auto finish = std::chrono::steady_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
    std::cout << policy_name << ": " << duration.count() << " milliseconds"
              << std::endl;
};

int main() {
    std::vector<std::uint64_t> v(1'000'000);
    std::mt19937 gen{std::random_device{}()};
    std::ranges::generate(v, gen);

#ifdef PARALLEL
    measure(execution::seq, "seq      ", v);
    measure(execution::unseq, "unseq    ", v);
    measure(execution::par_unseq, "par_unseq", v);
    measure(execution::par, "par      ", v);
#else
    measure(execution::seq, "No execution policy", v);
#endif

    return 0;
}