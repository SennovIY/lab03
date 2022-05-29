#include "histogram.h"
#include "svg.h"

#include <curl/curl.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

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
read_input(istream& in, bool prompt = "true") {
    Input data;

    if (prompt) {
        cerr << "Enter number count: ";
    }
    size_t number_count;
    in >> number_count;

    if (prompt) {
        cerr << "Enter numbers: ";
    }
    data.numbers = input_numbers(in, number_count);

    if (prompt) {
        cerr << "Enter column count: ";
    }
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

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    // TODO: дописывать данные к буферу.
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);

    size_t data_size = item_size * item_count;

    buffer->write(static_cast<const char*>(items), data_size);

    return data_size;
}

Input download(const string& address) {
    stringstream buffer;

    // TODO: заполнить буфер.
    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            exit(1);
        }
    curl_easy_cleanup(curl);
    }

    return read_input(buffer, false);
}

int main(int argc, char* argv[]) {
    Input input;
    if (argc > 1) {
        input = download(argv[1]);
    } else {
        input = read_input(cin, true);
    }

    // Ввод данных
    /*const auto input = read_input(cin, true);*/

    // Обработка данных
    const auto bins = make_histogram(input);

    // Вывод данных
    show_histogram_svg(bins);

    return 0;
}
