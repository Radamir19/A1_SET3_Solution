#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <iomanip>
#include <string>

// Структура для представления круга
struct Circle {
    long double x, y, r;
};

// Функция для проверки, находится ли точка внутри круга
bool is_inside(long double px, long double py, const Circle& c) {
    if (c.r <= 0) return false;
    long double dx = px - c.x;
    long double dy = py - c.y;
    return (dx * dx + dy * dy) <= (c.r * c.r);
}

// Функция, выполняющая один замер методом Монте-Карло
long double run_monte_carlo(long long num_points, const std::vector<Circle>& circles, bool use_narrow_box, std::mt19937& gen) {
    long double min_x, max_x, min_y, max_y;

    if (use_narrow_box) {
        // "Узкий" прямоугольник (пересечение BBox'ов)
        min_x = circles[0].x - circles[0].r;
        max_x = circles[0].x + circles[0].r;
        min_y = circles[0].y - circles[0].r;
        max_y = circles[0].y + circles[0].r;
        for (size_t i = 1; i < circles.size(); ++i) {
            min_x = std::max(min_x, circles[i].x - circles[i].r);
            max_x = std::min(max_x, circles[i].x + circles[i].r);
            min_y = std::max(min_y, circles[i].y - circles[i].r);
            max_y = std::max(max_y, circles[i].y + circles[i].r);
        }
    } else {
        // "Широкий" прямоугольник (объединение BBox'ов)
        min_x = circles[0].x - circles[0].r;
        max_x = circles[0].x + circles[0].r;
        min_y = circles[0].y - circles[0].r;
        max_y = circles[0].y + circles[0].r;
        for (size_t i = 1; i < circles.size(); ++i) {
            min_x = std::min(min_x, circles[i].x - circles[i].r);
            max_x = std::max(max_x, circles[i].x + circles[i].r);
            min_y = std::min(min_y, circles[i].y - circles[i].r);
            max_y = std::max(max_y, circles[i].y + circles[i].r);
        }
    }

    if (min_x >= max_x || min_y >= max_y) return 0.0L;
    long double box_area = (max_x - min_x) * (max_y - min_y);
    std::uniform_real_distribution<long double> distX(min_x, max_x);
    std::uniform_real_distribution<long double> distY(min_y, max_y);
    long long hits = 0;
    for (long long i = 0; i < num_points; ++i) {
        long double px = distX(gen); long double py = distY(gen);
        if (is_inside(px, py, circles[0]) && is_inside(px, py, circles[1]) && is_inside(px, py, circles[2])) {
            hits++;
        }
    }
    return (long double)hits / num_points * box_area;
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    std::vector<Circle> circles(3);
    // Входные данные для задачи A1
    circles[0] = {1, 1, 1};
    circles[1] = {1.5, 2, sqrtl(5.0L)/2.0L};
    circles[2] = {2, 1.5, sqrtl(5.0L)/2.0L};

    // Точное значение для задачи из A1, необходимое для расчета погрешности
    const long double PI = acos(-1.0L);
    const long double TRUE_AREA = 0.25L * PI + 1.25L * asin(0.8L) - 1.0L;

    std::mt19937 gen(1337);
    std::cout << "N,box_type,estimated_area,relative_error\n";
    std::cout << std::fixed << std::setprecision(17);

    // Цикл эксперимента
    for (long long n = 100; n <= 100000; n += 500) {
        // Замер для "широкого" прямоугольника
        long double area_wide = run_monte_carlo(n, circles, false, gen);
        long double err_wide = (TRUE_AREA > 0) ? std::abs(area_wide - TRUE_AREA) / TRUE_AREA : 0.0L;
        std::cout << n << ",wide," << area_wide << "," << err_wide << "\n";

        // Замер для "узкого" прямоугольника
        long double area_narrow = run_monte_carlo(n, circles, true, gen);
        long double err_narrow = (TRUE_AREA > 0) ? std::abs(area_narrow - TRUE_AREA) / TRUE_AREA : 0.0L;
        std::cout << n << ",narrow," << area_narrow << "," << err_narrow << "\n";
    }
    return 0;
}