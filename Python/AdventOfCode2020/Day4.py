#!/usr/bin/python3
import Day1 as Auth
import sys
import re

##############################################################################
# CONSTANTS
##############################################################################
INPUT_URL = "https://adventofcode.com/2020/day/4/input"

##############################################################################
# FUNCTIONS
##############################################################################
def pairValid(pairStr):
  key, val = pairStr.split(":")
  
  if key == "byr":
    val = int(val)
    if val >= 1920 and val <= 2002: return True
  elif key == "hcl":
    if re.fullmatch("#[0-9a-f]{6}", val) is not None: return True
  elif key == "ecl":
    if re.fullmatch("(amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth)", val) is not None:
      return True
  elif key == "cid":
    return True
  elif key == "eyr":
    val = int(val)
    if val >= 2020 and val <= 2030: return True
  elif key == "pid":
    if re.fullmatch("[0-9]{9}", val) is not None: return True
  elif key == "iyr":
    val = int(val)
    if val >= 2010 and val <= 2020: return True
  elif key == "hgt":
    matchHgtLst = re.fullmatch("([0-9]+)cm", val)
    if matchHgtLst is not None:
      if int(matchHgtLst[1]) >= 150 and int(matchHgtLst[1]) <= 193:
        return True
    matchHgtLst = re.fullmatch("([0-9]+)in", val)
    if matchHgtLst is not None:
      if int(matchHgtLst[1]) >= 59 and int(matchHgtLst[1]) <= 76:
        return True
  
  return False


##############################################################################
# MAIN
##############################################################################
if __name__ == "__main__":
  Auth.login()
  inputResponse = Auth.loginSession.get(INPUT_URL)
  passportLst = inputResponse.text.split("\n\n")
  
  numFields = 0
  foundCid = False
  numValid = 0
  
  for passport in passportLst:
    passport = passport.rstrip().replace("\n", " ")
    for pair in passport.split(" "):
      if pairValid(pair): numFields += 1 ## for part 2
      #numFields += 1 ##for part 1
      if pair.startswith("cid"): foundCid = True
    if numFields == 8:
      numValid += 1
    if numFields == 7 and foundCid == False:
      numValid += 1
    numFields = 0
    foundCid = False

  print("Num valid= "+str(numValid))
  