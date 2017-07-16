echo 'Starts training'

while true;
do
  if [[ $(pgrep python3) -eq 0 ]]; then
    echo 'Training is not detected, start it.'
    nohup mj-server >/dev/null 2>&1 &
    sleep 1
    nohup python3 main.py >mct_output 2>&1 &
    sleep 1
    nohup mj-player >/dev/null 2>&1 &
    sleep 1
    nohup mj-player >/dev/null 2>&1 &
    sleep 1
    nohup mj-player >/dev/null 2>&1 &
    echo 'Training starts.'
  else
    echo 'Training is running.'
  fi
  sleep 5
done
