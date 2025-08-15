//
// Created by START on 15.08.2025.
//

#include "App.h"

#include <ctime>
#include <iostream>
#include <vector>

#include "string"

using namespace std;

// Legacy & SubMethods
tuple<string, string> App::EncryptMessage(string message) {
    vector<int> locNew;
    vector<int> keyList;
    vector<int> spaceList;
    string row = "abcdefghijklmnopqrstuvwxyz,?!.";
    string encryptedMessage;
    string key;

    srand(time(nullptr));

    // Initialization
    for (int j = 0; j < message.length(); j++) {
        char messageChar = message[j];
        int keyValue = rand() % 9; // Generating a random key

        if (messageChar != ' ') {
            keyList.push_back(keyValue); // Saving key
        }
        else {
            encryptedMessage += "-";
            key += "-";
            continue;
        }

        for (int k = 0; k < row.length(); k++) {
            char abcChar = row[k]; // Receiving char from row
            if (tolower(messageChar) == abcChar) { // Checking char
                int position = k + keyValue;
                if (position >= row.length()) { // Adjusting overspills
                    position -= row.length();
                }
                locNew.push_back(position); // Saving char's position to a list
                encryptedMessage += row[position];
                key += to_string(keyValue);
                break;
            }
        }
    }
    // cout << "DEBUG: " << "Encrypted message: " << encryptedMessage << endl;
    // cout << "DEBUG: " << "Your key: " << key << endl;
    return {encryptedMessage, key};
}

string App::DecryptMessage(string message, string key, string master) {
    string row = "abcdefghijklmnopqrstuvwxyz,?!.";
    string keyOrigin;
    string decryptedMessage;

    if (master.length() < key.length()) {
        master.append(master);
    }
    master = master.substr(0, key.length());

    for (int l = 0; l < key.length(); l++) {

        if (key[l] == '-') {
            keyOrigin += "-";
            continue;
        }

        int keyChar = key[l] - '0';
        int masterChar = master[l] - '0';
        int combined = keyChar - masterChar;

        if (combined < 0) {
            combined += 10;
        }

        keyOrigin += to_string(combined);
    }

    // cout << "DEBUG: " << keyOrigin << endl;

    for (int i = 0; i < message.length(); i++) {
        char messageChar = message[i];
        char keyChar = keyOrigin[i];

        if (keyChar == '-') {
            decryptedMessage += " ";
            continue;
        }

        int keyValue = keyChar - '0'; // Tranformation from char to int

        if (messageChar == '-') {
            decryptedMessage += " ";
            continue;
        }

        for (int rowIndex = 0; rowIndex < row.length(); rowIndex++) {
            char rowChar = row[rowIndex];

            if (rowChar == messageChar) {
                int posOrigin = rowIndex - keyValue;
                // cout << "DEBUG: " << rowIndex << "," << rowChar << "," << keyValue << ";" << endl;
                if (posOrigin < 0) {
                    posOrigin += row.length();
                }

                for (int r = 0; r < row.length(); r++) {
                    if (r == posOrigin) {
                        decryptedMessage += row[r];
                        break;
                    }
                }

                // char charOrigin = row[posOrigin];
                // decryptedMessage += charOrigin;
                break;
            }
        }
    }

    // cout << "DEBUG: Decrypted Message:" << decryptedMessage;
    return decryptedMessage;
}

string App::GenerateMasterKey(int length) {
    string masterKey;
    srand(time(nullptr));

    for (int i = 0; i < length; i++) {
        int number = rand() % 9;
        masterKey += to_string(number);
    }

    // cout << "Master key: " << masterKey;
    return masterKey;
}

string App::UseMasterKey(string key, string master) {
    string combinedKey;

    while (master.length() < key.length()) {
        master.append(master);
    }

    for (int i = 0; i < key.length(); i++) {

        if (key[i] == '-') {
            combinedKey += "-";
            continue;
        }

        int keyChar = key[i] - '0';
        int masterChar = master[i] - '0';
        int combined = masterChar + keyChar;

        if (combined >= 10) {
            combined -= 10;
        }

        combinedKey += to_string(combined);
    }
    // cout << "DEBUG: " << "Combined key: " << combinedKey << endl;
    return combinedKey;
}

// Methods representing each of the application's functionalities
string App::AppMasterKeyGenerator() {
    string userInputLocal;
    string cont;
    int length;
    bool isLengthCorrect = false;

    while (!isLengthCorrect) {
        cin.clear();
        cout << "Enter length of your Master-key (min. 100): ";
        cin >> userInputLocal;

        if (userInputLocal == "exit") {
            isLengthCorrect = AppOperationCancelled();
            return userInputLocal;
        }

        try {
            length = stoi(userInputLocal);
            isLengthCorrect = true;
        } catch (exception& e) {
            cout << "Enter a number!" << endl;
        }
    }

    string masterKey = GenerateMasterKey(length);

    cout << "Generated Master-Key:\n" << masterKey << endl;
    cout << "\nThis key has been saved to the key repository!" << endl;

    return masterKey;
}

void App::AppClickToContinue() {
    string cont;

    cin.clear();
    cout << "Press any key to continue...";
    cin >> cont;
}

bool App::AppOperationCancelled() {
    cout << "Operation cancelled! You'll return to the Main Menu!\n" << endl;
    AppClickToContinue();
    return true;

}

string App::AppImportMasterKey() {
    string userInputLocal;
    string cont;
    bool isKeyCorrect;

    cout << "If you'd like to cancel, type 'exit'" << endl;
    cin.ignore();

    while (!isKeyCorrect) {
        bool incorrect = false;
        cin.clear();
        cout << "Enter a Master-Key (length min. 50): ";
        cin >> userInputLocal;

        if (userInputLocal == "exit") {
            isKeyCorrect = true;
            break;
        }

        if (userInputLocal.length() < 50) {
            cout << "This key is too short!" << endl;
            cin.clear();
            continue;
        }

        for (int i = 0; i < userInputLocal.length(); i++) {
            if (!isdigit(userInputLocal[i])) {
                cout << "This is not a number!" << endl;
                incorrect = true;
                break;
            }
        }

        if (!incorrect) {
            break;
        }
    }

    return userInputLocal;
}

int App::AppIntInputProcess() {
    bool isCorrect = false;
    string userInput;
    int selection;

    cin.clear();
    cout << "Enter your choice: ";
    cin >> userInput;

    while (!isCorrect) {

        if (userInput == "exit") {
            selection = 0;
            break;
        }

        if (userInput.empty() || userInput.length() > 1) {
            cout << "Inappropriate input length!" << endl;
            continue;
        }

        try {
            selection = stoi(userInput);
        } catch (exception& e) {
            cout << "Enter a number!" << endl;
            continue;
        }

        if (selection < 0) {
            cout << "Cannot enter a negative number!" << endl;
            continue;
        }

        isCorrect = true;
    }

    return selection;
}

string App::AppStringInputProcess() {
    bool isCorrect = false;
    string userInput;

    cin.clear();
    cout << "Enter your choice: ";
    cin >> userInput;

    while (!isCorrect) {

        if (userInput == "exit") {
            break;
        }

        if (userInput.empty() || userInput.length() > 1) {
            cout << "Inappropriate input length!" << endl;
            continue;
        }

        try {
            int selection = stoi(userInput);
        } catch (exception& e) {
            cout << "Enter a number!" << endl;
            continue;
        }

        isCorrect = true;
    }

    return userInput;
}

string App::AppMasterKeyInputProcess() {
    bool isCorrect = false;
    string userInput;

    while (!isCorrect) {
        cout << "Enter a Master-Key (min. length 50): ";
        cin.clear();
        cin >> userInput;

        if (userInput == "exit") {
            break;
        }

        if (userInput.length() < 50) {
            cout << "This key is too short!" << endl;
            continue;
        }

        for (int i = 0; i < userInput.length(); i++) {
            if (!isdigit(userInput[i])) {
                cout << "This is not a number!" << endl;
                userInput = "";
                break;
            }
        }

        if (!userInput.empty()) {
            isCorrect = true;
        }
    }
    return userInput;
}

tuple<string, string, string, bool> App::AppEncryptMessage(vector<string> list) {
    string message;
    string answerMasterKey;
    string masterKey;
    string answerGenMasterKey;
    string cont;
    bool isMasterGenerated = false;

    cin.ignore();
    while (message.empty()) {
        cin.clear();
        cout << "Enter a message: " << endl;
        getline(cin, message);
        if (message == "exit") {
            AppOperationCancelled();
            return {"", "", "", isMasterGenerated};
        }
    }

    auto [encryptedMessage, key] = EncryptMessage(message);

    // cout << "DEBUG: " << "Key: " << key << endl;

    bool answered = false;

    while (!answered) {
        cin.clear();
        cout << "Encrypt with a master key? (Y/N): ";
        cin >> answerMasterKey;

        if (answerMasterKey == "Y") {
            if (list.empty()) {
                cout << "You have not generated a master key yet!" << endl;

                while (!answered) {
                    cout << "Would you like to generate one and use it (Y/N)?:";
                    cin >> answerGenMasterKey;

                    if (answerGenMasterKey == "Y") {
                        masterKey = AppMasterKeyGenerator();
                        key = UseMasterKey(key, masterKey);
                        isMasterGenerated = true;
                        answered = true;
                    }

                    if (answerGenMasterKey == "N") {
                        cout << "!! MASTER-KEY IS MISSING, Generated key is insecure." << endl;
                        answered = true;
                    }
                }
            }
            else {
                cout << "Select a key:";
                for (int i = 0; i < list.size(); i++) {
                    cout << " " << i + 1 << ") " << list[i] << endl;
                }
                cout << "-----------------------------" << endl;

                string selection = AppStringInputProcess();

                answered = false;
                while (!answered) {
                    for (int j = 0; j < list.size(); j++) {
                        if (selection == "exit") {
                            AppOperationCancelled();
                            return {"", "", "", isMasterGenerated};
                        }
                        if (stoi(selection) - 1 == j) {
                            masterKey = list[j];
                            answered = true;
                            break;
                        }

                    }
                }
                // cout << "DEBUG: " << encryptedMessage << endl;
                // cout << "DEBUG: Used master:" << masterKey << endl;
                // cout << "DEBUG: Key before master:" << key << endl;
                key = UseMasterKey(key, masterKey);
            }
        }
        if (answerMasterKey == "N") {
            cout << "!! MASTER-KEY IS MISSING, Generated key is insecure." << endl;
            answered = true;
        }
        if (answerMasterKey == "exit") {
            AppOperationCancelled();
            return {"", "", "", isMasterGenerated};
        }
    }
    return {encryptedMessage, key, masterKey, isMasterGenerated};
}

string App::AppDecryptMessage(vector<string> masterList) {
    string message;
    string key;
    string masterKey;
    string cont;
    bool completed = false;

    while (!completed) {
        cin.clear();
        cout << "Enter encrypted message: ";
        cin >> message;

        if (!message.empty()) {
            completed = true;
        }
    }

    // EXIT
    if (message == "exit") {
        AppOperationCancelled();
        return message;
    }

    completed = false;

    while (!completed) {
        cin.clear();
        cout << "Enter a key: ";
        cin >> key;

        if (!key.empty()) {
            completed = true;
        }
    }

    // EXIT
    if (key == "exit") {
        AppOperationCancelled();
        return key;
    }

    completed = false;

    while (!completed) {
        cout << "Enter a Master-Key (1) or find an already existing one (2)?" << endl;
        string inputMasterKey = AppStringInputProcess();

        if (inputMasterKey == "exit") {
            AppOperationCancelled();
            return inputMasterKey;
        }

        if (inputMasterKey == "1") {
            masterKey = AppMasterKeyInputProcess();

            if (masterKey == "exit") {
                AppOperationCancelled();
                return masterKey;
            }
            completed = true;
        }
        else if (inputMasterKey == "2" && !masterList.empty()) {

            cout << "Select a key:";
            for (int i = 0; i < masterList.size(); i++) {
                cout << " " << i + 1 << ") " << masterList[i];
            }
            cout << "-----------------------------" << endl;

            string userInputLocal = AppStringInputProcess();

            completed = false;
            while (!completed) {
                for (int j = 0; j < masterList.size(); j++) {
                    if (userInputLocal == "exit") {
                        completed = AppOperationCancelled();
                        return userInputLocal;
                    }
                    if (stoi(userInputLocal) - 1 == j) {
                        masterKey = masterList[j];
                        completed = true;
                        break;
                    }
                }
            }
        }
        else {
            cout << "Wrong input!" << endl;
        }
    }

    message = DecryptMessage(message, key, masterKey);

    return message;
}

void App::Start() {
    bool running = true;
    vector<string> masterList;

    while (running) {
        bool completed = false;

        cout << "--------------Encryption App--------------" << endl;
        cout << " 1) Encrypt a message" << endl;
        cout << " 2) Decrypt a message" << endl;
        cout << " 3) Generate Master-Key" << endl;
        cout << " 4) Import a Master-Key" << endl;
        cout << " 5) Key Repository" << endl;
        cout << " 6) Exit\n" << endl;

        while (!completed) {
            int selection = AppIntInputProcess();

            if (selection == 0) {
                cout << "App closed!" << endl;
                running = false;
                break;
            }

            cout << "If you'd like to cancel any operation, type 'exit'" << endl;

            switch (selection) {

                case 1: {

                    auto [encryptedMessage, key, masterKey, isMasterGenerated] = AppEncryptMessage(masterList);

                    if (!key.empty() && !encryptedMessage.empty()) {
                        cout << "\n---------------------Final-Result------------------" << endl;
                        cout << "Encrypted message:\t" << encryptedMessage << endl;
                        cout << "Key:\t\t\t" << key << endl;
                        cout << "---------------------------------------------------" << endl;

                        if (isMasterGenerated) {
                            masterList.push_back(masterKey);
                        }

                        AppClickToContinue();
                    }

                    completed = true;
                    break;
                }
                case 2: {

                    string message = AppDecryptMessage(masterList);

                    if (message != "exit") {
                        cout << "Decrypted message: " << endl << message << "\n" << endl;
                        AppClickToContinue();
                    }

                    completed = true;
                    break;
                }
                case 3: {
                    string masterKey = AppMasterKeyGenerator();

                    if (masterKey != "exit") {
                        masterList.push_back(masterKey);
                        AppClickToContinue();
                    }

                    completed = true;
                    break;
                }
                case 4: {
                    string masterKey = AppImportMasterKey();

                    if (masterKey == "exit") {
                        cout << "Master-Key import cancelled!";
                    }
                    else {
                        masterList.push_back(masterKey);
                        cout << "Master-Key successfully imported!" << endl;
                    }

                    AppClickToContinue();

                    completed = true;
                    break;
                }
                case 5: {
                    string cont;

                    cout << "List of Master-keys" << endl;
                    cout << "-------------------" << endl;
                    cout << "No.\t" << "key" << endl;

                    if (masterList.empty()) {
                        cout << "It's so empty in here :(" << endl;;
                    }
                    else {
                        for (int i = 0; i < masterList.size(); i++) {
                            cout << i << ".\t" << masterList[i] << endl;
                        }
                    }

                    cout << "-------------------" << endl;

                    cin.clear();
                    cout << "Press any key to continue...";
                    cin >> cont;

                    completed = true;
                    break;
                }
                case 6: {
                    completed = true;
                    running = false;
                    break;
                }
                default: {
                    cout << "Something went horribly wrong!" << endl;
                    running = false;
                    break;
                }
            }
        }
    }



}
