import QtQuick 2.15
import QtLocation 5.6
import QtPositioning 5.5
import QtQuick.Window 2.14

Window {
    width: Qt.platform.os == "android" ? Screen.width : 512
    height: Qt.platform.os == "android" ? Screen.height : 512
    visible: true
    Plugin {
        id: mapPlugin
        name: "osm"
        PluginParameter {
                   name: "osm.mapping.providersrepository.disabled"
                   value: "true"
               }
        PluginParameter {
                    name: "osm.mapping.providersrepository.address"
                    value: "http://maps-redirect.qt.io/osm/5.8/"
                }}
    MapQuickItem {
        id: marker
        anchorPoint.x: image.width/4
        anchorPoint.y: image.height
        coordinate: QtPositioning.coordinate(40.75253061253879, -74.17195258804027)
        sourceItem: Image {
            id: image
            source: "marker.png"
            width: 15
            height: 15
            transform: Rotation{
                id: rotaion_yaw
                angle: 30}
        }
    }

    Map {
        id: position_marker
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(40.75253061253879, -74.17195258804027)
        zoomLevel: 30
        Component.onCompleted: position_marker.addMapItem(marker)

    }
    Connections{
        target: Mainwindow
        onGps_change: {
            position_marker.center = QtPositioning.coordinate(lat/10000000,lon/10000000)
            marker.coordinate = QtPositioning.coordinate(lat/10000000,lon/10000000)
            rotaion_yaw.angle = yaw
        }
    }
}

