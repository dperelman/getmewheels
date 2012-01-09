/*****************************************************************************
 * Copyright: 2010-2011 Christian Fetzer <fetzer.ch@googlemail.com>          *
 * Copyright: 2010-2011 Michael Zanetti <mzanetti@kde.org>                   *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation, either version 3 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License         *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
 *                                                                           *
 ****************************************************************************/

#include "gmwparkingspot.h"

GMWParkingSpot::GMWParkingSpot(const QString &name, const QString &address, const QGeoCoordinate &location, const QPixmap image,
        quint16 capacityUsed, quint16 capacityTotal) :
    GMWItem(name, address, location, image),
    m_capacityUsed(capacityUsed), m_capacityTotal(capacityTotal)
{
}

GMWItem::Type GMWParkingSpot::objectType() const
{
    return GMWItem::TypeParkingLot;
}

quint16 GMWParkingSpot::capacityUsed() const
{
    return m_capacityUsed;
}

quint16 GMWParkingSpot::capacityTotal() const
{
    return m_capacityTotal;
}

QDataStream &operator<<(QDataStream& stream, const GMWParkingSpot& parkingSpot)
{
    stream << dynamic_cast<const GMWItem&>(parkingSpot);
    stream << parkingSpot.m_capacityUsed << parkingSpot.m_capacityTotal;
    return stream;
}

QDataStream &operator>>(QDataStream& stream, GMWParkingSpot& parkingSpot)
{
    stream >> dynamic_cast<GMWItem&>(parkingSpot);
    stream >> parkingSpot.m_capacityUsed;
    stream >> parkingSpot.m_capacityTotal;
    return stream;
}
