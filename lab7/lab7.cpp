#include <iostream>
#include <vector>
#include <string>

using namespace std; 

void divisorsNumber(uint64_t &ans, uint64_t &n, uint64_t& m) {
    
    uint_least64_t bound_up = 0;
    uint_least64_t bound_low = 1;
    string num = to_string(n);
    uint_least64_t len = num.size();

    for (uint_least64_t i = 0; i < len; ++i) {

        bound_up = bound_up * 10 + (uint_least64_t)num[i] - (uint_least64_t)'0'; 
        uint_least64_t l = bound_low + (m - bound_low % m) % m; 
        uint_least64_t r = bound_up - bound_up % m; 

        if (l <= r) {
            ans += (r - l) / m + 1;
        }
        bound_low *= 10; 
    }

    if (!(n % m)) {
        --ans; 
    }
}

int main() {
    ios:: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    uint_least64_t n, m;
    cin >> n >> m;
    uint_least64_t ans = 0;

    divisorsNumber(ans, n, m);
    cout << ans << "\n";
    return 0;
}