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

#pragma once

#include <memory>
#include <string>

#include "resource/CpuResource.h"
#include "resource/DiskResource.h"
#include "resource/GpuResource.h"
#include "resource/Resource.h"

namespace milvus {
namespace scheduler {

class ResourceFactory {
 public:
    static std::shared_ptr<Resource>
    Create(const std::string& name, const std::string& type, uint64_t device_id, bool enable_loader = true,
           bool enable_executor = true);
};

}  // namespace scheduler
}  // namespace milvus
