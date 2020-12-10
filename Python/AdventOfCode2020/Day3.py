#!/usr/bin/python3
import Day1 as Auth

##############################################################################
# CONSTANTS
##############################################################################
INPUT_URL = "https://adventofcode.com/2020/day/3/input"

##############################################################################
# FUNCTIONS
##############################################################################
def countTrees(lineLst, slope):
  lineLen = len(lineLst[0])
  row = 0
  col = 0
  numTrees = 0

  while row < (len(lineLst)-1):
    col = (col+slope[0])%lineLen
    row += slope[1]
    if lineLst[row][col] == "#":
      numTrees += 1
  
  return numTrees

##############################################################################
# MAIN
##############################################################################
if __name__ == "__main__":
  Auth.login()
  inputResponse = Auth.loginSession.get(INPUT_URL)
  
  lineLst = inputResponse.text.splitlines()
  slopeLst = [(1,1),(3,1),(5,1),(7,1),(1,2)]
  
  answer2 = 1
  for slope in slopeLst:
    answer2 *= countTrees(lineLst, slope)
  
  answer = countTrees(lineLst, (3,1))
  print("Answer: "+str(answer))
  print("Answer2: "+str(answer2))