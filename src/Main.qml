import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 640
    height: 480
visible:
    true
title:
    qsTr("Hello World")


    GridLayout {
    id:
        grid
        columns: 3
        objectName: "grid"
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
                // ensure content uses full area
                padding: 0
                objectName: index
                onClicked: grid.buttonClicked(objectName)
            }
        }

        // Button {
        //     text: ""
        //     objectName: "0"
        //     onClicked: grid.buttonClicked(objectName)
        // }
        // Button {
        //     text: ""
        //     objectName: "1"
        //     onClicked: grid.buttonClicked(objectName)
        // }
        // Button {
        //     text: ""
        //     objectName: "2"
        //     onClicked: grid.buttonClicked(objectName)
        // }
        // Button {
        //     text: ""
        //     objectName: "3"
        //     onClicked: grid.buttonClicked(objectName)
        // }
        // Button {
        //     text: ""
        //     objectName: "4"
        //     onClicked: grid.buttonClicked(objectName)
        // }
        // Button {
        //     text: ""
        //     objectName: "5"
        //     onClicked: grid.buttonClicked(objectName)
        // }
        // Button {
        //     text: ""
        //     objectName: "6"
        //     onClicked: grid.buttonClicked(objectName)
        // }
        // Button {
        //     text: ""
        //     objectName: "7"
        //     onClicked: grid.buttonClicked(objectName)
        // }
        // Button {
        //     text: ""
        //     objectName: "8"
        //     onClicked: grid.buttonClicked(objectName)
        // }
    }
}
