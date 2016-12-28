#!/bin/env python2

# slackware包制作工具

import sys
import commands

pkgBaseName = sys.argv[1]

sysVersion = "14.2"
sysPlatform = "x86_64"
pkgSufix = "tgz"
baseDirName = "/home/lsw"

pkgName = pkgBaseName + "_" + sysVersion + "_" + sysPlatform + "." + pkgSufix

buildDir = baseDirName + "/build_for_makepkg/" + pkgBaseName

cmdList = [
        "./configure --prefix=/usr/local",
        "rm -rf " + buildDir,
        "make install DESTDIR=" + buildDir,
        "cd " + buildDir,
        "makepkg -l y -c n ../" + pkgName,
        "cp ../" + pkgName + " " + baseDirName
        ] 

for val in cmdList : 
    print val
    commands.getoutput(val)
