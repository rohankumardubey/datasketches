/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef THETA_UNION_BASE_HPP_
#define THETA_UNION_BASE_HPP_

#include "theta_update_sketch_base.hpp"

namespace datasketches {

template<
  typename Entry,
  typename ExtractKey,
  typename Policy,
  typename Sketch,
  typename CompactSketch,
  typename Allocator = std::allocator<Entry>
>
class theta_union_base {
public:
  using hash_table = theta_update_sketch_base<Entry, ExtractKey, Allocator>;
  using resize_factor = typename hash_table::resize_factor;
  using comparator = compare_by_key<ExtractKey>;

  theta_union_base(uint8_t lg_cur_size, uint8_t lg_nom_size, resize_factor rf, uint64_t theta, uint64_t seed, const Policy& policy, const Allocator& allocator);

  template<typename FwdSketch>
  void update(FwdSketch&& sketch);

  CompactSketch get_result(bool ordered = true) const;

private:
  Policy policy_;
  hash_table table_;
  uint64_t union_theta_;
};

} /* namespace datasketches */

#include "theta_union_base_impl.hpp"

#endif
