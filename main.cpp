#include "histogram.h"
#include "svg.h"

#include <iostream>
#include <vector>
#include <windows.h>
#include <tchar.h>
#define INFO_BUFFER_SIZE 32767

using namespace std;

vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count) {
    double min, max;
    find_minmax(numbers, min, max);
    vector<size_t> bins(bin_count);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count) {
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

    DWORD info = GetVersion();

    printf("version = %u\n", info);
    printf("version = %08x\n", info);

    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;
    printf("version = %08x\n", version);

    DWORD platform = info >> 16;

    DWORD version_mask = 0b00000000'11111111;
    DWORD version_major = version & version_mask;
    DWORD version_minor = version >> 8;

    DWORD build;
    if ((info & 0x80000000) == 0) {
        build = platform;
    }

    printf("Windows v%u.%u (build %u)\n", version_major, version_minor, build);


    TCHAR  infoBuf[INFO_BUFFER_SIZE];
    DWORD  bufCharCount = INFO_BUFFER_SIZE;

    if(!GetComputerName(infoBuf, &bufCharCount)) printf("GetComputerName");
    printf("\nComputer name: %s\n", infoBuf);

    return 0;
    // Ввод данных
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    // Обработка данных
    const auto bins = make_histogram(numbers, bin_count);

    // Вывод данных
    show_histogram_svg(bins);


}
