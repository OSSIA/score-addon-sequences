#pragma once
#include <Process/GenericProcessFactory.hpp>

#include <sequence/Presenter.hpp>
#include <sequence/Process.hpp>
#include <sequence/View.hpp>

namespace sequence
{
using LayerFactory = Process::LayerFactory_T<
    sequence::Model, sequence::Presenter, sequence::View>;
}
