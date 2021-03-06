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
#include <utility>
#include <vector>

#include "Array.h"
#include "Buffer.h"
#include "Config.h"
#include "Schema.h"
#include "Tensor.h"
#include "knowhere/adapter/ArrowAdapter.h"

namespace knowhere {

class Dataset;

using DatasetPtr = std::shared_ptr<Dataset>;

class Dataset {
 public:
    Dataset() = default;

    Dataset(std::vector<ArrayPtr>&& array, SchemaPtr array_schema, std::vector<TensorPtr>&& tensor,
            SchemaPtr tensor_schema)
        : array_(std::move(array)),
          array_schema_(std::move(array_schema)),
          tensor_(std::move(tensor)),
          tensor_schema_(std::move(tensor_schema)) {
    }

    Dataset(std::vector<ArrayPtr> array, SchemaPtr array_schema)
        : array_(std::move(array)), array_schema_(std::move(array_schema)) {
    }

    Dataset(std::vector<TensorPtr> tensor, SchemaPtr tensor_schema)
        : tensor_(std::move(tensor)), tensor_schema_(std::move(tensor_schema)) {
    }

    Dataset(const Dataset&) = delete;
    Dataset&
    operator=(const Dataset&) = delete;

    DatasetPtr
    Clone() {
        auto dataset = std::make_shared<Dataset>();

        std::vector<ArrayPtr> clone_array;
        for (auto& array : array_) {
            clone_array.emplace_back(CopyArray(array));
        }
        dataset->set_array(clone_array);

        std::vector<TensorPtr> clone_tensor;
        for (auto& tensor : tensor_) {
            auto buffer = tensor->data();
            std::shared_ptr<Buffer> copy_buffer;
            // TODO: checkout copy success;
            buffer->Copy(0, buffer->size(), &copy_buffer);
            auto copy = std::make_shared<Tensor>(tensor->type(), copy_buffer, tensor->shape());
            clone_tensor.emplace_back(copy);
        }
        dataset->set_tensor(clone_tensor);

        if (array_schema_)
            dataset->set_array_schema(CopySchema(array_schema_));
        if (tensor_schema_)
            dataset->set_tensor_schema(CopySchema(tensor_schema_));

        return dataset;
    }

 public:
    const std::vector<ArrayPtr>&
    array() const {
        return array_;
    }

    void
    set_array(std::vector<ArrayPtr> array) {
        array_ = std::move(array);
    }

    const std::vector<TensorPtr>&
    tensor() const {
        return tensor_;
    }

    void
    set_tensor(std::vector<TensorPtr> tensor) {
        tensor_ = std::move(tensor);
    }

    SchemaConstPtr
    array_schema() const {
        return array_schema_;
    }

    void
    set_array_schema(SchemaPtr array_schema) {
        array_schema_ = std::move(array_schema);
    }

    SchemaConstPtr
    tensor_schema() const {
        return tensor_schema_;
    }

    void
    set_tensor_schema(SchemaPtr tensor_schema) {
        tensor_schema_ = std::move(tensor_schema);
    }

    // const Config &
    // meta() const { return meta_; }

    // void
    // set_meta(Config meta) {
    //    meta_ = std::move(meta);
    //}

 private:
    std::vector<ArrayPtr> array_;
    SchemaPtr array_schema_;
    std::vector<TensorPtr> tensor_;
    SchemaPtr tensor_schema_;
    // Config meta_;
};

using DatasetPtr = std::shared_ptr<Dataset>;

}  // namespace knowhere
