#include<iostream>
#include<fstream>
#include<cstring>
#include <algorithm>
#include "siswa.h"

using namespace std;

siswa siswaKursus[30];

bool banding(siswa a, siswa b){
	if(a.persen_nilai > b.persen_nilai)
		return 1;
	else
		return 0;
}

void inputData(int i)
{
	ofstream datasiswa("data.dat");
	cout << "Input Data Siswa Ke-" << i + 1 << endl;
	cout << "Kode Siswa\t: "; cin >> siswaKursus[i].kode_siswa;
	cout << "Nama\t\t: "; cin >> siswaKursus[i].nama;

	datasiswa.write((char*)&siswaKursus, sizeof(siswaKursus));
	datasiswa.close();

}

void dataNilai(int j, int kode_mapel)
{
	ifstream bukadata("data.dat");
	bukadata.read((char*)&siswaKursus, sizeof(siswaKursus));

	cout << siswaKursus[j].kode_siswa <<"\t"<< siswaKursus[j].nama<<"\t";
	cout << "\t Nilai[A/B/C/D/E]: ";
	fflush(stdin);
	cin >> siswaKursus[j].nilai[kode_mapel];

	ofstream simpandata("data.dat");
	simpandata.write((char*)&siswaKursus, sizeof(siswaKursus));

	bukadata.close();
	simpandata.close();
}

void rekapDataSiswa(int banyakSiswa){
    int i, j;
	int hitungNilaiA, maxNilai, minNilai;
	char maxNama[50], minNama[50];
	float totalNilai = 0, rataNilai;
	ifstream fileRekap("data.dat");
	fileRekap.read((char*)&siswaKursus, sizeof(siswaKursus));

	cout << "Kode\tNama\t\tM1\tM2\tM3\tM4\t%\tKet." << endl << endl;
	for(i = 0; i < banyakSiswa; i++){
        cout << siswaKursus[i].kode_siswa <<"\t"<< siswaKursus[i].nama<<"\t\t";
        for (j = 0; j < 4; j++){
            cout << siswaKursus[i].nilai[j]<<"\t";

			hitungNilaiA = strcmp(siswaKursus[i].nilai[j], "A");
			if (hitungNilaiA == 0){
				siswaKursus[i].hitung_nilai += 1;
			}
        }
        siswaKursus[i].persen_nilai = siswaKursus[i].hitung_nilai*100/4;
		cout << siswaKursus[i].persen_nilai;

		if(siswaKursus[i].persen_nilai >= 75){
            cout << "\tLulus" << endl;
		}else{
            cout << "\tTidak Lulus" << endl;
		}

	}
	cout << "=============================================================================\n\n";
	cout << "Jumlah Siswa\t\t: " << i;

	for(i = 0; i < banyakSiswa; i++){
        totalNilai = totalNilai + siswaKursus[i].persen_nilai;
	}
	rataNilai = totalNilai/i;
	cout << "\nRata-Rata Nilai Kelas\t: " << rataNilai << "\n";

    maxNilai = siswaKursus[i].persen_nilai;
    minNilai = siswaKursus[0].persen_nilai;
	for(i = 0; i < banyakSiswa; i++){
        if(siswaKursus[i].persen_nilai > maxNilai){
            maxNilai = siswaKursus[i].persen_nilai;
            strcpy(maxNama, siswaKursus[i].nama);
        }
        if(siswaKursus[i].persen_nilai < minNilai){
            minNilai = siswaKursus[i].persen_nilai;
            strcpy(minNama, siswaKursus[i].nama);
        }
	}
	cout << "Nilai tertinggi\t\t: " << maxNilai << "\t\tNama Siswa: " << maxNama << "\n";
    cout << "Nilai terendah\t\t: " << minNilai << "\t\tNama Siswa: " << minNama << "\n";
    cout << "\n";
    cout << "=============================================================================\n";
    cout << "RANK SISWA\n\n";
    sort(siswaKursus, siswaKursus+banyakSiswa, banding);
    cout << "Rank\tKode\tNama\t\tNilai(%)" << endl << endl;
    for(i = 0; i < banyakSiswa; i++){
        cout << i+1 << "\t" << siswaKursus[i].kode_siswa <<"\t"<< siswaKursus[i].nama << "\t\t"<< siswaKursus[i].persen_nilai << endl;
    }
	fileRekap.close();
}

int main()
{
    int i, n = 4;
	int x; int Mapel=0;
	char pilih_lagi;
	int pilih;
	cout << "Pilih Opsi" << endl;
	cout << "1. Memasukkan Data Siswa\n2. Nilai Siswa\n3. Rekap Data" << endl;
	cout << "Pilih nomor: ";
	cin >> pilih;
	system("cls");

	switch (pilih){
    case 1:
        for (i = 0; i < n; i++){
            inputData(i);
            system("cls");
        }
        break;
    case 2:
        cout << "Catatan Kode Mapel: \n";
        cout << "Kode M1: Listening\n";
        cout << "Kode M2: Structure\n";
        cout << "Kode M3: Reading\n";
        cout << "Kode M4: Writing\n";
        cout << "\n";
        do{
            cout << "Nilai Mapel dengan kode M" << Mapel + 1 << endl;
            for (x = 0; x < n; x++){
				dataNilai(x, Mapel);
			}
			cout << "\nMasukkan nilai mapel berikutnya[Y/N]= ";
			cin >> pilih_lagi;
			Mapel++;
        }while(pilih_lagi == 'y' || pilih_lagi == 'Y');
        break;
    case 3:
        rekapDataSiswa(n);
        break;
    default:
        cout << "Pilihan Salah";
	}

	return 0;

}
