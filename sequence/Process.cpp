#include "Process.hpp"

#include <wobjectimpl.h>
#include <Automation/AutomationModel.hpp>
#include <Curve/Segment/Power/PowerSegment.hpp>
W_OBJECT_IMPL(sequence::Model)
W_OBJECT_IMPL(sequence::Breakpoint)
namespace sequence
{

Model::Model(
    const TimeVal& duration, const Id<Process::ProcessModel>& id,
    QObject* parent)
    : Process::ProcessModel{duration, id, "sequenceProcess", parent}
{
  metadata().setInstanceName(*this);

  {
  auto autom = new Automation::ProcessModel(duration, Id<Process::ProcessModel>{1}, this);
  autom->curve().fromCurveData({
       {
            Id<Curve::SegmentModel>{1},
            Curve::Point{0, 0},
            Curve::Point{0.2, 0.6},
            {}, Id<Curve::SegmentModel>{2},
          Metadata<ConcreteKey_k, Curve::PowerSegment>::get(),
            QVariant::fromValue(Curve::PowerSegmentData{})
        },
        {
            Id<Curve::SegmentModel>{2},
            Curve::Point{0.2, 0.6},
            Curve::Point{0.7, 0.3},
            Id<Curve::SegmentModel>{1}, Id<Curve::SegmentModel>{3},
            Metadata<ConcreteKey_k, Curve::PowerSegment>::get(),
            QVariant::fromValue(Curve::PowerSegmentData{})
        },
        {
            Id<Curve::SegmentModel>{3},
            Curve::Point{0.7, 0.3},
            Curve::Point{1., 0.5},
            Id<Curve::SegmentModel>{2}, {},
            Metadata<ConcreteKey_k, Curve::PowerSegment>::get(),
            QVariant::fromValue(Curve::PowerSegmentData{})
        }});

  processes.add(autom);
  m_front = autom->id();
  }

  {
  auto autom = new Automation::ProcessModel(duration, Id<Process::ProcessModel>{2}, this);
  autom->curve().fromCurveData({
       {
            Id<Curve::SegmentModel>{1},
            Curve::Point{0, 0.7},
            Curve::Point{0.5, 0.5},
            {}, Id<Curve::SegmentModel>{2},
          Metadata<ConcreteKey_k, Curve::PowerSegment>::get(),
            QVariant::fromValue(Curve::PowerSegmentData{})
        },
        {
            Id<Curve::SegmentModel>{2},
            Curve::Point{0.5, 0.5},
            Curve::Point{0.7, 0.8},
            Id<Curve::SegmentModel>{1}, Id<Curve::SegmentModel>{3},
            Metadata<ConcreteKey_k, Curve::PowerSegment>::get(),
            QVariant::fromValue(Curve::PowerSegmentData{})
        },
        {
            Id<Curve::SegmentModel>{3},
            Curve::Point{0.7, 0.8},
            Curve::Point{1., 0.},
            Id<Curve::SegmentModel>{2}, {},
            Metadata<ConcreteKey_k, Curve::PowerSegment>::get(),
            QVariant::fromValue(Curve::PowerSegmentData{})
        }});

  processes.add(autom);
  }

  {
    auto bp = new Breakpoint{Id<Breakpoint>{0}, this};
    bp->setPosition(0.);
    breakpoints.add(bp);
  }
  {
    auto bp = new Breakpoint{Id<Breakpoint>{1}, this};
    bp->setPosition(0.5);
    breakpoints.add(bp);
  }
  {
    auto bp = new Breakpoint{Id<Breakpoint>{2}, this};
    bp->setPosition(1.);
    breakpoints.add(bp);
  }
}

Model::~Model()
{
}

QString Model::prettyName() const noexcept
{
  return tr("sequence Process");
}

void Model::startExecution()
{
}

void Model::stopExecution()
{
}

void Model::reset()
{
}

void Model::setDurationAndScale(const TimeVal& newDuration) noexcept
{
  setDuration(newDuration);
  for(auto& proc : processes)
    proc.setDurationAndScale(newDuration);
}

void Model::setDurationAndGrow(const TimeVal& newDuration) noexcept
{
  setDuration(newDuration);
  for(auto& proc : processes)
    proc.setDurationAndGrow(newDuration);
}

void Model::setDurationAndShrink(const TimeVal& newDuration) noexcept
{
  setDuration(newDuration);
  for(auto& proc : processes)
    proc.setDurationAndShrink(newDuration);
}
}
template <>
void DataStreamReader::read(const sequence::Model& proc)
{
  insertDelimiter();
}

template <>
void DataStreamWriter::write(sequence::Model& proc)
{
  checkDelimiter();
}

template <>
void JSONObjectReader::read(const sequence::Model& proc)
{
}

template <>
void JSONObjectWriter::write(sequence::Model& proc)
{
}
