// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "knowhere/index/vector_index/helpers/IndexParameter.h"
#include "knowhere/common/Exception.h"

#include <faiss/Index.h>

namespace knowhere {

faiss::MetricType
GetMetricType(METRICTYPE& type) {
    if (type == METRICTYPE::L2) {
        return faiss::METRIC_L2;
    }
    if (type == METRICTYPE::IP) {
        return faiss::METRIC_INNER_PRODUCT;
    }

    KNOWHERE_THROW_MSG("Metric type is invalid");
}

}  // namespace knowhere
