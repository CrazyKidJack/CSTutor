#!/usr/bin/python3
import Day1 as Auth
import re

##############################################################################
# CONSTANTS
##############################################################################
INPUT_URL = "https://adventofcode.com/2020/day/2/input"

##############################################################################
# FUNCTIONS
##############################################################################
def parseLine(line):
  re.findall("([0-9]+)-([0-9]+) ([a-zA-Z]): ([a-zA-Z]+)", line)
    
  return password, letter, min, max
  
def passwordValid(min, max, letter, password):
  count = 0
  for l in password:
    if l == letter:
      count += 1
      
  if count >= int(min) and count <= int(max):
    return True
  return False

def passwordValid2(pos1, pos2, letter, password):
  if password[int(pos1) - 1] == letter:
    if password[int(pos2) -1] == letter: return False
    
    return True
  elif password[int(pos2) -1] == letter: return True
  
  return False

##############################################################################
# MAIN
##############################################################################
if __name__ == "__main__":
  Auth.login()
  inputResponse = Auth.loginSession.get(INPUT_URL)
  inputLst = re.findall("([0-9]+)-([0-9]+) ([a-zA-Z]): ([a-zA-Z]+)", inputResponse.text)
  print("Num inputs: "+str(len(inputLst)))
  
  numValid = 0
  for idx in range(len(inputLst)):
    if passwordValid(*(inputLst[idx])):
      numValid += 1
  print("Num Valid: "+str(numValid))
  
  numValid = 0
  for idx in range(len(inputLst)):
    if passwordValid2(*(inputLst[idx])):
      numValid += 1
  print("Num Valid2: "+str(numValid))
  