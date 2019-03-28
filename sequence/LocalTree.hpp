#pragma once
#include <LocalTree/LocalTreeComponent.hpp>
#include <LocalTree/Scenario/ProcessComponent.hpp>

namespace sequence
{
class Model;

class LocalTreeProcessComponent : public LocalTree::ProcessComponent_T<Model>
{
  COMPONENT_METADATA("da1573cd-2bbe-40cb-acb9-abed8844c8e4")

public:
  LocalTreeProcessComponent(
      const Id<score::Component>& id, ossia::net::node_base& parent,
      sequence::Model& scenario, LocalTree::DocumentPlugin& doc,
      QObject* parent_obj);

  ~LocalTreeProcessComponent() override;
};

using LocalTreeProcessComponentFactory
    = LocalTree::ProcessComponentFactory_T<LocalTreeProcessComponent>;
}
