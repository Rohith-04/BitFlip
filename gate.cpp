#include "gate.h"

Gate::Gate() {}

QRectF Gate::boundingRect() const{
    return(0 , 0 , m_pixmap.width(), m_pixmap.height);
}
