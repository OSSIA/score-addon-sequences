#pragma once
#include <Process/LayerView.hpp>
#include <ossia/detail/optional.hpp>

namespace sequence
{
class Presenter;
class View final : public Process::LayerView
{
  W_OBJECT(View)
public:
  explicit View(QGraphicsItem* parent);
  ~View() override;

  void movePoint(double from, double to) W_SIGNAL(movePoint, from, to);

  void setPresenter(Presenter* p) { m_presenter = p; }
private:
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
  void paint_impl(QPainter*) const override;
  ossia::optional<double> m_clicked;
  Presenter* m_presenter{};
};
}
