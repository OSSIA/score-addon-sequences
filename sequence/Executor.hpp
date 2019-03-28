#pragma once
#include <Process/Execution/ProcessComponent.hpp>

#include <ossia/dataflow/node_process.hpp>

namespace sequence
{
class Model;
class ProcessExecutorComponent final
    : public Execution::ProcessComponent_T<
          sequence::Model, ossia::node_process>
{
  COMPONENT_METADATA("6cdcea63-658a-4675-94ad-550d1d235e79")
public:
  ProcessExecutorComponent(
      Model& element, const Execution::Context& ctx,
      const Id<score::Component>& id, QObject* parent);
};

using ProcessExecutorComponentFactory
    = Execution::ProcessComponentFactory_T<ProcessExecutorComponent>;
}
