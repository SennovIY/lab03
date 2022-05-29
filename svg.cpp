#include "svg.h"
#include <windows.h>
#include <tchar.h>

const auto INFO_BUFFER_SIZE = 32767;

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end() {
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string fill = "black", string stroke = "black") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "'/>";
}

void get_version_info(DWORD &version_major, DWORD &version_minor, DWORD &build) {
    DWORD info = GetVersion();

    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;
    DWORD platform = info >> 16;

    DWORD version_mask = 0b00000000'11111111;
    version_major = version & version_mask;
    version_minor = version >> 8;

    if ((info & 0x80000000) == 0) {
        build = platform;
    }

  //  printf("Windows v%u.%u (build %u)\n", version_major, version_minor, build);




  /*  if(!GetComputerName(infoBuf, &bufCharCount)) printf("GetComputerName");
    printf("\nComputer name: %s\n", infoBuf);*/
}

void show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto BIN_STROKE = "red";
    const auto BIN_FILL = "#3CB371";

    const auto MAX_ASTERISK = (IMAGE_WIDTH - TEXT_WIDTH)/10;

    size_t max_bin = bins[0];
    for (size_t bin : bins) {
        if (max_bin < bin) {
            max_bin = bin;
        }
    }

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        double height = bin;
        if (max_bin > MAX_ASTERISK) {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bin);
        }
        /* string bin_text = "";
        if (bin < 100) {
            bin_text += " ";
        }
        if (bin < 10) {
            bin_text += " ";
        }
        bin_text += to_string(bin); */
        const double bin_width = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, BIN_FILL, BIN_STROKE);
        top += BIN_HEIGHT;
    }

    DWORD version_major, version_minor, build;
    TCHAR  infoBuf[INFO_BUFFER_SIZE];
    DWORD  bufCharCount = INFO_BUFFER_SIZE;
    GetComputerName(infoBuf, &bufCharCount);
    get_version_info(version_major, version_minor, build);

    svg_text(TEXT_LEFT, top + 20, "Windows v" + to_string(version_major) + "." + to_string(version_minor) + " (build " + to_string(build) + ")");
    svg_text(TEXT_LEFT, top + 40, "Computer name: ");
    svg_text(TEXT_LEFT + 110, top + 40, infoBuf);
    svg_end();
}
