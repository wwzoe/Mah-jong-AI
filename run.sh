#!/usr/bin/env bash
gnome-terminal -x sh -c "mj-server; bash"
sleep 1
gnome-terminal -x sh -c "python3 main.py; bash"
sleep 1
nohup mj-player >/dev/null 2>&1 &
sleep 1
nohup mj-player >/dev/null 2>&1 &
sleep 1
nohup mj-player >/dev/null 2>&1 &
sleep 1
