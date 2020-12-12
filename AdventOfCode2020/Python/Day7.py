#!/usr/bin/python3
import Day1 as Auth
import sys
import re
import json

##############################################################################
# CONSTANTS
##############################################################################
INPUT_URL = "https://adventofcode.com/2020/day/7/input"

##############################################################################
# FUNCTION
##############################################################################
def makeIn2OutGraph(ruleLst):
  graph = {}
  for rule in ruleLst:
    colorLst = re.split(" bags?(?:(?:[^0-9]+[0-9]+,? ?)|\.)", rule)
    del colorLst[-1] #match always go to end of string, causing empty match
    outColor = colorLst[0]
    
    #Loop thru inside colors
    for idx in range(1, len(colorLst)):
      inColor = colorLst[idx]
      graph.setdefault(inColor, []).append(outColor)
  return graph

def makeOut2InGraph(ruleLst):
  graph = {}
  for rule in ruleLst:
    colorLst = re.split(" bags?[^0-9]+", rule)
    del colorLst[-1] #match always go to end of string, causing empty match
    outColor = colorLst[0]
    
    #Loop thru inside colors
    for idx in range(1, len(colorLst)):
      inColor = colorLst[idx]
      graph.setdefault(outColor, []).append(inColor)
  return graph

def colorsContain(inColor, in2OutGraph):
  outColors = set()
  for outColor in in2OutGraph.get(inColor,[]):
    outColors.add(outColor)
    outColors.update(colorsContain(outColor, in2OutGraph))
  
  return outColors

def containsBags(outColor, out2InGraph):
  count = 0
  for inColor in out2InGraph.get(outColor, []):
    num, inColor = inColor.split(" ",1)
    count += int(num)
    count += (int(num) * containsBags(inColor, out2InGraph))
    
  return count

##############################################################################
# MAIN
##############################################################################
if __name__ == "__main__":
  Auth.login()
  inputResponse = Auth.loginSession.get(INPUT_URL)
  ruleLst = inputResponse.text.splitlines()
  
  in2OutGraph = makeIn2OutGraph(ruleLst)
  print(len(colorsContain("shiny gold", in2OutGraph)))
  
  out2InGraph = makeOut2InGraph(ruleLst)
  print(json.dumps(out2InGraph, indent=2))
  print(containsBags("shiny gold", out2InGraph))