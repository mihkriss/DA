#include <iostream>
#include <vector>
#include <array>
#include <iomanip>

struct Record { //структура для ввода данных
    int key;
    uint_least64_t value;
};

void counting_sort(std::vector<Record>& v) {
    std::vector<int> data_indexes(1000000, 0); //вектор на миллион элементов заполненный нулями
    for (auto& i: v) { //проходимся по всем значениям вектора //for (int i = 0; i < v.size(); ++i)
        ++data_indexes[i.key]; //инкрементируем 
    }
    for (int i = 1; i < data_indexes.size(); ++i) { //считаем префиксные суммы
        data_indexes[i] += data_indexes[i - 1]; //сумма 0 и 1 индексов в первый потом 1 и 2 индексов во втрой и тд
    }
    std::vector<Record> answ(v.size()); //вспомогательный вектор на размер исходного, чтобы там были отсортированные данные
    for (auto i = v.rbegin(); i != v.rend(); ++i) { //идем с конца вектора(итератор с конца) до начала вектора
        answ[--data_indexes[i->key]] = std::move(*i); //в отсортированный вектор в текущий индекс пишем текущее значен
    } //*i - то что лежит под итератором
    v = std::move(answ);
}

int main() {
    std::ios_base::sync_with_stdio(NULL); //отключение синхронизации с сишными функциями
    std::cin.tie(NULL); //отключение синхронизации cin c cout
    std::cout.tie(NULL);
    std::vector<Record> data; //создаем вектор структур
    Record new_elem; //создаем элемент типа рекорд
    while (std::cin >> new_elem.key >> new_elem.value) { //пока идет считывание счиытваем кей и велью
        data.push_back(std::move(new_elem)); //добавляем в вектор элемент
    }
    counting_sort(data); //когда считывание закончилось отправляем вектор в функцию сортировки
    for (auto& i: data) { //выводим
        std::cout << std::setw(6) << std::setfill('0') << i.key << "\t" << i.value << "\n";
    }
}