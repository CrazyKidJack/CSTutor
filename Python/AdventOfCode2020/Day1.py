#!/usr/bin/python3
import requests
import sys
import getpass
import re

##############################################################################
# CONSTANTS
##############################################################################
INIT_LOGIN_URL = "https://adventofcode.com/auth/github"
GITHUB_LOGIN_URL = "https://github.com/session"
REPORT_URL = "https://adventofcode.com/2020/day/1/input"

##############################################################################
# FUNCTIONS
##############################################################################
def getCreds():
  gitHubUser=input("GitHub Username: ")
  try:
    gitHubPass = getpass.getpass("GitHub Password: ")
  except Exception as error:
    print('ERROR', error)
    sys.exit()
  return gitHubUser, gitHubPass
  
def getTokens(loginSession):
  loginInitResponse = loginSession.get(INIT_LOGIN_URL)

  authenticity_tokenLst = re.findall('name="authenticity_token" value="([^"]*)"', loginInitResponse.text)
  if len(authenticity_tokenLst) != 1:
    print(failure)
    sys.exit()
  auth_token = authenticity_tokenLst[0]

  returnToLst = re.findall('name="return_to" id="return_to" value="([^"]*)"', loginInitResponse.text)
  if len(authenticity_tokenLst) != 1:
    print(failure)
    sys.exit()
  returnTo = returnToLst[0]
    
  return auth_token, returnTo

def findPart1Answer(lineLst):
  for i in range(len(lineLst)-1):
    need = 2020 - int(lineLst[i])
    for j in range(i+1, len(lineLst)):
      if int(lineLst[j]) == need:
        print("i= "+lineLst[i]+" j= "+lineLst[j])
        return int(lineLst[i])*int(lineLst[j])
  else:
    print("No matches...")
    sys.exit()
    
def findPart2Answer(lineLst):
  for i in range(len(lineLst)-2):
    need = 2020 - int(lineLst[i])
    for j in range(i+1, len(lineLst)-1):
      if int(lineLst[j]) >= need:
        continue
      need2 = need - int(lineLst[j])
      for k in range(j+1, len(lineLst)):
        if int(lineLst[k]) == need2:
          print("i= "+lineLst[i]+" j= "+lineLst[j]+" k= "+lineLst[k])
          return int(lineLst[i])*int(lineLst[j])*int(lineLst[k])
  else:
    print("No matches...")
    sys.exit()

##############################################################################
# MAIN
##############################################################################
loginSession = requests.Session()

auth_token, returnTo = getTokens(loginSession)
gitHubUser, gitHubPass = getCreds()

gitHubLoginPayload = {
  "authenticity_token": auth_token,
  "login": gitHubUser,
  "password": gitHubPass,
  "return_to": returnTo,
}
gitHubLoginResponse = loginSession.post(GITHUB_LOGIN_URL, data=gitHubLoginPayload)

reportResponse = loginSession.get(REPORT_URL)

lineLst = reportResponse.text.splitlines()
print("part1 solution: "+str(findPart1Answer(lineLst)))

print("part2 solution: "+str(findPart2Answer(lineLst)))