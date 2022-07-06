#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

int TBadSymbol(unordered_map<int, vector<int>>& tbl, int& str, int position, const int& size){
    if(!tbl[str].empty()){
        auto t = upper_bound(tbl[str].begin(), tbl[str].end(), position, [](int a, int b){
            return a > b;
        });
        return position - *t;
    }
    return 1;
}
int TGoodSuf(vector<int>& pattern, int i) {
    if (pattern.size() > i && pattern[i]) {
        return pattern.size() - pattern[i];
    }
    return 0;
}
 
unordered_map<int, vector<int>> dictionary(vector<int>& pattern){
    unordered_map<int, vector<int>> res;
    for(int i = pattern.size() - 1; i >= 0; --i){
        res[pattern[i]].push_back((int)(i));
    }
    return res;
}; 
vector<int> Zfunc(const vector<int>& str) {
	vector<int> arr(str.size());
    int left = 0, right = 0;
	for (int i = 1; i < str.size(); ++i) {
		if (i <= left) {
			arr[i] = min(right - i + 1, arr[i - left]);
        }
		while (i + arr[i] < str.size() && str[arr[i]] == str[i + arr[i]]) {
			++arr[i];
        }
		if (i + arr[i] - 1 > right) {
			left = i;
            right = i + arr[i] - 1;
        }
	}
	return arr;
}
 
vector<int> nArr(vector<int> str) {
    reverse(str.begin(), str.end());
    vector<int> arr = Zfunc(str), n_arr(str.size());
    for (uint64_t i = 1; i < arr.size(); ++i) {
        n_arr[arr.size() - i - 1] = arr[i];
    }
    return n_arr;
}
 
vector<int> strong(const vector<int>& n) {
    vector<int> stg(n.size());
    for (int i = 0; i < n.size(); ++i) {
        if (n[i]) {
            stg[n.size() - n[i]] = i;
        }
    }
    return stg;
}
 
pair<int, int> number_string(int index, vector<int>& v) {
    uint_fast64_t  i = 0;
    while (index - v[i] > 0) {
        index -= v[i];
        ++i;
    } 
    return {i + 1, index};
}
  
vector<int> TBoyarMurr(vector<int>& text, vector<int>& pattern) {
    std::unordered_map<int, std::vector<int>> tbl;
    
    tbl = dictionary(pattern);  
    uint_fast64_t  i = pattern.size() - 1;
    vector<int> position;
    vector<int> len;
    len = strong(nArr(pattern));

    while(i < text.size()){
        bool flag = true;
        int stop = i - pattern.size();
        int incompatible;
        int k = pattern.size() - 1;
        for(int j = i; j > stop; --j){
            if (text[j] != pattern[k]){
                flag = false; 
                incompatible = text[j];
                break;
            }
            --k;
        }
        if(flag){
            position.push_back(i - pattern.size() + 1);
            ++i;
        } else {
            i += std::max(TBadSymbol(tbl, incompatible, k, pattern.size()), max(TGoodSuf(len, i), 1));
        }
    }
    return position;
}
 
 
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    uint_fast64_t str;
    vector<int> pattern;
    vector<int> count;
    vector<int> text;

    bool flag = true;
    while (flag) {
            cin >> str;
            pattern.push_back(str);
            while (cin.peek() == ' ') {
                cin.ignore(1);
            }
            flag = false;
        cin.ignore(1);
    }
    while (1) {
        uint_fast64_t cnt = 0;
            cin >> str; 
            text.push_back(str);
            ++cnt;
            while (cin.peek() == ' ') {
                cin.ignore(1);
            }
        cin.ignore(1);
        count.push_back(cnt);
        if (cin.peek() == EOF) {
            break;
        }
    }
 
    vector<int> a;   
        a = TBoyarMurr(text, pattern);

    for (auto& i: a) {
        auto print = number_string(i + 1, count);
        cout << print.first  << ", " <<  print.second << endl;
    }
  
}