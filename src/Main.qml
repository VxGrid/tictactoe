import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    color: "green"

    Column {
        spacing: 10

        Text {
                text: "Choose difficulty:"
                font.pixelSize: 16
                color: "white"
            }

        ButtonGroup {
            id: radioGroup
            objectName: "radioGroup"
            signal selectionChanged(string text)

            onCheckedButtonChanged: {
                    if (checkedButton)
                        selectionChanged(checkedButton.text)
            }
        }

        RadioButton {
            text: "Beginner"
            checked: true
            ButtonGroup.group: radioGroup
        }

        RadioButton {
            text: "Medium"
            ButtonGroup.group: radioGroup
        }

        RadioButton {
            text: "Expert"
            ButtonGroup.group: radioGroup
        }
    }

    Text {
            id: infoText
            objectName: "infoText"
            text: ""
            font.pixelSize: 16
            color: "white"
            anchors.bottom: grid.top
            anchors.horizontalCenter: grid.horizontalCenter
            anchors.bottomMargin: 20
        }

    GridLayout {
        id: grid
        columns: 3
        objectName: "grid"
        anchors.centerIn: parent
        signal buttonClicked(string name)

        Repeater {
            id : reaper
            objectName: "reaper"
            model: 9
            Button {
                property int index: model.index
                text: ""

                width: 40
                height: 40
                Layout.preferredWidth: 40
                Layout.preferredHeight: 40
                // ensure content uses full area
                padding: 0
                objectName: index
                onClicked: grid.buttonClicked(objectName)

                background: Rectangle {
                            color: "blue"
                            radius: 6
                        }
                contentItem: Text {
                        text: parent.text
                        color: "white"

                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight   // optional: "..." if text is too long
                        font.pixelSize: 30
                    }
            }
        }
    } // GridLayout

    Button {
            id: resetButton
            text: "Reset"
            anchors.top: grid.bottom
            anchors.horizontalCenter: grid.horizontalCenter
            anchors.topMargin: 20
            objectName: "resetButton"
            onClicked: grid.buttonClicked(objectName)
        }
}
