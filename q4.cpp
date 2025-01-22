#include<iostream>
#include<vector>

template<int N>
class Field {
private:
    std::vector<bool> field;
public:
    Field() :field(N + 2, false) {//false = white, true = black
        this->field[0] = this->field[N + 1] = true;
    }
    const std::vector<bool>& get_vector() {
        return this->field;
    }
    const std::vector<bool>& set_field(const std::vector<bool>& src) {
        auto s = src.begin();
        for (auto i = this->field.begin() + 1; i != this->field.end() - 1; i++) {
            *i = *s;
            s++;
        }
        return this->field;
    }
    const std::vector<bool>& update_field() {
        std::vector<bool> tmp_field(this->field);
        auto s = tmp_field.begin() + 1;
        for (auto i = this->field.begin() + 1; i != this->field.end() - 1; i++) {
            int w_c = 0;
            for (auto j = i - 1; j != i + 2; j++) {
                if (!(*j)) w_c++;
            }
            if (w_c % 2) *s = true;
            else *s = false;
            s++;
        }
        this->field = tmp_field;
        return this->field;
    }
    void print()const{
        for (auto i = this->field.begin() + 1; i != this->field.end() - 1; i++) std::cout << (*i ? "\x1b[42m" : "\x1b[46m") << " ";
        std::cout <<"\x1b[49m" << std::endl;
    }
    bool operator==(const Field& rhs)const{
        auto s = rhs.field.begin() + 1;
        for (auto i = this->field.begin() + 1; i != this->field.end() - 1; i++) {
            if (*s++ != *i) return false;
        }
        return true;
    }
    bool operator!=(const Field& rhs)const {
        return !(*this == rhs);
    }
    std::vector<bool>::const_reference operator[](std::size_t i)const{
        return this->field[i + 1];
    }
    std::vector<bool>::reference operator[](std::size_t i) {
        return this->field[i + 1];
    }
};

int main() {
    Field<9> ans;
    ans[0] = true;
    ans[1] = true;
    ans[3] = true;
    ans[5] = true;
    int n_step = 0;
    std::cout << "Black is \x1b[42m \x1b[49m. White is \x1b[46m \x1b[49m." << std::endl;
    std::cout << "Please enter a number of steps you would like to move forward.[>0]" << std::endl;
    std::cin >> n_step;
    if (n_step <= 0) {
        std::cout << "Invalid number." << std::endl;
        return 0;
    }
    for (int i = 0; i < 511; i++) {
        Field<9> f;
        for (int j = 0; j < 9; j++) {
            f[j] = (i >> j) & 1 ? true : false;
        }
        Field<9> h(f);
        for (int j = 0; j < n_step; j++) {
            f.update_field();
        }
        if (f == ans) {
            std::cout << "This is the state from " << n_step << " steps ago." << std::endl;
            h.print();
            std::cout << std::endl << "<<History>>"<<std::endl;
            std::cout << 1;
            h.print();
            for (int j = 1; j <= n_step; j++) {
                h.update_field();
                std::cout << j + 1;
                h.print();
            }
            break;
        }
    }
}