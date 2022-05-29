#include "histogram.h"
#include "svg.h"

#include <iostream>
#include <vector>

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

vector<double> input_numbers(istream& in, size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

Input
read_input(istream& in) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter column count: ";
    in >> data.bin_count;

    return data;
}

vector<size_t> make_histogram(Input data) {
    double min, max;
    find_minmax(data.numbers, min, max);
    vector<size_t> bins(data.bin_count);
    for (double number : data.numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * data.bin_count);
        if (bin == data.bin_count) {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}

void show_histogram_text(const vector<size_t>& bins) {
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_bin = bins[0];
    for (size_t bin : bins) {
        if (max_bin < bin) {
            max_bin = bin;
        }
    }

    for (size_t bin : bins) {
        double height = bin;

        if (max_bin > MAX_ASTERISK) {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bin);
        }

        if (bin < 100) {
            cout << " ";
        }
        if (bin < 10) {
            cout << " ";
        }
        cout << bin << "|";
        for (size_t i = 0; i < height; i++) {
            cout << "*";
        }
        cout << endl;
    }
}

int main() {
    // Ввод данных
    const auto input = read_input(cin);

    // Обработка данных
    const auto bins = make_histogram(input);

    // Вывод данных
    show_histogram_svg(bins);

    return 0;
}
