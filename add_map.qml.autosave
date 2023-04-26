import QtQuick 2.15
import QtLocation 5.6
import QtPositioning 5.5
import QtQuick.Window 2.14
import position.marker 1.0

Window {
    width: Qt.platform.os == "android" ? Screen.width : 512
    height: Qt.platform.os == "android" ? Screen.height : 512
    visible: true
    Plugin {
        id: mapPlugin
        name: "osm" // "mapboxgl", "esri", ...
        //property variant uavlink_msg_global_position_t

    }
    function addMarker(latitude, longitude)
        {
            var Component = Qt.createComponent("qrc:/marker.qml")
            var item = Component.createObject(window, {
                                                  coordinate: QtPositioning.coordinate(latitude, longitude)
                                              })
            map.addMapItem(item)
        }
    Map {
        Uavlink_msg_global_position_t{
            id: position_marker}
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(/*position_marker.lat, position_marker.lon*/20.960965, 105.950315)
        zoomLevel: 14
        Component.onCompleted:addMarker(position_marker.lat, position_marker.lon)
//        MapItemView {
//            model: markerModel
//            delegate: MapQuickItem {
//                anchorPoint.x: image.width/2
//                anchorPoint.y: image.height
//                coordinate: QtPositioning.coordinate(20.960965, 105.950315/*position_marker.lat, position_marker.lon*/)
//                sourceItem: Column {
//                    Image {
//                        id: image
//                        source: "qrc:/marker.png"
//                    }
//                    Text {
//                        text: "MSG_Position"
//                        color: "white"
//                        font.pixelSize: 12
//                    }
//                }
//            }
//        }
//        ListModel {
//            id: markerModel
//            ListElement {
//                latitude: 21.007406553751757
//                longitude: 105.84280452935386
//                label: "HN"
//            }
//        }
    }
}


