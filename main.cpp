#include <iostream>
#include <vector>
#include <bitset>
#include <chrono>


struct thing {
    std::vector<int> weight;
    std::vector<int> cost;
};

static const int MAX_COUNT = 127;

class TrickyBackpack {
public:
    TrickyBackpack(int& count, int& weight);
    ~TrickyBackpack() {}

    void PutData(struct thing& thing_item);
    void GenerateMatrix(struct thing& thing_item);

    void PrintResponse();

private:

    int weight;
    int count;

    std::bitset<MAX_COUNT> take;
    int answer;
};

TrickyBackpack::TrickyBackpack(int& count, int& weight)
: answer(0) {
    this->count = count;
    this->weight = weight;
}

void TrickyBackpack::PutData(struct thing& thing_item) {
    int one_weight;
    int one_cost;

    for (int i = 0; i < this->count; ++i) {
        std::cin >> one_weight >> one_cost;

        thing_item.weight.push_back(one_weight);
        thing_item.cost.push_back(one_cost);
    }
}

void TrickyBackpack::GenerateMatrix(struct thing& thing_item) {
    std::vector<std::vector<int> > total(this->count + 1, std::vector<int> (this->weight + 1));
    std::vector<std::vector<int> > total_more(this->count + 1, std::vector<int> (this->weight + 1));
    std::vector<std::vector<std::bitset<MAX_COUNT> > > mask(this->count + 1, std::vector<std::bitset<MAX_COUNT> > (this->weight + 1));
    std::vector<std::vector<std::bitset<MAX_COUNT> > > mask_more(this->count + 1, std::vector<std::bitset<MAX_COUNT> > (this->weight + 1));
    for (int k = 1; k < this->count + 1; ++k) {
        for (int s = 1; s <= this->weight; ++s) {
            total[k][s] = total[k - 1][s];
            mask[k][s] = mask[k - 1][s];
            if (thing_item.cost[k - 1] > total[k][s] && s - thing_item.weight[k - 1] == 0){
                total[k][s] = thing_item.cost[k - 1];
                mask[k][s] = 0;
                mask[k][s][k - 1] = 1;
            }
            if (total[k][s] > this->answer){
                this->answer = total[k][s];
                this->take = mask[k][s];
            }
        }
    }
    for (int i = 2; i < this->count + 1; ++i){
        for (int k = 1; k < this->count + 1; ++k) {
            for (int s = 1; s <= this->weight; ++s) {
                total_more[k][s] = total_more[k - 1][s];
                mask_more[k][s] = mask_more[k - 1][s];
                if ((s - thing_item.weight[k - 1] > 0 && total[k - 1][s - thing_item.weight[k - 1]] > 0) &&
                (i * (thing_item.cost[k - 1] + total[k - 1][s - thing_item.weight[k - 1]] / (i - 1)) > total_more[k][s])){
                    total_more[k][s] = i * (thing_item.cost[k - 1] + total[k - 1][s - thing_item.weight[k - 1]] / (i - 1));
                    mask_more[k][s] = mask[k - 1][s - thing_item.weight[k - 1]];
                    mask_more[k][s][k - 1] = 1;
                }
                if (total_more[k][s] > this->answer){
                    this->answer = total_more[k][s];
                    this->take = mask_more[k][s];
                }
            }
        }
        std::swap(total_more, total);
        std::swap(mask_more, mask);
    }
}

void TrickyBackpack::PrintResponse() {
    std::cout << this->answer << std::endl;

    for (int i = 0; i < this->count; ++i) {
        if (this->take[i]){
            std::cout << i + 1 << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    int count;
    int weight;

    std::cin >> count >> weight;
    TrickyBackpack bag(count, weight);

    struct thing thing_item;
    bag.PutData(thing_item);
    bag.GenerateMatrix(thing_item);
    bag.PrintResponse();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << std::endl;

    return 0;
}