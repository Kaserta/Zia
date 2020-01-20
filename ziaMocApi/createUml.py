#!/bin/env python3

import shutil
import subprocess

def assembleHeaders(path, tab):
    head = ""
    for t in tab:
        head = head + " -i " + path + t
    return head

gen = shutil.which("hpp2plantuml") #checking if command exist


if gen is None:
    subprocess.run(["pip3", "install", "--user", "hpp2plantuml"]) #installing command if does not exist

sharedHeadersPath = "./"
sharedHeaders = ["api.hpp", "IModule.hpp"]

sharedTotal = assembleHeaders(sharedHeadersPath, sharedHeaders)

#server gen
subprocess.run(["hpp2plantuml " + sharedTotal[1:] + " -o " + "./UML/sharedHeaders.puml"], shell=True)

