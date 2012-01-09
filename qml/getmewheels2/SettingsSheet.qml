import QtQuick 1.1
import com.nokia.meego 1.0

Sheet {
    id: settingsSheet
    acceptButtonText: "Save"
    rejectButtonText: "Cancel"

    content: Column {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        SectionHeader {
            width: parent.width
            headerText: qsTr("General")
        }

        SelectionButton {
            titleText: "Location"
            subTitleText: gmwEngine.location
            width: parent.width
            onClicked: {
                selectLocationsDialog.model = 0;
                locationsModel.clear();
                gmwEngine.supportedLocations().forEach(function(item) { print("got location:" + item); locationsModel.append( {name: item} ) });
                selectLocationsDialog.model = locationsModel;
                selectLocationsDialog.open();
            }
        }

        Item {
            id: spacer1
            width: parent.width
            height: 20
        }

        SectionHeader {
            width: parent.width
            headerText: qsTr("car2go account")
        }

        Label {
            width: parent.width
            text: "To be able to create bookings for cars you need to be signed in with your car2go account. Note that there may be costs associated with it. Please visit http://www.car2go.com for detailed informations."
            wrapMode: Text.WordWrap
        }

        Label {
            width: parent.width
            text: "GetMeWheels is authenticated until " + gmwEngine.authExpirationDate
            wrapMode: Text.WordWrap
            visible: gmwEngine.authenticated
        }

        Button {
            text: gmwEngine.authenticated ? "Renew Authentication" : "Authenticate GetMeWheels"
            width: parent.width
            onClicked: {
                oauthSetupSheet.state = "step1";
                oauthSetupSheet.open();
            }
        }

        SelectionButton {
            id: accountSelectionButton
            titleText: "Account"
            subTitleText: gmwEngine.defaultAccountName
            width: parent.width
            enabled: gmwEngine.authenticated
            onClicked: {
                selectAccountDialog.model = 0;
                accountModel.clear();
                gmwEngine.accountNames().forEach(function(item) { accountModel.append({name: item}) } );
                selectAccountDialog.model = accountModel;
                selectAccountDialog.open();
            }
        }



    }

    ListModel {
        id: locationsModel
    }
    SelectionDialog {
        id: selectLocationsDialog
        titleText: "Select Location"
        model: locationsModel
        onAccepted: {
            gmwEngine.location = locationsModel.get(selectLocationsDialog.selectedIndex).name;
            gmwSettings.location = locationsModel.get(selectLocationsDialog.selectedIndex).name;
        }
    }

    ListModel {
        id: accountModel
    }
    SelectionDialog {
        id: selectAccountDialog
        titleText: "Select Account"
        onAccepted: {
            print("selected: "+ accountModel.get(selectAccountDialog.selectedIndex).name);
            gmwEngine.setDefaultAccountName(accountModel.get(selectAccountDialog.selectedIndex).name);
//            accountSelectionButton.subTitleText = gmwEngine.defaultAccountName();
        }
    }

    OAuthSetupSheet {
        id: oauthSetupSheet
    }
}
