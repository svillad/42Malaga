#!/usr/bin/expect -f
# Uso:
#   ./connect.exp  [nick] [user] [host] [port]

set nick  [lindex $argv 0];  if {$nick  == ""} { set nick "svillad" }
set user  [lindex $argv 1];  if {$user  == ""} { set user "sebas" }
set host  [lindex $argv 2];  if {$host  == ""} { set host "127.0.0.1" }
set port  [lindex $argv 3];  if {$port  == ""} { set port "6667" }

set timeout 5

puts "Conectando a $host:$port como $nick/$user …"
spawn nc $host $port

expect "NICK"
send "NICK $nick\r"

expect "USER"
send "USER $user 0 * :$user\r"

interact