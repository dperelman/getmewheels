/*****************************************************************************
 * Copyright: 2010-2011 Christian Fetzer <fetzer.ch@googlemail.com>          *
 * Copyright: 2010-2012 Michael Zanetti <michael_zanetti@gmx.net>            *
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
#include "data/gmwgasstation.h"
#include "data/gmwparkingspot.h"

#include <QtCore/QList>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>

#if defined Q_WS_S60 || QT_VERSION >= 0x050000
#include "../3rdParty/kqoauth/src/kqoauthmanager.h"
#include "../3rdParty/kqoauth/src/kqoauthrequest.h"
#else
#include <QtOAuth>
#endif

class Location;

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
    void removeAuthentication();
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

#if defined Q_WS_S60 || QT_VERSION >= 0x050000
    KQOAuthManager *m_oauthManager;
    KQOAuthRequest *m_oauthRequest;
    QString m_screenName;
    QString m_token;
    QString m_tokenSecret;
    QString m_temporaryToken;
    QString m_temporaryTokenSecret;
#else
    QOAuth::Interface *m_qoauth;
    QByteArray m_screenName;
    QByteArray m_token;
    QByteArray m_tokenSecret;
#endif
    GMWAccount m_account;

    static const QByteArray Car2GoRequestTokenURL;
    static const QByteArray Car2GoAccessTokenURL;
    static const QByteArray Car2GoAuthorizeURL;

    static const QByteArray ConsumerKey;
    static const QByteArray ConsumerSecret;

    static const QByteArray ParamCallback;
    static const QByteArray ParamCallbackValue;
    static const QByteArray ParamVerifier;
    static const QByteArray ParamScreenName;

    QEventLoop m_loop;
    bool waitForResponse();
    bool m_timeout;
    QByteArray m_lastData;

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

#if defined Q_WS_S60 || QT_VERSION >= 0x050000
    void receivedToken(const QString &token, const QString &tokenSecret);
    void temporaryTokenReceived(const QString & token, const QString & tokenSecret);
    void authorizationReceived(const QString & token, const QString & verifier);
    void accessTokenReceived(const QString & token, const QString & tokenSecret);
    void requestReady(const QByteArray &response);
    void authorizedRequestDone();
#endif

private:
    QVariantMap parseJson(const QByteArray &data);
};

#endif // CAR2GOENGINE_H
