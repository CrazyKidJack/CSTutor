#!/bin/bash
tail "$0" -n +7 | g++ -x c++ -o "$0.$$.out" -
$0.$$.out "$0" "$@"
STATUS=$?
rm $0.$$.out
exit $STATUS
#include <iostream>
using namespace std;

int main(){
  cout << "it worked!" << endl;

  return 0;
}

