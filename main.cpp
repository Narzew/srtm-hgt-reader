
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "srtmHgtReader.h"

using namespace std;

int arysize = 10000;
double latlons[10000][4];

void clear_latlons(){
    for(int i=0;i<arysize;i++){
        for(int j=0;j<4;j++){
            latlons[i][j] = 0;
        }
    }
}

void parse_coords(string filename){
    clear_latlons();
    ifstream plik;
    string line = "";
    double a1,a2,a3;
    int lcount = 0;
    plik.open(filename.c_str());
    if(plik.is_open() == true){
        while(plik >> a1 >> a2 >> a3){
            latlons[lcount][0] = a1;
            latlons[lcount][1] = a2;
            latlons[lcount][2] = a3;
            lcount++;
        }
    } else {
        cout << "ERROR: Failed to load coordinates from file: " << filename << "\n";
    }
    plik.close();
}

void calculate_elevs(string outname){
    ofstream outfile;
    outfile.open(outname.c_str(), ios::out);
    int i;
    for (i = 0; i < 1000; ++i) {
        if(latlons[i][0] == 0 || latlons[i][1] == 0){
            continue;
        } else {
            latlons[i][3] = srtmGetElevation(latlons[i][0], latlons[i][1]);
            outfile.precision(14);
            outfile <<latlons[i][0] << " " << latlons[i][1] << " " << latlons[i][2] << " ";
            outfile.precision(6);
            outfile << latlons[i][3] << "\n";
        }
    }
    outfile.close();
    printf("All values calculated\n");
}


double distance(double lat1,double lon1,double lat2,double lon2)
{
 double dlon = lon1 - lon2;
 double dlat = lat1 - lat2;

 dlon = dlon * (M_PI/180.0); //degrees to radians
 dlat = dlat * (M_PI/180.0);

 double a1,a2,a,sa,c,d;

 if(dlon==0 && dlat==0)
   return 0;

 a1 = sin (dlat / 2);
 a2 = sin (dlon / 2);
 a = (a1 * a1) + cos (lat1) * cos (lat2) * a2 * a2;
 sa = sqrt (a);
 if (sa <= 1.0)
   {c = 2 * asin (sa);}
 else
   {c = 2 * asin (1.0);}
 d = 6378137 * c; //in meters

 return d;
}

/**
 * Example Usage
 * Download srtm HGT files ie from http://dds.cr.usgs.gov/srtm/version2_1/SRTM3/
 */

int main(int argc, char *argv[]) {
    cout.precision(8);
    string fname;
    string outname;

    if(argv[1] != NULL && argv[2] != NULL){
        fname = argv[1];
        outname = argv[2];
    } else {
        cout << "\nElevationsReader v 1.1 3\" (C) zbycz, CLI interface by Narzew\nUsage: ElevationsReader.exe input output\nPut SRTM 3 arcsec .hgt files in srtm/ folder.\nCreate file with coordinates like this:\nx y d\nwhere x = latitude, y = longitude, d = distance (you could put any value you want here), for example:\n-12.786198 -74.976402 0\n39.739236 -104.990251 100\n-26.195246 28.034088 200\n-16.196715 -68.038287 300\n51.365468 22.000938 1513\nSave file with coordinates and parse it filename as first parameter, and you will get result in output file, for ex:\nElevationsReader.exe coords.txt result.txt\n";
        exit(-1);
    }
    parse_coords(fname);
    calculate_elevs(outname);
    srtmClose();
    return 0;
}
