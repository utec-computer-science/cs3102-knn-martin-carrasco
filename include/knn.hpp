#include <cmath>
#include <iostream>
#include <memory>
#include <tuple>
#include <type_traits>
#include <vector>

template <class KNNTrait> struct Point {
  using ObjType = typename KNNTrait::ObjType;

  std::array<ObjType, KNNTrait::Size> value;

  bool operator<(const Point &point) const {
    for (int x = 0; x < value.size(); x++) {
      if (value[x] >= point.value[x])
        return false;
    }
    return true;
  }
  double distance(const Point &point) const {
    double total = 0;
    for (int x = 0; x < value.size(); x++)
      total += pow(point.value[x] - value[x], 2);
    return sqrt(total);
  }

  void print() {
    std::cout << "(";
    for (auto start = value.begin(); start != value.end(); start++) {
      std::cout << *start << ",";
    }
    std::cout << ")";
  }
};

template <class Trait> class KNN {
public:
  static const unsigned int Size = Trait::Size;
  using Point = ::Point<KNN<Trait>>;
  using ObjType = typename Trait::ObjType;
  using PointPtr = Point *;

private:
  std::vector<PointPtr> points;

public:
  template <class... Args> void insert_point(Args... objs);

  template <class... Args> auto get_neighbors(Args... objs, int k);
};

class Int2DPoints {
public:
  using ObjType = int;
  constexpr static unsigned int Size = 2;
};
