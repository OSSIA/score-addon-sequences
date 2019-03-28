#pragma once
#include <Process/Inspector/ProcessInspectorWidgetDelegate.hpp>
#include <Process/Inspector/ProcessInspectorWidgetDelegateFactory.hpp>

#include <score/command/Dispatchers/CommandDispatcher.hpp>

#include <sequence/Process.hpp>

namespace sequence
{
class InspectorWidget final
    : public Process::InspectorWidgetDelegate_T<sequence::Model>
{
public:
  explicit InspectorWidget(
      const sequence::Model& object, const score::DocumentContext& context,
      QWidget* parent);
  ~InspectorWidget() override;

private:
  CommandDispatcher<> m_dispatcher;
};

class InspectorFactory final
    : public Process::InspectorWidgetDelegateFactory_T<Model, InspectorWidget>
{
  SCORE_CONCRETE("93a7e349-fdde-4ade-b6cc-8d1242719b7d")
};
}
