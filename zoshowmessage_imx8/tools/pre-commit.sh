#!/bin/sh

qmake CONFIG+=debug CONFIG+=precommit && make qmake_all
git add versioncontrol.h
