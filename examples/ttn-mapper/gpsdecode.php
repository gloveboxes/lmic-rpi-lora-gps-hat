<?php
// Unpack into 6 bytes
$data = unpack('C*',pack('H*', str_replace(' ','','F7 2A 05 6A 0D 17 00 AA')));
print_r($data);
echo "\n";
// Combine each 3 bytes into a 24bit int
$lat = ($data[1] + ($data[2] << 8) + ($data[3] << 16)) / -10000;
$lon = ($data[4] + ($data[5] << 8) + ($data[6] << 16)) / 10000;
$alt = $data[7];
$tdop = $data[8] / 100;
var_dump( $lat, $lon,$alt,$tdop );
