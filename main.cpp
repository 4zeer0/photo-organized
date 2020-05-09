#include <string>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <windows.h>
#include <typeinfo>
#include <direct.h>

namespace fs = std::filesystem;

using namespace std;

int main() {
    WIN32_FILE_ATTRIBUTE_DATA fInfo;
    SYSTEMTIME st;
    string path = "C:/Users/pedro/Desktop/Sample";

    for (const auto & entry : fs::directory_iterator(path)) {


        fs::path paths = entry.path().filename();
        string imageName = paths.u8string();
        string fullPath;
        fullPath.append(path);
        fullPath.append("/");
        fullPath.append(imageName);

        if (paths.extension() == ".jpg") {
            GetFileAttributesEx(fullPath.c_str(), GetFileExInfoStandard, &fInfo);
            FileTimeToSystemTime(&fInfo.ftLastWriteTime, &st);
            cout << st.wMonth << "/" << st.wDay << "/" << st.wYear << endl;


            string folderPath, folderMonth, folderYear, folderDay, folderName = "/", folderWeekDay;
            int folderWeekDayNum, folderMonthNum;

            folderMonthNum = st.wMonth;
            folderYear = to_string(st.wYear);
            folderDay = to_string(st.wDay);
            folderWeekDayNum = st.wDayOfWeek;


            switch (folderWeekDayNum) {
                case 0:
                    folderWeekDay = "Sunday";
                    break;
                case 1:
                    folderWeekDay = "Monday";
                    break;
                case 2:
                    folderWeekDay = "Tuesday";
                    break;
                case 3:
                    folderWeekDay = "Wednesday";
                    break;
                case 4:
                    folderWeekDay = "Thursday";
                    break;
                case 5:
                    folderWeekDay = "Friday";
                    break;
                case 6:
                    folderWeekDay = "Saturday";
                    break;
            }

            switch (folderMonthNum) {
                case 1:
                    folderMonth = "January";
                    break;
                case 2:
                    folderMonth = "February";
                    break;
                case 3:
                    folderMonth = "March";
                    break;
                case 4:
                    folderMonth = "April";
                    break;
                case 5:
                    folderMonth = "May";
                    break;
                case 6:
                    folderMonth = "June";
                    break;
                case 7:
                    folderMonth = "July";
                    break;
                case 8:
                    folderMonth = "August";
                    break;
                case 9:
                    folderMonth = "September";
                    break;
                case 10:
                    folderMonth = "October";
                    break;
                case 11:
                    folderMonth = "November";
                    break;
                case 12:
                    folderMonth = "December";
                    break;

            }

            folderName.append(folderWeekDay);
            folderName.append(" ");
            folderName.append(folderDay);
            folderName.append(", ");
            folderName.append(folderMonth);
            folderName.append(", ");
            folderName.append(folderYear);
            folderPath = path.c_str();
            folderPath.append(folderName);

            cout << folderName << endl;

            if (!fs::exists(folderPath)) {
                _mkdir(folderPath.c_str());
            }

            string checkPath;
            checkPath.append(folderPath.c_str());
            checkPath.append("/");
            checkPath.append(imageName);
            cout << "CHECK: " << checkPath << endl;

            if (!fs::exists(checkPath)) {

                fs::copy(fullPath.c_str(), folderPath.c_str());
            }
        }
    }
}
