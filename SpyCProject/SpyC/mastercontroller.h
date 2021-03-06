#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

// Qt
#include <QObject>
#include <QGeoPath>
#include <QThread>
#include <QTimer>

// Application
#include "iservice.h"
#include "drone.h"
#include <alert.h>
#include "comstation.h"
class DroneModel;
class SettingController;

class MasterController : public QObject, public IService
{
    Q_OBJECT
    Q_PROPERTY(DroneModel *droneModel READ droneModel NOTIFY droneModelChanged)
    Q_PROPERTY(SettingController *settingController READ settingController NOTIFY settingControllerChanged)
    Q_PROPERTY(Drone *currentDrone READ currentDrone WRITE setCurrentDrone NOTIFY currentDroneChanged)
    Q_PROPERTY(QString applicationTitle READ applicationTitle WRITE setApplicationTitle NOTIFY applicationTitleChanged)

public:
    friend class SpyC;
    friend class SettingController;

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor
    MasterController(QObject *pParent=nullptr);

    //! Destructor
    virtual ~MasterController();

    //-------------------------------------------------------------------------------------------------
    // IService interface
    //-------------------------------------------------------------------------------------------------

    //! Startup
    virtual bool startup(const QStringList &lArgs=QStringList());

    //! Shutdown
    virtual void shutdown();

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Send message
    void sendMessage(const QString &sMessage);

    //! Detect drones
    Q_INVOKABLE void startComStation();

    //! Validate a safety plan request
    Q_INVOKABLE void validateSafetyPlanRequest(const QString &sDroneUID);

    //! Validate a mission plan request
    Q_INVOKABLE void validateMissionPlanRequest(const QString &sDroneUID);

    //! Validate a landing plan request
    Q_INVOKABLE void validateLandingPlanRequest(const QString &sDroneUID);

    //! Validate an exclusion area request
    Q_INVOKABLE void validateExclusionAreaRequest(const QString &sDroneUID);

    //! Arm
    Q_INVOKABLE void arm(const QString &sDroneUID);

    //! Take off
    Q_INVOKABLE void takeOff(const QString &sDroneUID);

    //! Go home
    Q_INVOKABLE void goHome(const QString &sDroneUID);

    //! Fail safe
    Q_INVOKABLE void failSafe(const QString &sDroneUID);

    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Set current drone
    void setCurrentDrone(Drone *pCurrentDrone);

    //! Return current drone
    Drone *currentDrone() const;

    //! Set application title
    void setApplicationTitle(const QString &sApplicationTitle);

    //! Return application title
    const QString &applicationTitle() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Upload safety plan
    void uploadSafetyPlan(const QString &sDroneUID);

    //! Upload mission plan
    void uploadMissionPlan(const QString &sDroneUID);

    //! Upload landing plan
    void uploadLandingPlan(const QString &sDroneUID);

    //! Uplaod exclusion area
    void uploadExclusionArea(const QString &sDroneUID);

    //! Load safety plan
    Q_INVOKABLE bool loadSafetyPlan(const QString &sFilePath);

    //! Save safety plan
    Q_INVOKABLE bool saveSafetyPlan(const QString &sFilePath, const QString &sDroneUID);

    //! Load mission plan
    Q_INVOKABLE bool loadMissionPlan(const QString &sFilePath);

    //! Save mission plan
    Q_INVOKABLE bool saveMissionPlan(const QString &sFilePath, const QString &sDroneUID);

    //! Load landing plan
    Q_INVOKABLE bool loadLandingPlan(const QString &sFilePath);

    //! Save landing plan
    Q_INVOKABLE bool saveLandingPlan(const QString &sFilePath, const QString &sDroneUID);

    //! Load exclusion area
    Q_INVOKABLE bool loadExclusionArea(const QString &sFilePath);

    //! Save exclusion area
    Q_INVOKABLE bool saveExclusionArea(const QString &sFilePath, const QString &sDroneUID);

private:
    //-------------------------------------------------------------------------------------------------
    // Getters & setters
    //-------------------------------------------------------------------------------------------------

    //! Return drone model view
    DroneModel *droneModel() const;

    //! Return setting controller
    SettingController *settingController() const;

    //! Return drone by UID
    Drone *getDrone(const QString &sDroneUID) const;

private:
    //! Application title
    QString m_sApplicationTitle = "";

    //! Com station
    ComStation *m_pComStation = nullptr;
    QThread m_comStationThread;

    //! Drone view model
    DroneModel *m_pDroneModel = nullptr;

    //! Drone list
    QVector<Drone *> m_vDrones;

    //! Current drone
    Drone *m_pCurrentDrone = nullptr;

    //! Setting controller
    SettingController *m_pSettingController = nullptr;

public slots:
    //! Incoming message
    void onIncomingMessage(const QString &sMessage);

    //! Drone global status changed
    void onDroneGlobalStatusChanged();

    //! Arm request
    void onArmRequest(const QString &sDroneUID);

    //! Take off request
    void onTakeOffRequest(const QString &sDroneUID);

    //! Go home request
    void onGoHomeRequest(const QString &sDroneUID);

    //! Fail safe request
    void onFailSafeRequest(const QString &sDroneUID);

    //! Validate safety plan
    void onValidateSafetyPlan(const QString &sDroneUID);

    //! Validate mission plan
    void onValidateMissionPlan(const QString &sDroneUID);

    //! Validate landing plan
    void onValidateLandingPlan(const QString &sDroneUID);

    //! Validate exclusion area
    void onValidateExclusionArea(const QString &sDroneUID);

signals:
    //! Current drone changed
    void currentDroneChanged();

    //! Drone model view changed
    void droneModelChanged();

    //! Setting controller changed
    void settingControllerChanged();

    //! Application title changed
    void applicationTitleChanged();

    //! Out going message
    void outGoingMessage(const QString &sMessage);

    //! Validate safety request
    void validateSafetyPlanReq(const QString &sDroneUID);

    //! Validate mission plan request
    void validateMissionPlanReq(const QString &sDroneUID);

    //! Validate landing plan request
    void validateLandingPlanReq(const QString &sDroneUID);

    //! Validate exclusion area request
    void validateExclusionAreaReq(const QString &sDroneUID);

    //! Send arm request
    void armRequest(const QString &sDroneUID);

    //! Send a take off request
    void takeOffRequest(const QString &sDroneUID);

    //! Go home request
    void goHomeRequest(const QString &sDroneUID);

    //! Send a failsafe request
    void failSafeRequest(const QString &sDroneUID);

    //! Mission plan error
    void missionPlanError(int iErrorId, const QString &sDroneUID);
};

#endif // MASTERCONTROLLER_H
