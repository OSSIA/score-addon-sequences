#include "Inspector.hpp"

#include <score/document/DocumentContext.hpp>

#include <QFormLayout>
#include <QLabel>
#include <QPushButton>

namespace sequence
{
InspectorWidget::InspectorWidget(
    const sequence::Model& object, const score::DocumentContext& context,
    QWidget* parent)
    : InspectorWidgetDelegate_T{object, parent}
    , m_dispatcher{context.commandStack}
{
  auto lay = new QFormLayout{this};
  lay->addWidget(new QLabel("change me"));
}

InspectorWidget::~InspectorWidget()
{
}
}
