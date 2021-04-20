#include <iostream>
#include <vector>


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
    void PartialSums(int& i, struct thing& thing_item, int& i_s, std::vector<int>& solution);

    void PrintResponse();

private:

    int weight;
    int count;

    std::vector<bool> take;

    int answer;
};

TrickyBackpack::TrickyBackpack(int& count, int& weight)
: answer(0), take(count, false) {
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

void TrickyBackpack::PartialSums(int& i, struct thing& thing_item, int& i_s, std::vector<int>& solution) {
    for (int k = 1; k < this->count; ++k) {
        if (i < this->count - 1){
            if (thing_item.weight[i] * k <= this->weight && thing_item.cost[i] * k > this->answer) {
                thing_item.cost[i + 1] = thing_item.cost[i] * k;
                thing_item.weight[i + 1] = thing_item.weight[i] * k;
                this->answer = thing_item.cost[i + 1];
            }
            i = i + 1;
            this->PartialSums(i, thing_item, i_s, solution);
        } else {
            solution[i_s + 1] = solution[i_s] + this->answer;
            this->take[i] = true;
            ++i_s;
            if (i_s < this->count - 1) {
                i = 0;
                this->PartialSums(i, thing_item, i_s, solution);
            } else {
                while (thing_item.weight[i_s] > this->weight)
                    --i_s;
                this->answer = solution[i_s];
            }
        }
    }
}

void TrickyBackpack::GenerateMatrix(struct thing& thing_item) {
    int index = 0;
    this->PartialSums(index, thing_item, index, thing_item.cost);

}

void TrickyBackpack::PrintResponse() {
    std::cout << this->answer << std::endl;
    for(int i = 0; i < this->count; ++i){
        if(this->take[i]){
            std::cout << i << " ";
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