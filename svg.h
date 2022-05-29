#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

#include <iostream>
#include <vector>
#include <windows.h>
#include <tchar.h>

using namespace std;

void correct_bin_height(const vector<size_t>& bins, double& bin_height);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string fill, string stroke);
void show_histogram_svg(const vector<size_t>& bins, double bin_height);
void get_version_info(DWORD &version_major, DWORD &version_minor, DWORD &build);

#endif // SVG_H_INCLUDED
