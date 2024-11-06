#include <LiquidCrystal.h>
#include <vector>

LiquidCrystal layar(10, 9, 8, 7, 6, 5);

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

void setup() {
  pinMode(A0, INPUT);
  layar.begin(16, 2); 

  Serial.begin(9600);
}

void loop() {
  int frekuensi = 2400;
  int desible = 40;

  int volume = 43;

  /*
    Perhitungan nilai crisp frekuensi sesuai member function
  */

  

 /*
    Perhitungan nilai crisp desible sesuai member function
  */

  delay(1000);

  layar.setCursor(0, 0); 
  layar.print("F: ");
  layar.print(frekuensi);
  layar.print("  ");
  layar.print("D: ");
  layar.print(desible);

  layar.setCursor(0, 1);
  layar.print("Volume: ");
  layar.print(volume);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");

  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 2400;
  desible = 40;

  volume = 43;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");

  frekuensi = 3674;
  desible = 40;

  volume = 44;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");

  frekuensi = 6255;
  desible = 40;

  volume = 48;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");

  frekuensi = 9514;
  desible = 40;

  volume = 57;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");

  frekuensi = 9215;
  desible = 40;

  volume = 54;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");

  frekuensi = 9200;
  desible = 40;

  volume = 53;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");

  frekuensi = 9200;
  desible = 49;

  volume = 56;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");

  frekuensi = 9200;
  desible = 57;

  volume = 67;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");

  frekuensi = 9200;
  desible = 54;

  volume = 65;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");

  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
  frekuensi = 9200;
  desible = 55;

  volume = 66;

  delay(1000);

  Serial.print("Frekuensi: ");
  Serial.println(frekuensi);
  Serial.print("Desible: ");
  Serial.println(desible);
  Serial.print("Volume: ");
  Serial.println(volume);
  Serial.println("");
}