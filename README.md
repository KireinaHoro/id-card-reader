# Id-card-reader

The reader is split into two parts: a scanner (the device with NFC reader) and a controller (that sends scan commands to the scanner).  The two roles communicate over the Nanomsg protocol.

## Dependencies

 - common dependency:
   - `nanomsg`
   - `nanomsgxx`
 - scanner:
   - `libnfc`
