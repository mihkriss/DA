#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

void Encoding() {
   unordered_map<string, int> CodeDictionary;
    for (int i = 0; i <= 25; ++i) {
        string str;
        str.push_back('a' + i);
        CodeDictionary.insert({str, i});
        CodeDictionary[str] = i;
    }
    CodeDictionary.insert({"\0", 26});

    char c;
    string word;
    while((c = getchar())) {
        string tmp = word;
        word += c;
        if(c == EOF) {
            word = tmp;
            cout << 26 << "\n";
            break;
        }
        if(CodeDictionary.count(word) == 0) {
            cout << CodeDictionary[tmp] << " ";
            int size = CodeDictionary.size();
            CodeDictionary.insert({word, size});
            word = c;
        }
    }
}

void Decoding() {
    unordered_map<int, string> DecodeDictionary;
    for (int i = 0; i <= 25; ++i) {
        string str;
        str.push_back('a' + i);
        DecodeDictionary.insert({i, str});
        DecodeDictionary[i] = str;
    }
        DecodeDictionary.insert({26, "\0"});

    int code;
    string word;
    while(cin >> code) {
        string tmp = word;
        if(DecodeDictionary.count(code) != 0) {
            word = DecodeDictionary[code];

            if(word == "EOF") {
                cout << "\n";
                break;
            }

            cout  << word;
            if(tmp != "") {
                word = tmp + word.front();
                int size = DecodeDictionary.size();
                DecodeDictionary.insert({size, word});
                word = DecodeDictionary[code];
            }
        }
        else {
            word = tmp + tmp.front(); 
            int size = DecodeDictionary.size();
            DecodeDictionary.insert({size, word});
            cout  << word;
        }
    }
}

int main() {

    string com;
    getline(cin, com);
    if(com == "compress") Encoding();
    else if(com == "decompress") Decoding();
    else cout << "Incorrect command!";

    return 0;
}