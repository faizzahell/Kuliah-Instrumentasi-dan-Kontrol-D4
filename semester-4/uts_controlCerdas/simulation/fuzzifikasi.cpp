#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<vector<float>> crisp_frekuensi(float frekuensi) {
    float crisp_frekuensi_1 = 0.0;
    float crisp_frekuensi_2 = 0.0;
    float crisp_frekuensi_3 = 0.0;

    vector<float> crispFrekuensi;
    vector<float> conditionFrekuensi;

    if (frekuensi >= 10 && frekuensi <= 6600) {
      if (frekuensi >= 10 && frekuensi <= 20) {
        crisp_frekuensi_1 = (frekuensi - 10) / (20 - 10);
      }

      if (frekuensi > 20 && frekuensi <= 6600) {
        crisp_frekuensi_1 = (6600 - frekuensi) / (6600 - 20);
      }
    }

    if (frekuensi >= 20 && frekuensi <= 16320) {
      if (frekuensi >= 20 && frekuensi <= 6600) {
        crisp_frekuensi_2 = (frekuensi - 20) / (6600 - 20);
      }

      if (frekuensi > 6600 && frekuensi <= 16320) {
        crisp_frekuensi_2 = (16320 - frekuensi) / (16320 - 6600);
      }
    }

    if (frekuensi >= 6600 && frekuensi <= 20000) {
      if (frekuensi >= 6600 && frekuensi <= 16320) {
        crisp_frekuensi_3 = (frekuensi - 6600) / (16320 - 6600);
      }

      if (frekuensi > 16320 && frekuensi <= 20000) {
        crisp_frekuensi_3 = (20000 - frekuensi) / (20000 - 16320);
      }
    }

    if (crisp_frekuensi_1 != 0.0) {
      crispFrekuensi.push_back(crisp_frekuensi_1);
      conditionFrekuensi.push_back(1.0);
    }

    if (crisp_frekuensi_2 != 0.0) {
      crispFrekuensi.push_back(crisp_frekuensi_2);
      conditionFrekuensi.push_back(2.0);
    }

    if (crisp_frekuensi_3 != 0.0) {
      crispFrekuensi.push_back(crisp_frekuensi_3);
      conditionFrekuensi.push_back(3.0);
    }

    vector<vector<float>> value;
    value.push_back(crispFrekuensi);
    value.push_back(conditionFrekuensi);

    return value;
}

vector<vector<float>> crisp_desible(float desible) {
    float crisp_desible_1 = 0.0;
    float crisp_desible_2 = 0.0;
    float crisp_desible_3 = 0.0;

    vector<float> crispDesible;
    vector<float> conditionDesible;

    if (desible >= 0 && desible <= 60) {
      if (desible >= 0 && desible <= 30) {
        crisp_desible_1 = (desible - 0) / (30 - 0);
      }

      if (desible > 30 && desible <= 60) {
        crisp_desible_1 = (60 - desible) / (60 - 30);
      }
    }

    if (desible >= 30 && desible <= 85) {
      if (desible >= 30 && desible <= 60) {
        crisp_desible_2 = (desible - 30) / (60 - 30);
      }

      if (desible > 60 && desible <= 85) {
        crisp_desible_2 = (85 - desible) / (85 - 60);
      }
    }

    if (desible >= 60 && desible <= 100) {
      if (desible >= 60 && desible <= 85) {
        crisp_desible_3 = (desible - 60) / (85 - 60);
      }

      if (desible > 85 && desible <= 100) {
        crisp_desible_3 = (100 - desible) / (100 - 85);
      }
    }

    if (crisp_desible_1 != 0.0) {
      crispDesible.push_back(crisp_desible_1);
      conditionDesible.push_back(1.0);
    }

    if (crisp_desible_2 != 0.0) {
      crispDesible.push_back(crisp_desible_2);
      conditionDesible.push_back(2.0);
    }

    if (crisp_desible_3 != 0.0) {
      crispDesible.push_back(crisp_desible_3);
      conditionDesible.push_back(3.0);
    }

    vector<vector<float>> value;
    value.push_back(crispDesible);
    value.push_back(conditionDesible);

    return value;
}

int main() {
    float frekuensi = 9200;
    float desible = 55;

    vector<vector<float>> valueFrekuensi = crisp_frekuensi(frekuensi);
    vector<float> crispFrekuensi = valueFrekuensi[0];
    vector<float> conditionFrekuensi = valueFrekuensi[1];

    vector<vector<float>> valueDesible = crisp_desible(desible);
    vector<float> crispDesible = valueDesible[0];
    vector<float> conditionDesible = valueDesible[1];

    for (int i = 0; i < crispFrekuensi.size(); ++i) {
      cout << "Crisp Frekuensi " << i + 1 << ": " << crispFrekuensi[i] << endl;
      cout << "Condition Frekuensi " << i + 1 << ": " << conditionFrekuensi[i] << endl;
    }

    cout << "\n";

    for (int i = 0; i < crispDesible.size(); ++i) {
      cout << "Crisp Desible " << i + 1 << ": " << crispDesible[i] << endl;
      cout << "Condition Desible " << i + 1 << ": " << conditionDesible[i] << endl;
    }

    return 0;
}
