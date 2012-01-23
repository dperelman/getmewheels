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

#ifndef CAR2GOENGINE_H
#define CAR2GOENGINE_H

#include "engines/gmwengine.h"
#include "engines/location.h"
#include "data/gmwgasstation.h"
#include "data/gmwparkingspot.h"

#include <QtCore/QList>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>

#include <QtOAuth/QtOAuth>

class Car2goEngine : public EnginePlugin
{
    Q_OBJECT

public:
    // See http://code.google.com/p/car2go/wiki/OpenAPIv20r10Locations
    Car2goEngine();

    QList<Location*> fetchLocations();

    void fetchGasStations(Location *location);
    void fetchParkingSpots(Location *location);
    void fetchVehicles(Location *location);

    bool startAuthentication();
    bool setAccessCode(const QString &code);
    bool authenticated();
    QDateTime authExpirationDate();
    QList<GMWAccount> accounts(Location *location);
    GMWAccount account();
    void setAccount(const GMWAccount &account);

    bool createBooking(Location *location, GMWVehicle *vehicle, const GMWAccount &account);
    bool cancelBooking(GMWVehicle *vehicle);
    QList<GMWVehicle*> bookings(Location *location);

    QString error() {return m_error;}

private:
    enum NetworkReplyType {IconReply, GasStationReply, VehiclesReply, ParkingSpotsReply};

    QNetworkAccessManager m_network;

    QNetworkReply* m_networkReplyParkingSpots;
    QNetworkReply* m_networkReplyGasStations;
    QNetworkReply* m_networkReplyVehicles;

    QString m_xmlParkingSpots;
    QString m_xmlGasStations;
    QString m_xmlVehicles;

    QPixmap m_imageParkingSpots;
    QPixmap m_imageParkingSpotsCP;
    QPixmap m_imageGasStations;
    QPixmap m_imageVehicles;
    QPixmap m_imageVehiclesED;
    QPixmap m_imageParkingSpotsL;
    QPixmap m_imageParkingSpotsCPL;
    QPixmap m_imageGasStationsL;
    QPixmap m_imageVehiclesL;
    QPixmap m_imageVehiclesEDL;

    QTime m_stats;

    GMWBusinessArea m_businessArea;

    QOAuth::Interface *m_qoauth;
    static const QByteArray Car2GoRequestTokenURL;
    static const QByteArray Car2GoAccessTokenURL;
    static const QByteArray Car2GoAuthorizeURL;

    static const QByteArray ConsumerKey;
    static const QByteArray ConsumerSecret;

    static const QByteArray ParamCallback;
    static const QByteArray ParamCallbackValue;
    static const QByteArray ParamVerifier;
    static const QByteArray ParamScreenName;

    QByteArray m_screenName;
    QByteArray m_token;
    QByteArray m_tokenSecret;
    GMWAccount m_account;

    QEventLoop m_loop;
    bool waitForResponse();
    bool m_timeout;

    Location *m_currentDownloadLocation;

    void parseVehicles(const QVariantMap &vehiclesMap);
    GMWVehicle *parseVehicle(const QVariantMap &vehicleMap);
    GMWVehicle *parseBookedVehicle(const QVariantMap &vehicleMap);

    void parseGasStations(const QVariantMap &gasStationsMap);
    GMWGasStation *parseGasStation(const QVariantMap &gasStationMap);

    void parseParkingSpots(const QVariantMap &parkingSpotsMap);
    GMWParkingSpot *parseParkingSpot(const QVariantMap &parkingSpotMap);

    QString m_error;

private slots:
    void receivedData(QNetworkReply *reply);
    void loadBusinessArea();
};

#endif // CAR2GOENGINE_H
