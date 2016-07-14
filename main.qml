import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2


ApplicationWindow {
    visible: true

    width: 900
    height: 600

    minimumWidth: width
    maximumWidth: width

    maximumHeight: height
    minimumHeight: height
    title: qsTr("Standing")
    signal envioSignal()



    //    property alias fileDescr: fileDialogDesc.fileUrl
    //    property alias fileDescr: fileDialogDesc.fileUrl
    //    property alias fileDescr: fileDialogDesc.fileUrl

    property int cantProblemas

    header: ToolBar{
        RowLayout{
            Layout.fillWidth: true
            anchors.fill: parent

            Switch{
                id: cambio
                text: "Simular"
                checked: false
            }
            ToolButton{
                text: "Enviar"
                anchors.right: parent.right
                onClicked: envioSignal();
            }
            Row{
                Slider{
                    id: slider
                    width: 250
                    value: 1.0
                }

                Text{
                    id: textoSlider
                    text: "Velocidad: " + velocidad.toFixed(0) +" ms"
                    //                    text: "Velocidad: " + slider.value.toFixed(1) +"x"

                    font.pointSize: 10
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

        }
    }

    Header{
        id: cabecera
        width: currentItem.ancho
        height: 25

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 5
    }

    ListModel{
        id: equipos
    }

    ListView{
        id: standing
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 35

        width: currentItem.ancho
        height: 530
        //        highlight: Rectangle { color: "lightsteelblue"; radius: 5;}
        model: equipos
        delegate: Team{}
        clip: true
        spacing: 5
        orientation: ListView.Vertical

        move: Transition {
            NumberAnimation { properties: "x,y"; duration: 2000 }
        }
    }

    property double velocidad: 3000 - 2500*slider.value
    Timer{
        interval: velocidad
        running: cambio.checked
        repeat: true
        onTriggered: envioSignal()

    }


    function enviarFallo(equipoID, problemaID){
        var valor = equipos.get(equipoID).problemas.get(problemaID).intentos
        equipos.get(equipoID).problemas.setProperty(problemaID, "intentos", valor+1)
    }


    function enviarAccepted(equipoID, problemaID, tiempo){
        var valor = equipos.get(equipoID).problemas.get(problemaID).intentos
        var probAcep = equipos.get(equipoID).totAceptado;

        equipos.get(equipoID).problemas.setProperty(problemaID, "intentos", valor+1)
        equipos.get(equipoID).problemas.setProperty(problemaID, "aceptado", 1)

        equipos.setProperty(equipoID,"totAceptado",probAcep+1);
        equipos.setProperty(equipoID,"totTiempo",tiempo);

    }
    property int stackOrder: 100
    function envio(posAnterior, posActual, problema, aceptado, tiempo){
        if (!aceptado) enviarFallo(posAnterior, problema);
        else{
            enviarAccepted(posAnterior,problema, tiempo);
            equipos.setProperty(posAnterior, "z", 1); //siempre al frente
            equipos.move(posAnterior, posActual,1);
            stackOrder++;
            if (posAnterior == 30){
                console.log(equipos.get(posAnterior).z)
                console.log(equipos.get(posAnterior).teamName)
            }
        }

    }

    function crearProblemas(totalProblemas){
        for(var i=0; i<equipos.count; i++){
            for (var j=0; j<totalProblemas; j++)
                equipos.get(i).problemas.append({"intentos" : 0,"aceptado" : 0});
        }
        cantProblemas = totalProblemas
    }

    function insertarEquipo(equipo){
        equipos.append({"teamName" : equipo,"problemas" : [], "totAceptado":0, "totTiempo":0})
    }



    //    FileDialog {
    //         id: fileDialogDesc
    //         title: "Please choose a description file"
    //         nameFilters: ["JSON (*.json)"]
    //         folder: shortcuts.home
    //         onAccepted: {
    //             console.log("You chose: " + fileDialog.fileUrl)
    //             Qt.quit()
    //         }
    //         onRejected: {
    //             console.log("No se pudo abrir")
    //         }
    //         Component.onCompleted: visible = true
    //     }


    Component.onCompleted: {
        //        insertarEquipo("Eloy");
        //        crearProblemas(cantProblemas);
        //        enviarFallo(2, 4);
        //        enviarAccepted(1,3)
        //        console.log(cabecera.x)
        //        console.log(standing.x)
        //        console.log(cabecera.y)
        //        console.log(standing.y)
        //        equipos.move(0,0,1);
    }

}
