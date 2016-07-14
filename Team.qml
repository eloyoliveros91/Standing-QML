import QtQuick 2.0
Row{
    spacing: 5    
    property int ancho: nombre.width+vistaProblemas.width+posicion.width+10
                        +aceptados.width+10+tiempo.width

    Rectangle{
        id: posicion
        color: "blue"
        radius: 5
        border.color: "gray"
        height: 25
        width: 30

        Text{
            text: index+1
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
        color: "lightblue"
        height: 25
        width: 150
        radius: 5
        border.color: "gray"
        Text{
            text: teamName
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
        model: problemas
        delegate: cuadroProblema
    }

    Component{
        id: cuadroProblema

        Rectangle{
            id: cuadro
            color: {
                if (intentos > 0 && aceptado==1)
                    "green"
                else if (intentos > 0 && aceptado==0)
                    "red"
                else "white"
            }
            border.color: "black"
            border.width: 1
            height: 25
            width: 50
            radius: 5
            Text{
                text: intentos ? "+" + intentos : ""
                horizontalAlignment: Text.AlignHCenter
                color: "black"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
//            MouseArea {
//                anchors.fill: parent
//                onClicked: problemas.setProperty(index, "intentos", intentos + 1)
//            }
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
            id: acepTexto
            text: totAceptado.toString();
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
            id: tiempoTexto
            text: totTiempo.toString();
            horizontalAlignment: Text.AlignHCenter
            color: "white"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }




}

