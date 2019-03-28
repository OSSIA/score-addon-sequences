#include "LocalTree.hpp"

#include <LocalTree/Property.hpp>
#include <sequence/Process.hpp>

namespace sequence
{
LocalTreeProcessComponent::LocalTreeProcessComponent(
    const Id<score::Component>& id, ossia::net::node_base& parent,
    sequence::Model& proc, LocalTree::DocumentPlugin& sys, QObject* parent_obj)
    : LocalTree::ProcessComponent_T<sequence::Model>{
          parent, proc, sys, id, "sequenceComponent", parent_obj}
{
}

LocalTreeProcessComponent::~LocalTreeProcessComponent()
{
}
}
