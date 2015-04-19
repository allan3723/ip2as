The program basically takes in two files in the format:

ip2as.out DB_091803.txt IP.list

and will output the following:

Link Interface(#.#.#.#/#) AS IP(That was searched for).

My program basically reads in the the IP that you need to find, reads each link as it goes down the database of the link interface and tries to match the IP address with the link interface starting with the first 8 bits of the IP address, then the next 8, or the longest prefix if it's not the entire 8 bits. It will stop searching once it match a interface. After that, it will go to nextSearch and go down the DB through all the links with the same first 8 bits in their IP and try to find a longer prefix that will match with the IP.

(Program does not have any error checking so it will not work if the IP is not valid).