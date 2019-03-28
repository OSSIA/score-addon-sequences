#include "View.hpp"
#include <sequence/Presenter.hpp>
#include <Process/Style/ScenarioStyle.hpp>

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <wobjectimpl.h>
W_OBJECT_IMPL(sequence::View)
namespace sequence
{

View::View(QGraphicsItem* parent) : LayerView{parent}
{
}

View::~View()
{
}

const constexpr double side = 7;
static const QPainterPath& triangle{[] {
  QPainterPath path;
  path.addEllipse({0, 0, 8, 8});
  return path;
}()};

void View::paint_impl(QPainter* p) const
{
  QPen pen(QColor::fromRgba(qRgba(200, 200, 200, 150)), 1);
  QBrush br(Qt::gray);
  p->setPen(pen);
  p->setBrush(br);
  for (double col : m_presenter->breakpoints())
  {
    p->save();
    p->translate(col * width() - side / 2., Header::headerHeight());
    p->setCompositionMode(QPainter::CompositionMode_Exclusion);
    p->drawLine(QPointF{side / 2., 0}, QPointF{side / 2., height() - Header::headerHeight()});
    p->setCompositionMode(QPainter::CompositionMode_SourceOver);
    p->drawPath(triangle);
    p->restore();
  }
}

void View::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  m_clicked = ossia::none;

  const auto pos = event->pos();
  for (double col : m_presenter->breakpoints())
  {
    if (std::abs(col * width() - pos.x()) < 2.)
    {
      if (event->button() == Qt::LeftButton)
      {
        m_clicked = col;
        break;
      }
      else if (event->button() == Qt::RightButton)
      {
        //removePoint(e.first);
      }
      break;
    }
  }
}

void View::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  if (m_clicked)
  {/*
    m_colors = m_origColors;
    auto cur_it = m_colors.find(*m_clicked);
    if (cur_it != m_colors.end())
    {
      auto col = cur_it->second;
      m_colors.erase(*m_clicked);
      auto np = std::max(0., event->pos().x()) / m_dataWidth;

      m_colors.insert(std::make_pair(np, col));
      update();
    }
    */
    movePoint(*m_clicked, event->pos().x());
  }
}

void View::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  if (m_clicked)
  {
    released({});
    /*
    m_colors = m_origColors;
    auto cur_it = m_colors.find(*m_clicked);
    if (cur_it != m_colors.end())
    {
      auto col = cur_it->second;
      m_colors.erase(*m_clicked);
      auto np = event->pos().x() / m_dataWidth;

      m_colors.insert(std::make_pair(np, col));
      movePoint(*m_clicked, np);
      update();
    }
    */
  }

  m_clicked = ossia::none;
}

}
