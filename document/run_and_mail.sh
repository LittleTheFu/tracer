#!/bin/bash

./ray_tracer

if [ $? -eq 0 ]; then
    SUBJECT="Ray Tracer Completed"
    BODY="The ray_tracer program has completed successfully."
else
    SUBJECT="Ray Tracer Failed"
    BODY="The ray_tracer program has failed. Please check the logs."
fi

# 发送电子邮件
echo "$BODY" | mail -s "$SUBJECT" xxx@live.com
