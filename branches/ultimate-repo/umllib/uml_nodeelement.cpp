/** @file uml_nodeelement.cpp
 * 	@brief Класс, представляющий объект на диаграмме
 * */
#include <QtGui>

#include "uml_nodeelement.h"
#include "realreporoles.h"

using namespace UML;

NodeElement::NodeElement()
: portsVisible(false)
{
	setAcceptsHoverEvents(true);
	dragState = None;
}

NodeElement::~NodeElement()
{
	foreach (EdgeElement *edge, edgeList)
		edge->removeLink(this);
}

void NodeElement::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
	if ( isSelected() ) {
		if ( QRectF(m_contents.topLeft(),QSizeF(4,4)).contains(event->pos()) ) {
			dragState = TopLeft;
		} else if ( QRectF(m_contents.topRight(),QSizeF(-4,4)).contains(event->pos()) ) {
			dragState = TopRight;
		} else if ( QRectF(m_contents.bottomRight(),QSizeF(-12,-12)).contains(event->pos()) ) {
			dragState = BottomRight;
		} else if ( QRectF(m_contents.bottomLeft(),QSizeF(4,-4)).contains(event->pos()) ) {
			dragState = BottomLeft;
		} else
			Element::mousePressEvent(event);
	} else
		Element::mousePressEvent(event);
}

void NodeElement::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
	if ( dragState == None ) {
		Element::mouseMoveEvent(event);
	} else {
			QRectF newcontents = m_contents;

			switch ( dragState ) {
				case TopLeft:       newcontents.setTopLeft(event->pos());		break;
				case Top:           newcontents.setTop(event->pos().y());		break;
				case TopRight:      newcontents.setTopRight(event->pos());		break;
				case Left:          newcontents.setLeft(event->pos().x());		break;
				case Right:         newcontents.setRight(event->pos().x());		break;
				case BottomLeft:    newcontents.setBottomLeft(event->pos());	break;
				case Bottom:        newcontents.setBottom(event->pos().y());	break;
				case BottomRight:   newcontents.setBottomRight(event->pos());	break;
				case None:														break;
			}

			if ( ! ( ( newcontents.width() < 10 ) || ( newcontents.height() < 10 ) ) ) {
				prepareGeometryChange();

				m_contents = newcontents;

				setPos(pos() + m_contents.topLeft());
				m_contents.translate(-m_contents.topLeft());

				transform.reset();
				transform.scale(m_contents.width(), m_contents.height());

				foreach (EdgeElement *edge, edgeList)
					edge->adjustLink();
			}
	}
}

void NodeElement::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
	m_contents = m_contents.normalized();

	moving = 1;
	QAbstractItemModel *im = const_cast<QAbstractItemModel *>(dataIndex.model());
	im->setData(dataIndex, pos(), Unreal::PositionRole);
	im->setData(dataIndex, QPolygon(m_contents.toAlignedRect()), Unreal::ConfigurationRole);
	moving = 0;

	if ( dragState != None )
		dragState = None;
	else
		Element::mouseReleaseEvent(event);
}

QVariant NodeElement::itemChange(GraphicsItemChange change, const QVariant &value)
{
	switch ( change ) {
		case ItemPositionHasChanged:
			{
				foreach (EdgeElement *edge, edgeList)
					edge->adjustLink();
			}
       		return value;
		default:
			return QGraphicsItem::itemChange(change, value);
	}
}

QRectF NodeElement::contentsRect() const
{
	return m_contents;
}

QRectF NodeElement::boundingRect() const
{
	return m_contents.adjusted(-kvadratik,-kvadratik,kvadratik,kvadratik);
}

void NodeElement::updateData()
{
	Element::updateData();

	if (moving == 0) {
		setPos(dataIndex.data(Unreal::PositionRole).toPointF());
		QRectF newRect = dataIndex.data(Unreal::ConfigurationRole).value<QPolygon>().boundingRect();
		if ( ! newRect.isEmpty() )
			m_contents = newRect;

		transform.reset();
		transform.scale(m_contents.width(), m_contents.height());
	}
}

static int portId(qreal id)
{
	int iid = qRound(id);
	if ( id < ( 1.0 * iid ) )
		return iid - 1;
	else
		return iid;
}

const QPointF NodeElement::getPortPos(qreal id) const
{
	int iid = portId(id);

	if ( id < 0.0 )
		return QPointF(0,0);
	if ( id < pointPorts.size() )
		return transform.map(pointPorts[iid]);
	if ( id < pointPorts.size() + linePorts.size() )
		return transform.map(linePorts.at(iid - pointPorts.size()).pointAt(id - 1.0 * iid));
	else
		return QPointF(0,0);
}

qreal NodeElement::getPortId(const QPointF &location) const
{
	for( int i = 0; i < pointPorts.size(); i++ ) {
		if ( QRectF(transform.map(pointPorts[i])-QPointF(kvadratik,kvadratik),QSizeF(kvadratik*2,kvadratik*2)).contains( location ) )
			return 1.0 * i;
	}

	for( int i = 0; i < linePorts.size(); i++ ) {
		QPainterPathStroker ps;
		ps.setWidth(kvadratik);

		QPainterPath path;
		path.moveTo(transform.map(linePorts[i].p1()));
		path.lineTo(transform.map(linePorts[i].p2()));

		path = ps.createStroke(path);
		if ( path.contains(location) )
			return ( 1.0 * ( i + pointPorts.size() ) + qMin( 0.9999,
						QLineF( linePorts[i].p1(), transform.inverted().map(location) ).length()
						/ linePorts[i].length() ) );
	}

	if (pointPorts.size()!=0) {
		int numMinDistance = 0;
		qreal minDistance = QLineF( pointPorts[0], transform.inverted().map(location) ).length();
		for( int i = 0; i < pointPorts.size(); i++ ) {
			if (QLineF( pointPorts[i], transform.inverted().map(location) ).length()<minDistance) {
				numMinDistance = i;
				minDistance = QLineF( pointPorts[i], transform.inverted().map(location) ).length();
			}
		}
		return 1.0 * numMinDistance;
	} else if (linePorts.size()!=0) {
		int numMinDistance = 0;
		qreal minDistance = QLineF( linePorts[0].p1(), transform.inverted().map(location) ).length();
		for( int i = 0; i < linePorts.size(); i++ ) {
			if (QLineF( linePorts[i].p1(), transform.inverted().map(location) ).length()<minDistance) {
				numMinDistance = i;
				minDistance = QLineF( linePorts[i].p1(), transform.inverted().map(location) ).length();
			}
		}
		return 1.0 * (numMinDistance + pointPorts.size());
	}

    return -1.0;
}

void NodeElement::setPortsVisible(bool value) {
	prepareGeometryChange();
	portsVisible = value;
}

void NodeElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*)
{
	if ( option->levelOfDetail >= 0.5 ) {
		if ( option->state & QStyle::State_Selected ) {
			painter->save();
//painter->drawRect(m_contents);

			QBrush b;
			b.setColor(Qt::blue);
			b.setStyle(Qt::SolidPattern);
			painter->setBrush(b);
			painter->setPen(Qt::blue);

			painter->drawRect(QRectF(m_contents.topLeft(),QSizeF(4,4)));
			painter->drawRect(QRectF(m_contents.topRight(),QSizeF(-4,4)));
//			painter->drawRect(QRectF(m_contents.bottomRight(),QSizeF(-4,-4)));
			painter->drawRect(QRectF(m_contents.bottomLeft(),QSizeF(4,-4)));

			painter->translate(m_contents.bottomRight());
			painter->drawLine(QLineF(-4,0,0,-4));
			painter->drawLine(QLineF(-8,0,0,-8));
			painter->drawLine(QLineF(-12,0,0,-12));

			painter->restore();
		}

		if (( option->state & QStyle::State_MouseOver )||(portsVisible)) {
			foreach (QPointF port, pointPorts) {
				painter->save();
				painter->setOpacity(0.7);
				painter->translate(transform.map(port));
				painter->setBrush(Qt::gray);
				painter->setPen(Qt::NoPen);
				painter->drawRect(QRectF(-5,-5,10,10));
				painter->setPen(Qt::darkGray);
				painter->drawLine(QLineF(-5,-5,5,5));
				painter->drawLine(QLineF(-5,5,5,-5));
				painter->restore();
			}

			foreach (QLineF port, linePorts) {
				QPen pen;
				pen.setBrush(Qt::gray);
				pen.setWidth(kvadratik);
				painter->setOpacity(0.7);
				painter->setPen(pen);
				painter->drawLine(transform.map(port));

				pen.setBrush(Qt::darkGray);
				pen.setWidth(1);
				painter->setPen(pen);
				painter->drawLine(transform.map(port));

			}
		}
	}
}
