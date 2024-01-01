#include <array>
#include <chrono>
#include <execution>
#include <iostream>
#include <valarray>

struct Point3D {
    std::valarray<double> coordinates;

    Point3D(double x, double y, double z) : coordinates({x, y, z}) {}
};

using Matrix3x3 = std::array<std::valarray<double>, 3>;

Point3D applyTransformation(const Point3D& point,
                            const Matrix3x3& rotationMatrix,
                            const Point3D& translation) {
    std::valarray<double> rotated(3);
    for (int i = 0; i < 3; ++i) {
        rotated[i] = (rotationMatrix[i] * point.coordinates).sum();
    }
    return Point3D(rotated[0] + translation.coordinates[0],
                   rotated[1] + translation.coordinates[1],
                   rotated[2] + translation.coordinates[2]);
}

int main() {
    // 예제 데이터: n개 3D 포인트
    std::vector<Point3D> points(5'000'000, Point3D(1.0, 2.0, 3.0));

    // 회전 행렬 및 이동 벡터 정의
    Matrix3x3 rotationMatrix = {std::valarray<double>{0, -1, 0},
                                std::valarray<double>{1, 0, 0},
                                std::valarray<double>{0, 0, 1}};
    Point3D translation(1.0, 2.0, 3.0);

    // 변환 시작 시간 측정
    auto start = std::chrono::high_resolution_clock::now();

    // 모든 포인트에 대해 변환 적용

    std::for_each(std::execution::par, points.begin(), points.end(),
                  [&rotationMatrix, &translation](auto& point) {
                      point = applyTransformation(point, rotationMatrix,
                                                  translation);
                  });

    // 변환 종료 시간 측정
    auto end = std::chrono::high_resolution_clock::now();

    // 소요된 시간 계산 및 출력
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count();
    std::cout << "@ Transformations completed in " << duration << " ms"
              << std::endl;

    return 0;
}
