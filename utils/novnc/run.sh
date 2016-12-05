#!/bin/bash

echo VNC client running at https://$C9_HOSTNAME/vnc.html
echo

supervisord -c utils/novnc/supervisord.conf