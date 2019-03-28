#include <score/command/Dispatchers/CommandDispatcher.hpp>

#include <sequence/Presenter.hpp>
#include <sequence/Process.hpp>
#include <sequence/View.hpp>

#include <Process/ProcessList.hpp>
#include <Process/Style/ScenarioStyle.hpp>
#include <QMenu>
#include <QPainter>
#include <score/graphics/GraphicsItem.hpp>
#include <Scenario/Application/Menus/ScenarioContextMenuManager.hpp>
#include <Scenario/Application/ScenarioApplicationPlugin.hpp>
namespace sequence
{
Header::Header(
    const Presenter& slotView,
    QGraphicsItem* parent)
    : QGraphicsItem{parent}
    , m_presenter{slotView}
    , m_width{m_presenter.view()->boundingRect().width()}
{
  this->setCacheMode(QGraphicsItem::NoCache);
  this->setAcceptHoverEvents(true);
  this->setFlag(ItemClipsToShape);
  this->setFlag(ItemClipsChildrenToShape);
  this->setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
}

QRectF Header::boundingRect() const
{
  return {0., 0., m_width, headerHeight()};
}

void Header::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget)
{
  /*
  painter->setRenderHint(QPainter::Antialiasing, false);
  const auto& style = Process::Style::instance();
  painter->setPen(style.SlotHeaderPen);
  painter->setBrush(style.NoBrush);

  if (m_width > 20)
  {

    // Grip
    double r = 4.5;
    double centerX = 9.;
    const double centerY = 7.5;

    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->drawLine(centerX - r, centerY + 0, centerX + r, centerY + 0);
    painter->drawLine(centerX - r, centerY - 3, centerX + r, centerY - 3);
    painter->drawLine(centerX - r, centerY + 3, centerX + r, centerY + 3);

    painter->setRenderHint(QPainter::Antialiasing, true);

    // Frame
    painter->drawRect(QRectF{0., 0., m_width, headerHeight() - 1});
  }
  else
  {
    painter->drawRect(QRectF{0., 0., m_width, headerHeight() - 1});
  }
  */
}

void Header::setWidth(qreal width)
{
  prepareGeometryChange();
  m_width = width;
  update();
}

/*
static std::unique_ptr<QDrag> slot_header_drag = nullptr;
static bool slot_drag_moving = false;
*/
void Header::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  /*
  slot_header_drag.reset();
  slot_drag_moving = false;
  m_presenter.selectedSlot(m_slotIndex);

  const auto xpos = event->pos().x();
  if (xpos >= 0 && xpos < 16)
  {
    slot_header_drag.reset(new QDrag(event->widget()));
  }
  else */if (
      boundingRect().contains(event->pos())
      && m_presenter.layers().size() > 1)
  {
      m_presenter.requestProcessSelectorMenu(event->screenPos(), event->scenePos());
  }

  event->accept();
}

void Presenter::requestProcessSelectorMenu(
    QPoint pos,
    QPointF sp) const
{
  if (const auto& proc = m_model.frontProcess())
  {
    for (auto& p : m_layers)
    {
      if (p.model->id() == proc)
      {
        auto menu = new QMenu;

        for (const auto& layer: m_layers)
        {
          auto& proc = layer.model->id();
          auto& p = m_model.processes.at(proc);
          auto name = p.prettyName();
          if (name.isEmpty())
            name = p.prettyShortName();
          QAction* procAct = new QAction{name, menu};
          QObject::connect(procAct, &QAction::triggered, [&, id=proc] {
            const_cast<Model&>(m_model).setFrontProcess(proc);
          });
          menu->addAction(procAct);
        }

        menu->exec(pos);
        menu->deleteLater();
        break;
      }
    }
  }
}

void Header::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  event->accept();
  /*

  const auto xpos = event->buttonDownPos(Qt::LeftButton).x();
  if (xpos >= 0 && xpos < 16 && slot_header_drag)
  {
    auto min_dist
        = (event->screenPos() - event->buttonDownScreenPos(Qt::LeftButton))
              .manhattanLength()
          >= QApplication::startDragDistance();

    if (min_dist)
    {
      slot_drag_moving = true;
    }
    if (!slot_drag_moving)
    {
      return;
    }

    bool temporal
        = dynamic_cast<const TemporalIntervalPresenter*>(&m_presenter);
    QMimeData* mime = new QMimeData;
    auto proc_id
        = temporal ? *m_presenter.model().smallView()[m_slotIndex].frontProcess
                   : m_presenter.model().fullView()[m_slotIndex].process;

    auto& proc = m_presenter.model().processes.at(proc_id);
    auto json = copyProcess(proc);
    json["Path"] = toJsonObject(score::IDocument::path(proc));
    json["Duration"] = m_presenter.model().duration.defaultDuration().msec();
    json["SlotIndex"] = m_slotIndex;
    json["View"] = temporal ? QStringLiteral("Small") : QStringLiteral("Full");
    mime->setData(score::mime::layerdata(), QJsonDocument{json}.toJson());
    slot_header_drag->setMimeData(mime);

    auto view = m_presenter.getSlots()[m_slotIndex].processes.front().view;
    slot_header_drag->setPixmap(view->pixmap().scaledToWidth(50));
    slot_header_drag->setHotSpot(QPoint(5, 5));

    QObject::connect(
        slot_header_drag.get(),
        &QDrag::destroyed,
        &m_presenter,
        [p = &m_presenter] { p->stopSlotDrag(); });

    m_presenter.startSlotDrag(m_slotIndex, mapToParent(event->pos()));
    slot_header_drag->exec();
    auto ptr = slot_header_drag.release();
    ptr->deleteLater();
  }
  */
}

void Header::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  /*
  slot_header_drag.reset();
  slot_drag_moving = false;
  */
  event->accept();
}

void Header::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
  /*
  const auto xpos = event->pos().x();
  if (xpos >= 0 && xpos < 16)
  {
    if (this->cursor().shape() != Qt::CrossCursor)
      setCursor(Qt::CrossCursor);
  }
  else
  {
    if (this->cursor().shape() == Qt::CrossCursor)
      unsetCursor();
  }
  */
}

void Header::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
  /*
  const auto xpos = event->pos().x();
  if (xpos >= 0 && xpos < 16)
  {
    if (this->cursor().shape() != Qt::CrossCursor)
      setCursor(Qt::CrossCursor);
  }
  else
  {
    if (this->cursor().shape() == Qt::CrossCursor)
      unsetCursor();
  }
  */
}

void Header::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
  /*
  if (this->cursor().shape() == Qt::CrossCursor)
    unsetCursor();
    */
}









Presenter::Presenter(
    const Model& layer, View* view,
    const Process::ProcessPresenterContext& ctx, QObject* parent)
  : Process::LayerPresenter{ctx, parent}, m_model{layer}, m_view{view}
  , m_header{new Header{*this, view}}
{
  view->setPresenter(this);
  for(auto& proc : layer.processes)
  {
    createLayer(proc);
  }

  updateBreakpoints();
  // TODO connect


  con(m_model,
      &Model::frontProcessChanged,
      this,
      [=](ossia::optional<Id<Process::ProcessModel>> proc) {
        if (proc)
        {
          on_layerModelPutToFront(m_model.processes.at(*proc));
        }
        else
        {
          {
            if (m_headerDelegate)
            {
              deleteGraphicsItem(m_headerDelegate);
              m_headerDelegate = nullptr;
            }
          }
        }
      });
  /*
  con(m_view, &View::movePoint,
      this, [=] (double oldpos, double newpos) {
    auto& proc = (Model&) m_model;
    for(auto& bp : proc.breakpoints)
    {
      if(bp.position() == oldpos)
      {
        bp.setPosition(newpos);
        break;
      }
    }

    for(auto& p : proc.processes)
    {
      p.moveBreakpoint(oldpos, newpos);
    }
  });

  con(m_view, &View::released,
      this, [] {

  });*/

}

void Presenter::setWidth(qreal val)
{
  m_view->setWidth(val);
  setHeaderWidth(val);
}

void Presenter::setHeight(qreal val)
{
  m_view->setHeight(val);
}

void Presenter::putToFront()
{
  m_view->setOpacity(1);
}

void Presenter::putBehind()
{
  m_view->setOpacity(0.2);
}

void Presenter::on_zoomRatioChanged(ZoomRatio r)
{
  m_zoomRatio = r;
  for(auto& proc : m_layers)
  {
    proc.presenter->on_zoomRatioChanged(r);
  }
  updateProcessesShape();
}

void Presenter::parentGeometryChanged()
{
  updateProcessesShape();
}

const Process::ProcessModel& Presenter::model() const
{
  return m_model;
}

const Id<Process::ProcessModel>& Presenter::modelId() const
{
  return m_model.id();
}

void Presenter::createLayer(const Process::ProcessModel& proc)
{

  const auto& procKey = proc.concreteKey();

  auto factory = score::GUIAppContext().interfaces<Process::LayerFactoryList>().findDefaultFactory(procKey);
  auto proc_view = factory->makeLayerView(proc, m_view);
  auto proc_pres
      = factory->makeLayerPresenter(proc, proc_view, m_context.context, this);
  proc_pres->on_zoomRatioChanged(m_zoomRatio);
  m_layers.push_back(
        Scenario::LayerData{&proc, proc_pres, proc_view});

  auto con_id = con(
        proc,
        &Process::ProcessModel::durationChanged,
        this,
        [&](const TimeVal&) {
    auto it
        = ossia::find_if(m_layers, [&](const Scenario::LayerData& elt) {
      return elt.model->id() == proc.id();
    });

    if (it != m_layers.end())
      updateProcessShape(*it);
  });

  con(proc,
      &IdentifiedObjectAbstract::identified_object_destroying,
      this,
      [=] { QObject::disconnect(con_id); });

  auto frontLayer = m_model.frontProcess();
  if (frontLayer && (*frontLayer == proc.id()))
  {
    on_layerModelPutToFront(proc);
  }
  else
  {
    on_layerModelPutToBack(proc);
  }

  updateProcessesShape();
}

void Presenter::updateBreakpoints()
{
  m_breakpoints.clear();
  for(auto& bp : m_model.breakpoints)
  {
    m_breakpoints.insert(bp.position());
  }
  m_view->update();
  //updateHeader();
}

void Presenter::updateProcessesShape()
{
  for (const auto& proc : m_layers)
  {
    updateProcessShape(proc);
  }
  m_view->update();
}

void Presenter::updateProcessShape(
    const Scenario::LayerData& data)
{
  {
    data.view->setPos(QPointF{0, Header::headerHeight() + 5.});
    data.presenter->setWidth(m_view->width());
    data.presenter->setHeight(m_view->height() - Header::headerHeight() - 5.);
    data.presenter->parentGeometryChanged();
    data.view->update();
  }
}

void Presenter::setHeaderWidth(
    double w)
{
  m_header->setWidth(w);

  if (m_headerDelegate)
  {
    m_headerDelegate->setSize(QSizeF{
        std::max(0., w - Header::handleWidth() - Header::menuWidth()),
        Header::headerHeight()});
    m_headerDelegate->setX(30);
  }
}
void Presenter::on_layerModelPutToFront(
    const Process::ProcessModel& proc)
{
  delete m_headerDelegate;
  m_headerDelegate = nullptr;
  {
    for (const auto& elt : m_layers)
    {
      if (elt.model->id() == proc.id())
      {
        auto factory = score::GUIAppContext().interfaces<Process::LayerFactoryList>().findDefaultFactory(elt.model->concreteKey());

        elt.presenter->putToFront();

        m_headerDelegate = factory->makeHeaderDelegate(*elt.presenter);
        m_headerDelegate->setParentItem(m_header);
        m_headerDelegate->setFlag(
            QGraphicsItem::GraphicsItemFlag::ItemClipsToShape);
        m_headerDelegate->setFlag(
            QGraphicsItem::GraphicsItemFlag::ItemClipsChildrenToShape);
        m_headerDelegate->setPos(30, 0);

        setHeaderWidth(m_view->width());
      }
      else
      {
        elt.presenter->putBehind();
      }
    }
  }
}

void Presenter::on_layerModelPutToBack(
    const Process::ProcessModel& proc)
{
  for (const auto& elt : m_layers)
  {
    if (elt.model->id() == proc.id())
    {
      elt.presenter->putBehind();
      return;
    }
  }
}

}
