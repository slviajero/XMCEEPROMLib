# XMCEEPROMLib

This is a poor man's implementation of an EEPROM dummy library for XMC1 boards. These boards have no build in EEPROM but the flash memory can be written from the program code using the xmc_flash API. On this flash memory a EEPROM emulation can be implemented. 

This version is much simpler than the Infineon example code for an EEPROM emulation. It has a lower level of flash protection as it was mainly meant for the Iot BASIC interpreter https://github.com/slviajero/tinybasic. Still, the library can be useful for small use cases.

Flash geometry and implications for the EEPROM emulation:

A XMC1 flash has 16 byte blocks. 16 blocks form one page of 256 bytes. Erasing and writing is done on page level. Only an entire page can be erased. Reading is done on block level. 

This suggests a separate buffering strategy for reading and writing. 
 
There is one pagebuffer for an entire page. It takes all the writes to the page and keeps it until a pagefault occurs, i.e. writes go beyond the page. It then flushes to the flash, erasing and updateing it and reads the requested page. Alternatively the page erase can be done with a the commit() function. Only changed pages are erased and written.
 
There is one blockbuffer for reading. If the read is outside the page loaded for write, the blockbuffer is read. All read requests go through the blockbuffer. If the read is inside the page loaded for write, satisfy the read request are satifsfied from there. 

Currently there is no check if pages need to be erased. There is also no copy and garbage collect mechanism like in the professional solution. For the use cases of this library, this is not needed.

Please take notice that this is a hobbyists work with no professional interest. All the code comes with no warranty as stated in the library file.



