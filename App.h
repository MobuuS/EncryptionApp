//
// Created by START on 15.08.2025.
//

#ifndef APP_H
#define APP_H
#include <string>
#include <vector>
using namespace std;


class App {
public:
    // SubMethods - methods that support/simplify main methods in the application
    static tuple<string, string> EncryptMessage(string message);
    static string DecryptMessage(string message, string key, string master);
    static string GenerateMasterKey(int length);
    static string UseMasterKey(string key, string master);

    // Main method
    static void Start();

    // Main methods - methods that assemble the code needed to go through a certain process in the application
    static bool AppOperationCancelled();
    static void AppClickToContinue();
    static string AppImportMasterKey();
    static string AppMasterKeyGenerator();
    static int AppIntInputProcess();
    static string AppStringInputProcess();
    static string AppMasterKeyInputProcess();
    static tuple<string, string, string, bool> AppEncryptMessage(vector<string> list);
    static string AppDecryptMessage(vector<string> list);
};



#endif //APP_H
