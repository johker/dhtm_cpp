# dhtm_core

Distributed Hierarchical Temporal Memory 

* Communication via SDRs (content) and simple command codes (control)
* No error correction for SDR due to its noise tolerance

Message format
* *ID*: uint16 - message ID 
* *Command*: uint16 - enum that describes the general purpose of the message.
* *Key*: uint32 - Specifies the payload - either the type of the SDR (e.g. level, encoding)  
* *Size*: uint16 - log2 of the payload size 
* *Payload*: Depends on the message type: Can be a parameter value (float) or a SDR (bit array)

Command and Key are sent two times as a simple error correction measure.

<!-- language: lang-none -->
--------------------------------------------------------------------------------------------------
||                            Header                              ||            Body            ||
--------------------------------------------------------------------------------------------------
||      ID	|     Command   |       Key      |       Size     ||           Payload          ||
--------------------------------------------------------------------------------------------------
||     0-1      |       2-5     |       6-11     |      12-13     ||           14 - n           ||
--------------------------------------------------------------------------------------------------

