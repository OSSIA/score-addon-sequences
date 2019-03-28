#pragma once
#include <Process/GenericProcessFactory.hpp>
#include <Process/Process.hpp>

#include <sequence/Metadata.hpp>
#include <State/Message.hpp>
namespace sequence
{
class Breakpoint : public IdentifiedObject<Breakpoint>
{
  W_OBJECT(Breakpoint)
public:
  Breakpoint(id_type id, QObject* parent) noexcept
    : IdentifiedObject{id, "Break", parent}
  {

  }

  double position() const noexcept { return m_position; }
  void setPosition(double d) {
    if(d != m_position)
    {
      m_position = d;
      positionChanged(d);
    }
  }
  void positionChanged(double d) W_SIGNAL(positionChanged, d);

  const std::vector<State::Message>& state() const noexcept { return m_state; }
  void setState(
      std::vector<State::Message> st)
  {
    m_state = std::move(st);
    stateChanged();
  }

  void stateChanged() W_SIGNAL(stateChanged);
private:
  double m_position{};
  std::vector<State::Message> m_state;
};

class Model final : public Process::ProcessModel
{
  SCORE_SERIALIZE_FRIENDS
  PROCESS_METADATA_IMPL(sequence::Model)
  W_OBJECT(Model)

public:
  Model(
      const TimeVal& duration, const Id<Process::ProcessModel>& id,
      QObject* parent);

  template <typename Impl>
  Model(Impl& vis, QObject* parent) : Process::ProcessModel{vis, parent}
  {
    vis.writeTo(*this);
  }

  ~Model() override;

  score::EntityMap<Process::ProcessModel> processes;
  score::EntityMap<Breakpoint> breakpoints;

  using optional_process = ossia::optional<Id<Process::ProcessModel>>;
  optional_process frontProcess() const noexcept { return m_front; }
  void setFrontProcess(optional_process d) {
    if(d != m_front)
    {
      m_front = d;
      frontProcessChanged(d);
    }
  }
  void frontProcessChanged(optional_process d) W_SIGNAL(frontProcessChanged, d);

private:
  optional_process m_front;
  QString prettyName() const noexcept override;
  void startExecution() override;
  void stopExecution() override;
  void reset() override;

  void setDurationAndScale(const TimeVal& newDuration) noexcept override;
  void setDurationAndGrow(const TimeVal& newDuration) noexcept override;
  void setDurationAndShrink(const TimeVal& newDuration) noexcept override;
};

using ProcessFactory = Process::ProcessFactory_T<sequence::Model>;
}
