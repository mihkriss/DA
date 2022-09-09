#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <vector>

 
using namespace std;
 
vector<int> z_func(const vector<string>& s) {
	vector<int> z(s.size());
    int idx_begin = 0, idx_end = 0;
	for (int i = 1; i < s.size(); ++i) {   
		if (i <= idx_end) {
			z[i] = min(idx_end - i + 1, z[i - idx_begin]);
        }
		while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
			++z[i];
        }
		if (i + z[i] - 1 > idx_end) {
			idx_begin = i;
            idx_end = i + z[i] - 1;
        }
	}
	return z;
}
// хорошего суффикса Создаем массив N , который будет показывать строка какой длины, заканчивающаяся в данной позиции, совпадаетс префиксом строки.
vector<int> n_func(vector<string> s) {
    reverse(s.begin(), s.end());
    vector<int> z = z_func(s), n(s.size());
    for (int i = 1; i < z.size(); ++i) {
        n[z.size() - i - 1] = z[i];
    }
    return n;
}
 //Далее посчитаем массив L‘, который показывает, в каком индексе кончается строка, которая равна суффиксу, начинающемуся в данной позиции так, что
//буква перед суффиксом и перед строкой не совпадают. 
vector<int> l_strong(const vector<int>& n) {
    vector<int> l(n.size());
    for (int i = 0; i < n.size(); ++i) {
        if (n[i]) {
            l[n.size() - n[i]] = i;
        }
    }
    return l;
}
 //Результат вычисления сдвига по правилу хорошего суффикса будет длина строки минус значение массива L‘ по i-тому индексу.
int GoodSuffixRule(const vector<int>& l, int i) {
    if (l.size() > i && l[i]) {
        return l.size() - l[i];
    }
    return 0;
}
 
 unordered_map<string, vector<int>> BuildMap(const vector<string>& pattern){   //создает словарь, где для каждой буквы паттерна перечислены индексы в паттерне

    unordered_map<string, vector<int>> result;
    for(int i = pattern.size() - 1; i >= 0; --i){
        result[pattern[i]].push_back(i);
    }
    return result;
};
 
int BadSymbolRule(unordered_map<string, vector<int>>& table, const string& c, int pos, const int& size){
    if(!table[c].empty()){
        auto it = upper_bound(table[c].begin(), table[c].end(), pos, [](int v1, int v2){
            return v1 > v2;
        });
        return pos - *it;
    }
    return 1;
}
 
// Создадим хеш мапу для каждого элемента, который встречается в нашей строке, поместим все индексы, на которых
// стоит данный элемент в строке. возвращать будем разницу индекса текущего элемента и элемента, который лежит в хеш мапе левее данного. Если левее
// данного элемента нет таких же элементов, то возвращаем 
vector<int> Search(const vector<string>& text, const vector<string>& pattern) {
    std::unordered_map<string, std::vector<int>> table;
   
    table = BuildMap(pattern);
  
    int i = pattern.size() - 1;
    vector<int> positions;
    vector<int> l;
    l = l_strong(n_func(pattern));
 
    while(i < text.size()){
        bool flag = true;
        int position_to_stop = i - pattern.size();
        string mismatched = "!";
        int k = pattern.size() - 1;
        for(int j = i; j > position_to_stop; --j){
            if (text[j] != pattern[k]){
                flag = false;
                mismatched = text[j];
                break;
            }
            --k;
        }
        if(flag){
            positions.push_back(i - pattern.size() + 1);
            ++i;
        } else {
            i += std::max(BadSymbolRule(table, mismatched, k, pattern.size()), max(GoodSuffixRule(l, i), 1));
        }
    }
    return positions;
}
 
pair<int, int> NumStringCnt(int idx, const vector<int>& v) {
    int num = 0;
    while (idx - v[num] > 0) {
        idx -= v[num];
        ++num;
    } 
    return {num + 1, idx};
}
 
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s, word;
    vector<string> pattern;
    vector<int> counter_words;
    vector<string> text;
   
    bool flag = true;
    while (flag) {
        while (cin.peek() == ' ') {
            cin.ignore(1);
        }
        while (cin.peek() != '\n' && cin >> s) {
            transform(s.begin(), s.end(), s.begin(),
                [](unsigned char c){ return std::tolower(c); });
            pattern.push_back(s);
            while (cin.peek() == ' ') {
                cin.ignore(1);
            }
            flag = false;
        }
        cin.ignore(1);
    }
    while (1) {
        int cnt = 0;
        while (cin.peek() == ' ') {
            cin.ignore(1);
        }
        while (cin.peek() != '\n' && cin >> s) {
            transform(s.begin(), s.end(), s.begin(),
                [](unsigned char c){ return std::tolower(c); });
            text.push_back(s);
            ++cnt;
            while (cin.peek() == ' ') {
                cin.ignore(1);
            }
        }
        cin.ignore(1);
        counter_words.push_back(cnt);
        if (cin.peek() == EOF) {
            break;
        }
    }
   
    vector<int> a;
    
        a = Search(text, pattern);
    
    for (auto& i: a) {
        auto p = NumStringCnt(i + 1, counter_words);
        cout << p.first  << ", " <<  p.second << endl;
    }
  
}