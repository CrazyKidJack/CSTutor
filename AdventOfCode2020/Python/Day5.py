import Day1 as Auth
import sys

##############################################################################
# CONSTANTS & GLOBALS
##############################################################################
INPUT_URL = "https://adventofcode.com/2020/day/5/input"
MAX_SEAT_ID = 1023
MIN_SEAT_ID = 0

##############################################################################
# FUNCTIONS
##############################################################################
def seat2Binary(seat):
  count = 0
  for ch in seat:
    if ch == "B" or ch == "R":
      count = count * 2 + 1
    else:
      count *= 2
  return count

##############################################################################
# MAIN
##############################################################################
if __name__ == "__main__":
  Auth.login()
  inputResponse = Auth.loginSession.get(INPUT_URL)
  seatLst = inputResponse.text.splitlines()
  
  maxNum = MIN_SEAT_ID
  minNum = MAX_SEAT_ID
  for seat in seatLst:
    newNum = seat2Binary(seat)
    if maxNum < newNum:
      maxNum = newNum
    if minNum > newNum:
      minNum = newNum
  
  print("min seat id= "+str(minNum))
  print("max seat id= "+str(maxNum))
  possibleSeatLst = list(range(minNum, maxNum+1))
  for seat in seatLst:
    newNum = seat2Binary(seat)
    possibleSeatLst.remove(newNum)
  
  if len(possibleSeatLst) == 1 or len(possibleSeatLst) == 2:
    print("Your seat is: "+str(possibleSeatLst[0]))
    if len(possibleSeatLst) == 2:
      print("Your seat is: "+str(possibleSeatLst[1]))
  else:
    for idx in range(1, len(possibleSeatLst)-1):
      if possibleSeatLst[idx-1] != possibleSeatLst[idx]-1 and possibleSeatLst[idx+1] != possibleSeatLst[idx]+1:
        print("Your seat is: "+str(possibleSeatLst[idx]))