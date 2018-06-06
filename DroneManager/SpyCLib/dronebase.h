#ifndef DRONEBASE_H
#define DRONEBASE_H

// Qt
#include <QObject>
#include <QTimer>
#include <QGeoCoordinate>
#include <QGeoPath>
#include <QVector>

// Application
#include "spyclib_global.h"
#include <waypoint.h>
#include <spycore.h>
#include "cxmlnode.h"

namespace Core {
class SPYCLIBSHARED_EXPORT DroneBase : public QObject
{
    Q_OBJECT

    // UID & video URL
    Q_PROPERTY(QString uid READ uid NOTIFY uidChanged)
    Q_PROPERTY(QString videoUrl READ videoUrl NOTIFY videoUrlChanged)

    // Initial position, current position and heading
    Q_PROPERTY(QGeoCoordinate position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(double heading READ heading WRITE setHeading NOTIFY headingChanged)

    // State, edit mode, work mode and global status
    Q_PROPERTY(int flightStatus READ flightStatus WRITE setFlightStatus NOTIFY flightStatusChanged)

    // Battery and return levels
    Q_PROPERTY(int batteryLevel READ batteryLevel WRITE setBatteryLevel NOTIFY batteryLevelChanged)
    Q_PROPERTY(int returnLevel READ returnLevel NOTIFY batteryLevelChanged)

public:
    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Default constructor
    DroneBase(QObject *pParent=nullptr);

    //! Constructor
    DroneBase(const QString &sDroneUID, QObject *pParent=nullptr);

    //! Constructor
    DroneBase(const QString &sDroneUID, const QString &sVideoUrl, const QGeoCoordinate &initialPos, QObject *pParent=nullptr);

    //! Destructor
    virtual ~DroneBase();

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return current status
    QString globalStatus();

    //! Return uid
    const QString &uid() const;

    //! Return fly status
    int flightStatus() const;

    //! Set flight status
    void setFlightStatus(int iFlightStatus);

    //! Return position
    const QGeoCoordinate &position() const;

    //! Set position
    void setPosition(const QGeoCoordinate &position);

    //! Return heading
    double heading() const;

    //! Set heading
    void setHeading(double dHeading);

    //! Return battery level
    int batteryLevel() const;

    //! Set battery level
    void setBatteryLevel(int iBatteryLevel);

    //! Return return level
    int returnLevel() const;

    //! Set return level
    void setReturnLevel(int iReturnLevel);

    //! Return safety plan
    const QGeoPath &safetyPlan() const;

    //! Set safety plan
    virtual void setSafetyPlan(const QGeoPath &safetyPlan);

    //! Return mission plan
    const WayPointList &missionPlan() const;

    //! Set mission plan
    virtual void setMissionPlan(const WayPointList &missionPlan);

    //! Return landing plan
    const WayPointList &landingPlan() const;

    //! Set landing plan
    virtual void setLandingPlan(const WayPointList &landingPlan);

    //! Return video url
    const QString &videoUrl() const;

    //! Set video url
    void setVideoUrl(const QString &sVideoUrl);

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Clear safety
    virtual void clearSafetyPlan();

    //! Clear mission plan
    virtual void clearMissionPlan();

    //! Clear landing plan
    virtual void clearLandingPlan();

    //-------------------------------------------------------------------------------------------------
    // Serialization
    //-------------------------------------------------------------------------------------------------

    //! Serialize drone status
    QString serializeGlobalStatus();

    //! Deserialize drone status
    void deserializeGlobalStatus(const QString &sGlobalStatus);

    //! Serialize position
    QString serializePosition();

    //! Deserialize position
    void deserializePosition(const QString &sPosition);

    //! Serialize battery level
    QString serializeBatteryLevel();

    //! Deserialise battery level
    void deserializeBatteryLevel(const QString &sBatteryLevel);

    //! Serialize return level
    QString serializeReturnLevel();

    //! Deserialise return level
    void deserializeReturnLevel(const QString &sBatteryLevel);

    //! Serialize safety plan
    QString serializeSafetyPlan();

    //! Deserialize safety plan
    void deserializeSafetyPlan(const QString &sSafetyPlan);

    //! Serialize mission plan
    QString serializeMissionPlan();

    //! Deserialize mission plan
    void deserializeMissionPlan(const QString &sMissionPlan);

    //! Serialize landing plan
    QString serializeLandingPlan();

    //! Deserialize landing plan
    void deserializeLandingPlan(const QString &sLandingPlan);

private:
    //! Serialize plan
    QString serializePlan(const QVector<Core::WayPoint> &plan, const QString &sPlanType, const QString &sDroneUID);

    //! Serialize plan
    QString serializePlan(const QGeoPath &plan, const QString &sPlanType, const QString &sDroneUID);

    //! Deserialize plan
    void deserializePlan(const CXMLNode &node, WayPointList &vWayPointList, QString &sDroneUID);

    //! Deserialize plan
    void deserializePlan(const CXMLNode &node, QGeoPath &geoPath, QString &sDroneUID);

private:
    //! UID
    QString m_sDroneUID = "";

    //! Status
    SpyCore::FlightStatus m_eFlightStatus = SpyCore::IDLE;

    //! Video url
    QString m_sVideoUrl = "";

    //! Safety
    QGeoPath m_safetyPlan;

    //! Mission plan
    WayPointList m_missionPlan;

    //! Landing plan
    WayPointList m_landingPlan;

    //! Exclusion area
    QList<QGeoPath> m_lExclusionArea;

    //! Current position
    QGeoCoordinate m_position;

    //! Heading
    double m_dHeading = 0;

    //! Battery level
    int m_iBatteryLevel = 0;

    //! Return level
    int m_iReturnLevel = 0;

signals:
    //! UID changed
    void uidChanged();

    //! Video url changed
    void videoUrlChanged();

    //! Flight status changed
    void flightStatusChanged();

    //! Position changed
    void positionChanged();

    //! Heading changed
    void headingChanged();

    //! Battery level changed
    void batteryLevelChanged();

    //! Return level changed
    void returnLevelChanged();

    //! Safety plan changed
    void safetyPlanChanged();

    //! Mission plan changed
    void missionPlanChanged();

    //! Landing plan changed
    void landingPlanChanged();

    //! New message
    void droneError(const SpyCore::DroneError &eDroneError, const QString &sDroneUID);
};
}

#endif // DRONEBASE_H
