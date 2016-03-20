/*    This file is part of the Gudhi Library. The Gudhi library
 *    (Geometric Understanding in Higher Dimensions) is a generic C++
 *    library for computational topology.
 *
 *    Author(s):       Siargey Kachanovich
 *
 *    Copyright (C) 2016  INRIA Sophia Antipolis-Méditerranée (France)
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "witness_complex_points"
#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>

#include <gudhi/Simplex_tree.h>
#include <gudhi/Witness_complex.h>
#include <gudhi/Landmark_choice_by_random_point.h>
#include <gudhi/Landmark_choice_by_furthest_point.h>

#include <iostream>
#include <vector>

typedef std::vector<double> Point;
typedef std::vector< Vertex_handle > typeVectorVertex;
typedef Gudhi::Simplex_tree<> Simplex_tree;
typedef Gudhi::witness_complex::Witness_complex<Simplex_tree> WitnessComplex;

BOOST_AUTO_TEST_CASE(witness_complex_points) {
  std::vector< typeVectorVertex > knn;
  std::vector< Point > points;
  // Add grid points as witnesses
  for (double i = 0; i < 10; i += 1.0)
    for (double j = 0; j < 10; j += 1.0)
      for (double k = 0; k < 10; k += 1.0)
        points.push_back(Point({i, j, k}));

  bool b_print_output = false;
  // First test: random choice
  Simplex_tree complex1;
  Gudhi::witness_complex::landmark_choice_by_random_point(points, 100, knn);
  assert(!knn.empty());
  WitnessComplex witnessComplex1(knn, 100, 3, complex1);
  BOOST_CHECK(witnessComplex1.is_witness_complex(knn, b_print_output));

  // Second test: furthest choice
  knn.clear();
  Simplex_tree complex2;
  Gudhi::witness_complex::landmark_choice_by_furthest_point(points, 100, knn);
  WitnessComplex witnessComplex2(knn, 100, 3, complex2);
  BOOST_CHECK(witnessComplex2.is_witness_complex(knn, b_print_output));
}