#pragma once
#include <Process/Focus/FocusDispatcher.hpp>
#include <Process/LayerPresenter.hpp>
#include <Process/ZoomHelper.hpp>
#include <Scenario/Document/Interval/IntervalPresenter.hpp>

#include <Scenario/Document/TimeSync/TriggerView.hpp>
#include <score/model/Identifier.hpp>

namespace sequence
{
class Model;
class View;
class Presenter;

class Header final
    : public QGraphicsItem
{
public:
  Header(
      const Presenter& slotView,
      QGraphicsItem* parent);

  const Presenter& presenter() const { return m_presenter; }
  static constexpr int static_type()
  {
    return QGraphicsItem::UserType + 854657;
  }
  int type() const override { return static_type(); }

  static constexpr double headerHeight() { return Scenario::SlotHeader::headerHeight(); }
  static constexpr double handleWidth() { return Scenario::SlotHeader::handleWidth(); }
  static constexpr double menuWidth() { return Scenario::SlotHeader::menuWidth(); }

  QRectF boundingRect() const override;
  void paint(
      QPainter* painter,
      const QStyleOptionGraphicsItem* option,
      QWidget* widget) override;

  void setWidth(qreal width);
  void setMini(bool b);

private:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) final override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) final override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) final override;

  void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
  void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

  const Presenter& m_presenter;
  qreal m_width{};
};

class Presenter final : public Process::LayerPresenter
{
public:
  explicit Presenter(
      const Model& model, View* view,
      const Process::ProcessPresenterContext& ctx, QObject* parent);

  const ossia::flat_set<double>& breakpoints() const noexcept
  { return m_breakpoints; }
  const std::vector<Scenario::LayerData>& layers() const noexcept
  { return m_layers; }
  void requestProcessSelectorMenu(
      QPoint pos,
      QPointF sp) const;

  View* view() const noexcept { return m_view; }

private:
  void setWidth(qreal width) override;
  void setHeight(qreal height) override;

  const Process::ProcessModel& model() const override;
  const Id<Process::ProcessModel>& modelId() const override;


  void putToFront() override;
  void putBehind() override;

  void on_zoomRatioChanged(ZoomRatio) override;
  void parentGeometryChanged() override;


  void createLayer(const Process::ProcessModel& proc);
  void on_layerModelPutToFront(const Process::ProcessModel& proc);
  void on_layerModelPutToBack(const Process::ProcessModel& proc);

  void updateProcessShape(const Scenario::LayerData& data);
  void updateProcessesShape();
  void updateHeader();
  void updateBreakpoints();
  void setHeaderWidth(double w);

  const Model& m_model;
  View* m_view{};

  double m_zoomRatio{};

  Header* m_header{};
  Process::HeaderDelegate* m_headerDelegate{};
  std::vector<Scenario::LayerData> m_layers;

  ossia::flat_set<double> m_breakpoints;
};
}
