import QtQuick 2.5
import Components 1.0
import "../../widgets"
import "../.."

Item {
    id: root
    property variant targetDrone

    // Return true if drone is valid
    function droneValid()
    {
        return (typeof targetDrone !== "undefined") && (targetDrone !== null)
    }

    Item {
        id: topContainer
        width: parent.width
        height: parent.height

        Grid {
            columns: 3
            anchors.fill: parent
            clip: true

            // Circle
            Item {
                width: parent.width/3
                height: width
                ImageButton {
                    id: circleExclusion
                    source: "qrc:/icons/ico-circle.svg"
                    label: qsTr("Circle")
                    textPosition: "below"
                    textColor: Theme.defaultFontColor
                    onClicked: {
                        onClicked: targetDrone.workMode = SpyC.EXCLUSION_EDIT
                        targetDrone.currentExclusionShape = SpyC.CIRCLE
                    }
                    checkable: true
                    checked: root.droneValid() ? ((targetDrone.workMode === SpyC.EXCLUSION_EDIT) && (targetDrone.currentExclusionShape === SpyC.CIRCLE)) : false
                    anchors.centerIn: parent
                }
            }

            // Rectangle
            Item {
                width: parent.width/3
                height: width
                ImageButton {
                    id: rectExclusion
                    source: "qrc:/icons/ico-rectangle.svg"
                    label: qsTr("Rectangle")
                    textPosition: "below"
                    textColor: Theme.defaultFontColor
                    onClicked: {
                        onClicked: targetDrone.workMode = SpyC.EXCLUSION_EDIT
                        targetDrone.currentExclusionShape = SpyC.RECTANGLE
                    }
                    checkable: true
                    checked: root.droneValid() ? ((targetDrone.workMode === SpyC.EXCLUSION_EDIT) && (targetDrone.currentExclusionShape === SpyC.RECTANGLE)) : false
                    anchors.centerIn: parent
                }
            }

            // Triangle
            Item {
                width: parent.width/3
                height: width
                ImageButton {
                    id: triangleExclusion
                    source: "qrc:/icons/ico-triangle.svg"
                    label: qsTr("Triangle")
                    textPosition: "below"
                    textColor: Theme.defaultFontColor
                    onClicked: {
                        onClicked: targetDrone.workMode = SpyC.EXCLUSION_EDIT
                        targetDrone.currentExclusionShape = SpyC.TRIANGLE
                    }
                    checkable: true
                    checked: root.droneValid() ? ((targetDrone.workMode === SpyC.EXCLUSION_EDIT) && (targetDrone.currentExclusionShape === SpyC.TRIANGLE)) : false
                    anchors.centerIn: parent
                }
            }
        }
    }
}


