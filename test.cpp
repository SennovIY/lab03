#include "histogram.h"
#include "svg.h"

#include <cassert>
#include <vector>

using namespace std;

void test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void test_same() {
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void test_alone() {
    double min = 0;
    double max = 0;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void test_empty() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}

void test_small_bin_height() {
    double bin_height = 50;
    correct_bin_height({1,2,3}, bin_height);
    assert(bin_height == 50);
}

void test_big_bin_height() {
    double bin_height = 200;
    correct_bin_height({1, 2, 3, 4, 5, 6, 7}, bin_height);
    assert(bin_height == 100);
}

int main() {
    test_positive();
    test_negative();
    test_same();
    test_alone();
    test_empty();
    test_small_bin_height();
    test_big_bin_height();
}
