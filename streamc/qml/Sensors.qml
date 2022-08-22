
import QtQuick 2.14

Rectangle{
    id: rectangle
    width: 1024
    height: 768
    color: "#000000"
    border.color: "#ffffff"

    Rectangle {
        id: base
        x: 416
        y: 186
        width: 332
        height: 408
        color: "#8c8686"
    }

    Rectangle {
        id: motor_left
        x: 370
        y: 239
        width: 40
        height: 111
        color: "#393636"
        radius: 10
    }

    Sensor {
        id: front_right
        x: 680
        y: 169
        width: 137
        height: 36

        visible: true
        rotation: 45
    }

    Sensor {
        id: front_left
        x: 347
        y: 169
        width: 137
        height: 36
        visible: true
        rotation: 315
    }

    Sensor {
        id: front_center
        x: 514
        y: 126
        width: 137
        height: 36
        visible: true
        rotation: 0
    }

    Rectangle {
        id: motor_right
        x: 754
        y: 239
        width: 40
        height: 111
        color: "#393636"
        radius: 10
    }

    Sensor {
        id: rear_right
        x: 688
        y: 583
        width: 137
        height: 36
        visible: true
        rotation: 130.303
    }

    Sensor {
        id: rear_center
        x: 514
        y: 624
        width: 137
        height: 36
        visible: true
        rotation: 180
    }

    Sensor {
        id: rear_left
        x: 346
        y: 581
        width: 137
        height: 36
        visible: true
        rotation: -134.193
    }

}
