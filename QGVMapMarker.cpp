#include "QGVMapMarker.h"

QGVMapMarker::QGVMapMarker()
{

}

QGVMapMarker::~QGVMapMarker()
{

}

bool QGVMapMarker::operator ==(const QGVMapMarker & m) const
{
    return(m.m_id == this->m_id);
}
