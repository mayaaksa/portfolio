#ifndef UTILITY_H
#define UTILITY_H

#include "App.h"

int findByNPM(string key);

int sequentialSearch(string key);
int binarySearch(string key);

void quickSort(int low, int high);
int partition(int low, int high);

void mergeSort(int l, int r);
void merge(int l, int m, int r);

void shellSort();

int hitungData(int n);
int hitungHuruf(int i, int j);
int hitungVokal(int i, int j);

bool isVokal(char c);

#endif