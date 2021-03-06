/* Copyright 2016 The TensorFlow Authors All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef TENSORFLOW_CORE_PROFILER_INTERNAL_RUNTIME_EAGER_PROFILER_H_
#define TENSORFLOW_CORE_PROFILER_INTERNAL_RUNTIME_EAGER_PROFILER_H_

#include "tensorflow/core/common_runtime/eager/context.h"
#include "tensorflow/core/profiler/internal/profiler_interface.h"

namespace tensorflow {
namespace profiler {
namespace runtime {

class TraceCollector : public RunMetadataListener {
 public:
  TraceCollector(EagerContext* const eager_context);

  void BeforeClearRunMetadata() override;

  Status CollectData(RunMetadata* run_metadata);

 private:
  RunMetadata run_metadata_;
  EagerContext* const context_;
};

class EagerProfiler : public ProfilerInterface {
 public:
  static std::unique_ptr<ProfilerInterface> Create(
      EagerContext* const eager_context);

  Status Start() override;

  Status Stop() override;

  Status CollectData(RunMetadata* run_metadata) override;

 private:
  EagerProfiler(EagerContext* const eager_context);

  // Trace is neither copyable nor movable.
  EagerProfiler(const EagerProfiler&) = delete;
  EagerProfiler& operator=(const EagerProfiler&) = delete;

  EagerContext* const context_;
  TraceCollector collector_;
};

}  // namespace runtime
}  // namespace profiler
}  // namespace tensorflow

#endif  // TENSORFLOW_CORE_PROFILER_INTERNAL_RUNTIME_EAGER_PROFILER_H_
