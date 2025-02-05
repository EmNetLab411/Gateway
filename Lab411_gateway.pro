QT       += core gui mqtt
QT += quick
QT += location
QT += quickwidgets


QT += qml network quick positioning location
#CONFIG += qmltypes
#QML_IMPORT_NAME = position.marker
#QML_IMPORT_MAJOR_VERSION = 1
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    communication/protocols/messages/uavlink_msg_command_t.cpp \
    communication/protocols/messages/uavlink_msg_control_robot_t.cpp \
    communication/protocols/messages/uavlink_msg_global_position_t.cpp \
    communication/protocols/messages/uavlink_msg_local_position_t.cpp \
    communication/protocols/messages/uavlink_msg_manual_control_t.cpp \
    communication/protocols/messages/uavlink_msg_sensor_t.cpp \
    communication/protocols/messages/uavlink_msg_setwp_t.cpp \
    communication/protocols/messages/uavlink_msg_state_t.cpp \
    communication/protocols/uavlink_message_t.cpp \
    console.cpp \
    main.cpp \
    mainwindow.cpp \
    mqttclient.cpp \
    mqttsubscription.cpp \
    restclient.cpp \
    settingsfile.cpp\
    udpclient.cpp
#    position.marker
HEADERS += \
    communication/protocols/messages/messageID.h \
    communication/protocols/messages/uavlink_msg_command_t.h \
    communication/protocols/messages/uavlink_msg_control_robot_t.h \
    communication/protocols/messages/uavlink_msg_global_position_t.h \
    communication/protocols/messages/uavlink_msg_local_position_t.h \
    communication/protocols/messages/uavlink_msg_manual_control_t.h \
    communication/protocols/messages/uavlink_msg_sensor_t.h \
    communication/protocols/messages/uavlink_msg_setwp_t.h \
    communication/protocols/messages/uavlink_msg_state_t.h \
    communication/protocols/uavlink_message_t.h \
    console.h \
    mainwindow.h \
    messageID.h \
    mqttclient.h \
    mqttsubscription.h \
    restclient.h \
    settingsfile.h \
    udpclient.h

FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(3rdParty/qextserialport/src/qextserialport.pri)
LIBS       += -lVLCQtCore -lVLCQtWidgets
RESOURCES += \
    Digital_maps.qrc

DISTFILES += \
    rest_api_tb.py
