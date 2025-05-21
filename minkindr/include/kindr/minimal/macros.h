#pragma once
#include <cmath>
namespace kindr {
namespace minimal {
#define CHECK_NEAR(val1, val2, abs_error)                                                    \
  if (std::abs((val1) - (val2)) > (abs_error)) {                                             \
    std::ostringstream oss;                                                                  \
    oss << "CHECK_NEAR failed: " << #val1 << "=" << (val1) << ", " << #val2 << "=" << (val2) \
        << ", abs_error=" << (abs_error);                                                    \
    throw std::runtime_error(oss.str());                                                     \
  }

#define EIGEN_MATRIX_NEAR(mat1, mat2, abs_error)                       \
  ((mat1).rows() == (mat2).rows() && (mat1).cols() == (mat2).cols() && \
   ((mat1) - (mat2)).cwiseAbs().maxCoeff() <= (abs_error))

#define EIGEN_MATRIX_EQUAL_DOUBLE(mat1, mat2)                          \
  ((mat1).rows() == (mat2).rows() && (mat1).cols() == (mat2).cols() && \
   ((mat1).array() == (mat2).array()).all())

}  // namespace minimal
}  // namespace kindr