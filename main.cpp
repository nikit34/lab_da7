#include <iostream>
#include <vector>

struct element {  // TODO: ???
    int data = 0;
    int num = 0;
};

struct thing {
    std::vector<int> weight;
    std::vector<int> cost;
};

class TrickyBackpack {
public:
    TrickyBackpack(int&& count, int&& weight);
    ~TrickyBackpack() {}

    void PutData(struct thing* thing_item);
    void GenerateMatrix(struct thing* thing_item);
    void FindPath(int count, int weight, struct thing* thing_item);
    void PrintResponse();
    void PrintState();

private:

    int weight;
    int count;

    std::vector<std::vector<element> > answer;
    std::vector<int> answer_path;
};

TrickyBackpack::TrickyBackpack(int&& count, int&& weight) {
    this->count = count;
    this->weight = weight;

    element next_element;
    std::vector<element> next_vector(this->weight, next_element);
    this->answer.resize(this->count, next_vector);
}

void TrickyBackpack::PutData(struct thing* thing_item) {
    int one_weight;
    int one_cost;

    for (int i = 0; i < this->count - 1; ++i) {
        std::cin >> one_weight >> one_cost;

        thing_item->weight.push_back(one_weight);
        thing_item->cost.push_back(one_cost);
    }
}

void TrickyBackpack::GenerateMatrix(struct thing* thing_item) {
    for (int k = 1; k < this->count; ++k) {
        for (int s = 1; s < this->weight; ++s) {
            if (s >= thing_item->weight[k - 1]) {
                if (
                    this->answer[k - 1][s].data * this->answer[k - 1][s].num <=
                    (this->answer[k - 1][s - thing_item->weight[k - 1]].data + thing_item->cost[k - 1]) * (this->answer[k - 1][s - thing_item->weight[k - 1]].num + 1)
                    ) {
                    this->answer[k][s].data = (this->answer[k - 1][s - thing_item->weight[k - 1]].data + thing_item->cost[k - 1]);
                    this->answer[k][s].num = this->answer[k - 1][s - thing_item->weight[k - 1]].num + 1;
                }
                else {
                    this->answer[k][s].data = this->answer[k - 1][s].data;
                    this->answer[k][s].num = this->answer[k - 1][s].num;
                }
            }
            else {
                this->answer[k][s].data = this->answer[k - 1][s].data;
                this->answer[k][s].num = this->answer[k - 1][s].num;
            }
        }
    }
}

void TrickyBackpack::PrintState() {
    for (int i = 0; i < this->answer.size(); ++i) {
        for (int j = 0; j < this->answer[i].size(); ++j) {
            std::cout << this->answer[i][j].data << " ";
        }
        std::cout << std::endl;
    }
}

void TrickyBackpack::FindPath(int count, int weight, struct thing* thing_item) {
    if (this->answer[count][weight].data == 0)
        return;
    if (this->answer[count - 1][weight].data == this->answer[count][weight].data)
        FindPath(count - 1, weight, thing_item);
    else {
        FindPath(count - 1, weight - thing_item->weight[count - 1], thing_item);
        this->answer_path.push_back(count);
    }
}

void TrickyBackpack::PrintResponse() {
    int answer_size = this->answer.size();
    int answer_path_size = this->answer_path.size();

    std::cout << this->answer[answer_size - 1][this->answer[answer_size - 1].size() - 1].data * this->answer[answer_size - 1][this->answer[answer_size - 1].size() - 1].num << std::endl;

    if (answer_path_size > 0) {
        for (int i = 0; i < answer_path_size - 1; i++) {
            std::cout << this->answer_path[i] << " ";
        }
        std::cout << this->answer_path[answer_path_size - 1] << std::endl;
    }
}

int main() {
    int count;
    int weight;

    std::cin >> count >> weight;
    TrickyBackpack bag(count + 1, weight + 1);

    struct thing thing_item;
    bag.PutData(&thing_item);
    bag.GenerateMatrix(&thing_item);
    bag.FindPath(count, weight, &thing_item);
    bag.PrintResponse();
    return 0;
}