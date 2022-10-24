#include <iostream>
#include <list>
#include <string>
#include <string.h>


using namespace std;

#define print(X) cout <<X<< endl

class SuffNodeConnection;

class SuffNode
{
public:
    SuffNode();
    ~SuffNode();
    SuffNodeConnection* Beginning(char symbol);
    SuffNode* Addition_descendant(char* from, char* to, int index);
    SuffNode* Entertainment_creation(SuffNodeConnection* connection, char* out_position);
    void Print();
    
public:
    list<SuffNodeConnection*>* connections;
    SuffNode* prefix_sumbol;
    SuffNode* parent;
    unsigned long long index;
};

class SuffNodeConnection
{
public:
    SuffNodeConnection(char* f, char* t, SuffNode* n)
    {
        from = f;
        to = t;
        suffix_node = n;
    }

    char* from;
    char* to;
    SuffNode* suffix_node;
};
//

SuffNode::SuffNode() {
    connections = new list<SuffNodeConnection*>();
    prefix_sumbol = NULL;
    parent = NULL;
    index = 0;
}

SuffNodeConnection* SuffNode::Beginning(char symbol) {
    for (SuffNodeConnection* connection : *connections) {
        if (*(connection->from) == symbol) {
            return connection;
        }
    }
    return NULL;
}

SuffNode* SuffNode::Addition_descendant(char* from, char* to, int index) {
    SuffNode* new_node = new SuffNode();
    new_node->index = index;
    new_node->parent = this;
    this->connections->push_front(new SuffNodeConnection(from, to, new_node));
    return new_node;
}

void SuffNode::Print() {
    cout << "ADDR:" << this << " PRNT:" << parent << " CTPF:" << prefix_sumbol << " INDX:" << index << endl;
    for (SuffNodeConnection* connection : *connections) {
        cout << "\t" << (void*)connection->from << ':' << (void*)connection->to << " - " << connection->suffix_node << endl;
    }
    for (SuffNodeConnection* connection : *connections) {
        if (connection->suffix_node != NULL) {
            connection->suffix_node->Print();
        }
    }
}
//OK


SuffNode* SuffNode::Entertainment_creation(SuffNodeConnection* connection, char* out_position) {
    SuffNode* new_node = new SuffNode();
    connection->suffix_node->parent = new_node;
    new_node->connections->push_front(new SuffNodeConnection(out_position, connection->to, connection->suffix_node));
    new_node->parent = this;
    connection->suffix_node = new_node;
    connection->to = out_position;
    return new_node;
}

SuffNode::~SuffNode() {
    for (SuffNodeConnection* connection : *connections) {
        delete connection;
    }
}
//OK

class SuffTree
{
public:
    SuffTree(string str);
    ~SuffTree();
    void Print();
    SuffNode* ReachKeyPoint();
    char* ReachConnectionUp(SuffNodeConnection* connection);
    int ReachInputLength();
private:
    void AdditionSuffix(char *str, int index);
    SuffNode* root;
    SuffNode* last_node;
    char* all_string;
    int input_lenght;
};
//OK

SuffTree::SuffTree(string str) {
    root = new SuffNode();
    last_node = NULL;
    int suffix_lenght = str.length();
    input_lenght = 0;;
    all_string = new char[suffix_lenght + 1];
    memcpy(all_string, str.c_str(), suffix_lenght + 1);
    input_lenght = suffix_lenght;
    for (int i = 0; i < suffix_lenght; i++) {
        AdditionSuffix(all_string + i, i + 1);
    }
    if (last_node != NULL) {
        last_node->prefix_sumbol = root;
    }
}
//OK

void SuffTree::AdditionSuffix(char* str, int index)
{
    SuffNode* current_node = root;
    SuffNodeConnection* current_connection = NULL;
    int currest_bias = 0;
    while (1) {
        if (current_connection == NULL) {
            current_connection = current_node->Beginning(*str);
            if (current_connection == NULL) {
                current_node->Addition_descendant(str, 0, index);
                return;
            }
            str++;
            currest_bias = 1;
        }
        if ((current_connection->from + currest_bias) == ReachConnectionUp(current_connection)) {
            current_node = current_connection->suffix_node;
            current_connection = NULL;
            currest_bias = 0;
            continue;
        }
        if (*(current_connection->from + currest_bias) == *str) {
            currest_bias++;
            str++;
        }
        else {
            SuffNode* middle_node = current_node->Entertainment_creation(current_connection, current_connection->from + currest_bias);
            middle_node->Addition_descendant(str, 0, index);
            if (last_node != NULL) {
                last_node->prefix_sumbol = middle_node;
            }
            last_node = middle_node;
            return;
        }
    }
}
//OK

void SuffTree::Print() {
    print("STROFF:" << (void*)all_string);
    print("STR:" << all_string);
    root->Print();
}

SuffTree::~SuffTree() {
    delete all_string;
    delete root;
}

char* SuffTree::ReachConnectionUp(SuffNodeConnection* connection) {
    if (connection->to) {
        return connection->to;
    } 
    else {
        return all_string + input_lenght;
    }
}
//OK

int SuffTree::ReachInputLength() {
    return input_lenght;
}

SuffNode* SuffTree::ReachKeyPoint() {
    return root;
}
//OK

struct SuffTreePosition
{
    SuffNode* node;
    SuffNodeConnection* connection;
    int bias;
};

class StatSearch
{
public:
    StatSearch(SuffTree* suffix_tree);
    int* Search_all_elem(string text);
private:
    SuffNode* Search(const char* str, int suffix_len);
    void Reach_success_entry(unsigned char* lenght, SuffNode* n);
    int* Reach_success(SuffNode* node);
    SuffTree* _suffix_tree;
};
//OK

StatSearch::StatSearch(SuffTree* suffix_tree) {
    _suffix_tree = suffix_tree;
}

SuffNode* StatSearch::Search(const char* str, int suffix_len) {
    SuffNode* current_node = _suffix_tree->ReachKeyPoint();
    while (suffix_len) {
        SuffNodeConnection* connection = current_node->Beginning(*str);
        if (connection == NULL) {
            return NULL;
        }
        int connection_size = _suffix_tree->ReachConnectionUp(connection) - connection->from;
        int comparison_size = connection_size < suffix_len ? connection_size : suffix_len;
        if (memcmp(connection->from, str, comparison_size)) {
            return NULL;
        }
        current_node = connection->suffix_node;
        suffix_len -= comparison_size;
        str += comparison_size;
    }
    return current_node;
}
//OK

void StatSearch::Reach_success_entry(unsigned char* lenght, SuffNode* n) {
    if (n->index) {
        lenght[(n->index) >> 3] |= 1 << ((n->index) & 7);
    }
    else {
        for (SuffNodeConnection* connection : *(n->connections)) {
            Reach_success_entry(lenght, connection->suffix_node);
        }
    }
}
//OK

int* StatSearch::Reach_success(SuffNode* node) {
    int count_bits = _suffix_tree->ReachInputLength() + 8;
    unsigned char* bits = new unsigned char[count_bits/8];
    memset(bits, 0, count_bits/8);
    if (node == NULL) {
        int* null = new int[1];
        null[0] = 0;
        return null;
    }
    Reach_success_entry(bits, node);
    int operate_bits = 0;
    for (int i = 0; i < (count_bits/8); i++) {
        unsigned char cc = bits[i];
        while (cc) {
            operate_bits += cc & 1;
            cc >>= 1;
        }
    }
    int* ret = new int[operate_bits + 1];
    int index = 0;
    for (int byte = 0; byte < (count_bits/8); byte++) {
        char cbyte = bits[byte];
        for (int bit = 0; bit < 8; bit++) {
            if (cbyte & (1 << bit)) {
                ret[index] = (byte << 3) + bit;
                index++;
            }
        }
    }
    ret[operate_bits] = 0;
    delete [] bits;
    return ret;
}
//OK


int* StatSearch::Search_all_elem(string pattern) {
    SuffNode* func_node = Search(pattern.c_str(), pattern.length());
    int* success = Reach_success(func_node);
    return success;
}
//OK

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    string text;
    getline(cin, text);
    text += '$';

    if (text.length() == 0) {
        return 0;
    }
    SuffTree tree = SuffTree(text);
    StatSearch search = StatSearch(&tree);
    string pattern;
    int pattern_index = 0;
    while (getline(cin, pattern)) {
        pattern_index++;
        if (pattern.length() == 0) {
            continue;
        }
        int* success = search.Search_all_elem(pattern);
        if (*success == 0) {
            continue;
        }
        cout << pattern_index << ": ";
        for (int i = 0; success[i]; i++) {
            if (i) {
                cout << ", ";
            }
            cout << success[i];
        }
        cout << endl;
        delete success;
    }
    return 0;
}
//OKKKKKK