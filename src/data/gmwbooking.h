/*****************************************************************************
 * Copyright: 2012 Michael Zanetti <michael_zanetti@gmx.net>                 *
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

#ifndef GMWBOOKING_H
#define GMWBOOKING_H

#include "gmwaccount.h"

#include <QDateTime>

class GMWBooking: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ toString NOTIFY changed)
    Q_PROPERTY(bool valid READ isValid NOTIFY changed)
    Q_PROPERTY(bool expired READ isExpired NOTIFY changed)
    Q_PROPERTY(int timeLeft READ timeLeft NOTIFY changed)
public:
    GMWBooking(QObject *parent = 0);
    GMWBooking(int id = -1, GMWAccount account = GMWAccount(), QObject *parent = 0);

    bool isValid() const;
    void invalidate();

    void setId(int id);
    int id() const;

    void setAccount(const GMWAccount &account);
    GMWAccount account() const;

    void setTime(const QDateTime &time);
    QDateTime time() const;
    void setExpirationTime(const QDateTime &time);
    QDateTime expirationTime() const;

    QString toString() const;
    bool isExpired() const;
    int timeLeft() const;

protected:
    void timerEvent(QTimerEvent *);

signals:
    void changed();

private:
    int m_id;
    GMWAccount m_account;
    QDateTime m_time;
    QDateTime m_expriationTime;
    int m_timerId;
};

#endif // GMWBOOKING_H
