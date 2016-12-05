#!/bin/bash

command_exists () {
    type "$1" &> /dev/null ;
}

if command_exists supervisor ; 
then
    echo INSTALLED    
else
  sudo apt-get install supervisor xvfb fluxbox x11vnc
  git clone git://github.com/kanaka/noVNC
fi

