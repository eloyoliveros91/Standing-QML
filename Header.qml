import QtQuick 2.0
Row{
    spacing: 5
    property int ancho: nombre.width+vistaProblemas.width+posicion.width+10
                        +aceptados.width+10+tiempo.width+10

    property var nombres: ['A', 'B', 'C','D','E','F','G','H','I','J','K','L','M','N','O'];
    Rectangle{
        id: posicion
        color: "blue"
        radius: 5
        border.color: "gray"
        height: 25
        width: 30

        Text{
            text: "Pos"
            font.bold: true
            font.pointSize: 10
            horizontalAlignment: Text.AlignHCenter
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }

    }

    Rectangle{
        id: nombre
        color: "red"
        height: 25
        width: 150
        radius: 5
        border.color: "gray"
        Text{
            text: "Equipo"
            font.bold: true
            font.pointSize: 10
            horizontalAlignment: Text.AlignHCenter
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    ListView{
        id: vistaProblemas
        orientation: ListView.Horizontal
        clip: true
        height: 25
        width: cantProblemas*55
        spacing: 5
        model: cantProblemas
        delegate: cuadroProblema
    }

    Component{
        id: cuadroProblema

        Rectangle{
            id: cuadro
            color: "red"
            border.color: "black"
            border.width: 1
            height: 25
            width: 50
            radius: 5
            Text{
                text: nombres[index]
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Rectangle{
        id: aceptados
        color: "green"
        border.color: "black"
        border.width: 1
        height: 25
        width: 50
        radius: 5
        Text{
            text: "Acc"
            horizontalAlignment: Text.AlignHCenter
            color: "white"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    Rectangle{
        id: tiempo
        color: "green"
        border.color: "black"
        border.width: 1
        height: 25
        width: 50
        radius: 5
        Text{
            text: "Tiempo"
            horizontalAlignment: Text.AlignHCenter
            color: "white"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }



}

