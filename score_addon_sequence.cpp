#include "score_addon_sequence.hpp"

#include <score/plugins/FactorySetup.hpp>

#include <sequence/CommandFactory.hpp>
#include <sequence/Executor.hpp>
#include <sequence/Inspector.hpp>
#include <sequence/Layer.hpp>
#include <sequence/LocalTree.hpp>
#include <sequence/Process.hpp>
#include <score_addon_sequence_commands_files.hpp>

score_addon_sequence::score_addon_sequence()
{
}

score_addon_sequence::~score_addon_sequence()
{
}

std::vector<std::unique_ptr<score::InterfaceBase>>
score_addon_sequence::factories(
    const score::ApplicationContext& ctx, const score::InterfaceKey& key) const
{
  return instantiate_factories<
      score::ApplicationContext,
      FW<Process::ProcessModelFactory, sequence::ProcessFactory>,
      FW<Process::LayerFactory, sequence::LayerFactory>,
      FW<Process::InspectorWidgetDelegateFactory, sequence::InspectorFactory>,
      FW<Execution::ProcessComponentFactory,
         sequence::ProcessExecutorComponentFactory>,
      FW<LocalTree::ProcessComponentFactory,
         sequence::LocalTreeProcessComponentFactory>>(ctx, key);
}

std::pair<const CommandGroupKey, CommandGeneratorMap>
score_addon_sequence::make_commands()
{
  using namespace sequence;
  std::pair<const CommandGroupKey, CommandGeneratorMap> cmds{
      CommandFactoryName(), CommandGeneratorMap{}};

  ossia::for_each_type<
#include <score_addon_sequence_commands.hpp>
      >(score::commands::FactoryInserter{cmds.second});

  return cmds;
}

#include <score/plugins/PluginInstances.hpp>
SCORE_EXPORT_PLUGIN(score_addon_sequence)
