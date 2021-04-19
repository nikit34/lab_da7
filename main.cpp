#include <iostream>
#include <vector>


struct thing {
    std::vector<int> weight;
    std::vector<int> cost;
};

static const int MAX_COUNT = 100;

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

    std::vector<std::vector<int> > total;
    std::vector<std::vector<int> > total_more;

    std::vector<std::vector<std::vector<bool> > > mask;
    std::vector<std::vector<std::vector<bool> > > mask_more;

    std::vector<bool> take;
    int answer;
};

TrickyBackpack::TrickyBackpack(int& count, int& weight) : take(MAX_COUNT, false), answer(0) {
    this->count = count;
    this->weight = weight;

    std::vector<int> tmp(this->weight + 1);
    this->total.resize(this->count + 1, tmp);
    this->total_more.resize(this->count + 1, tmp);

    std::vector< std::vector<bool> > tmp_vector_bool;
    tmp_vector_bool.resize(this->weight + 1, this->take);
    this->mask.resize(this->count + 1, tmp_vector_bool);
    this->mask_more.resize(this->count + 1, tmp_vector_bool);
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
    for (int k = 1; k < this->count + 1; ++k) {
        for (int s = 1; s <= this->weight; ++s) {
            this->total[k][s] = this->total[k - 1][s];
            this->mask[k][s] = this->mask[k - 1][s];
            if (thing_item.cost[k - 1] > this->total[k][s] && s - thing_item.weight[k - 1] == 0){
                this->total[k][s] = thing_item.cost[k - 1];
                memset(&this->mask[k][s], 0, MAX_COUNT);
                this->mask[k][s][k - 1] = 1;
            }
            if (this->total[k][s] > this->answer){
                this->answer = this->total[k][s];
                this->take = this->mask[k][s];
            }
        }
    }
    for (int i = 2; i < this->count + 1; ++i){
        for (int k = 1; k < this->count + 1; ++k) {
            for (int s = 1; s <= this->weight; ++s) {
                this->total_more[k][s] = this->total_more[k - 1][s];
                this->mask_more[k][s] = this->mask_more[k - 1][s];
                if (s - thing_item.weight[k - 1] > 0 && this->total[k - 1][s - thing_item.weight[k - 1]] > 0){
                    if (i * (thing_item.cost[k - 1] + this->total[k - 1][s - thing_item.weight[k - 1]] / (i - 1)) > this->total_more[k][s]){
                        this->total_more[k][s] = i * (thing_item.cost[k - 1] + this->total[k - 1][s - thing_item.weight[k - 1]] / (i - 1));
                        this->mask_more[k][s] = this->mask[k - 1][s - thing_item.weight[k - 1]];
                        this->mask_more[k][s][k - 1] = 1;
                    }
                }
                if (this->total_more[k][s] > this->answer){
                    this->answer = this->total_more[k][s];
                    this->take = this->mask_more[k][s];
                }
            }
        }
        std::swap(this->total_more, this->total);
        std::swap(this->mask_more, this->mask);
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
    int count;
    int weight;

    std::cin >> count >> weight;
    TrickyBackpack bag(count, weight);

    struct thing thing_item;
    bag.PutData(thing_item);
    bag.GenerateMatrix(thing_item);


    bag.PrintResponse();
    return 0;
}
