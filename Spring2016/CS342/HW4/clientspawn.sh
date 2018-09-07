#!/bin/bash 
COUNTER=0
while [  $COUNTER -lt 5 ]; do
  java ChatClient &
  let COUNTER=COUNTER+1 
done
