{\rtf1\ansi\ansicpg1252\cocoartf1348\cocoasubrtf170
{\fonttbl\f0\fmodern\fcharset0 CourierNewPSMT;\f1\fswiss\fcharset0 ArialMT;}
{\colortbl;\red255\green255\blue255;\red67\green67\blue67;}
\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\deftab720
\pard\pardeftab720\sl364

\f0\fs26 \cf2 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 pin = 1
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 led = 0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 min_pw_ms = 20
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 upload_rate_ms = 60000
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \
pulse_detected = 0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 timestamp = 0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 counter = 0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 conn = nil
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \
gpio.mode(led, gpio.OUTPUT)
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 gpio.mode(pin, gpio.INT)
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \
gpio.write(led, gpio.LOW)
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \
if not wifi.sta.getip() then
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  print("Connecting to wifi")
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  wifi.setmode(wifi.STATION)
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \'a0 \'a0 wifi.sta.config("net_name","net_pwd")
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  ip = wifi.sta.getip()
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  print(ip)
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 end
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \
function upload()\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  conn = net.createConnection(net.TCP, 0)\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  conn:on("receive",\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0   function(conn, payload)\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    success = true
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    print(payload)
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0   end)  
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  conn:on("disconnection",\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0   function(conn, payload)
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    print('\\nDisconnected')
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0   end)
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  conn:on("connection",\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0   function(conn, payload)\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    print('\\nConnected')\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    conn:send("GET/ logdata.php?"
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    .."timestamp="..timestamp
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    .."&key=your-key"
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    .."&counter="..counter
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    .." HTTP/1.1\\r\\n"\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    .."Host: your_host.com\\r\\n"\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    .."Connection: keep-alive\\r\\n"
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    .."Accept: */*\\r\\n"\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    .."User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)\\r\\n"\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0    .."\\r\\n")
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0   end)  
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  print("Opening port")
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  conn:connect(80,'your_host.com')\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 end
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \
function pin1up(level)
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  pulse_detected = 1
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 end
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \
function maintask()
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \'a0 \'a0 \'a0 \'a0 print("Counter is:"..counter)
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \'a0 \'a0 \'a0 \'a0 if not wifi.sta.getip() then
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \'a0 \'a0 \'a0 \'a0 \'a0 \'a0 print("Connecting to AP, Waiting...")\'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \'a0 \'a0 \'a0 \'a0 else \'a0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \'a0 \'a0 \'a0 \'a0 \'a0 \'a0 gpio.write(0, gpio.HIGH)
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \'a0 \'a0 \'a0 \'a0 \'a0 \'a0 print("Uploading to server...")
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \'a0 \'a0 \'a0 \'a0 \'a0 \'a0 upload()
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \'a0 \'a0 \'a0 \'a0end
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 end
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \
function pulsetask()
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  timestamp = timestamp + 1
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  if pulse_detected == 1 then
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0   counter = counter + 1
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0   pulse_detected = 0
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0  end
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 end
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \
gpio.trig(pin, "up", pin1up)
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 tmr.alarm(0, upload_rate_ms, 1, maintask);
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 tmr.alarm(1, min_pw_ms, \'a0 \'a0 \'a01, pulsetask);
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \

\f0 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \
maintask();}