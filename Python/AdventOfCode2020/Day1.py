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
print(reportResponse.text)
