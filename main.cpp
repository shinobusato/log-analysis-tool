#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

int main() {
    ifstream file("access.log");

    if (!file) {
        cout << "ログファイルを開けませんでした" << endl;
        return 1;
    }

    string line;
    map<string, map<string, int>> url_count;

    // ログ読み込み＆集計
    while (getline(file, line)) {
        stringstream ss(line);

        string ip, date, url;
        int status;

        if ((ss >> ip) && (ss >> date) && (ss >> url) && (ss >> status)) {
            url_count[date][url]++;
            // エラー判定（400以上）
            if (status >= 400) {
                cout << line << endl;
            }
        }
        else {
            //エラー判定（読み込めない値があった）
            cout << line << endl;
        }
    }

    file.close();

    // CSVファイル作成
    ofstream output("result.csv");

    if (!output) {
        cout << "CSVファイルを作成できませんでした" << endl;
        return 1;
    }

    // ヘッダー
    output << "URL,Count" << endl;

    // データ書き込み
    for (const auto& pair_day : url_count) {
        output << "--" << pair_day.first << "--" << endl;
        for (const auto& pair_url : pair_day.second) {
            output << pair_url.first << "," << pair_url.second << endl;
        }
    }

    output.close();

    cout << "CSVファイルを出力しました（result.csv）" << endl;

    return 0;
}
