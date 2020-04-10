#include "../include/knn.hpp"
#include <algorithm>
#include <experimental/array>
#include <queue>
#include <stdexcept>
#include <tuple>
#include <utility>

template <typename Target, typename... Ts>
using areT = std::experimental::conjunction<std::is_same<Ts, Target>...>;

template <class Trait>
template <class... Args>
void KNN<Trait>::insert_point(Args... objs) {
  const int size = sizeof...(objs);

  static_assert(size == Size);
  static_assert(areT<ObjType, Args...>::value);

  std::array<ObjType, Size> obj_unpacked = {objs...};

  auto new_point = new Point();
  new_point->value = obj_unpacked;
  points.push_back(new_point);
}

template <class Trait>
template <class... Args>
auto KNN<Trait>::get_neighbors(Args... objs, int k) {
  const int size = sizeof...(objs);

  static_assert(size == Size);
  static_assert(areT<ObjType, Args...>::value);

  std::array<ObjType, Size> obj_unpacked = {objs...};

  auto compare_point = new Point();
  compare_point->value = obj_unpacked;

  std::vector<PointPtr> distances;
  distances.resize(points.size());


  std::partial_sort_copy(points.begin(), points.begin() + k,
                         distances.end(),
                         [](const auto &point1, const auto &point2) {
                           return point1->distance(compare_point) <
                                  point2->distance(compare_point);
                         });
  return distances;
}
