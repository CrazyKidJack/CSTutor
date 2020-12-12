#!/usr/bin/python3
import Day1 as Auth
import sys
import string

##############################################################################
# CONSTANTS
##############################################################################
INPUT_URL = "https://adventofcode.com/2020/day/6/input"

##############################################################################
# FUNCTIONS
##############################################################################


##############################################################################
# MAIN
##############################################################################
if __name__ == "__main__":
  Auth.login()
  inputResponse = Auth.loginSession.get(INPUT_URL)
  groupLst = inputResponse.text.split("\n\n")
  
  total = 0
  for group in groupLst:
    ansSet = set()
    for ans in group:
      if ans == "\n": continue
      ansSet.add(ans)
    total += len(ansSet)
    
  print("total = " + str(total))
  
  total = 0
  for group in groupLst:
    prevAnsSet = set(string.ascii_lowercase)
    personLst = group.splitlines()
    for person in personLst:
      ansSet = set()
      for ans in person:
        ansSet.add(ans)
      prevAnsSet.intersection_update(ansSet)
    total += len(prevAnsSet)
    
  print("total = " + str(total))
        