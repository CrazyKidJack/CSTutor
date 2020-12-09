#!/bin/bash
now=$(date +%Y%m%d_%H%M%S)
exeName="$0.$$.$now.exe"
tail -n +10 "$0" | g++ -x c++ -o "$exeName" -
./"$exeName"
rtnCode=$?
rm ./"$exeName"
exit $rtnCode

#include <iostream>
using namespace std;

int main(){
  cout << "it worked!" << endl;

  return 0;
}
