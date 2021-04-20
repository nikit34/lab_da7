#include <iostream>
#include <vector>
#include <chrono>


struct Item {
    int weight;
    int cost;
};

Item operator+ (const Item &lhs, const Item &rhs) {
    return { lhs.weight + rhs.weight, lhs.cost + rhs.cost };
}

Item& operator+= (Item &lhs, const Item &rhs) {
    lhs.weight += rhs.weight;
    lhs.cost += rhs.cost;
    return lhs;
}

class TrickyBackpack {
public:
    TrickyBackpack(int& count, int& weight);
    ~TrickyBackpack() {}

    void PutData(std::vector<Item>& pairs);
    void GenerateMatrix(std::vector<Item>& pairs);
    void partialSums(int index, Item item, std::vector<Item> &items, Item &solution);
    void PrintResponse();

private:

    int weight;
    int count;

    int answer;
};

TrickyBackpack::TrickyBackpack(int& count, int& weight) {
    this->count = count;
    this->weight = weight;
}

void TrickyBackpack::PutData(std::vector<Item>& pairs) {
    Item item;
    for (int i = 0; i < this->count; ++i) {
        std::cin >> item.weight >> item.cost;
        pairs.push_back(item);
    }
}

void TrickyBackpack::partialSums(int index, Item item, std::vector<Item> &items, Item &solution) {
    if (index == items.size()) {
        if (item.weight <= this->weight && item.cost > solution.cost) {
            solution = item;
        }
    }
    else {
        this->partialSums(index + 1, item, items, solution);
        item += items[index];
        this->partialSums(index + 1, item, items, solution);
    }
}

void TrickyBackpack::GenerateMatrix(std::vector<Item>& pairs) {
    Item item {0,0};
    Item solution {0,0};
    this->partialSums(0, item, pairs, solution);
    this->answer = solution.cost;
}

void TrickyBackpack::PrintResponse() {
    std::cout << this->answer << std::endl;
    
    std::cout << std::endl;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    int count;
    int weight;

    std::cin >> count >> weight;
    TrickyBackpack bag(count, weight);

    std::vector<Item> pairs;
    bag.PutData(pairs);
    bag.GenerateMatrix(pairs);
    bag.PrintResponse();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << std::endl << "time: " << duration.count() << std::endl;

    return 0;
}