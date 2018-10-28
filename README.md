# SerialLink
Serial transfer library for Teensy 3.x and LC. Includes automatic response messages to confirm receipt and blocking / nonblocking / timeout functionality.

# Description
This library is meant to enable easily sending data between multiple Teensy devices using serial. Why use SerialLink instead of Serial? Because SerialLink automatically sends an Ack or Nack message on receipt. Sending options include a blocking send to wait on receiving an Ack, a blocking send with timeout, and a non-blocking send.

CRC-16 is used for the CRC check using the Teensy hardware for fast computation (https://github.com/FrankBoesing/FastCRC).

Callback functions are used instead of polling for receipt of a new message.

In the future, I plan to add request and response functionality similar to Wire's requestFrom and onRequest to implement bi-directional requests for data in addition to sending unsolicited data.

Currently, this library is limited to Teensy devices using Serial1, Serial2, or Serial3.

# Function Description
## Object Declaration
Objects are already declared for you. Serial1Link is the object corresponding to using SerialLink over Serial1, Serial2Link for Serial2 and Serial3Link for Serial3.
## Setup Functions
**begin(unsigned int baud)** Begin bus communication at the requested baud rate.
**onReceive(function)** Callback function for handling received messages. The callback function should return a void and take an unsigned int as the only parameter, which provides the received packet size.
## Sending Functions
**beginTransmission** Initializes a message to be sent.
**write(unsigned char)** Writes a signle char to the transmit buffer.
**write(unsigned char *, unsigned int len)** Writes a buffer to the transmit buffer, a pointer to the buffer should be given as well as the buffer length.
**endTransmission()** Blocking method, sends the message and waits for an Ack response. Automatically resends the message until an Ack is received.
**endTransmission(unsigned int timeout)** Blocking method, sends the message and waits for an Ack response. Times out after *timeout* microseconds if an Ack is not received. Automatically resends the message until an Ack is received or a timeout occurs.
**sendTransmission()** Non blocking method, simply sends the message.
**getTransmissionStatus()** checks the Ack status if using *sendTransmission()*. Returns true if an Ack response has been received.
## Reading Functions
**available()** Returns the number of bytes available to read in the receive buffer.
**read()** Reads a single byte from the receive buffer.
**read(unsigned char *,unsigned int len)** Reads len bytes from the buffer placing the data in the buffer pointed to.
