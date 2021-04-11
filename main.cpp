#include <iostream>
#include <vector>

struct element {
    int data = 0;
    int num = 0;
};

struct data {
    std::vector<int> weight;
    std::vector<int> cost;
};

class TrickyBackpack {
public:
    TrickyBackpack(int &&count, int &&weight);
    ~TrickyBackpack() {}

    void PutData(struct data *init_data);
    void GenerateMatrix(struct data* init_data);
    void FindPath(int count, int weight, struct data* init_data);
    void PrintResponse();
    void PrintState();

private:

    int weight;
    int count;

    std::vector<std::vector<element> > answer;
    std::vector<int> answer_path;
};

TrickyBackpack::TrickyBackpack(int &&count, int &&weight) {
    this->count = count;
    this->weight = weight;

    element next_element;
    std::vector<element> next_vector(this->weight, next_element);
    this->answer.resize(this->count, next_vector);
}

void TrickyBackpack::PutData(struct data *init_data) {
    int one_weight;
    int one_cost;

    for (int i = 0; i < this->count - 1; ++i) {
        std::cin >> one_weight >> one_cost;

        init_data->weight.push_back(one_weight);
        init_data->cost.push_back(one_cost);
    }
}

void TrickyBackpack::GenerateMatrix(struct data* init_data){
    for (int k = 1; k < this->count; ++k) {
        for (int s = 1; s < this->weight; ++s) {
            if (s >= init_data->weight[k - 1]) {
                if (
                    this->answer[k - 1][s].data * this->answer[k - 1][s].num <=
                    (this->answer[k - 1][s - init_data->weight[k - 1]].data + init_data->cost[k - 1]) * (this->answer[k - 1][s - init_data->weight[k - 1]].num + 1)
                ) {
                    this->answer[k][s].data = (this->answer[k - 1][s - init_data->weight[k - 1]].data + init_data->cost[k - 1]);
                    this->answer[k][s].num = this->answer[k - 1][s - init_data->weight[k - 1]].num + 1;
                }
                else {
                    this->answer[k + 1][s + init_data->weight[k + 1]].data = this->answer[k + 1][s + init_data->weight[k + 1]].data;
                    this->answer[k + 1][s + init_data->weight[k + 1]].num = this->answer[k + 1][s + init_data->weight[k + 1]].num;
                }
            }
            else {
                if (this->answer[k + 1][s].data * this->answer[k + 1][s].num <=
                    this->answer[k][s].data * this->answer[k][s].num
                ) {
                    this->answer[k][s].data = this->answer[k][s].data;
                    this->answer[k][s].num = this->answer[k][s].num;
                } else {
                    this->answer[k + 1][s].data = this->answer[k + 1][s].data;
                    this->answer[k + 1][s].num = this->answer[k + 1][s].num;
                }
            }
        }
    }
}

void TrickyBackpack::PrintState() {
    for (int i = 0; i < this->answer.size(); ++i) {
        for (int j = 0; j < this->answer[i].size(); ++j){
            std::cout << this->answer[i][j].data << " ";
        }
        std::cout << std::endl;
    }
}

void TrickyBackpack::FindPath(int count, int weight, struct data* init_data) {
    if (this->answer[count][weight].data == 0)
        return;
    if (this->answer[count - 1][weight].data == this->answer[count][weight].data)
        FindPath(count - 1, weight, init_data);
    else {
        FindPath(count - 1, weight - init_data->weight[count - 1], init_data);
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

int main(){
    int count;
    int weight;
    std::cin >> count >> weight;
    TrickyBackpack bag(count + 1, weight + 1);
    
    struct data init_data;
    bag.PutData(&init_data);
    bag.GenerateMatrix(&init_data);
    bag.FindPath(count, weight, &init_data);
    bag.PrintResponse();
    return 0;
}