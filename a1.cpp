#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

struct Circle {
    long double x, y, r;
};

bool is_inside(long double px, long double py, const Circle& c) {
    if (c.r <= 0) return false;
    long double dx = px - c.x;
    long double dy = py - c.y;
    return (dx * dx + dy * dy) <= (c.r * c.r);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::vector<Circle> circles(3);
    for (int i = 0; i < 3; ++i) {
        std::cin >> circles[i].x >> circles[i].y >> circles[i].r;
    }

    long double min_x = circles[0].x - circles[0].r;
    long double max_x = circles[0].x + circles[0].r;
    long double min_y = circles[0].y - circles[0].r;
    long double max_y = circles[0].y + circles[0].r;

    for (size_t i = 1; i < circles.size(); ++i) {
        min_x = std::max(min_x, circles[i].x - circles[i].r);
        max_x = std::min(max_x, circles[i].x + circles[i].r);
        min_y = std::max(min_y, circles[i].y - circles[i].r);
        max_y = std::min(max_y, circles[i].y + circles[i].r);
    }

    if (min_x >= max_x || min_y >= max_y) {
        std::cout << std::fixed << std::setprecision(17) << 0.0L << std::endl;
        return 0;
    }

    long double box_area = (max_x - min_x) * (max_y - min_y);

    const long long num_points = 20000000;
    std::mt19937 gen(1337);
    std::uniform_real_distribution<long double> distX(min_x, max_x);
    std::uniform_real_distribution<long double> distY(min_y, max_y);

    long long hits = 0;
    for (long long i = 0; i < num_points; ++i) {
        long double px = distX(gen);
        long double py = distY(gen);

        if (is_inside(px, py, circles[0]) &&
            is_inside(px, py, circles[1]) &&
            is_inside(px, py, circles[2])) {
            hits++;
        }
    }

    long double estimated_area = (long double)hits / num_points * box_area;

    std::cout << std::fixed << std::setprecision(17) << estimated_area << std::endl;

    return 0;
}