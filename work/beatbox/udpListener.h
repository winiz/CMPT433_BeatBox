// updListener.h
// Listen to a UDP port and accept commands.
//
// Commands:
//   help
//   count
//   get 5
//   first 30
//   last 15
//   stop
//
// Usage:
//   netcat -u 192.168.0.121 12345
//   Then just type commands and press enter.

#ifndef _UDP_LISTENER_H_
#define _UDP_LISTENER_H_

// Start listening to the UDP port on a separate thread.
void UdpListener_startListening(void);

void UdpListener_cleanup(void);

#endif
