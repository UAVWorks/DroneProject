import QtQuick 2.5
import Components 1.0
import "../.."
import "../../widgets"

Item {
    anchors.margins: Theme.standardMargin
    property variant targetDrone
    ListView {
        id: alertView
        model: targetDrone.alertModel
        anchors.fill: parent
        spacing: 3
        clip: true
        delegate: Item {
            width: alertView.width
            height: Theme.alertDeleagateHeight
            Rectangle {
                anchors.left: parent.left
                anchors.leftMargin: Theme.standardMargin
                anchors.right: parent.right
                anchors.rightMargin: Theme.standardMargin
                height: parent.height
                color: "transparent"
                border.color: (level === SpyC.NOMINAL) ? Theme.nominalColor : (level === SpyC.WARNING ? Theme.warningColor : Theme.criticalColor)
                border.width: 3
                StandardText {
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.standardMargin
                    anchors.verticalCenter: parent.verticalCenter
                    text: what
                }
                StandardText {
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.standardMargin
                    anchors.verticalCenter: parent.verticalCenter
                    text: date
                }
            }
        }
    }
}
