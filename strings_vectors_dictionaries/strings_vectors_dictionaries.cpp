/***************************************
 * Автор:    Рычков Михаил             *
 * Название: Строки, векторы и словари *
 * Вариант:  24                        *
 ***************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;

int main() {
  constexpr int maxCount = 100;
  constexpr int maxMagnitude = 1000;
  constexpr int maxTextLength = 200;
  constexpr int maxKeyLength = 40;
  constexpr int maxAsciiValue = 127;
  constexpr int minOwnerCount = 2;

  char part;
  if (!(cin >> part)) {
    cout << "INVALID" << endl;
    return 1;
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  if (part == 'A') {
    string text;
    if (!getline(cin, text) || text.size() > maxTextLength) {
      cout << "INVALID" << endl;
      return 1;
    }

    for (unsigned char symbol : text) {
      if (symbol > maxAsciiValue) {
        cout << "INVALID" << endl;
        return 1;
      }
    }

    size_t position = text.find('a');

    if (position == string::npos) {
      cout << "NONE" << endl;
    }
    else {
      cout << position + 1 << endl;
    }

  }
  else if (part == 'B') {
    int count;
    if (!(cin >> count) || count < 0 || count > maxCount) {
      cout << "INVALID" << endl;
      return 1;
    }

    vector<int> values;
    for (int elementIndex = 0; elementIndex < count; ++elementIndex) {
      int value;
      if (!(cin >> value) || value < -maxMagnitude || value > maxMagnitude) {
        cout << "INVALID" << endl;
        return 1;
      }
      values.push_back(value);
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    if (values.empty()) {
      cout << "EMPTY" << endl;
    }
    else {
      for (size_t elementIndex = 0; elementIndex < values.size(); ++elementIndex) {
        if (elementIndex > 0) {
          cout << " ";
        }
        cout << values[elementIndex];
      }
      cout << endl;
    }

  }
  else if (part == 'C') {
    int pairCount;
    if (!(cin >> pairCount) || pairCount < 0 || pairCount > maxCount) {
      cout << "INVALID" << endl;
      return 1;
    }

    map<string, int> values;
    for (int pairIndex = 0; pairIndex < pairCount; ++pairIndex) {
      string key;
      int value;

      if (!(cin >> key >> value) || key.size() > maxKeyLength || value < -maxMagnitude || value > maxMagnitude) {
        cout << "INVALID" << endl;
        return 1;
      }

      for (unsigned char symbol : key) {
        if (symbol > maxAsciiValue) {
          cout << "INVALID" << endl;
          return 1;
        }
      }

      values[key] = value;
    }

    if (values.empty()) {
      cout << "NONE" << endl;
    }
    else {
      auto minimumEntry = values.begin();

      for (auto entry = values.begin(); entry != values.end(); ++entry) {
        if (entry->second < minimumEntry->second || (entry->second == minimumEntry->second && entry->first < minimumEntry->first)) {
          minimumEntry = entry;
        }
      }

      cout << minimumEntry->first << " "
           << minimumEntry->second << endl;
    }

  }
  else if (part == 'D') {
    int count;
    if (!(cin >> count) || count < 0 || count > maxCount) {
      cout << "INVALID" << endl;
      return 1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    map<string, vector<string>> itemOwners;

    for (int recordIndex = 0; recordIndex < count; ++recordIndex) {
      string name;
      string item;

      if (!getline(cin, name) || !getline(cin, item) || name.empty() || item.empty() || name.size() > maxTextLength || item.size() > maxTextLength || name.front() == ' ' || name.back() == ' ' || item.front() == ' ' || item.back() == ' ') {
        cout << "INVALID" << endl;
        return 1;
      }

      for (unsigned char symbol : name) {
        if (symbol > maxAsciiValue) {
          cout << "INVALID" << endl;
          return 1;
        }
      }

      for (unsigned char symbol : item) {
        if (symbol > maxAsciiValue) {
          cout << "INVALID" << endl;
          return 1;
        }
      }

      vector<string>& owners = itemOwners[item];

      if (find(owners.begin(), owners.end(), name) == owners.end()) {
        owners.push_back(name);
      }
    }

    bool foundSharedItem = false;

    for (const auto& entry : itemOwners) {
      if (entry.second.size() >= minOwnerCount) {
        cout << entry.first << endl;
        foundSharedItem = true;
      }
    }

    if (!foundSharedItem) {
      cout << "EMPTY" << endl;
    }

  }
  else {
    cout << "INVALID" << endl;
    return 1;
  }

  return 0;
}